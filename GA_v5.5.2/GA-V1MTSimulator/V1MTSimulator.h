
/* 
 * File:   V1MTSimulator.h
 * Author: Pedro F. Toledo <pedrotoledocorrea@gmail.com>
 *
 * Created on November 11, 2012, 7:54 PM
 */

#ifndef V1MTSIMULATOR_H
#define  V1MTSIMULATOR_H

#include "../GA-FilterResponse/FilterResponse.h"
#include "V1Neuron.h"
#include "MTNeuron.h"
#include <vector>

class V1MTSimulator {
public:
//------------------------------------------------------------------------------
//Standard methods--------------------------------------------------------------
//------------------------------------------------------------------------------
                 V1MTSimulator(const V1MTSimulator& orig);
  virtual       ~V1MTSimulator();
  V1MTSimulator &operator=(const V1MTSimulator V1MTSimulatorP);
//------------------------------------------------------------------------------
//Constructors------------------------------------------------------------------
//------------------------------------------------------------------------------
  V1MTSimulator(int TotalStepsP, FilterResponse ExternalFilterP, int V1TotalNeuronsP, double** V1NeuronsPositionsP, int MTTotalNeuronsP, double** MTNeuronsPositionsP, int V1OrientationsP, int V1SpatialFrequenciesP, int V1TemporalFrequenciesP, double* V1InternalWeightsP, bool NormalizeP, double* ObjectiveVectorP, int ResultCalculationElementsP, double* SensibilityP);
//------------------------------------------------------------------------------
//Parameter Static Operations---------------------------------------------------
//------------------------------------------------------------------------------                  
  void BuildV1MTNet();
  void CalculateNetWeights();
//------------------------------------------------------------------------------
//Simulation Operations---------------------------------------------------------
//------------------------------------------------------------------------------
  void Simulate();
//------------------------------------------------------------------------------
//Results Operations------------------------------------------------------------
//------------------------------------------------------------------------------  
  int      GetTotalSteps();
  double   CalculateSimulationResultOrientation();
  double   CalculateSimulationResultMagnitude();
  double   CalculateSimulationResultOrientationStdv();
  double   CalculateSimulationResultFitting();
  double   CalculateSimulationResultStdvFitting();
  double*  GetSimulationResultsCondensed();
  double** GetSimulationResult();
private:
  //Simulator Definitions
    int    TotalSteps;
    double DifferentialStep;
    double DynamicTau;
    int    SimulationState;
  //V1 Description
    int          V1TotalNeurons;
    int          V1Orientations;
    int          V1SpatialFrequencies;
    int          V1TemporalFrequencies;
    double       V1Radius;
    double       V1ConductanceLeak;
    double       V1InhibitionFactor;
    double       V1WeightsFactor;
    double       V1ExitatoryFactor;
    double*      V1SpatialFrequenciesArray;
    double*      V1TemporalFrequenciesArray;
    double**     V1NeuronsPositions;
    double****** V1InternalWeights;
    std::vector<V1Neuron>    V1Neurons;
  //MT description
    int                   MTTotalNeurons;
    int                   MTOrientations;
    double                MTSigma;
    double                MTAperture;
    double                MTAmplificationFactor;
    double**              MTNeuronsPositions;
    std::vector<MTNeuron> MTNeurons;
  //Filter Response Descriptor
    FilterResponse Faces;
  //Results
    int     ResultCalculationElements;
    bool    NormalizedFitting;
    double* ObjectiveVector;
    double  ResultOrientation;
    double  ResultMagnitude;
    double  ResultStdv;
    double  ResultFitting;
    double  ResultStdvFitting;
    double* Sensibility;
};

#endif  /* V1MTSIMULATOR_H */
