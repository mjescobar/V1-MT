/* 
 * File:   Population.cpp
 * Author: Pedro F. Toledo <pedrotoledocorrea@gmail.com>
 * 
 * Created on November 11, 2012, 11:50 AM
 */

#include "Population.h"

#define free(p) free(p);p=NULL;

//------------------------------------------------------------------------------
//Standard methods--------------------------------------------------------------
//------------------------------------------------------------------------------

Population::Population(const Population& orig){
  PopulationSize    = orig.PopulationSize;
  WeightsSize       = orig.WeightsSize;
  ResultsDimensions = orig.ResultsDimensions;
  FittingDimensions = orig.FittingDimensions;
  Individuals       = orig.Individuals;
  WeightsSize       = orig.WeightsSize;
  WeightsMax        = orig.WeightsMax;
  WeightsMin        = orig.WeightsMin;
  BestCaseFitting   = orig.BestCaseFitting;
  SimulationSize    = orig.SimulationSize;
  BestCaseAngle     = orig.BestCaseAngle;
  BestCaseResults   = (double**)malloc(sizeof(double*)*orig.SimulationSize);
  for(int i=0;i<orig.SimulationSize;i++){
    BestCaseResults[i] = (double*)malloc(sizeof(double)*orig.ResultsDimensions);
  }
  BestCaseWeights = (double*)malloc(sizeof(double)*WeightsSize);
  for(int i=0;i<WeightsSize;i++){
    BestCaseWeights[i] = orig.BestCaseWeights[i];
  }
}

Population::~Population(){
  free(BestCaseWeights);
  for(int i=0;i<SimulationSize;i++){
    free(BestCaseResults[i]);
  }
  free(BestCaseResults);
}

//------------------------------------------------------------------------------
//Constructors------------------------------------------------------------------
//------------------------------------------------------------------------------

Population::Population(int PopulationSizeP, int WeightsSizeP, int ResultsDimensionsP, int FittingDimensionsP, int SimulationSizeP) {
  PopulationSize    = PopulationSizeP;
  WeightsSize       = WeightsSizeP;
  WeightsMax        = -1;
  WeightsMin        = -1;
  WeightsStep       = -1;
  ResultsDimensions = ResultsDimensionsP;
  FittingDimensions = FittingDimensionsP;
  BestCaseFitting   = -1;
  BestCaseAngle     = -1;
  BestCaseWeights   = (double*)malloc(sizeof(double)*WeightsSize);
  SimulationSize    = SimulationSizeP;
  BestCaseResults   = (double**)malloc(sizeof(double*)*SimulationSizeP);
  for(int i=0;i<SimulationSizeP;i++){
    BestCaseResults[i] = (double*)malloc(sizeof(double)*ResultsDimensionsP);
  }
  for(int i=0;i<WeightsSize;i++){
    BestCaseWeights[i] = 0;
  }
  Individuals.reserve(PopulationSizeP);
  for(int i=0;i<PopulationSizeP;i++){
    Individuals.push_back(Individual(i,WeightsSize,ResultsDimensions,FittingDimensions,SimulationSize));
  }
}

//------------------------------------------------------------------------------
//Global Operations-------------------------------------------------------------
//------------------------------------------------------------------------------

Individual* Population::GetIndividual(int i){
  return &(Individuals[i]);
}

int Population::GetPopulationSize(){
  return PopulationSize;
}

//------------------------------------------------------------------------------
//Operations Related to Weights-------------------------------------------------
//------------------------------------------------------------------------------

int Population::GetWeightsSize(){
  return WeightsSize;
}

void Population::PlantingRandom(double MinP, double MaxP, int StepsP){
  double* Weights;
  WeightsMax  = MaxP;
  WeightsMin  = MinP;
  WeightsStep = StepsP;
  for(int i=0;i<(int)Individuals.size();i++){
    Weights = (double*)malloc(sizeof(double)*Individuals[i].GetWeightsSize());
    for(int j=0;j<Individuals[i].GetWeightsSize();j++){
      Weights[j] = (rand()%(StepsP+1))*(MaxP - MinP)/((double)(StepsP))+MinP;
    }
    Individuals[i].AddWeights(Weights);
    free(Weights);
  }
}

void Population::PlantingFixed(double ValueP, double MinP, double MaxP, int StepsP){
  double* Weights;
  WeightsMax  = MaxP;
  WeightsMin  = MinP;
  WeightsStep = StepsP;
  for(int i=0;i<(int)Individuals.size();i++){
    Weights = (double*)malloc(sizeof(double)*Individuals[i].GetWeightsSize());
    for(int j=0;j<Individuals[i].GetWeightsSize();j++){
      Weights[j] = ValueP;
    }
    Individuals[i].AddWeights(Weights);
    free(Weights);
  }
}

void Population::PlantingFromFile(char* FileNameP, double MinP, double MaxP, int StepsP){
  WeightsMax  = MaxP;
  WeightsMin  = MinP;
  WeightsStep = StepsP;
  for(int i=0;i<(int)Individuals.size();i++){
    FILE* file = fopen(FileNameP,"r");
    double* Weights = (double*)malloc(sizeof(double)*Individuals[i].GetWeightsSize());
    bool HeaderFound = false;
    char ForGets[1024];
    do{
      fgets(ForGets,1024,file);
      HeaderFound = (strstr(ForGets,"Best Fitting Weights")==NULL)?false:true;
    }while(!HeaderFound);
    for(int j=0;j<Individuals[i].GetWeightsSize();j++){
      fscanf(file,"%lf",&(Weights[j]));
    }
    fclose(file);
    Individuals[i].AddWeights(Weights);
    free(Weights);
  }
}

//------------------------------------------------------------------------------
//Operations Related to GA------------------------------------------------------
//------------------------------------------------------------------------------

void      Population::NaturalSelection(double ProbabilityP){
  double* PopulationFittings = (double*)malloc(sizeof(double)*Individuals.size());
  int* PopulationPositions = (int*)malloc(sizeof(int)*Individuals.size());
  double* Roulette = (double*)malloc(sizeof(double)*Individuals.size());
  double** CurrentWeights = (double**)malloc(sizeof(double*)*Individuals.size());
  //Extracting Results
  for(int i=0;i<(int)Individuals.size();i++){
    PopulationFittings[i] = Individuals[i].GetFittingLast()[3];
    PopulationPositions[i] = i;
  }
  //Sorting Results
  double TmpFitting;
  int TmpPosition;
  for(int i=1;i<(int)Individuals.size();i++){
    for(int j=1;j<(int)Individuals.size();j++){
      if(PopulationFittings[j]<PopulationFittings[j-1]){
        TmpFitting = PopulationFittings[j-1];
        TmpPosition = PopulationPositions[j-1];
        PopulationFittings[j-1] = PopulationFittings[j];
        PopulationPositions[j-1] = PopulationPositions[j];
        PopulationFittings[j] = TmpFitting;
        PopulationPositions[j] = TmpPosition;
      }
    }
  }
  if(BestCaseFitting > PopulationFittings[0] || BestCaseFitting == -1){
    BestCaseFitting = PopulationFittings[0];
    BestCaseAngle = Individuals[PopulationPositions[0]].GetFittingLast()[0];
    double* Tmp1 = Individuals[PopulationPositions[0]].GetWeightsLast();
    for(int i=0;i<WeightsSize;i++){
      BestCaseWeights[i] = Tmp1[i];
    }
    double** Tmp2 = Individuals[PopulationPositions[0]].GetResultsLast();
    for(int i=0;i<SimulationSize;i++){
      for(int j=0;j<ResultsDimensions;j++){
        BestCaseResults[i][j] = Tmp2[i][j];
      }
    }
  }
  //Making Roulette and storing current weights
  Roulette[0] = ProbabilityP;
  for(int i=1;i<(int)Individuals.size();i++){
    Roulette[i] = (1-Roulette[i-1])*ProbabilityP+Roulette[i-1];
  }
  for(int i=0;i<(int)Individuals.size();i++){
    Roulette[i] /= Roulette[(int)Individuals.size()-1];
    CurrentWeights[i] = (double*)malloc(sizeof(double)*Individuals[i].GetWeightsSize());
    for(int j=0;j<(int)Individuals[i].GetWeightsSize();j++){
      double* Tmp = Individuals[i].GetWeightsLast();
      CurrentWeights[i][j] = Tmp[j];
    }
  }
  //Making New Weights
  double Random;
  for(int i=0;i<(int)Individuals.size();i++){
    Random = (double)rand()/(double)RAND_MAX;
    for(int j=0;j<(int)Individuals.size();j++){
      if(Random < Roulette[j]){
        Individuals[i].SetMixedWeights(CurrentWeights[PopulationPositions[j]]);
        j = Individuals.size();
      }
    }
  }
  for(int i=0;i<(int)Individuals.size();i++){
    free(CurrentWeights[i]);
  }
  free(CurrentWeights);
  free(PopulationFittings);
  free(PopulationPositions);
  free(Roulette);
}

void Population::Mutate(double ProbabilityP,int CriteriaP, bool* MutationMaskP){
  double Random;
  double FutureValue;
  double MutateStep = (WeightsMax-WeightsMin)/(double)pow(WeightsStep,CriteriaP);
  for(int i=0;i<(int)Individuals.size();i++){
    double* TemporalWeights = Individuals[i].GetWeightsLast();
    for(int j=0;j<(int)Individuals[i].GetWeightsSize();j++){
      if(MutationMaskP[j]){
        Random = (double)rand()/(double)RAND_MAX;
        if(Random<ProbabilityP){
          FutureValue = TemporalWeights[j];
          Random = (double)rand()/(double)RAND_MAX;
          if(Random<0.5){
            FutureValue += MutateStep;
          }
          else{
            FutureValue -= MutateStep;
          }
          if(FutureValue>WeightsMax+MutateStep/10 || FutureValue<WeightsMin-MutateStep/10){
            if(FutureValue>WeightsMax){
              FutureValue -= MutateStep*2;
            }
            else{
              FutureValue += MutateStep*2;
            }
          }
          TemporalWeights[j] = FutureValue;
        }
      }
      else{
        TemporalWeights[j] = 0;
      }
    }
  }
  free(MutationMaskP);
}

//------------------------------------------------------------------------------
//Operations Related to Results-------------------------------------------------
//------------------------------------------------------------------------------

double Population::GetMaxAngle(){
  double Value = Individuals[0].GetFittingLast()[0];
  for(int i=1;i<(int)Individuals.size();i++){
    Value = (Individuals[i].GetFittingLast()[0]>Value)?Individuals[i].GetFittingLast()[0]:Value;
  }
  return Value;
}

double Population::GetMinAngle(){
  double Value = Individuals[0].GetFittingLast()[0];
  for(int i=1;i<(int)Individuals.size();i++){
    Value = (Individuals[i].GetFittingLast()[0]<Value)?Individuals[i].GetFittingLast()[0]:Value;
  }
  return Value;
}

double Population::GetAvgAngle(){
  double Value = 0;
  for(int i=0;i<(int)Individuals.size();i++){
    Value += Individuals[i].GetFittingLast()[0];
  }
  Value /= (double)Individuals.size();
  return Value;
}

double Population::GetStdAngle(){
  double Avg = GetAvgAngle();
  double Value = 0;
  for(int i=0;i<(int)Individuals.size();i++){
    double Tmp = Individuals[i].GetFittingLast()[0] - Avg;
    Value += Tmp*Tmp;
  }
  Value /= (double)Individuals.size();
  return sqrt(Value);
}

double Population::GetMaxFitting(){
  double Value = Individuals[0].GetFittingLast()[3];
  for(int i=1;i<(int)Individuals.size();i++){
    Value = (Individuals[i].GetFittingLast()[3]>Value)?Individuals[i].GetFittingLast()[3]:Value;
  }
  return Value;
}

double Population::GetMinFitting(){
  double Value = Individuals[0].GetFittingLast()[3];
  for(int i=1;i<(int)Individuals.size();i++){
    Value = (Individuals[i].GetFittingLast()[3]<Value)?Individuals[i].GetFittingLast()[3]:Value;
  }
  return Value;
}

double Population::GetAvgFitting(){
  double Value = 0;
  for(int i=0;i<(int)Individuals.size();i++){
    Value += Individuals[i].GetFittingLast()[3];
  }
  Value /= (double)Individuals.size();
  return Value;
}

double Population::GetStdFitting(){
  double Avg = GetAvgFitting();
  double Value = 0;
  for(int i=0;i<(int)Individuals.size();i++){
    double Tmp = Individuals[i].GetFittingLast()[3] - Avg;
    Value += Tmp*Tmp;
  }
  Value /= (double)Individuals.size();
  return sqrt(Value);
}

double Population::GetBestFittingValue(){
  return BestCaseFitting;
}

double* Population::GetBestFittingWeights(){
  return BestCaseWeights;
}

double** Population::GetBestFittingResults(){
  return BestCaseResults;
}

double Population::GetBestFittingAngle(){
  return BestCaseAngle;
}
