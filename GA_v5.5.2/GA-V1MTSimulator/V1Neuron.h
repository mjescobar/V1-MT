
/* 
 * File:   V1Neuron.h
 * Author: Pedro F. Toledo <pedrotoledocorrea@gmail.com>
 *
 * Created on October 29, 2012, 5:20 PM
 */

#ifndef V1NEURON_H
#define  V1NEURON_H

#include <vector>
#include <math.h>
#include "../GA-FilterResponse/FilterResponse.h"

class V1Neuron {
public:
//------------------------------------------------------------------------------
//Standard methods--------------------------------------------------------------
//------------------------------------------------------------------------------
           V1Neuron(const V1Neuron& orig);
  virtual ~V1Neuron();
//------------------------------------------------------------------------------
//Constructors------------------------------------------------------------------
//------------------------------------------------------------------------------
  V1Neuron(int TimeStepsP, int OrientationsP, int SpatialFrequenciesP, int TemporalFrequenciesP, double xP, double yP, double V1ConductanceLeakP, double V1InhibitionFactorP, double V1ExitatoryFactorP);
//------------------------------------------------------------------------------
//Parameter Static Operations---------------------------------------------------
//------------------------------------------------------------------------------
  int    GetOrientations();
  void   SetInternalWeightsV1V1(double****** InternalWeightsV1P);
  void   AddFilterResponseLink(FilterResponse* FacesP);
  void   SetSpatialFrequenciesReference(double* Reference);
  void   SetTemporalFrequenciesReference(double* Reference);
  double GetX();
  double GetY();
  double CalculateDistanceWeightV1V1(double xP, double yP, int OrientationP, int SpatialFreqP, int TemporalFreqP);  
//------------------------------------------------------------------------------
//Parameters Dynamic Operations-------------------------------------------------
//------------------------------------------------------------------------------
  void AddV1Link(V1Neuron &Neuron);
  void CalculateCombinedWeights();
//------------------------------------------------------------------------------
//Simulation Operations---------------------------------------------------------
//------------------------------------------------------------------------------
  void CalculateDActivation();
  void CalculateActivation(double StepP);
//------------------------------------------------------------------------------
//Results Operations------------------------------------------------------------
//------------------------------------------------------------------------------
  double GetMTContribution(int OrientationP);
//------------------------------------------------------------------------------
//Non Linearity Calculations----------------------------------------------------
//------------------------------------------------------------------------------
  double V1NonLinearity(double ValueP);
  double NonLinearityV1MT(double Activation);
private:  
  int             LinkedV1Neurons;
  int             CurrentTime;
  int             MaxTimeSteps;
  int             Orientations;
  int             SpatialFrequencies;
  int             TemporalFrequencies;
  double          x;
  double          y;
  double          ConductanceLeak;
  double          InhibitionFactor;
  double          ExitatoryFactor;
  double*         SpatialFrequenciesReference;
  double*         TemporalFrequenciesReference;
  double**        SumActivation;
  double****      Activation;
  double****      ActivationNonLinearity;
  double****      DActivation;
  double****      CombinedWeights;
  V1Neuron**      V1LinksTotal;
  double******    InternalWeightsV1;
  V1Neuron*****   V1Links;
  FilterResponse* ExternalExitation;
};

#endif  /* V1NEURON_H */
