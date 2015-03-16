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


#include "cellarray.h"

extern int errno;

double CellArray::get_radius( int circle_index )
{
    double rad;

    if( circle_index > (R0*d0) )
	rad = R0 + (exp(decayRate*(circle_index/d0-R0)) - 1)/decayRate;
    else
	rad = circle_index / d0;

    return rad; 
}

double CellArray::get_density( double rad )
{
    double density;

    if( rad > R0 )
	density = d0/(1 + decayRate*(rad - R0));
    else
	density = d0;

    return density; 
}

int CellArray::get_numberUnits( double rad )
{
    int nUnits;
    if( rad == 0 ) 
	nUnits = 1;
    else
	nUnits = (int)floor( 2*M_PI*get_density(rad)*rad );

    return nUnits;
}

double CellArray::spatial_scaling( double rad )
{
	if( rad > R0 )
		return pow( (rad/R0), beta );
	else
		return 1;
}

double CellArray::temporal_scaling( double rad )
{
    if( rad > R0 )
	return pow((rad/R0), gamma);
    else
	return 1;
}

CellArray::CellArray( double stepp )
{
    nb_units = 0;
    nb_circles = 0;
	R0 = gamma = beta = 0;

    step = stepp;

	// Put here the biological plausible values
    e_exc = 0.070;
    e_inh = -0.010;
	restingPotential = 0; 
    gleak = 50;
    tau = 0.001;

    srand( (unsigned)time( NULL ) );

	coordList.clear();
}


CellArray::~CellArray(void)
{
}

int CellArray::totalNumberUnits()
{
    return nb_units;
}

void CellArray::set_step( double s )
{
    step = s;
}

void CellArray::set_timesPerFrame( int tf )
{
    timesPerFrame = tf;
}

void CellArray::set_Rmax( double f )
{
    Rmax = f;
} 

void CellArray::set_foveaDensity( double f )
{
    d0 = f;
}

void CellArray::set_foveaRadius( double f )
{
    R0 = f;
}

void CellArray::set_decayRate( double f )
{
    decayRate = f;
}

void CellArray::set_beta( double f )
{
    beta = f;
}

void CellArray::set_gamma( double f )
{
    gamma = f;
}

void CellArray::set_channel( double rmax, double d, double r0, double k, double bet, double gam )
{
    Rmax = rmax;
    d0 = d;
    R0 = r0;
    decayRate = k;
    beta = bet;
    gamma = gam;
}

void CellArray::set_Eexc( double f )
{
    e_exc = f;
}

void CellArray::set_Einh( double f )
{
    e_inh = f;
}

void CellArray::set_Erest( double f )
{
    restingPotential = f;
}

void CellArray::set_gleak( double f )
{
    gleak = f;
}

void CellArray::set_tau( double f )
{
    tau = f;
}

double CellArray::get_Rmax()
{
    return Rmax;
} 

double CellArray::get_step()
{
    return step;
} 

void CellArray::build( int init_index )
{
	double currRadius, currLength, deltaAngle, nCellsCircle;
	int nCells = 0;

	CoordInfoStr cordTmp;
	coordList.clear();

	// Add the cell at the center
	cordTmp.xPos = 0;
	cordTmp.yPos = 0;
	cordTmp.radius = 0;
	coordList.insert( make_pair(nCells, cordTmp) );
	nCells++;

	// Implementation of cells 
	currRadius = 1/d0;
	while( currRadius <= Rmax )
	{
		currLength = 2 * M_PI * currRadius;
		nCellsCircle = currLength * density( currRadius ); 
		deltaAngle = 2 * M_PI / nCellsCircle;
		for( int i = 0; i < nCellsCircle; i++ )
		{
			cordTmp.xPos = currRadius * cos(i * deltaAngle);
			cordTmp.yPos = currRadius * sin(i * deltaAngle);
			cordTmp.radius = currRadius;
			coordList.insert( make_pair(nCells, cordTmp) );
			nCells++;
		}
		currRadius += 1/density( currRadius );
	}
	nb_units = nCells;

	// Here comes the particular implementation of each channel
	// 		V1: create spatial-temporal filters
	// 		MT: create coordinates and receptive fields shapes
	channel_build( init_index );
}

void CellArray::build_readingFromMap( int init_index, const char *mapFileName )
{
	int nCells = 0;
	FILE *mapFile = NULL;
	int retValue = 0;
	double cx, cy;

	CoordInfoStr cordTmp;
	coordList.clear();

	mapFile = fopen( mapFileName, "r" );
	if( mapFile == NULL )
	{
		printf("ERROR, file %s cannot be openned for reading (errno = %d)\n", mapFileName, errno);
		return;
	}

	while( retValue != EOF )
	{
		retValue = fscanf( mapFile, "%lf %lf", &cx, &cy );

		if( retValue != EOF )
		{
			cordTmp.xPos = cx;
			cordTmp.yPos = cy;
			cordTmp.radius = sqrt(cx*cx + cy*cy);

			coordList.insert( make_pair(nCells, cordTmp) );
			nCells++;
		}
	}
	nb_units = nCells;

	// Here comes the particular implementation of each channel
	// 		V1: create spatial-temporal filters
	// 		MT: create coordinates and receptive fields shapes
	channel_build( init_index );

	if( mapFile )
		fclose(mapFile);
}

void CellArray::build_uniformCellArray(int xSize, int ySize, int init_index)
{
	int xCenter = xSize/2;
	int yCenter = ySize/2;
	int ind = 0;
	CoordInfoStr cordTmp;

	nb_units = xSize * ySize;

	coordList.clear();
	for( int i = 0; i < xSize; i ++)
		for ( int j = 0; j < ySize; j ++)
		{
			cordTmp.xPos = i - xCenter;
			cordTmp.yPos = j - yCenter;
			coordList.insert( make_pair(ind, cordTmp) );

			ind++;
		}

	// Here comes the particular implementation of each channel
	// 		V1: create spatial-temporal filters
	// 		MT: create coordinates and receptive fields shapes
	channel_build( init_index );
}

void CellArray::save(FILE*& print_file, int channel_index, int inIndex)
{   
	CoordinateList::iterator it;	
    
	channel_print(print_file, channel_index);
    fprintf(print_file, "<units>\n");
	for( it = coordList.begin(); it != coordList.end(); it++ )
	{
		fprintf( print_file, "*Id %d Xpos %lf Ypos %lf\n",
				(*it).first + inIndex, (*it).second.xPos, (*it).second.yPos);
	}
    fprintf(print_file, "</units>\n</channel %d>\n\n", channel_index);
}

void CellArray::save_simple(FILE*& print_file, int channel_index, int ly_index, int inIndex)
{   
	CoordinateList::iterator it;	
    
	for( it = coordList.begin(); it != coordList.end(); it++ )
	{
		fprintf( print_file, " %d %lf %lf %d %d\n",
				(*it).first + inIndex, (*it).second.xPos, (*it).second.yPos, channel_index, ly_index);
	}
}

double CellArray::density( double r )
{
    double dens;

    if( r > R0 )
	dens = d0/(1 + decayRate*(r - R0));
    else
	dens = d0;

    return dens;
}

double CellArray::get_foveaRadius()
{
	return R0;
}

double CellArray::get_foveaDensity()
{
	return d0;
}

CoordinateList *CellArray::getCoordList()
{
	return &coordList;
}
