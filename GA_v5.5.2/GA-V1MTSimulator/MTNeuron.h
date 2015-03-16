
/* 
 * File:   MTNeuron.h
 * Author: Pedro F. Toledo <pedrotoledocorrea@gmail.com>
 *
 * Created on November 3, 2012, 11:56 AM
 */

#ifndef MTNEURON_H
#define  MTNEURON_H

#include <stdlib.h>
#include <stdio.h>
#include "V1Neuron.h"

class MTNeuron {
public:
//------------------------------------------------------------------------------
//Standard methods--------------------------------------------------------------
//------------------------------------------------------------------------------  
           MTNeuron(const MTNeuron& orig);
  virtual ~MTNeuron();
//------------------------------------------------------------------------------
//Constructors------------------------------------------------------------------
//------------------------------------------------------------------------------
  MTNeuron(int TimeStepsP, int OrientationsP, double xP, double yP);
//------------------------------------------------------------------------------
//Parameter Static Operations---------------------------------------------------
//------------------------------------------------------------------------------
  void  AddV1Link(V1Neuron &Neuron);
  void  CalculateV1MTConnectionWeights(double SigmaP, double AmplificagionFactorP, double OrientationRangeP);
//------------------------------------------------------------------------------
//Simulation Operations---------------------------------------------------------
//------------------------------------------------------------------------------
  void  CalculateActivation();
//------------------------------------------------------------------------------
//Results Operations------------------------------------------------------------
//------------------------------------------------------------------------------
  double**  GetActivation();
private:
  int      Orientations;
  int      CurrentTimeStep;
  int      LinkedV1Neurons;
  int      TotalTimeSteps;
  double    x;
  double    y;
  double    ***V1MTConnectionWeights;
  double    **Activation;
  V1Neuron  **V1LinksTotal;
};

#endif  /* MTNEURON_H */
