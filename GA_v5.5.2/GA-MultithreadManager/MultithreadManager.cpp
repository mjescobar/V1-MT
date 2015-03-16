/* 
 * File:   MultithreadManager.cpp
 * Author: Pedro F. Toledo <pedrotoledocorrea@gmail.com>
 * 
 * Created on November 29, 2012, 12:46 PM
 */

#include "MultithreadManager.h"

#define PI 3.1415926
#define free(p) free(p);p=NULL;

//------------------------------------------------------------------------------
//Standard methods--------------------------------------------------------------
//------------------------------------------------------------------------------

MultithreadManager::~MultithreadManager() {
  //TBC
}

//------------------------------------------------------------------------------
//Constructors------------------------------------------------------------------
//------------------------------------------------------------------------------

MultithreadManager::MultithreadManager(int PopulationSizeP,bool NormalizeP, double* ObjectiveVectorP, int ResultCalculationElementsP) {
  Simulators.reserve(PopulationSizeP);
  TotalSimulations           = PopulationSizeP;
  CurrentSimulation          = 0;
  SimulationConcurrencyMutex = PTHREAD_MUTEX_INITIALIZER;
  Normalize                  = NormalizeP;
  ObjectiveVector            = ObjectiveVectorP;
  ResultCalculationElements  = ResultCalculationElementsP;
}

MultithreadManager::MultithreadManager(const MultithreadManager& orig) {
}

//------------------------------------------------------------------------------
//Class operations--------------------------------------------------------------
//------------------------------------------------------------------------------

void* Simulate(void* MultithreadManagerP){
  bool EndCondition = false;
  int ToSimulate;
  MultithreadManager* GlobalSimulator = (MultithreadManager*)MultithreadManagerP;
  while(GlobalSimulator->GetCurrentSimulation() < GlobalSimulator->GetTotalSimulations()){
    pthread_mutex_lock(&GlobalSimulator->SimulationConcurrencyMutex);
      if(GlobalSimulator->GetCurrentSimulation() < GlobalSimulator->GetTotalSimulations()){
        ToSimulate = GlobalSimulator->CurrentSimulationStep();
      }
      else{
        EndCondition = true;
      }
    pthread_mutex_unlock(&GlobalSimulator->SimulationConcurrencyMutex);
    if(EndCondition){
      pthread_exit((void*)"End");
    }
    else{
      GlobalSimulator->GetSimulator(ToSimulate)->BuildV1MTNet();
      GlobalSimulator->GetSimulator(ToSimulate)->CalculateNetWeights();
      GlobalSimulator->GetSimulator(ToSimulate)->Simulate();
    }
  }
  return NULL;
}

void MultithreadManager::FillManager(Population WorldP, int TotalStepsP, FilterResponse ExternalFilterP, int V1TotalNeuronsP, double** V1NeuronsPositionsP, int MTTotalNeuronsP, double** MTNeuronsPositionsP, int V1OrientationsP, int V1SpatialFrequenciesP, int V1TemporalFrequenciesP, double* SensibilityP){
  for(int i=0;i<WorldP.GetPopulationSize();i++){
    Simulators.push_back(V1MTSimulator(TotalStepsP,ExternalFilterP,V1TotalNeuronsP,V1NeuronsPositionsP,MTTotalNeuronsP,MTNeuronsPositionsP,V1OrientationsP,V1SpatialFrequenciesP,V1TemporalFrequenciesP,WorldP.GetIndividual(i)->GetWeightsLast(), Normalize, ObjectiveVector, ResultCalculationElements, SensibilityP));
  }
}

void MultithreadManager::ExportResults(Population* WorldP){
  for(int i=0;i<WorldP->GetPopulationSize();i++){
    WorldP->GetIndividual(i)->AddFitting(Simulators[i].GetSimulationResultsCondensed());
    WorldP->GetIndividual(i)->RefreshResults(Simulators[i].GetTotalSteps(),Simulators[i].GetSimulationResult());
  }
}

int MultithreadManager::GetTotalSimulations(){
  return TotalSimulations;
}

int MultithreadManager::GetCurrentSimulation(){
  return CurrentSimulation;
}
  
int MultithreadManager::CurrentSimulationStep(){
  return CurrentSimulation++;
}

void MultithreadManager::Run(int MaxThreadsP){
  pthread_t*      ThreadMatrix;
  pthread_attr_t    ThreadAttributes;
  ThreadMatrix = (pthread_t*)malloc(sizeof(pthread_t)*MaxThreadsP);
  pthread_attr_init(&ThreadAttributes);
  pthread_attr_setdetachstate(&ThreadAttributes,PTHREAD_CREATE_JOINABLE);
  for(int i=0;i<MaxThreadsP;i++){
    pthread_create(&(ThreadMatrix[i]),&ThreadAttributes,Simulate,(void*) this);
    usleep(1000);    
  }
  for(int i=0;i<MaxThreadsP;i++){
    pthread_join(ThreadMatrix[i],NULL);
  }
  free(ThreadMatrix);
}

V1MTSimulator* MultithreadManager::GetSimulator(int PositionP){
  return &Simulators[PositionP];
}
