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


#ifndef CELLPORTHANDLER_H
#define CELLPORTHANDLER_H

#include "instantsynapse.h"

class CellPortHandler
{
protected:

  vector<InstantSynapse*> inputSynapses;
  vector<double*> inputNernst;
  int lastPort;

public:

  CellPortHandler()
  {
    inputSynapses.push_back(new InstantSynapse);
    inputNernst.push_back(0);
    lastPort=0;
  }


  virtual ~CellPortHandler(){}


  virtual int new_currentInput(InstantSynapse *syn=0)
  {
    if(syn==0)
      inputSynapses.push_back(new InstantSynapse);
    else
      inputSynapses.push_back(syn);
    inputNernst.push_back(0);
    lastPort++;
    return lastPort;
  }



  virtual int new_ionicChannel(double valNernst, InstantSynapse *syn=0)
  {
    if(syn==0)
      inputSynapses.push_back(new InstantSynapse);
    else
      inputSynapses.push_back(syn);
    inputNernst.push_back(new double(valNernst));
    lastPort++;
    return lastPort;
  }

  InstantSynapse& inputSynapse(int port=0)
  {
    if(port>lastPort)
      cerr<<"Error in CellPortHandler::inputSynapse(port): Asking for a synaptic port that does not exist."<<endl;
    return *(inputSynapses[port]);
  }

};


#endif

















