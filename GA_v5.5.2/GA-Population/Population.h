/* 
 * File:   Population.h
 * Author: Pedro F. Toledo <pedrotoledocorrea@gmail.com>
 *
 * Created on November 11, 2012, 11:50 AM
 */

#ifndef POPULATION_H
#define POPULATION_H

#include "../GA-Individual/Individual.h"
#include <math.h>

class Population {
public:
//------------------------------------------------------------------------------
//Standard methods--------------------------------------------------------------
//------------------------------------------------------------------------------
           Population(const Population& orig);
  virtual ~Population();
//------------------------------------------------------------------------------
//Constructors------------------------------------------------------------------
//------------------------------------------------------------------------------
  Population(int PopulationSizeP, int WeightsSizeP, int ResultsDimensionsP, int FittingDimensionsP, int SimulationSizeP);
//------------------------------------------------------------------------------
//Global Operations-------------------------------------------------------------
//------------------------------------------------------------------------------
  Individual* GetIndividual(int i);
  int         GetPopulationSize();
//------------------------------------------------------------------------------
//Operations Related to Weights-------------------------------------------------
//------------------------------------------------------------------------------
  int  GetWeightsSize();
  void PlantingRandom(double MinP, double MaxP, int StepsP);
  void PlantingFromFile(char* FileNameP, double MinP, double MaxP, int StepsP);
  void PlantingFixed(double ValueP, double MinP, double MaxP, int StepsP);
//------------------------------------------------------------------------------
//Operations Related to GA------------------------------------------------------
//------------------------------------------------------------------------------
  void NaturalSelection(double ProbabilityP);
  void Mutate(double ProbabilityP,int CriteriaP,bool* MutationMask);
//------------------------------------------------------------------------------
//Operations Related to Results-------------------------------------------------
//------------------------------------------------------------------------------
  double   GetMaxAngle();
  double   GetMinAngle();
  double   GetAvgAngle();
  double   GetStdAngle();
  double   GetMaxFitting();
  double   GetMinFitting();
  double   GetAvgFitting();
  double   GetStdFitting();
  double   GetBestFittingValue();
  double   GetBestFittingAngle();
  double*  GetBestFittingWeights();
  double** GetBestFittingResults();
private:
  int                     WeightsStep;
  int                     ResultsDimensions;
  int                     FittingDimensions;
  int                     PopulationSize;
  int                     SimulationSize;
  int                     WeightsSize;
  double                  WeightsMax;
  double                  WeightsMin;
  double                  BestCaseFitting;
  double                  BestCaseAngle;
  double*                 BestCaseWeights;
  double**                BestCaseResults;
  std::vector<Individual> Individuals;
};

#endif  /* POPULATION_H */
