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


#ifndef GABOR_H_
#define GABOR_H_

#include <iostream>
#include <math.h>

#include "cimg/CImg.h"
using namespace cimg_library;

inline double Gabor_Zero(double sigma,double T,double freq, double x, double y,double phi)
{
  return (exp(-((x*x)+(y*y))/(2*sigma*sigma))  *  (sin(2*M_PI*freq*(x*cos(T)+y*sin(T))+phi)))/(sigma*sqrt(2*M_PI));
}

inline double Gabor_FirstDerivative( double sigma, double th, double freq, double x, double y, double phi )
{
    double gaussValue, sigma_2 = sigma*sigma;

    double xa = x*cos(th) - y*sin(th);	// Rotation in clockwise direction
    //double xa = -x*sin(th) + y*cos(th);	// Rotation in clockwise direction

    gaussValue = -xa*exp(-(x*x+y*y)/(2*sigma_2))*sin(2*M_PI*freq*xa)/sigma_2
	+ 2*exp(-(x*x+y*y)/(2*sigma_2))*cos(2*M_PI*freq*xa)*M_PI*freq;


    return gaussValue;
}

inline double Gabor_SecondDerivative( double sigma, double th, double freq, double x, double y, double phi )
{
    double gaussValue, sigma_2 = sigma*sigma, sigma_4 = sigma_2*sigma_2;

    double xa = x*cos(th) - y*sin(th);	// Rotation in clockwise direction
    //double xa = -x*sin(th) + y*cos(th);	// Rotation in clockwise direction

    gaussValue = exp(-(x*x+y*y)/(2*sigma_2))*(-sin(2*M_PI*freq*xa)*sigma_2
	    + xa*xa*sin(2*M_PI*freq*xa) - 4*xa*cos(2*M_PI*freq*xa)*M_PI*freq*sigma_2
	    - 4*sin(2*M_PI*freq*xa)*M_PI*M_PI*freq*freq*sigma_4)/sigma_4;


    return gaussValue;
}

inline CImg<double> build_GaborZero(double sigma, double orient, double freq, double phi)
{
	//CImg<double> filt((int)((6*sigma)+1),((int)(6*sigma)+1));
	CImg<double> filt((int)(5 * sigma), (int)(5 * sigma));
	double f_cx = 0.5*filt.dimx();
	double f_cy = 0.5*filt.dimy();
	double norm = 0;

	for( int x = 0; x < filt.dimx(); x++ )
		for( int y = 0; y < filt.dimy(); y++ )
		{
			filt(x,y) = Gabor_Zero(sigma, orient, freq, x - f_cx, y - f_cy, phi);
			//norm += filt(x,y)*filt(x,y);
			norm += abs(filt(x,y));
		}

	for( int x = 0; x < filt.dimx(); x++ )
		for( int y = 0; y < filt.dimy(); y++ )
        {
            //filt(x,y) = filt(x,y) / sqrt(norm); 
            filt(x,y) = filt(x,y) / norm; 
        }

	// Maybe it is necessary substract the mean

	return filt;
}

inline CImg<double> build_GaborFirst(double sigma, double orient, double freq, double phi)
{
	//CImg<double> filt((int)(6*sigma),(int)(6*sigma));
	CImg<double> filt((int)(5 * sigma), (int)(5 * sigma));
	double f_cx = 0.5*filt.dimx();
	double f_cy = 0.5*filt.dimy();
	double norm = 0;

	for( int x = 0; x < filt.dimx(); x++ )
		for( int y = 0; y < filt.dimy(); y++ )
		{
			filt(x,y) = Gabor_FirstDerivative(sigma, orient, freq, x - f_cx, y - f_cy, phi);
			//norm += filt(x,y)*filt(x,y);
			norm += abs(filt(x,y));
		}

	for( int x = 0; x < filt.dimx(); x++ )
		for( int y = 0; y < filt.dimy(); y++ )
        {
            //filt(x,y) = filt(x,y) / sqrt(norm); 
            filt(x,y) = filt(x,y) / norm; 
        }

	// Maybe it is necessary substract the mean

	return filt;
}

inline CImg<double> build_GaborSecond(double sigma, double orient, double freq, double phi)
{
	//CImg<double> filt((int)(6*sigma),(int)(6*sigma));
	CImg<double> filt((int)(5 * sigma), (int)(5 * sigma));
	double f_cx = 0.5*filt.dimx();
	double f_cy = 0.5*filt.dimy();
	double norm = 0;

	for( int x = 0; x < filt.dimx(); x++ )
		for( int y = 0; y < filt.dimy(); y++ )
		{
			filt(x,y) = Gabor_SecondDerivative(sigma, orient, freq, x - f_cx, y - f_cy, phi);
			//norm += filt(x,y)*filt(x,y);
			norm += abs(filt(x,y));
		}

	for( int x = 0; x < filt.dimx(); x++ )
		for( int y = 0; y < filt.dimy(); y++ )
        {
            //filt(x,y) = filt(x,y) / sqrt(norm); 
            filt(x,y) = filt(x,y) / norm; 
        }

	// Maybe it is necessary substract the mean

	return filt;
}

inline double convolveSepFilters(CImg<double> &image, 
				CImg<double> filt1, 
				CImg<double> filt2, 
				double centerfilter_x, 
				double centerfilter_y) 
{
    double my_result = 0.0;

    for (int i = 0; i < filt1.dimx(); i ++)
	my_result += filt1(i) * image.linear_pix2d(centerfilter_x - (filt1.dimx() - 1)/2 + i, centerfilter_y);

    for (int j = 0; j < filt2.dimx(); j ++)
	my_result += filt2(j) * image.linear_pix2d(centerfilter_x, centerfilter_y - (filt2.dimx() - 1)/2 + j);

    return my_result;
}


#endif // GABOR_H_
