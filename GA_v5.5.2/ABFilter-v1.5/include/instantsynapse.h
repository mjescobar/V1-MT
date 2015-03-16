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


#ifndef INSTANTSYNAPSE_H
#define INSTANTSYNAPSE_H

#include "cimg/misc_tools.h"
#include "cimg/cimg_tools.h"


// A 'quite' general tool to model instantaneous synaptic transmission, with its possible non linearities. 
//Its parameters are:
//	- Gmax, maximum output value (saturation)
//	- v0, threshold of the function. Transmission is 'compressed' for v<v0, and 'saturated' for v>v0
//	- lambda, slope of the function at point v0 (if power_exp = 1 )
//	- eta, relative sizes of the 'saturation' zone and of the 'compression' zone

//	- power_exp, an 'artificial' exponent to be able to generate power-law synaptic functions
//	Allows to implement transmissions of the type v->v^2 (but in a very complicated way !!!! :-)   )

//The most general formula it implements is, for an input value v :

//  workPoint = ( v > v0 ) ?  lambda/Gmax * pow ( v - v0 , power_exp ) :	//workPoint > 0
//              - lambda/Gmax * pow ( v0 - v , power_exp ) ;			//workPoint < 0

// output = (workPoint > 0 )?   Gmax * ( eta + (1-eta)*workPoint/(1-eta+workPoint) ) :
//           			Gmax * eta * eta/(eta-workPoint);


class InstantSynapse
{
protected:
  double eta, Gmax, lambda, v0, zeroPoint, workPoint, power_exp;
  bool useZP;

  inline void actualize(void)
  {
    if(useZP) v0=-Gmax/lambda*zeroPoint;
    else zeroPoint=-lambda/Gmax*v0;
  }
  double nonLinTransmission(double inputValue); //const;


public:

  bool isUsed;		//to tell if the synapse has been initialized, or if it is just 'virtual' (to win some calcuation time).
  bool isLinear;	//to tell if the synapse has been initialized non-linearly (to win some calcuation time).

  InstantSynapse(bool uZP=false);
~InstantSynapse(){}

  //************* Transmission functions: *******

  double transmission(double inputValue); //const;
  void addTransmission(const CImg<double>& input, CImg<double>& output); //const;
  void apply(CImg<double>& input); //const;
  CImg<double> transmission(const CImg<double>& input); //const;

  //************* Initialization functions: *****

  //****** (1) Already coded functions:

  //returns 	val_v^2 /(val_v + lam * (v-input)^power_exp ) 	if lam*(input-v) < 0
  // 		val_v + lam * (v-input)^power_exp		if lam*(input-v) > 0
  InstantSynapse& rectification(double v, double lam=1.0, double val_v=0.0);

  //A simple linear amplification of the input___Warning! Output can be negative...
  InstantSynapse& linearAmplification( double lam );

  //If you want to change the power exponent (default is 1, of course)
  InstantSynapse& set_power_exp(double val);

  //just to represent the shape of the synapse's rectification function
  void draw_transmission( double xmin=-2.0, double xmax=2.0, const double* color = green );


  //******** (2) Custom functions:

  //Decide wether the synapse formalism should use a 'zeroPoint' or rather a 'v0'
  InstantSynapse& useZeroPoint(void);
  //direct setting of parameters:
  InstantSynapse& set_Gmax(double val);
  InstantSynapse& set_eta(double val);
  InstantSynapse& set_lambda(double val);
  InstantSynapse& set_v0(double val);
  InstantSynapse& set_zeroPoint(double val);
  //once all other synaptic parameters are fixed, calculates zeroPoint (or v0...) so as to have g as transmission output when inputValue=v
  double calculate_v0(double g, double v); //const;
  double calculate_zeroPoint(double g, double v); //const;


  //get_X functions (because of the ambiguity zeroPoint <-> v0)
  double get_zeroPoint(void); //const;
  double get_v0(void); //const;

};
#endif


