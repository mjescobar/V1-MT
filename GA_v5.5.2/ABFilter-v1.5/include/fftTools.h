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


#ifndef _FFT_TOOLS_
#define _FFT_TOOLS_

#include <fftw3.h>

#define cimg_display_type 1
#define cimg_OS 1
#include "CImg.h"

// *****************************************************************************
//
//  FFTtool class, created by Maria-Jose ESCOBAR (april 2007)
//
//	This class was created in order to help the usage and implementation of
//	FFT transform and FFT filtering using the library fftw-3.1.2.
//	You just need to specify in your Makefile the location of the library's
//	header file (fftw3.h) and the library (libfftw3.a). The rest of the usage
//	is transparent for the user.
//	
//	See the description of each method to see how to use it. An example
//	of a filtering of two images can be found in testFFTtool.cpp file.
//
//	Feel free to do any change in the current methods or add additional ones.
//	Of course, taking care of the correct functionallity of the class.
//
// *****************************************************************************

using namespace cimg_library;

// *****************************************************************************
//  Format used to deliver the FFT of images generated. This is a way to store
//  the complex image obtained when the FFT is calculated.
//
typedef struct cpxIm
{
    CImg<double>	real;
    CImg<double>	imag;
}COMPLEX_IMAG;

// *****************************************************************************
//  Class definition:
//
class FFTtool
{
    private:
	void transferInfoFromCImgToFFTW(CImg<double> cimgImag, fftw_complex *fftImag);
	void transferInfoFromFFTWToCImg(double *fftImag, CImg<double> &cimgImag);
	void transferInfoFromFFTWToComplex(fftw_complex *fftImag, COMPLEX_IMAG *cimgImag);
	void transferInfoFromComplexToFFTW(COMPLEX_IMAG *inCpx, fftw_complex *outfftw);

	void createExtendedImage(CImg<double> &im, int xFinal, int yFinal);
	void loadSubUnit(CImg<double> &imag, CImg<double> sbImag, int x0, int y0);

    public:
	FFTtool();
	~FFTtool();

	// *****************************************************************************
	//  Function: 
	//	void getFFTtransform(CImg<double> inImag, COMPLEX_IMAG *fftInImag);
	//
	//  Description:
	//	Calculates the FFT of an input image.
	//
	//  Input Parameters:
	//	inImag: input image to calculate FFT
	//
	//  Return value:
	//	A Complex image with the FFT of inImag
	//
	COMPLEX_IMAG getFFTtransform(CImg<double> inImag);

	// *****************************************************************************
	//  Function: 
	//	void getFFTtransform(CImg<double> inImag, COMPLEX_IMAG *fftInImag, int desX, int desY);
	//
	//  Description:
	//	Calculates the FFT of an input image. If the input image is smaller than
	//	the desired size, you can indicate the final size and an extended version of
	//	the input image will be generated before calculate the FFT. The extended
	//	version corresponds a bigger image with the input image in the center, the
	//	rest of the image is filled with the mean value of inImag.
	//
	//  Input Parameters:
	//	inImag: input image to calculate FFT
	//	desX: desired X size to extend the image size.	
	//	desY: desired Y size to extend the image size.	
	//
	//  Return value:
	//	A Complex image with the FFT of inImag
	//
	COMPLEX_IMAG getFFTtransform(CImg<double> inImag, int desX, int desY);

	// *****************************************************************************
	//  Function: 
	//	CImg<double> getFFTinverse(COMPLEX_IMAG fftImag);
	//
	//  Description:
	//	Calculates the FFT inverse of a complex image.
	//
	//  Input Parameters:
	//	fftImag: Complex image to calculate FFT inverse.
	//
	//  Return value:
	//	A CImg<double> image with the FFT inverse.	
	//
	CImg<double> getFFTinverse(COMPLEX_IMAG fftImag);

	// *****************************************************************************
	//  Function: 
	//	void multComplexImages(COMPLEX_IMAG imag1, COMPLEX_IMAG imag2, COMPLEX_IMAG *multResult);
	//
	//  Description:
	//	Multiplies two complex images pointwise. This is done to filter the frequency 
	//	contain of two images, normally the inputs are FFT transforms of images.
	//
	//  Input Parameters:
	//	imag1: Complex image to multiply. 
	//	imag2: Complex image to multiply. 
	//
	//  Return value:
	//	A complex image with the result of the pointwise multiplication. 
	//
	COMPLEX_IMAG multComplexImages(COMPLEX_IMAG imag1, COMPLEX_IMAG imag2);

	// *****************************************************************************
	//  Function: 
	//	void quadrantShift(CImg<double> &img);
	//
	//  Description:
	//	If the input imag <img> is generated as the FFT inverse of the multiplication
	//	of two FFT complex images, a shift in the quadrants of <img> is generated.
	//	This function corrects the quadrant shifting and gives the correct arrange for <img>.	
	//
	//  Input Parameters:
	//	img (by reference): Input CImg image with the quadrant shifting. 
	//
	//  Return value:
	//	img: Input CImg image without the quadrant shifting. 
	//
	void quadrantShift(CImg<double> &img);
};


#endif // _FFT_TOOLS_


