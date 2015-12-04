/* 
 * File:   main.cpp
 * Author: Pedro F. Toledo <pedrotoledocorrea@gmail.com>
 *
 * Created on November 10, 2012, 10:48 PM
 */

#include <cstdlib>
#include <stdio.h>
#include <ctime> 
#include <sys/time.h>
#include <vector>
#include "../GA-MultithreadManager/MultithreadManager.h"
#include "../GA-FilterResponse/FilterResponse.h"
#include "../GA-Population/Population.h"
#include "../GA-Tools/Tools.h"

#define PI 3.1415926
#define free(p) free(p);p=NULL;

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
  //--------------------------------------------------------------------------
  //Variables Declaration-----------------------------------------------------
  //--------------------------------------------------------------------------
    //GA variables
      //GA Control
        double        NaturalSelectionFactor = 0.25;
      //Population Variables
        int PopulationSize            = 1;
        int ResultCalculationElements = 10;
        int FittingDimensions         = 5; //Angle,Magnitude,StdvAngle,Fitting,StdFitting
        int ResultDimensions          = 32;
        int V1Orientations            = 32;
        int V1SpatialFrequencies      = 4;
        int V1TemporalFrequencies     = 4;
    //Simulator Variables
      //Simulator Parameters
        double** V1NeuronsFastList    = (double**)malloc(sizeof(double*)*1);
                 V1NeuronsFastList[0] = (double*)malloc(sizeof(double)*2);
        double** MTNeuronsFastList    = (double**)malloc(sizeof(double*)*1);
                 MTNeuronsFastList[0] = (double*)malloc(sizeof(double)*2);
        int      V1NeuronsFastListSize;
        int      MTNeuronsFastListSize;
      //Simulation Parameters
        int  TimeSteps = 100;
        bool Normalize = true;
        FilterResponse Filters(V1Orientations,V1SpatialFrequencies,V1TemporalFrequencies,1,NULL,NULL);
    //Population Constructor
      Population World(PopulationSize, V1Orientations*V1SpatialFrequencies*V1TemporalFrequencies*V1Orientations*V1SpatialFrequencies*V1TemporalFrequencies, ResultDimensions, FittingDimensions, TimeSteps);      
  //--------------------------------------------------------------------------
  //Starting Variables--------------------------------------------------------
  //--------------------------------------------------------------------------
    //Planting Random seed
      srand((unsigned)time(0)); 
    //Planting Random Individuals
      World.PlantingFromFile(argv[1],0,1,10);
    //Starting Simulator Variables
      //Filling Neurons Positions Lists
        V1NeuronsFastList[0][0] = 0;
        V1NeuronsFastList[0][1] = 0;
        V1NeuronsFastListSize   = 1;
        MTNeuronsFastList[0][0] = 0;
        MTNeuronsFastList[0][1] = 0;
        MTNeuronsFastListSize   = 1;
      //Filling Filter responses for Simulator Fa-Or-Sp-Tm-Ma-Ratio-Selectivity
        int or1, or2, sf1, sf2, tf1, tf2;
        sscanf(argv[2],"%d",&or1);
        sscanf(argv[3],"%d",&sf1);
        sscanf(argv[4],"%d",&tf1);
        sscanf(argv[5],"%d",&or2);
        sscanf(argv[6],"%d",&sf2);
        sscanf(argv[7],"%d",&tf2);
        Filters.SuperposeActivationDifuse(0,or1,sf1,tf1,1,5,0.3); //Filling Filter responses for Simulator Fa-Or-Sp-Tm-Ma-Ratio-Selectivity
        Filters.SuperposeActivationDifuse(0,or2,sf2,tf2,1,5,0.3); //Filling Filter responses for Simulator Fa-Or-Sp-Tm-Ma-Ratio-Selectivity
        Filters.FillInfluenceMask();
        double ObjectiveVector[8];
        double Sensibility[8];
  //--------------------------------------------------------------------------
  //Starting Simulation ------------------------------------------------------
  //--------------------------------------------------------------------------
    printf("-------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("-                                                                                                                                                           -\n");
    printf("-                                                                    V1MT Simple Simulator                                                                  -\n");
    printf("-                                                   Author: Pedro F. Toledo <pedrotoledocorrrea@gmail.com>                                                  -\n");
    printf("-                                                                                                                                                           -\n");
    printf("-------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
    MultithreadManager GlobalSimulator(World.GetPopulationSize(),Normalize,ObjectiveVector,ResultCalculationElements);
    GlobalSimulator.FillManager(World,TimeSteps,Filters,V1NeuronsFastListSize,V1NeuronsFastList,MTNeuronsFastListSize,MTNeuronsFastList,V1Orientations,V1SpatialFrequencies,V1TemporalFrequencies,Sensibility);
    GlobalSimulator.Run(1);
    GlobalSimulator.ExportResults(&World);
    World.NaturalSelection(NaturalSelectionFactor);
    printf("- Result Parameters -----------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("  Measured Angle:         %.3f[Deg]\n",World.GetBestFittingAngle()*180/PI);
    printf("-------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("- Temporal Result -------------------------------------------------------------------------------------------------------------------------------------------\n");
    double** Tmp2 = World.GetBestFittingResults();
    for(int i=0;i<TimeSteps-1;i++){
      for(int j=0;j<ResultDimensions;j++){
        printf("%8.5f\t",Tmp2[i][j]);
      }
      printf("\n");
    }
    for(int i=0;i<V1NeuronsFastListSize;i++){
      free(V1NeuronsFastList[i]);
    }
    free(V1NeuronsFastList);
    for(int i=0;i<MTNeuronsFastListSize;i++){
      free(MTNeuronsFastList[i]);
    }
    free(MTNeuronsFastList);
    return 0;
}
