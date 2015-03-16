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


#include "cell.h"
#include "cimg/cimg_tools.h"

void Cell::allocateValues(void)
{
    RecFilter::allocateValues();
}

double Cell::spatialFiltering(CImg<double> image, double xpos, double ypos)
{
    double convValue = 0;

#ifdef FFT_FILTERING

    convValue = (*convResult)((int)xpos, (int)ypos); 

#else // FFT_FILTERING

    // Normal convolution
    convValue = applyfilter_interpol( image, *userFilter, xpos, ypos );
printf("conValue = %lf\n",convValue);
#endif // FFT_FILTERING

    return convValue;
}

void Cell::setConvValue(double cValue)
{
    convValue = cValue;
}

double Cell::getConvValue()
{
    return convValue;
}

Cell::Cell(double stepp) : RecFilter(stepp)
{
    spatialPeriod = 4;
    spatialPhase = 0, orientation = 0;
    spatFilterDegree = 0;
    userFilter = NULL; 
#ifdef FFT_FILTERING
    convResult = NULL; 
#endif // FFT_FILTERING
    convValue = 0;
}

Cell::~Cell(void){}

void Cell::set_tempNormFactor( double factor )
{
    tNormFactor = factor;
}

void Cell::set_spatialPeriod(double val)
{
    this->spatialPeriod = val;
}

void Cell::set_spatialPhase(double val)
{
    this->spatialPhase = val;
}

void Cell::set_orientation(double val)
{
    this->orientation = val;
}

void Cell::set_spatialFilterDegree(int dg)
{
    this->spatFilterDegree = dg;
}

void Cell::set_spatialFilter(CImg<double> *spatFilter)
{
    userFilter = spatFilter;
}

#ifdef FFT_FILTERING
void Cell::set_convResult(CImg<double> *convR)
{
    convResult = convR;
}
#endif // FFT_FILTERING
