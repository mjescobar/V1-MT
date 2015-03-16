/* 
 * File:   Individual.h
 * Author: Pedro F. Toledo <pedrotoledocorrea@gmail.com>
 *
 * Created on November 9, 2012, 10:08 PM
 */

#ifndef INDIVIDUAL_H
#define INDIVIDUAL_H

#include "../GA-UniversalStorage/UniversalStorage.h"

class Individual {
public:
//------------------------------------------------------------------------------
//Standard methods--------------------------------------------------------------
//------------------------------------------------------------------------------
           Individual(const Individual& orig);
           Individual();
  virtual ~Individual();
//------------------------------------------------------------------------------
//Constructors------------------------------------------------------------------
//------------------------------------------------------------------------------
  Individual(int IdP, int WeightsSizeP, int ResultsDimensionsP, int FittingDimensionsP, int SimulationStepsP);
//------------------------------------------------------------------------------
//Global Operations-------------------------------------------------------------
//------------------------------------------------------------------------------
  int GetId();
  int GetWeightsSize();
  int GetResultsSize();
  int GetFittingSize();
//------------------------------------------------------------------------------
//Operations Related to Weights-------------------------------------------------
//------------------------------------------------------------------------------
  void    AddWeights(double* VectorValues);
  void    DeleteWeights(int PositionP);
  void    FreeWeights(int PositionP);
  void    SetMixedWeights(double* OtherWeights);
  void    ShiftWeights();
  double* GetWeightsLast();
  int     GetWeightsStored();
//------------------------------------------------------------------------------
//Operations Related to Results-------------------------------------------------
//------------------------------------------------------------------------------
  void     RefreshResults(int StepsP, double** VectorValues);
  double** GetResultsLast();
  int      GetResultsStored();
//------------------------------------------------------------------------------
//Operations Related to Fitting-------------------------------------------------
//------------------------------------------------------------------------------
  void    AddFitting(double* VectorValues);
  double* GetFittingLast();
  double* GetFittingStep(int StepP);
  int     GetFittingStored();
private:
  int              Id;
  int              WeightsDimension;
  int              ResultsDimension;
  int              FittingDimension;
  int              SimulationSteps;
  UniversalStorage Weights;
  UniversalStorage Results;
  UniversalStorage Fitting;
};

#endif /* INDIVIDUAL_H */
