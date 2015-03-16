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

#ifndef _ABFILTER_H_
#define _ABFILTER_H_

#include "recfilter.h"
#include "gabor.h"
#include "cell.h"

#define W_MIN   5   
#define W_MAX   60  
#define XI_MIN  0
#define XI_CUT  1.6874
#define XI_MAX  2

#define FSIZE   512

typedef struct
{
    int			id;
    CImg<double>	filter;
    CImg<double>	*convFFTRes;
    double		convValue;
}SpatFilterInfo;
typedef map< int, SpatFilterInfo > SpatialFilterList;

typedef struct
{
    Cell		filter;
    double              weight;
    SpatFilterInfo	*spatFilterPtr;
} FilterInfo;
typedef vector< FilterInfo > FilterGroup;


class ABFilter: public RecFilter
{
/** \mainpage ABFilter library

	This library is available in order to help the implementation of spatiotemporal filtering
	in video sequences. Specifically, this library implements the physiological plausible filters
	proposed by Adelson and Bergen (1985)(*).

	The ABFilter library is based on the creation of entities that could be associated to neurons. 
	Each entity is an ABFilter instance that has assigned a spatial location in the input video.
	Besides the spatial location, an ABFilter instance should also have associated a location in the
	spatial-temporal frequency space.

	The library contains three directories containing:
	\arg \b doc: html and latex documentation of the library
	\arg \b src: Makefile and test sample file (testABFilter.cpp)
	\arg \b include: header and code of the library

	\section libgeneration How to generate the library

	To generate de library, inside src folder, type: 

 	\code make lib \endcode

	\section compilation How to compile
	To compile the test file, inside src folder, type:

	\code make testABFilter \endcode 

	\section run How to run the test file

	Library includes a video sequence in INR format (grating.inr) to test the filtering. You can modify the 
	testABFilter code to load a list of images instead of a video sequence.
	To run the test file with the included video sequence, type for instance:

	\code ./testABFilter -i grating.inr -r 8 -ef 5 -xi 1 -omega 5 -orient 45 \endcode

	If you face any problem do not hesitate in contact me.


	(*) Adelson, E. and L. Bergen: 1985, 'Spatiotemporal energy models for the perception of
	motion'. Journal of the Optical Society of America A, volume 2, pp 284-299.	 

	\author Maria-Jose Escobar  (@link WWW http://www.elo.utfsm.cl/profesores/~mjescobar) 
*/
private:

	double davalue;
	double spatialFrequency;
	double tauFilter;
	double angle;
	double orientation;
	double ampFactor;
	double step;
    bool   staticFilter;
	SpatialFilterList	spatFilterList;
	int			spatFilterIndex;
	int nGroups;
	FilterGroup	*fGroup;
  	CImg<double>	oddSpat;
    CImg<double>	evenSpat;

	void buildSpatialFilter(void);
	void setValue(double);
	double getValue();
	void set_nGroups(int nG);
	void addFilterToGroup(Cell flt, double w, int group, int spatFltId = -1);
//	int addSpatFilterToList( CImg<double> inFilt, CImg<double> *convFFTImag );
	int addSpatFilterToList( CImg<double> *inFilt);
	void allocateValues();

#ifdef FFT_FILTERING
	COMPLEX_IMAG	fftOddSpat;
	COMPLEX_IMAG	fftEvenSpat;
	CImg<double>	oddConvResult;
	CImg<double>	evenConvResult;
#endif // FFT_FILTERING

public:
	ABFilter(void);
  	~ABFilter(void);

	// =====================================================================
	/** \fn void set_spatialOrient(double angle)
	 *	\brief Used to set the spatial orientation selectivity
	 *  \param angle Value of the angle in radians
	 *  
	 *  This function is used to set the spatial orientation selectivity
	 *  of the ABFilter instance. This value is associated to the direction
	 *  of Gabor derivatives conforming the spatial part of the filters.
	 */
	void set_spatialOrient(double angle);
	// =====================================================================

	// =====================================================================
	/** \fn void set_temporalFrequency(double tFreq)
	 *	\brief Used to set the location of the filter in the temporal frequency space
	 *	\param tFreq Location of the filter in the temporal frequency space (in cycles/sec)
	 *
	 */
	void set_temporalFrequency(double tFreq);
	// =====================================================================

	// =====================================================================
	/** \fn void set_spatialFrequency(double sFreq)
	 *	\brief Used to set the location of the filter in the spatial frequency space
	 *	\param sFreq Location of the filter in the spatial frequency space (in cycles/pixels)
	 *
	 */
	void set_spatialFrequency(double sFreq);
	// =====================================================================

	// =====================================================================
	/** \fn void set_step(double step)
	 *	\brief Set the temporal step between two computations of filter activity 
	 *	\param step Timestep between two computations of filter activity  
	 *
	 *  The timestep between two computation of the filter activity is needed for
	 *	the temporal convolution performed by the RecFilter class.
	 * 	The timestep is normally set in 5msec.	
	 */
	void set_step(double step);	
	// =====================================================================

	// =====================================================================
	/** \fn double convolve(CImg<double> &image, double centerx, double centery)
	 *	\brief Performs the spatiotemporal filtering, convolving the input image with 
	 *  an ABFilter entity.
	 *	\param image input image to filter in CImg (@link CImg http://cimg.sourceforge.net @endlink) format
	 *	\param centerx x-position in the image to localize the filter 
	 *	\param centery y-position in the image to localize the filter 
	 *	\return It returns the result of the convolution, as a double  
	 *
	 */
	double convolve(CImg<double> &image, double centerx, double centery);
	// =====================================================================

	// =====================================================================
	/** \fn void filter_build()
	 *	\brief Once the configuration of the filter is done, call this method 
	 *  to internally set up the filter BEFORE using ABFilter::convolve method.
	 *
	 */
	void filter_build();
	// =====================================================================

};

#endif // _ABFILTER_H_  
