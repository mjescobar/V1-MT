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


#include <instantsynapse.h>

InstantSynapse::InstantSynapse(bool uZP) : isUsed(false), isLinear(false)
{
  eta=0;              //initialized to 'basic rectification, amplification factor of 1'
  Gmax=50000;
  lambda=1;
  power_exp = 1.0;
  v0=0;
  zeroPoint=0;
  useZP=uZP;
  workPoint=0;
}


double InstantSynapse::nonLinTransmission(double inputValue) //const
{
  workPoint = (power_exp == 1) ? lambda/Gmax * ( inputValue-v0 ):
              ( inputValue > v0 ) ?  lambda/Gmax * pow ( inputValue-v0 , power_exp ) :
              - lambda/Gmax * pow ( v0 - inputValue , power_exp ) ;
  if(eta)
    return (workPoint>0)?
           Gmax * (eta + (1-eta)*workPoint/(1-eta+workPoint)) :
           Gmax * eta*eta/(eta-workPoint);

  return (workPoint>0)?
         Gmax*workPoint/(1+workPoint):
         0;
}

double InstantSynapse::transmission(double inputValue) //const
{
  if(!isUsed)	return inputValue;
  if(isLinear)	return lambda*inputValue;
  return nonLinTransmission(inputValue);
}

void InstantSynapse::addTransmission(const CImg<double>& input, CImg<double>& output) //const
{
  if( (input.dimx()!=output.dimx())||(input.dimy()!=output.dimy())||(input.dimz()!=output.dimz())||(input.dimv()!=output.dimv())  )
  {
    cerr<<"Error in function instantSynapse::addTransmission: input and output images do not have the same dimensions"<<endl;
    exit(0);
  }

  if(!isUsed) 		output+=input;
  else if(isLinear)	output+=lambda*input;
  else for(uint i=0;i<input.size();++i) output.data[i]+=nonLinTransmission(input.data[i]);
}

void InstantSynapse::apply(CImg<double>& input) //const
{
  if(isUsed)
  {
    if(isLinear)	input*=lambda;
    else	for(uint i=0;i<input.size();++i) input.data[i]=nonLinTransmission(input.data[i]);
  }
}

CImg<double> InstantSynapse::transmission(const CImg<double>& input) //const
{
  CImg<double> output(input);
  apply(output);
  return output;
}


InstantSynapse& InstantSynapse::useZeroPoint(void)
{
  useZP=true;
  return (*this);
}

//Initialization functions:

//once all other synaptic parameters are fixed, calculates zeroPoint so as to have g as transmission output when inputValue=v.

double InstantSynapse::calculate_v0(double g, double v) //const
{
  if(g>Gmax) cerr<<"in calculate_zeroPoint(): requested conductance g is bigger than maximum conductance."<<endl;
  double K=g/Gmax;

  if ( K > eta )	//workpoint is positive
  {
    double wP = (K-eta)*(1-eta)/(1-K) ;
    return  v - pow ( Gmax / lambda * wP , 1/power_exp ) ;
  }
  else 			//workpoint is negative
  {
    double wP =  eta*(K-eta)/K ;
    return v + pow ( - Gmax / lambda * wP , 1/power_exp ) ;
  }
}

double InstantSynapse::calculate_zeroPoint(double g, double v) //const
{
  return -lambda/Gmax*calculate_v0(g,v);
}


InstantSynapse& InstantSynapse::rectification( double v, double lam, double val_v )
{
  Gmax=500000;   //big value: transmission==linear for input>v0
  eta=val_v/Gmax;
  lambda=lam;   //required slope in the zone v>v0
  v0=v;
  actualize(); isUsed=true; isLinear=false; return *this;
}


InstantSynapse& InstantSynapse::linearAmplification(double lam)
{
  lambda=lam;   //required slope
  isUsed=true;
  isLinear=true;
  return *this;
}

InstantSynapse& InstantSynapse::set_power_exp  (double val)
{
  this->power_exp = val ;
  actualize();
  isUsed=true;
  isLinear=false;
  return *this;
}

InstantSynapse& InstantSynapse::set_Gmax(double val)
{
  this->Gmax=val;
  actualize();
  isUsed=true;
  isLinear=false;
  return *this;
}
InstantSynapse& InstantSynapse::set_eta(double val)
{
  this->eta=val;
  actualize();
  isUsed=true;
  isLinear=false;
  return *this;
}
InstantSynapse& InstantSynapse::set_lambda(double val)
{
  this->lambda=val;
  actualize();
  isUsed=true;
  isLinear=false;
  return *this;
}
InstantSynapse& InstantSynapse::set_v0(double val)
{
  if(useZP) cerr<<"do not use set_v0 for a synapse where the zeroPoint matters..."<<endl;
  this->v0=val;
  actualize();
  isUsed=true;
  isLinear=false;
  return *this;
}

InstantSynapse& InstantSynapse::set_zeroPoint(double val)
{
  if(!useZP) cerr<<"do not use set_zeroPoint for a synapse where v0 matters..."<<endl;
  actualize();
  isUsed=true;
  isLinear=false;
  return *this;
}

double InstantSynapse::get_zeroPoint(void) //const
{
  return this->zeroPoint;
}
double InstantSynapse::get_v0(void) //const
{
  return this->v0;
}



//just to represent the shape of the synapse's rectification function
void InstantSynapse::draw_transmission(double xmin, double xmax, const double* color)
{
  int nbsamples=200;  //200 values should be very sufficient.
  CImg<double> transmissionValues(nbsamples);
  cimg_forX(transmissionValues,x)
  transmissionValues(x)=transmission(xmin+(double)x/(nbsamples-1)*(xmax-xmin));

  CImg<double> figure(400,300,1,3,255);
  figure.fill(255.0);

  CImgSignalDrawer sd; sd.style=0; sd.width=2;
  sd.axisX.begin=xmin; sd.axisX.end=xmax; //linear
  sd.draw(figure, transmissionValues , color );

  figure.display();
}




