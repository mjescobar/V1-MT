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


#include "fftTools.h"

using namespace std;

FFTtool::FFTtool()
{
}

FFTtool::~FFTtool()
{
}

COMPLEX_IMAG FFTtool::getFFTtransform(CImg<double> inImag)
{
    COMPLEX_IMAG fftImag;
    fftImag.real.assign(inImag.dimx(), inImag.dimy());
    fftImag.imag.assign(inImag.dimx(), inImag.dimy());

    fftw_plan fwdPlan;
    fftw_complex *FFTimag = NULL;
    double *imag = NULL;
    int imagLen = inImag.dimx()*inImag.dimy();

    // Memory allocation and normalize image
    FFTimag = (fftw_complex *)fftw_malloc(sizeof(fftw_complex) * imagLen);
    imag = inImag.data;

    // Create plan and calculate FFT
    fwdPlan = fftw_plan_dft_r2c_2d(inImag.dimx(), inImag.dimy(), imag, FFTimag, FFTW_ESTIMATE);
    fftw_execute(fwdPlan);

    // Copy FFT image output to CImg format
    transferInfoFromFFTWToComplex(FFTimag, &fftImag);
 
    // Freeing memory
    fftw_free(FFTimag);
    fftw_destroy_plan(fwdPlan);

    return fftImag;
}

COMPLEX_IMAG FFTtool::getFFTtransform(CImg<double> inImag, int desX, int desY)
{
    COMPLEX_IMAG fftImag;

    createExtendedImage(inImag, desX, desY);
    fftImag = getFFTtransform(inImag);

    return fftImag;
}

COMPLEX_IMAG FFTtool::multComplexImages(COMPLEX_IMAG imag1, COMPLEX_IMAG imag2)
{
    // NOTE: Assuming same sizes for imag1 and imag2.. no validation is done
    COMPLEX_IMAG mulResult = imag1;

    for(int i = 0; i < imag1.real.dimx(); i ++)
	for(int j = 0; j < imag1.real.dimy(); j ++)
	{
	    // (a + jb) * (c + jd) --> (ac - bd) + j(ad + bc)
	    (mulResult.real)(i,j) = (imag1.real)(i,j) * (imag2.real)(i,j) 
		- (imag1.imag)(i,j) * (imag2.imag)(i,j);
	    (mulResult.imag)(i,j) = (imag1.real)(i,j) * (imag2.imag)(i,j) 
		+ (imag1.imag)(i,j) * (imag2.real)(i,j);
	}

    return mulResult;
}

CImg<double> FFTtool::getFFTinverse(COMPLEX_IMAG fftImag)
{
    fftw_plan	invPlan;
    CImg<double> invFFTimag(fftImag.real.dimx(), fftImag.real.dimy());
    int imagLen = fftImag.real.dimx() * fftImag.imag.dimy();

    // Memory allocation
    fftw_complex *fftIn = (fftw_complex *)fftw_malloc(sizeof(fftw_complex) * imagLen);
    double *outInvFFT = (double *)fftw_malloc(sizeof(double) * imagLen);

    // Create plan
    transferInfoFromComplexToFFTW(&fftImag, fftIn);
    invPlan = fftw_plan_dft_c2r_2d(invFFTimag.dimx(), invFFTimag.dimy(), fftIn, outInvFFT, FFTW_ESTIMATE);
    fftw_execute(invPlan);
    transferInfoFromFFTWToCImg(outInvFFT, invFFTimag);

    // Eliminate plan and free memory
    fftw_free(fftIn); fftw_free(outInvFFT);
    fftw_destroy_plan(invPlan);

    // Load image in fftw format
    return invFFTimag;
}

void FFTtool::createExtendedImage(CImg<double> &im, int xFinal, int yFinal)
{
    CImg<double> imgTmp(xFinal, yFinal);
    imgTmp.fill(0);

    if( (xFinal < im.dimx()) || (yFinal < im.dimy()) )
    {
	printf("ERROR, the filter size (%dx%d) is bigger than the image (%dx%d).. aborting\n",
		im.dimx(), im.dimy(), xFinal, yFinal);
	return;
    }

    // Center im in zero befor extend the image
    double mean = im.sum()/(im.dimx() * im.dimy());
    im -= mean;

    // Now that the image is centered, extend it
    int xCenter = xFinal/2, yCenter = yFinal/2;
    int xCenter_f = im.dimx()/2, yCenter_f = im.dimy()/2;
    for(int i = 0; i < im.dimx(); i ++)
	for(int j = 0; j < im.dimy(); j ++)
	    imgTmp(xCenter - xCenter_f + i, yCenter - yCenter_f + j) = im(i, j);

    im = imgTmp;
}


void FFTtool::transferInfoFromCImgToFFTW(CImg<double> cimgImag, fftw_complex *fftImag)
{
    fftw_complex *tmpPtr = fftImag;
    for(int i = 0; i < cimgImag.dimx(); i ++)
        for(int j = 0; j < cimgImag.dimy(); j ++)
        {
            (*tmpPtr)[0] = cimgImag(i,j);
            (*tmpPtr)[1] = 0;
            tmpPtr ++;
        }
}

void FFTtool::transferInfoFromFFTWToComplex(fftw_complex *fftImag, COMPLEX_IMAG *cimgIm)
{
    fftw_complex *tmpPtr = fftImag;
    double *realData = cimgIm->real.data;
    double *imagData = cimgIm->imag.data;

    for(int i = 0; i < cimgIm->real.dimx(); i ++)
        for(int j = 0; j < cimgIm->real.dimy(); j ++)
        {
            *realData = (*tmpPtr)[0];
	    *imagData =  (*tmpPtr)[1];
            tmpPtr++; realData++; imagData++;
        }
}

void FFTtool::transferInfoFromComplexToFFTW(COMPLEX_IMAG *inCpx, fftw_complex *outfftw)
{
    fftw_complex *tmpPtr = outfftw;
    double *realData = inCpx->real.data;
    double *imagData = inCpx->imag.data;

    for(int i = 0; i < inCpx->real.dimx(); i ++)
        for(int j = 0; j < inCpx->real.dimy(); j ++)
	{
	    (*tmpPtr)[0] = *realData;
	    (*tmpPtr)[1] = *imagData;
	    tmpPtr++; realData++; imagData++;
	}
}

void FFTtool::transferInfoFromFFTWToCImg(double *fftImag, CImg<double> &cimgImag)
{
    double *tmpPtr = fftImag;
    for(int i = 0; i < cimgImag.dimx(); i ++)
        for(int j = 0; j < cimgImag.dimy(); j ++)
        {
            cimgImag(j,i) = (*tmpPtr);
            tmpPtr++;
        }
}

void FFTtool::quadrantShift(CImg<double> &img)
{
    CImg<double> subUnit1(img.dimx()/2, img.dimy()/2);
    CImg<double> subUnit2(img.dimx()/2, img.dimy()/2);
    CImg<double> subUnit3(img.dimx()/2, img.dimy()/2);
    CImg<double> subUnit4(img.dimx()/2, img.dimy()/2);

    // Swap 1st quadrant with 4th one
    subUnit1 = img.get_crop(0, 0, subUnit1.dimx() - 1, subUnit1.dimy() - 1);
    subUnit2 = img.get_crop(0, subUnit1.dimy(), subUnit1.dimx() - 1, img.dimy() - 1);
    subUnit3 = img.get_crop(subUnit1.dimx(), 0, img.dimx() - 1, subUnit1.dimy() - 1);
    subUnit4 = img.get_crop(subUnit1.dimx(), subUnit1.dimy(), img.dimx() - 1, img.dimy() - 1);
    loadSubUnit(img, subUnit4, 0, 0);
    loadSubUnit(img, subUnit1, subUnit1.dimx(), subUnit1.dimy());
    loadSubUnit(img, subUnit3, 0, subUnit1.dimy());
    loadSubUnit(img, subUnit2, subUnit1.dimx(), 0);
}

void FFTtool::loadSubUnit(CImg<double> &imag, CImg<double> sbImag, int x0, int y0)
{
    for( int i = 0; i < sbImag.dimx(); i ++ )
        for ( int j = 0; j < sbImag.dimy(); j ++ )
            imag(x0 + i, y0 + j) = sbImag(i, j);
}
