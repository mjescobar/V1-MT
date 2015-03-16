/* 
 * File:   MultithreadManager.h
 * Author: Pedro F. Toledo <pedrotoledocorrea@gmail.com>
 *
 * Created on November 29, 2012, 12:46 PM
 */

#ifndef MULTITHREADMANAGER_H
#define MULTITHREADMANAGER_H

#include <vector>
#include <unistd.h>
#include <pthread.h>

#include "../GA-V1MTSimulator/V1MTSimulator.h"
#include "../GA-Population/Population.h"

class MultithreadManager {
public:
//------------------------------------------------------------------------------
//Standard methods--------------------------------------------------------------
//------------------------------------------------------------------------------
  virtual ~MultithreadManager();
//------------------------------------------------------------------------------
//Constructors------------------------------------------------------------------
//------------------------------------------------------------------------------
  MultithreadManager(int PopulationSizeP, bool NormalizeP, double* ObjectiveVectorP, int ResultCalculationElementsP);
  MultithreadManager(const MultithreadManager& orig);
//------------------------------------------------------------------------------
//Class operations--------------------------------------------------------------
//------------------------------------------------------------------------------
  int             GetTotalSimulations();
  int             GetCurrentSimulation();
  int             CurrentSimulationStep();
  void            Run(int MaxThreadsP);
  void            ExportResults(Population* WorldP);
  void            FillManager(Population WorldP, int TotalStepsP, FilterResponse ExternalFilterP, int V1TotalNeuronsP, double** V1NeuronsPositionsP, int MTTotalNeuronsP, double** MTNeuronsPositionsP, int V1OrientationsP, int V1SpatialFrequenciesP, int V1TemporalFrequenciesP, double* SensibilityP);
  V1MTSimulator*  GetSimulator(int PositionP);
  pthread_mutex_t SimulationConcurrencyMutex;
private:
  int                        TotalSimulations;
  int                        CurrentSimulation;
  int                        ResultCalculationElements;
  bool                       Normalize;
  double*                    ObjectiveVector;
  std::vector<V1MTSimulator> Simulators;
};

#endif  /* MULTITHREADMANAGER_H */
