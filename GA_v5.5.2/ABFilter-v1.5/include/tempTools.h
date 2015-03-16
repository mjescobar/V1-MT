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


#ifndef TEMP_TOOLS_H_
#define TEMP_TOOLS_H_

#include <time.h>
#include <sys/time.h>

struct timeval;
typedef struct timeval tiempo_t;

inline long dif_sec_tmp( tiempo_t *begin, tiempo_t *end ) // Difference in seconds
{
    long diffs;

    diffs = end->tv_sec - begin->tv_sec;

    if ( ( end->tv_usec - begin->tv_usec ) < -500000 )
	diffs--;
    else
	if ( ( end->tv_usec - begin->tv_usec ) > 500000 )
	    diffs++;

    return( diffs );
}

inline long dif_msec_tmp(tiempo_t *p_tmp_ini, tiempo_t *p_tmp_fin) // Difference in milliseconds
{
    long sec,usec;
    long rtn;

    if ((p_tmp_ini == NULL) || (p_tmp_fin == NULL))
    {
	return 0;
    }

    sec = (p_tmp_fin->tv_sec - p_tmp_ini->tv_sec) * 1000;
    usec = p_tmp_fin->tv_usec - p_tmp_ini->tv_usec;
    rtn = sec + usec/1000;
    return rtn;
}

inline long dif_usec_tmp(tiempo_t *tmp_ini, tiempo_t *tmp_end) // Difference in microseconds
{
    long usec_ini, usec_end, usec_diff;

    if ((tmp_ini == NULL) || (tmp_end == NULL))
    {
	return 0;
    }

    usec_ini = (tmp_ini->tv_sec)*1000000 + tmp_ini->tv_usec;
    usec_end = (tmp_end->tv_sec)*1000000 + tmp_end->tv_usec;
    usec_diff = usec_end - usec_ini;

    return usec_diff;
}


#endif // TEMP_TOOLS_H_
