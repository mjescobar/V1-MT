
// =====================================================================================
/*	testABFilter.cpp : Example code used to show how the ABFilter library can
 *                     be used
 *
 *  author			 : Maria-Jose Escobar Silva
 *					   Electronic Engineering Department
 *					   Universidad Tecnica Federico Santa Maria, Chile
 *                     http://www.profesores.elo.utfsm.cl/~mjescobar
 *
 *	date			 : November 2010
 *
 *	-----------------------------------------------------------------------------------
 *
 *	To compile:
 *				make testABFilter	
 *	
 *	For help type: 
 *				./testABFilter -h				
 *
 */
// =====================================================================================
#include "../include/ABFilter.h"
#include <stdio.h>
#include <math.h>
#include <errno.h>
#include <libgen.h>

#define _USE_MATH_DEFINES

int main(int argc, char **argv) 
{ 

	// =====================================================================================
	// 		Input paramters description
	// =====================================================================================
	const char *input = cimg_option("-i", "", "Input video sequence"); 
	const int N_rep = cimg_option("-r", 5, "Number of repetitions of each frame");
	const int beginning_frame = cimg_option("-bf", 0, "beginning frame of input sequence");
	const int end_frame = cimg_option("-ef", 0, "ending frame of input sequence (not included)"); 
	const double xi = cimg_option("-xi", 1.0, "xi, spatial frequency selectivity in cycles/pixel");
	const double omega = cimg_option("-omega", 30.0, "omega, temporal frequency selectivity in cycles/sec");
	const double orientation = cimg_option("-orient", 0.0, "spatial orientation selectivity in degrees");
	const double step = cimg_option("-s", 0.005, "Time length of one step, in seconds");

	FILE	*outFile = NULL;

	if( argc < 3 )
	{
		if( argc > 1 )
		{
			if( strcmp(argv[1], "-h") == 0 )
			{
				return 0;
			}
		}
		else
		{
			printf("\nFor options please type: ./testABFilter -h\n\n");
			return 0;
		}
	}

	// ===============================================================================
	//	Creating output file to save the convolution result 
	// ===============================================================================
	char outFileName[256];
	sprintf(outFileName, "%s.out", basename((char *)input));

	if( (outFile = fopen(outFileName, "w")) == NULL )
	{
		printf("ERROR openining file %s (errno = %d).... aborting\n", outFileName, errno);
		return -1;
	}


	// ===============================================================================
	//	Checking input image size, and reading it
	// ===============================================================================
	CImg<double> In(input);
	fprintf(outFile,"\n\n\tVideo Size: x: %d, Y: %d\n\n", In.dimx(), In.dimy());
	int s_sx = In.dimx(), s_sy = In.dimy();
	int beginfrm = 0, endfrm = In.dimz();

	if( (beginning_frame < end_frame) && (beginning_frame < endfrm) )
	{
		beginfrm = (beginning_frame > beginfrm) ? beginning_frame : beginfrm;
		endfrm = (end_frame < endfrm) ? end_frame : endfrm;
	}

	// ==============================================================================
	//	Creating the filter
	// ==============================================================================
	ABFilter filter;

	// Setting the spatial orientation selectivity
	filter.set_spatialOrient(orientation);

	// Setting the spatial frequency selectivity
	filter.set_spatialFrequency(xi);

	// Setting the temporal frequency selectivity
	filter.set_temporalFrequency(omega);	

	// Setting time step needed for temporal convolution
	filter.set_step(step);

	// IMPORTANT::	once the setup is done, build the filter
	//				before using it
	filter.filter_build();

	//=======================================================================
	//	Here we go!
	//=======================================================================
	
	CImg<double> Seq(s_sx, s_sy);
	double convResult;
	
	// Go frame by frame
	for (int t = 0; t < endfrm - beginfrm; t++)
	{	   
		Seq = In.get_slice(beginfrm + t);

		// Repeat each frame N_rep times, to let the temporal convolution 
		// evolve in time
		for (int i = 0; i < N_rep; i++)
		{
			// Do the convolution, locating the filter at the center of
			// the input image
			convResult = filter.convolve(Seq, In.dimx()/2, In.dimy()/2);

			fprintf(outFile, "%lf \n", convResult);
		}
	}

	// =================================================================
	//	Cleaning
	// =================================================================

	if( outFile )
		fclose(outFile);
	
	return 0;	
}
