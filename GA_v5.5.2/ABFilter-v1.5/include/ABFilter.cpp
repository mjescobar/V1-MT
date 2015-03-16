/* ***********************************************************************

Copyright or © or Copr. INRIA, France
contributor(s) : Maria-Jose Escobar, Adrien Wohrer (January 2011)

email: Maria-Jose.Escobar@inria.fr

This software is a computer program whose purpose is to help the 
implementation of spatiotemporal filtering in video sequences. 
Specifically, this library implements the physiological plausible 
filters proposed by Adelson and Bergen (1985).

This software is governed by the CeCILL-C license under French law and
abiding by the rules of distribution of free software.  You can  use, 
modify and/ or redistribute the software under the terms of the CeCILL-C
license as circulated by CEA, CNRS and INRIA at the following URL
"http://www.cecill.info". 

As a counterpart to the access to the source code and  rights to copy,
modify and redistribute granted by the license, users are provided only
with a limited warranty  and the software's author,  the holder of the
economic rights,  and the successive licensors  have only  limited
liability. 

In this respect, the user's attention is drawn to the risks associated
with loading,  using,  modifying and/or developing or reproducing the
software by the user in light of its specific status of free software,
that may mean  that it is complicated to manipulate,  and  that  also
therefore means  that it is reserved for developers  and  experienced
professionals having in-depth computer knowledge. Users are therefore
encouraged to load and test the software's suitability as regards their
requirements in conditions enabling the security of their systems and/or 
data to be ensured and,  more generally, to use and operate it in the 
same conditions as regards security. 

The fact that you are presently reading this means that you have had
knowledge of the CeCILL-C license and that you accept its terms.

*********************************************************************** */

#include "ABFilter.h"

ABFilter::ABFilter()
{
	spatFilterList.clear();
	spatFilterIndex = 0;
	fGroup = NULL;
	nGroups = 0;
	ampFactor = 1;
    staticFilter = false;
}

ABFilter::~ABFilter(void){}

void ABFilter::set_nGroups(int nG)
{
    nGroups = nG;

    if (fGroup)
	delete []fGroup;
    fGroup = new FilterGroup[nG];
}

void ABFilter::set_step(double stepp)
{
	step=stepp;
}

void ABFilter::addFilterToGroup(Cell flt, double w, int group, int spatFltId)
{
	FilterInfo fltTmp;

	fltTmp.filter = flt;
	fltTmp.weight = w;
	fltTmp.spatFilterPtr = NULL;
	if( spatFltId != -1)
	{
		SpatialFilterList::iterator itt = spatFilterList.find(spatFltId);

		if ( itt != spatFilterList.end() )
		{
			fltTmp.spatFilterPtr = &((*itt).second); 
		}
	}
	fGroup[group].push_back(fltTmp);
}


void ABFilter::setValue(double val)
{
	davalue = val;  
}

double ABFilter::getValue()
{
	return davalue;
}

void ABFilter::set_spatialOrient(double orient)
{
	double orRad = orient*M_PI/180;

    orientation = orRad;
}

void ABFilter::set_spatialFrequency(double sFreq)
{
	double freq, xi;

    xi = 2*M_PI*sFreq;
	if (xi >= XI_MIN && xi <=  XI_CUT) 
		freq = 0.2662*xi + 0.00082521;
	else 
		if (xi > XI_CUT && xi < XI_MAX) 
			freq = 0.5*xi - 0.39; 
		else
		{	
			printf("\nERROR:: Spatial frequency selectivity out of range, (%lf)\n"
				" please set a value in the range [%04lf,%04lf] cycles/pixel\n", sFreq, XI_MIN/(2*M_PI), XI_MAX/(2*M_PI));
			exit(0);
		}

	//spatialFrequency = freq;
	spatialFrequency = sFreq;
}

void ABFilter::set_temporalFrequency(double tFreq)
{
    double tau, omega;

    if( tFreq == 0 )
    {
        staticFilter = true;
        tauFilter = 0.4556*pow(2*M_PI,-1.0009);
    }
    else
    {
        omega = 2*M_PI*tFreq; 
        if (omega >= W_MIN && omega <= W_MAX) 
            tau = 0.4556*pow(omega,-1.0009);
        else 
        {
            printf("\nERROR:: Temporal frequency selectivity out of range, (%lf)\n"
                    " please set a value in the range [%04lf,%04lf] cycles/sec\n", tFreq, W_MIN/(2*M_PI), W_MAX/(2*M_PI));
            exit(0);
        }
        tauFilter = tau;
    }	
}


int ABFilter::addSpatFilterToList( CImg<double> *inFilt)
{
	SpatFilterInfo fltInfo;
	fltInfo.filter = *inFilt;
	fltInfo.id = spatFilterIndex;
	spatFilterList.insert( make_pair(spatFilterIndex, fltInfo) );

	spatFilterIndex ++;

	return fltInfo.id; 
}

void ABFilter::buildSpatialFilter()
{
	double sigma, spatialPeriod;
//    double xi;

    // The spatial part corresponds to 1st or 2nd derivative of Gaussian functions,
    // depending on the value inserted in spatFilterDegree.
    //
    // According to biological facts and Watson&Ahumada recommendation, there is a relationship
    // between sigma and the spatialFrequencyuency of the filter.
    // The value for sigma follows:
    //
    //          sigma = 1.324 * T / 6 = 1.324 / (6*f)
    //
    //	where f (or T) corresponds to the sine/cosine spatialFrequencyuency, which increases together with
    // the derivative order. Doing 'numerical' approximation we get that 
    //	
    //		xi = 0.0383 + 3.0741*sqrt( 0.6505*f - 0.0016 ); // not used by now
    //
    //		f_1st_derivative = 3 * f_kernel / 2; 
    //		f_2nd_derivative = 2 * f_kernel;

	double radRF;
	char filename [FSIZE];
	CImg<double> fltTmp;
	spatialPeriod = 1 / spatialFrequency; 
	radRF =  1.5 * 0.5622 * spatialPeriod ;
	radRF = floor(radRF * 100)/100;

	// Create new set of spatial part for filters
	sigma = 0.5622*spatialPeriod; // Good value

	oddSpat = build_GaborFirst(sigma, orientation + M_PI, 1/spatialPeriod, 0); 
	strcpy(filename, "");
	sprintf(filename, "oddSpat.jpg");
	if( orientation == 0 )
    {
        fltTmp = oddSpat;
        fltTmp.normalize(0,255);
        fltTmp.save(filename);
    }

	evenSpat = build_GaborSecond(sigma, orientation + M_PI, 1/spatialPeriod, 0); 
	strcpy(filename, "");
	sprintf(filename, "evenSpat.jpg");
	if( orientation == 0 )
    {
        fltTmp = evenSpat;
        fltTmp.normalize(0,255);
        fltTmp.save(filename);
    }
#ifdef FFT_FILTERING
	// Getting the FFT transforms
	fftOddSpat = fft.getFFTtransform( filter.oddSpat, desFilterSizeX, desFilterSizeY );
	fftEvenSpat = fft.getFFTtransform( filter.evenSpat, desFilterSizeX, desFilterSizeY );
#endif // FFT_FILTERING

}

void ABFilter::filter_build()
{
    ABFilter::buildSpatialFilter();
    //printf("step = %lf\n",step);
    //printf("tauFilter = %lf\n",tauFilter);
    //printf("spatialFrequency = %lf\n",spatialFrequency);
    //printf("orientation = %lf\n",orientation);
    // ===================================================
    //      Case Adelson & Bergen filters
    // ===================================================
#ifdef OPPOSITE_ENERGY
    set_nGroups(4);
#else // OPPOSITE_ENERGY
    set_nGroups(2);
#endif // OPPOSITE_ENERGY

    // These are our 4 filters that will be loaded into the V1GroupCell object 
    Cell oddSpat_slowTime(step);
    Cell oddSpat_fastTime(step);
    Cell evenSpat_slowTime(step);
    Cell evenSpat_fastTime(step);

    // Temporal filters used for temporal calculation
    RecFilter posFilt1(step);
    posFilt1.warningVerbose = false;
    posFilt1.ExpCascade_nonRec( 2*tauFilter, 2 );
    oddSpat_fastTime -= posFilt1;
    posFilt1.ExpCascade_nonRec( 3*tauFilter, 3 );
    oddSpat_fastTime.Cascade( posFilt1 );
    oddSpat_fastTime.set_step(step);
    oddSpat_fastTime.set_orientation(orientation);
    oddSpat_fastTime.set_spatialPhase(0);
    oddSpat_fastTime.set_spatialPeriod(1/spatialFrequency);
    oddSpat_fastTime.set_spatialFilterDegree(1);

    // Temporal filters used for temporal calculation
    RecFilter posFilt2(step);
    posFilt2.warningVerbose = false;
    posFilt2.ExpCascade_nonRec( 2*tauFilter, 2 );
    oddSpat_slowTime -= posFilt2;
    posFilt2.ExpCascade_nonRec( 5*tauFilter, 5 );
    oddSpat_slowTime.Cascade( posFilt2 );
    oddSpat_slowTime.set_step(step);
    oddSpat_slowTime.set_orientation(orientation);
    oddSpat_slowTime.set_spatialPhase(0);
    oddSpat_slowTime.set_spatialPeriod(1/spatialFrequency);
    oddSpat_slowTime.set_spatialFilterDegree(1);


    // Temporal filters used for temporal calculation
    RecFilter posFilt3(step);
    posFilt3.warningVerbose = false;
    posFilt3.ExpCascade_nonRec( 2*tauFilter, 2 );
    evenSpat_fastTime -= posFilt3;
    posFilt3.ExpCascade_nonRec( 3*tauFilter, 3 );
    evenSpat_fastTime.Cascade( posFilt3 );
    evenSpat_fastTime.set_step(step);
    evenSpat_fastTime.set_orientation(orientation);
    evenSpat_fastTime.set_spatialPhase(0);
    evenSpat_fastTime.set_spatialPeriod(1/spatialFrequency);
    evenSpat_fastTime.set_spatialFilterDegree(2);

    // Temporal filters used for temporal calculation
    RecFilter posFilt4(step);
    posFilt4.warningVerbose = false;
    posFilt4.ExpCascade_nonRec( 2*tauFilter, 2 );
    evenSpat_slowTime -= posFilt4;
    posFilt4.ExpCascade_nonRec( 5*tauFilter, 5 );
    evenSpat_slowTime.Cascade( posFilt4 );
    evenSpat_slowTime.set_step(step);
    evenSpat_slowTime.set_orientation(orientation);
    evenSpat_slowTime.set_spatialPhase(0);
    evenSpat_slowTime.set_spatialPeriod(1/spatialFrequency);
    evenSpat_slowTime.set_spatialFilterDegree(2);

    // Setting the pointers to the spatial filter

    oddSpat_fastTime.set_spatialFilter( &oddSpat );
    oddSpat_slowTime.set_spatialFilter( &oddSpat );
    evenSpat_fastTime.set_spatialFilter( &evenSpat);
    evenSpat_slowTime.set_spatialFilter( &evenSpat);
#ifdef FFT_FILTERING
    oddSpat_fastTime.set_convResult( &oddConvResult);
    oddSpat_slowTime.set_convResult( &oddConvResult);
    evenSpat_fastTime.set_convResult( &evenConvResult);
    evenSpat_slowTime.set_convResult( &evenConvResult);
#endif // FFT_FILTERING

#ifdef FFT_FILTERING
    int filt1 = units[unit_index].addSpatFilterToList( (*it).second.oddSpat, &(*it).second.oddConvResult );
    int filt2 = units[unit_index].addSpatFilterToList( (*it).second.evenSpat, &(*it).second.evenConvResult );
#else // FFT_FILTERING
    int filt1 = addSpatFilterToList(&oddSpat );
    int filt2 = addSpatFilterToList(&evenSpat );
#endif // FFT_FILTERING

    // Adding filters to Group 0 
    addFilterToGroup(oddSpat_fastTime, 1.0*ampFactor, 0, filt1);	// left -> right
    addFilterToGroup(evenSpat_slowTime, -1.0*ampFactor, 0, filt2);	// left -> right
    //units[unit_index].addFilterToGroup(evenSpat_slowTime, 1.0*ampFactor, 0, filt2);	// right -> left
    //units[unit_index].addFilterToGroup(oddSpat_fastTime, 1.0*ampFactor, 0, filt1);	// right -> left

    // Adding filters to Group 1 
    addFilterToGroup(oddSpat_slowTime, 1.0*ampFactor, 1, filt1);	// left -> right
    addFilterToGroup(evenSpat_fastTime, 1.0*ampFactor, 1, filt2);	// left -> right
    //units[unit_index].addFilterToGroup(evenSpat_fastTime, -1.0*ampFactor, 1, filt2);	// right -> left
    //units[unit_index].addFilterToGroup(oddSpat_slowTime, 1.0*ampFactor, 1, filt1);	// right -> left

#ifdef OPPOSITE_ENERGY

    // Adding filters to Group 2 
    addFilterToGroup(evenSpat_slowTime, 1.0*ampFactor, 2);	// right -> left
    addFilterToGroup(oddSpat_fastTime, 1.0*ampFactor, 2);	// right -> left

    // Adding filters to Group 3 
    addFilterToGroup(evenSpat_fastTime, -1.0*ampFactor, 3);	// right -> left
    addFilterToGroup(oddSpat_slowTime, 1.0*ampFactor, 3);	// right -> left

#endif // OPPOSITE_ENERGY

    // And finally, allocating values
    allocateValues();

}

void ABFilter::allocateValues()
{
    FilterGroup::iterator itt;

    for (int ng = 0; ng < nGroups; ng ++)
        for (itt = fGroup[ng].begin(); itt != fGroup[ng].end(); itt ++) 
        {
            (*itt).filter.allocateValues();
   
        }

    done = true;
}


double ABFilter::convolve( CImg<double> &image, double centerx, double centery )
{
    double tmpValue = 0, value = 0;
    double tFactor = 1;

    SpatialFilterList::iterator itt;

    for( itt = spatFilterList.begin(); itt != spatFilterList.end(); itt ++ )
    {
#ifdef FFT_FILTERING
        CImg<double> *cRes;
        cRes = (*itt).second.convFFTRes;
        (*itt).second.convValue = (*cRes)((int)(centerx), (int)(centery));
#else // FFT_FILTERING
        (*itt).second.convValue = applyfilter_interpol( image, (*itt).second.filter, centerx, centery );
#endif // FFT_FILTERING
    }

    davalue = 0;
    for (int ng = 0; ng < nGroups; ng ++)
    {
        value = 0;

        for (unsigned int i = 0; i < fGroup[ng].size(); i ++)
        {	
            // Spatial-Temporal convolution of the input image with the filter group
            tmpValue = (fGroup[ng].at(i)).spatFilterPtr->convValue;
            (fGroup[ng].at(i)).filter.feedInput( tmpValue );

            // ===== CONVOLUCION TEMPORAL =====
            if( staticFilter )
                (fGroup[ng].at(i)).filter.tempStepStatic( );
            else
                (fGroup[ng].at(i)).filter.tempStep( );
  
            value += tFactor * (fGroup[ng].at(i)).weight * (fGroup[ng].at(i)).filter.read();  // temporal convolution
            //value += tFactor * (fGroup[ng].at(i)).weight * tmpValue;  // temporal convolution
        }
        davalue += value * value;

        //davalue += value;
    }
    return davalue;
}
