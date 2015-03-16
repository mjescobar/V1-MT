/* 
 * File:   V1MTSimulator.cpp
 * Author: Pedro F. Toledo <pedrotoledocorrea@gmail.com>
 * 
 * Created on November 11, 2012, 7:54 PM
 */

#include "V1MTSimulator.h"

#define PI 3.1415926
#define free(p) free(p);p=NULL;

//------------------------------------------------------------------------------
//Standard methods--------------------------------------------------------------
//------------------------------------------------------------------------------

V1MTSimulator::V1MTSimulator(const V1MTSimulator& orig){
  Sensibility = orig.Sensibility;
  TotalSteps = orig.TotalSteps;
  DifferentialStep = orig.DifferentialStep;
  DynamicTau = orig.DynamicTau;
  SimulationState = orig.SimulationState;
  V1TotalNeurons = orig.V1TotalNeurons;
  V1Orientations = orig.V1Orientations;
  V1SpatialFrequencies = orig.V1SpatialFrequencies;
  V1TemporalFrequencies = orig.V1TemporalFrequencies;
  V1Radius = orig.V1Radius;
  V1ConductanceLeak = orig.V1ConductanceLeak;
  V1InhibitionFactor = orig.V1InhibitionFactor;
  V1WeightsFactor = orig.V1WeightsFactor;
  V1ExitatoryFactor = orig.V1ExitatoryFactor;
  V1NeuronsPositions = orig.V1NeuronsPositions;
  V1SpatialFrequenciesArray = (double*)malloc(sizeof(double)*V1SpatialFrequencies);
  V1SpatialFrequenciesArray[0] = orig.V1SpatialFrequenciesArray[0];
  V1TemporalFrequenciesArray = (double*)malloc(sizeof(double)*V1TemporalFrequencies);
  V1TemporalFrequenciesArray[0] = orig.V1TemporalFrequenciesArray[0];
  for(int i=1;i<V1SpatialFrequencies;i++){
    V1SpatialFrequenciesArray[i] = V1SpatialFrequenciesArray[i-1]*2;
  }
  for(int i=1;i<V1TemporalFrequencies;i++){
    V1TemporalFrequenciesArray[i] = V1TemporalFrequenciesArray[i-1]*2;
  }
  V1InternalWeights = (double******)malloc(sizeof(double*****)*V1Orientations);
  for(int i=0;i<V1Orientations;i++){
    V1InternalWeights[i] = (double*****)malloc(sizeof(double****)*V1SpatialFrequencies);
    for(int j=0;j<V1SpatialFrequencies;j++){
      V1InternalWeights[i][j] = (double****)malloc(sizeof(double***)*V1TemporalFrequencies);
      for(int k=0;k<V1TemporalFrequencies;k++){
        V1InternalWeights[i][j][k] = (double***)malloc(sizeof(double**)*V1Orientations);
        for(int l=0;l<V1Orientations;l++){
          V1InternalWeights[i][j][k][l] = (double**)malloc(sizeof(double*)*V1SpatialFrequencies);
          for(int m=0;m<V1SpatialFrequencies;m++){
            V1InternalWeights[i][j][k][l][m] = (double*)malloc(sizeof(double)*V1TemporalFrequencies);
            for(int n=0;n<V1TemporalFrequencies;n++){
              V1InternalWeights[i][j][k][l][m][n] = V1WeightsFactor*orig.V1InternalWeights[i][j][k][l][m][n];
            }
          }
        }        
      }
    }
  }
  V1Neurons = orig.V1Neurons;
  MTTotalNeurons = orig.MTTotalNeurons;
  MTOrientations = orig.MTOrientations;
  MTSigma = orig.MTSigma;
  MTAperture = orig.MTAperture;
  MTAmplificationFactor = orig.MTAmplificationFactor;
  MTNeuronsPositions = orig.MTNeuronsPositions;
  MTNeurons = orig.MTNeurons;
  Faces = orig.Faces;
  ResultOrientation = orig.ResultOrientation;
  ResultMagnitude = orig.ResultMagnitude;
  ResultStdv = orig.ResultStdv;
  ResultFitting = orig.ResultFitting;
  ResultStdvFitting = orig.ResultStdvFitting;
  ObjectiveVector = orig.ObjectiveVector;
  NormalizedFitting = orig.NormalizedFitting;
  ResultCalculationElements = orig.ResultCalculationElements;
}

V1MTSimulator::~V1MTSimulator() {
  if(V1SpatialFrequenciesArray!=NULL){
    free(V1SpatialFrequenciesArray);
  }
  if(V1TemporalFrequenciesArray!=NULL){
    free(V1TemporalFrequenciesArray);
  }
  if(V1InternalWeights!=NULL){
    for(int i=0;i<V1Orientations;i++){
      for(int j=0;j<V1SpatialFrequencies;j++){
        for(int k=0;k<V1TemporalFrequencies;k++){
          for(int l=0;l<V1Orientations;l++){
            for(int m=0;m<V1SpatialFrequencies;m++){
              free(V1InternalWeights[i][j][k][l][m]);
            }
            free(V1InternalWeights[i][j][k][l]);
          }
          free(V1InternalWeights[i][j][k]);
        }
        free(V1InternalWeights[i][j]);
      }
      free(V1InternalWeights[i]);
    }
    free(V1InternalWeights);
  }
}

V1MTSimulator  &V1MTSimulator::operator=(const V1MTSimulator V1MTSimulatorP){
  //Simulator Definitions
    TotalSteps = V1MTSimulatorP.TotalSteps;
    DifferentialStep = V1MTSimulatorP.DifferentialStep;
    DynamicTau = V1MTSimulatorP.DynamicTau;
    SimulationState = V1MTSimulatorP.SimulationState;
  //V1 Description
    V1TotalNeurons = V1MTSimulatorP.V1TotalNeurons;
    V1NeuronsPositions = V1MTSimulatorP.V1NeuronsPositions;
    V1Orientations = V1MTSimulatorP.V1Orientations;
    V1SpatialFrequencies = V1MTSimulatorP.V1SpatialFrequencies;
    V1TemporalFrequencies = V1MTSimulatorP.V1TemporalFrequencies;
    V1Radius = V1MTSimulatorP.V1Radius;
    V1ConductanceLeak = V1MTSimulatorP.V1ConductanceLeak;
    V1InhibitionFactor = V1MTSimulatorP.V1InhibitionFactor;
    V1WeightsFactor = V1MTSimulatorP.V1WeightsFactor;
    V1ExitatoryFactor = V1MTSimulatorP.V1ExitatoryFactor;
  //Array Filling
    V1SpatialFrequenciesArray = (double*)malloc(sizeof(double)*V1SpatialFrequencies);
    V1SpatialFrequenciesArray[0] = V1MTSimulatorP.V1SpatialFrequenciesArray[0];
    V1TemporalFrequenciesArray = (double*)malloc(sizeof(double)*V1TemporalFrequencies);
    V1TemporalFrequenciesArray[0] = V1MTSimulatorP.V1TemporalFrequenciesArray[0];
    for(int i=1;i<V1SpatialFrequencies;i++){
      V1SpatialFrequenciesArray[i] = V1SpatialFrequenciesArray[i-1]*2;
    }
    for(int i=1;i<V1TemporalFrequencies;i++){
      V1TemporalFrequenciesArray[i] = V1TemporalFrequenciesArray[i-1]*2;
    }
    V1InternalWeights = (double******)malloc(sizeof(double*****)*V1Orientations);
    for(int i=0;i<V1Orientations;i++){
      V1InternalWeights[i] = (double*****)malloc(sizeof(double****)*V1SpatialFrequencies);
      for(int j=0;j<V1SpatialFrequencies;j++){
        V1InternalWeights[i][j] = (double****)malloc(sizeof(double***)*V1TemporalFrequencies);
        for(int k=0;k<V1TemporalFrequencies;k++){
          V1InternalWeights[i][j][k] = (double***)malloc(sizeof(double**)*V1Orientations);
          for(int l=0;l<V1Orientations;l++){
            V1InternalWeights[i][j][k][l] = (double**)malloc(sizeof(double*)*V1SpatialFrequencies);
            for(int m=0;m<V1SpatialFrequencies;m++){
              V1InternalWeights[i][j][k][l][m] = (double*)malloc(sizeof(double)*V1TemporalFrequencies);
              for(int n=0;n<V1TemporalFrequencies;n++){
                V1InternalWeights[i][j][k][l][m][n] = V1WeightsFactor*V1MTSimulatorP.V1InternalWeights[i][j][k][l][m][n];
              }
            }
          }        
        }
      }
    }    
  //MT description
    MTTotalNeurons = V1MTSimulatorP.MTTotalNeurons;
    MTNeuronsPositions = V1MTSimulatorP.MTNeuronsPositions;
    MTOrientations = V1MTSimulatorP.MTOrientations;
    MTSigma = V1MTSimulatorP.MTSigma;
    MTAperture = V1MTSimulatorP.MTAperture;
    MTAmplificationFactor = V1MTSimulatorP.MTAmplificationFactor;
  //Building filter responses
    Faces = V1MTSimulatorP.Faces;
  //Basic SetUp
    V1Neurons.reserve(V1TotalNeurons);
    MTNeurons.reserve(MTTotalNeurons);
  //Results
    ResultCalculationElements = V1MTSimulatorP.ResultCalculationElements;
    ResultOrientation = V1MTSimulatorP.ResultOrientation;
    ResultMagnitude = V1MTSimulatorP.ResultMagnitude;
    ResultStdv = V1MTSimulatorP.ResultStdv;
    ResultFitting = V1MTSimulatorP.ResultFitting;
    ResultStdvFitting = V1MTSimulatorP.ResultStdvFitting;
    NormalizedFitting = V1MTSimulatorP.NormalizedFitting;
    ObjectiveVector = V1MTSimulatorP.ObjectiveVector;
    Sensibility = V1MTSimulatorP.Sensibility;
  //Return
    return *this;
}

//------------------------------------------------------------------------------
//Constructors------------------------------------------------------------------
//------------------------------------------------------------------------------

V1MTSimulator::V1MTSimulator(int TotalStepsP, FilterResponse ExternalFilterP, int V1TotalNeuronsP, double** V1NeuronsPositionsP, int MTTotalNeuronsP, double** MTNeuronsPositionsP, int V1OrientationsP, int V1SpatialFrequenciesP, int V1TemporalFrequenciesP, double* V1InternalWeightsP, bool NormalizeP, double* ObjectiveVectorP, int ResultCalculationElementsP, double* SensibilityP){
  //Simulator Definitions
    TotalSteps = TotalStepsP;
    DifferentialStep = 0.005;
    DynamicTau = 1;
    SimulationState = 0;
    //0  Created
    //1  Net Builded
    //2  Weights Calculated
    //3  Simulated
  //V1 Description
    V1TotalNeurons = V1TotalNeuronsP;
    V1NeuronsPositions = V1NeuronsPositionsP;
    V1Orientations = V1OrientationsP;
    V1SpatialFrequencies = V1SpatialFrequenciesP;
    V1TemporalFrequencies = V1TemporalFrequenciesP;
    V1Radius = 0.1;
    V1ConductanceLeak = -0.1;
    V1InhibitionFactor = 0.8;
    V1WeightsFactor = 1000;
    V1ExitatoryFactor = 1 - V1InhibitionFactor;
    V1SpatialFrequenciesArray = (double*)malloc(sizeof(double)*V1SpatialFrequencies);
    V1SpatialFrequenciesArray[0] = 0.025;
    V1TemporalFrequenciesArray = (double*)malloc(sizeof(double)*V1TemporalFrequencies);
    V1TemporalFrequenciesArray[0] = 1.00;
    V1InternalWeights = (double******)malloc(sizeof(double*****)*V1Orientations);
    int InternalCounter = 0;
    for(int i=0;i<V1Orientations;i++){
      V1InternalWeights[i] = (double*****)malloc(sizeof(double****)*V1SpatialFrequencies);
      for(int j=0;j<V1SpatialFrequencies;j++){
        V1InternalWeights[i][j] = (double****)malloc(sizeof(double***)*V1TemporalFrequencies);
        for(int k=0;k<V1TemporalFrequencies;k++){
          V1InternalWeights[i][j][k] = (double***)malloc(sizeof(double**)*V1Orientations);
          for(int l=0;l<V1Orientations;l++){
            V1InternalWeights[i][j][k][l] = (double**)malloc(sizeof(double*)*V1SpatialFrequencies);
            for(int m=0;m<V1SpatialFrequencies;m++){
              V1InternalWeights[i][j][k][l][m] = (double*)malloc(sizeof(double)*V1TemporalFrequencies);
              for(int n=0;n<V1TemporalFrequencies;n++){
                V1InternalWeights[i][j][k][l][m][n] = V1WeightsFactor*V1InternalWeightsP[InternalCounter++];
              }
            }
          }        
        }
      }
    }    
  //MT description
    MTTotalNeurons = MTTotalNeuronsP;
    MTNeuronsPositions = MTNeuronsPositionsP;
    MTOrientations = 8;
    MTSigma = 2.0/3.0;                //After gets multiplied for V1Radius
    MTAperture = PI/4.0+0.1;          //Pi/4 + Guard Band
    MTAmplificationFactor = 1;
  //Array Filling
    for(int i=1;i<V1SpatialFrequencies;i++){
      V1SpatialFrequenciesArray[i] = V1SpatialFrequenciesArray[i-1]*2;
    }
    for(int i=1;i<V1TemporalFrequencies;i++){
      V1TemporalFrequenciesArray[i] = V1TemporalFrequenciesArray[i-1]*2;
    }
  //Building filter responses
    Faces = ExternalFilterP;
  //Basic SetUp
    V1Neurons.reserve(V1TotalNeurons);
    MTNeurons.reserve(MTTotalNeurons);
  //Results
    ResultCalculationElements = ResultCalculationElementsP;
    ResultOrientation = 0;
    ResultMagnitude = 0;
    ResultStdv = 0;
    ResultFitting = 0;
    ResultStdvFitting = 0;
    NormalizedFitting = NormalizeP;
    ObjectiveVector = ObjectiveVectorP;
    Sensibility = SensibilityP;
}

//------------------------------------------------------------------------------
//Parameter Static Operations---------------------------------------------------
//------------------------------------------------------------------------------

void V1MTSimulator::BuildV1MTNet(){
  //Creating the V1Neurons List
    double Radius;
    for(int i=0;i<V1TotalNeurons;i++){
      V1Neuron Temp(TotalSteps, V1Orientations, V1SpatialFrequencies, V1TemporalFrequencies, V1NeuronsPositions[i][0], V1NeuronsPositions[i][1], V1ConductanceLeak, V1InhibitionFactor, V1ExitatoryFactor);
      Temp.AddFilterResponseLink(&Faces);
      Temp.SetInternalWeightsV1V1(V1InternalWeights);
      Temp.SetSpatialFrequenciesReference(V1SpatialFrequenciesArray);
      Temp.SetTemporalFrequenciesReference(V1TemporalFrequenciesArray);
      V1Neurons.push_back(Temp);
      Radius = sqrt(V1NeuronsPositions[i][0]*V1NeuronsPositions[i][0]+V1NeuronsPositions[i][1]*V1NeuronsPositions[i][1]);
      V1Radius = (V1Radius<Radius)?Radius:V1Radius;
    }
    MTSigma *= V1Radius; //Recalculating according to measured V1Radius
    //Creating the MTNeurons List
    for(int i=0;i<MTTotalNeurons;i++){
      MTNeurons.push_back(MTNeuron(TotalSteps, MTOrientations, MTNeuronsPositions[i][0], MTNeuronsPositions[i][0]));
    }
    //Linking V1Neurons
    for(int i=0;i<(int)V1Neurons.size();i++){
      for(int j=0;j<(int)V1Neurons.size();j++){
        V1Neurons[i].AddV1Link(V1Neurons[j]);
      }
    }
  //Linking V1-MT Neurons
    for(int i=0;i<(int)MTNeurons.size();i++){
      for(int j=0;j<(int)V1Neurons.size();j++){
        MTNeurons[i].AddV1Link(V1Neurons[j]);
      }
    }
    SimulationState++;
}

void V1MTSimulator::CalculateNetWeights(){
  //Calculating V1 Weights
    for(int i=0;i<(int)V1Neurons.size();i++){
      V1Neurons[i].CalculateCombinedWeights();
    }
  //Calculating MT Weights
    for(int i=0;i<(int)MTNeurons.size();i++){
      MTNeurons[i].CalculateV1MTConnectionWeights(MTSigma, MTAmplificationFactor, MTAperture);
    }
    SimulationState++;
}

//------------------------------------------------------------------------------
//Simulation Operations---------------------------------------------------------
//------------------------------------------------------------------------------

void V1MTSimulator::Simulate(){
  for(int i=0;i<TotalSteps-1;i++){
    //Calculate V1 Activations
    for(int j=0;j<(int)V1Neurons.size();j++){
      V1Neurons[j].CalculateDActivation();
      V1Neurons[j].CalculateActivation(DifferentialStep/DynamicTau);
    }
    //Calculate MT Activation
    for(int j=0;j<(int)MTNeurons.size();j++){
      MTNeurons[j].CalculateActivation();
    }
    Faces.Step();
  }
  ResultOrientation = CalculateSimulationResultOrientation();;
  ResultMagnitude = CalculateSimulationResultMagnitude();
  ResultStdv = CalculateSimulationResultOrientationStdv();
  ResultFitting = CalculateSimulationResultFitting();
  ResultStdvFitting = CalculateSimulationResultStdvFitting();
  SimulationState++;
}

//------------------------------------------------------------------------------
//Results Operations------------------------------------------------------------
//------------------------------------------------------------------------------  

double V1MTSimulator::CalculateSimulationResultOrientation(){
  double XContribution = 0;
  double YContribution = 0;
  for(int i=0;i<ResultCalculationElements;i++){
    for(int j=0;j<(int)MTNeurons.size();j++){
      for(int k=0;k<MTOrientations;k++){
        XContribution += MTNeurons[j].GetActivation()[i+TotalSteps-ResultCalculationElements-1][k]*cos(((double)-k)*2*PI/MTOrientations);
        YContribution += MTNeurons[j].GetActivation()[i+TotalSteps-ResultCalculationElements-1][k]*sin(((double)-k)*2*PI/MTOrientations);
      }
    }
  }
  return atan2(YContribution,XContribution);
}

double V1MTSimulator::CalculateSimulationResultMagnitude(){
  double XContribution = 0;
  double YContribution = 0;
  for(int i=0;i<ResultCalculationElements;i++){
    for(int j=0;j<(int)MTNeurons.size();j++){
      for(int k=0;k<MTOrientations;k++){
        XContribution += MTNeurons[j].GetActivation()[i+TotalSteps-ResultCalculationElements-1][k]*cos(((double)-k)*2*PI/MTOrientations);
        YContribution += MTNeurons[j].GetActivation()[i+TotalSteps-ResultCalculationElements-1][k]*sin(((double)-k)*2*PI/MTOrientations);
      }
    }
  }
  XContribution /= 5.0;
  YContribution /= 5.0;
  return sqrt(XContribution*XContribution+YContribution*YContribution);
}

double V1MTSimulator::CalculateSimulationResultOrientationStdv(){
  double* Temp = (double*)malloc(sizeof(double)*ResultCalculationElements);
  double XContribution = 0;
  double YContribution = 0;
  double AngleAvg = 0;
  double StdvAccumulation = 0;
  for(int i=0;i<ResultCalculationElements;i++){
    Temp[i] = 0;
    for(int j=0;j<(int)MTNeurons.size();j++){
      XContribution = 0;
      YContribution = 0;
      for(int k=0;k<MTOrientations;k++){
        XContribution += MTNeurons[j].GetActivation()[i+TotalSteps-ResultCalculationElements-1][k]*cos(((double)-k)*2*PI/MTOrientations);
        YContribution += MTNeurons[j].GetActivation()[i+TotalSteps-ResultCalculationElements-1][k]*sin(((double)-k)*2*PI/MTOrientations);
      }
      Temp[i] += atan2(YContribution,XContribution);
    }
    AngleAvg += (Temp[i]/(double)MTNeurons.size())/(double)ResultCalculationElements;
  }
  for(int i=0;i<ResultCalculationElements;i++){
    StdvAccumulation += (AngleAvg-Temp[i])*(AngleAvg-Temp[i]);
  }
  free(Temp);
  return sqrt(StdvAccumulation/(double)ResultCalculationElements);
}

double V1MTSimulator::CalculateSimulationResultFitting(){
  double** Fitting = (double**)malloc(sizeof(double)*(ResultCalculationElements));
  for(int i=0;i<ResultCalculationElements;i++){
    Fitting[i] = (double*)malloc(sizeof(double)*(MTOrientations+1));
  }
  for(int i=0;i<ResultCalculationElements;i++){
    double BasePonderation = 0.1;
    double Max = 0;
    //Normalization
    for(int j=0;j<MTOrientations;j++){
      Fitting[i][j] = MTNeurons[0].GetActivation()[TotalSteps-ResultCalculationElements+i-1][j];
      Max = (Max<Fitting[i][j])?Fitting[i][j]:Max;
    }
    for(int j=0;j<MTOrientations;j++){
      if(NormalizedFitting){
        Fitting[i][j] /= Max;
      }
    }
    //Fitting
    Fitting[i][MTOrientations] = 0;
    for(int j=0;j<MTOrientations;j++){
      double TFitting;
      for(int k=0;k<MTOrientations;k++){
        TFitting = (Fitting[i][j]-Fitting[i][(j+k)%MTOrientations]) - (ObjectiveVector[j]-ObjectiveVector[(j+k)%MTOrientations]);
        if(k==0){
          TFitting = (Fitting[i][j] - ObjectiveVector[j]);
        }
        TFitting = (TFitting>0)?TFitting:-TFitting;
        TFitting += 1;
        TFitting = pow(TFitting,Sensibility[j]);
        TFitting -= 1;
        Fitting[i][MTOrientations] += TFitting/(ObjectiveVector[j]*(1-BasePonderation)+BasePonderation);
      }
    }
  }
  double AvgFitting = 0;
  for(int i=0;i<ResultCalculationElements;i++){
    AvgFitting += Fitting[i][MTOrientations]/(double)ResultCalculationElements;
    free(Fitting[i]);
  }
  free(Fitting);
  return AvgFitting;
}

double V1MTSimulator::CalculateSimulationResultStdvFitting(){
  double** Fitting = (double**)malloc(sizeof(double)*(ResultCalculationElements));
  for(int i=0;i<ResultCalculationElements;i++){
    Fitting[i] = (double*)malloc(sizeof(double)*(MTOrientations+1));
  }
  for(int i=0;i<ResultCalculationElements;i++){
    double Max = 0;
    for(int j=0;j<MTOrientations;j++){
      Fitting[i][j] = MTNeurons[0].GetActivation()[TotalSteps-ResultCalculationElements+i-1][j];
      Max = (Max<Fitting[i][j])?Fitting[i][j]:Max;
    }
    Fitting[i][MTOrientations] = 0;
    for(int j=0;j<MTOrientations;j++){
      if(NormalizedFitting){
          Fitting[i][j] /= Max;
      }
      double TFitting = Fitting[i][j] - ObjectiveVector[j];
      Fitting[i][MTOrientations] += TFitting*TFitting;
    }
  }
  double AvgFitting = 0;
  for(int i=0;i<ResultCalculationElements;i++){
    AvgFitting += Fitting[i][MTOrientations]/(double)ResultCalculationElements;
  }
  double StdFitting = 0;
  for(int i=0;i<ResultCalculationElements;i++){
    StdFitting += (Fitting[i][MTOrientations]-AvgFitting)*(Fitting[i][MTOrientations]-AvgFitting)/(double)ResultCalculationElements;
    free(Fitting[i]);
  }
  free(Fitting);
  return sqrt(StdFitting);
}

double* V1MTSimulator::GetSimulationResultsCondensed(){
  double* ResultArray = (double*)malloc(sizeof(double)*5);
  ResultArray[0] = ResultOrientation;
  ResultArray[1] = ResultMagnitude;
  ResultArray[2] = ResultStdv;
  ResultArray[3] = ResultFitting;
  ResultArray[4] = ResultStdvFitting;
  return ResultArray;
}

double** V1MTSimulator::GetSimulationResult(){
  double** ToReturn = (double**)malloc(sizeof(double*)*TotalSteps);
  for(int i=0;i<TotalSteps;i++){
    ToReturn[i] = (double*)malloc(sizeof(double)*MTOrientations);
    for(int j=0;j<(int)MTNeurons.size();j++){
      for(int k=0;k<MTOrientations;k++){
        ToReturn[i][k] = MTNeurons[j].GetActivation()[i][k];
      }
    }
  }
  return ToReturn;
}

int V1MTSimulator::GetTotalSteps(){
  return TotalSteps;
}
