/* 
 * File:   Individual.cpp
 * Author: Pedro F. Toledo <pedrotoledocorrea@gmail.com>
 * 
 * Created on November 9, 2012, 10:08 PM
 */

#include "Individual.h"

#define free(p) free(p);p=NULL;

//------------------------------------------------------------------------------
//Standard methods--------------------------------------------------------------
//------------------------------------------------------------------------------

Individual::Individual(const Individual& orig){
  Id               = orig.Id;
  WeightsDimension = orig.WeightsDimension;
  ResultsDimension = orig.ResultsDimension;
  FittingDimension = orig.FittingDimension;
  SimulationSteps  = orig.SimulationSteps;
  Weights          = orig.Weights;
  Results          = orig.Results;
  Fitting          = orig.Fitting;
}

Individual::Individual(){
  Id               = -1;
  WeightsDimension = -1;
  ResultsDimension = -1;
  FittingDimension = -1;
  SimulationSteps  = -1;
  Weights          = UniversalStorage(0, NULL);
  Results          = UniversalStorage(0, NULL);
  Fitting          = UniversalStorage(0, NULL);
}

Individual::~Individual(){
  //TBC
}

//------------------------------------------------------------------------------
//Constructors------------------------------------------------------------------
//------------------------------------------------------------------------------

Individual::Individual(int IdP, int WeightsSizeP, int ResultsDimensionsP, int FittingDimensionsP, int SimulationStepsP){
  Id               = IdP;
  WeightsDimension = WeightsSizeP;
  ResultsDimension = ResultsDimensionsP;
  FittingDimension = FittingDimensionsP;
  SimulationSteps  = SimulationStepsP;
  Weights          = UniversalStorage(0, NULL);
  Results          = UniversalStorage(0, NULL);
  Fitting          = UniversalStorage(0, NULL);
  int* InternalVectorSize = (int*)malloc(sizeof(double)*2);
  if(Results.GetFieldSize()==0){
    InternalVectorSize[0] = SimulationSteps;
    InternalVectorSize[1] = ResultsDimension;
    Results.AddStorage(2, InternalVectorSize);
  }
  free(InternalVectorSize);
}

//------------------------------------------------------------------------------
//Global Operations-------------------------------------------------------------
//------------------------------------------------------------------------------

int Individual::GetId(){
  return Id;
}

int Individual::GetWeightsSize(){
  return WeightsDimension;
}

int Individual::GetResultsSize(){
  return ResultsDimension;
}

int Individual::GetFittingSize(){
  return FittingDimension;
}

//------------------------------------------------------------------------------
//Operations Related to Weights-------------------------------------------------
//------------------------------------------------------------------------------

void Individual::AddWeights(double* VectorValues){
  int* InternalVectorSize = (int*)malloc(sizeof(int)*1);
  InternalVectorSize[0] = WeightsDimension;
  Weights.AddStorage(1, InternalVectorSize);
  double *InternalData = (double*)Weights.GetLast()->GetData();
  for(int i=0;i<WeightsDimension;i++){
    InternalData[i] = VectorValues[i];
  }
  free(InternalVectorSize);
}

void Individual::DeleteWeights(int PositionP){
  Weights.DeleteStorage(PositionP);
}

void Individual::FreeWeights(int PositionP){
  Weights.FreeStorage(PositionP);
}

void Individual::SetMixedWeights(double* OtherWeights){
  double Random;
  for(int i=0;i<WeightsDimension;i++){
    Random = (double)rand()/(double)RAND_MAX;
    GetWeightsLast()[i] = (Random<0.5)?GetWeightsLast()[i]:OtherWeights[i];
  }
}

void Individual::ShiftWeights(){
  Weights.Shift();
}

double* Individual::GetWeightsLast(){
  return (double*)(Weights.GetLast()->GetData());
}

int Individual::GetWeightsStored(){
  return Weights.GetFieldSize();
}

//------------------------------------------------------------------------------
//Operations Related to Results-------------------------------------------------
//------------------------------------------------------------------------------

void Individual::RefreshResults(int StepsP, double** VectorValuesP){
  double** InternalData = (double**)Results.GetLast()->GetData();
  for(int i=0;i<StepsP;i++){
    for(int j=0;j<ResultsDimension;j++){
      InternalData[i][j] = VectorValuesP[i][j];
    }
    free(VectorValuesP[i]);
  }
  free(VectorValuesP);
}
double** Individual::GetResultsLast(){
  return (double**)(Results.GetLast()->GetData());
}

//------------------------------------------------------------------------------
//Operations Related to Fitting-------------------------------------------------
//------------------------------------------------------------------------------

void Individual::AddFitting(double* VectorValues){
  int* InternalVectorSize = (int*)malloc(sizeof(int)*1);
  InternalVectorSize[0] = FittingDimension;
  Fitting.AddStorage(1, InternalVectorSize);
  double* InternalData = (double*)((Fitting.GetLast())->GetData());
  for(int i=0;i<FittingDimension;i++){
    InternalData[i] = VectorValues[i];
  }
  free(InternalVectorSize);
  free(VectorValues);
}

double* Individual::GetFittingLast(){
  return (double*)(Fitting.GetLast()->GetData());
}

double*      Individual::GetFittingStep(int StepP){
  return (double*)Fitting.GetPosition(StepP)->GetData();
}

int        Individual::GetFittingStored(){
  return Fitting.GetFieldSize();
}
