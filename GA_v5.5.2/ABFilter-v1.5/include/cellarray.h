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


#ifndef CELL_ARRAY_H_
#define CELL_ARRAY_H_

#include <iostream>
#include <map>
#include <errno.h>

#define cimg_display_type 1
#define cimg_OS 1
#include "cimg/CImg.h"

using namespace std;
using namespace cimg_library;

typedef struct
{
    double	xPos;
    double	yPos;
}COORD;
typedef struct
{
    double 	xPos;
    double	yPos;
    double	radius;
}CoordInfoStr;
typedef std::map<int, CoordInfoStr> CoordinateList;

class CellArray 
{
    protected :
	int		nb_units;
	double		step;			// Time step 
	int		timesPerFrame;
	CoordinateList	coordList;

	// =====================================================================================
	// Parameters needed to construct the layer (distribution of cells)
	// =====================================================================================
	double	Rmax;			// Size parameters (maximum radius and fovea) 
	double	R0;
	double	d0;			// Sampling parameters
	double	decayRate;
	double	gamma;
	double	beta;

	// =====================================================================================
	// Parameters needed for the cells' synapses 
	// =====================================================================================
	double 	e_exc;
	double	e_inh;
	double	restingPotential;
	double	gleak;	
	double	tau;

	// =====================================================================================
	// Tools to retrieve "position<-->identificator"  of units :
	// =====================================================================================
	int		nb_circles;		// Number of circles in the channel, INCLUDING central point 
	double		*angular_offset;		// Angular_offset[n] is the angular_offset of circle n.


	// =====================================================================================
	// Layer initialization: cells placement and filter building
	// =====================================================================================
	virtual void channel_build( int init_index ){}

    public :

	// =====================================================================================
	// Functions to handle SAMPLING :
	// =====================================================================================
	double get_radius( int circle_index );
	double get_density( double rad );
	int get_numberUnits( double rad );
	double density( double r );

	// =====================================================================================
	// Functions to handle the filters'  scales with eccentricity :
	// =====================================================================================
	double spatial_scaling( double rad );
	double temporal_scaling( double rad );

	// =====================================================================================
	// Constructors/Destructor :
	// =====================================================================================
	CellArray( double stepp = 1.0 );
	virtual ~CellArray();

	// =====================================================================================
	// Accessors :
	// =====================================================================================
	int totalNumberUnits();

	// =====================================================================================
	// Channel parameter definition functions :
	// =====================================================================================
	void set_step( double s );
	void set_timesPerFrame( int tf );
	void set_Rmax( double f );
	void set_foveaDensity( double f );
	void set_foveaRadius( double f );
	void set_decayRate( double f );
	void set_beta( double f );
	void set_gamma( double f );

	// =====================================================================================
	// A more convenient way :
	// =====================================================================================
	void set_channel(double rmax, double d, double r0, double k, double bet, double gam);

	// =====================================================================================
	//Global cell parameters definition (synapses and integrative properties) :
	// =====================================================================================
	void set_Eexc( double f );
	void set_Einh( double f );
	void set_Erest( double f );
	void set_gleak( double f );
	void set_tau( double f );

	// =====================================================================================
	//And the MOST CLASSICAL get-X functions : 
	// =====================================================================================
	double get_Rmax();
	double get_step();
	double get_foveaRadius();
	double get_foveaDensity();

	CoordinateList *getCoordList();

	// =====================================================================================
	// =====================================================================================
	//  ----  NOW -- The interesting part ----

	// The building function:
	void build(int init_index);
	void build_readingFromMap( int init_index, const char *mapFileName );
	void build_uniformCellArray(int xSize, int ySize, int init_index);

	// Feeding an image to the cell layer, this function returns the sum of all the
	// cell responses belonging this channel.
	// This function is declared as virtual, which it means that must be declared
	// for each class inherited from it.
	virtual double feed_image(CImg<double> & image, double xCenter, double yCenter) {return 0;}

	// Saving/loading functions:
	virtual void channel_print(FILE*& print_file, int channel_index){}

	void save(FILE*& print_file, int channel_index, int inIndex);
	void save_simple(FILE*& print_file, int channel_index, int ly_index, int inIndex);

	void feedColumnInhibition();

};


#endif // CELL_ARRAY_H_ 
