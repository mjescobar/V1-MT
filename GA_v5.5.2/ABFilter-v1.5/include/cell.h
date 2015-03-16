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


#ifndef CELL_H
#define CELL_H

#include "cimg/CImg.h"
#include "tempTools.h"
#include "recfilter.h"
#include "gabor.h"
#include "cimg/cimg_tools.h"

#ifdef FFT_FILTERING
#include "fftTools.h"
#endif // FFT_FILTERING

using namespace cimg_library;

class Cell : public RecFilter
{
	protected:
		double	spatialPeriod, spatialPhase, orientation;
		double	sigma;
		int	spatFilterDegree;
		double	convValue;

		CImg<double>	*userFilter;
#ifdef FFT_FILTERING
		CImg<double>	*convResult;
#endif // FFT_FILTERING

	public:
        double tNormFactor;

		Cell(double stepp=1);
		~Cell(void);

        void set_tempNormFactor(double factor);
		void set_spatialPeriod(double val);
		void set_spatialPhase(double val);
		void set_orientation(double val);
		void set_spatialFilterDegree(int dg);
		void set_spatialFilter(CImg<double> *spatFilter);
#ifdef FFT_FILTERING
		void set_convResult(CImg<double> *convR);
#endif // FFT_FILTERING

		void allocateValues(void);
		double spatialFiltering(CImg<double> image, double posx, double posy);

		void setConvValue(double cValue);
		double getConvValue();
};

#endif // CELL_H
