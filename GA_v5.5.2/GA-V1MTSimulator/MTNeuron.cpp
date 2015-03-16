/* 
 * File:   MTNeuron.cpp
 * Author: Pedro F. Toledo <pedrotoledocorrea@gmail.com>
 * 
 * Created on November 3, 2012, 11:56 AM
 */

#include "MTNeuron.h" 

#define PI 3.1415926
#define free(p) free(p);p=NULL;

//------------------------------------------------------------------------------
//Standard methods--------------------------------------------------------------
//------------------------------------------------------------------------------  
MTNeuron::MTNeuron(int TimeStepsP, int OrientationsP, double xP, double yP){
  x = xP;
  y = yP;
  Activation = (double**)malloc(sizeof(double*)*TimeStepsP);
  for(int i=0;i<TimeStepsP;i++){
    Activation[i] = (double*)malloc(sizeof(double)*OrientationsP);
    for(int j=0;j<OrientationsP;j++){
      Activation[i][j] = 0;
    }
  }
  TotalTimeSteps = TimeStepsP;
  V1LinksTotal = NULL;
  V1MTConnectionWeights = NULL;
  LinkedV1Neurons = 0;
  CurrentTimeStep = 0;
  Orientations = OrientationsP;
}
MTNeuron::~MTNeuron() {
  for(int i=0;i<TotalTimeSteps;i++){
    free(Activation[i]);
  }
  free(Activation);
  if(V1MTConnectionWeights != NULL){
    for(int i=0;i<Orientations;i++){
      for(int j=0;j<LinkedV1Neurons;j++){
        free(V1MTConnectionWeights[i][j]);
      }
      free(V1MTConnectionWeights[i]);
    }
    free(V1MTConnectionWeights);
  }
  if(V1LinksTotal != NULL){
    free(V1LinksTotal);
  }
}
//------------------------------------------------------------------------------
//Constructors------------------------------------------------------------------
//------------------------------------------------------------------------------
MTNeuron::MTNeuron(const MTNeuron& orig){
  Orientations = orig.Orientations;
  CurrentTimeStep = orig.CurrentTimeStep;
  LinkedV1Neurons = orig.LinkedV1Neurons;
  TotalTimeSteps = orig.TotalTimeSteps;
  x = orig.x;
  y = orig.y;
  V1LinksTotal = NULL;
  if(orig.V1LinksTotal!=NULL){
    V1LinksTotal = (V1Neuron**)malloc(sizeof(V1Neuron*)*LinkedV1Neurons);
    for(int i=0;i<LinkedV1Neurons;i++){
      V1LinksTotal[i] = orig.V1LinksTotal[i];
    }
  }
  V1MTConnectionWeights = NULL;
  if(orig.V1MTConnectionWeights != NULL){
    V1MTConnectionWeights = (double***)malloc(sizeof(double**)*Orientations);
    for(int i=0;i<Orientations;i++){
      V1MTConnectionWeights[i] = (double**)malloc(sizeof(double*)*LinkedV1Neurons);
      for(int j=0;j<LinkedV1Neurons;j++){
        V1MTConnectionWeights[i][j] = (double*)malloc(sizeof(double)*V1LinksTotal[j]->GetOrientations());
        for(int k=0;k<V1LinksTotal[j]->GetOrientations();k++){
          V1MTConnectionWeights[i][j][k] = orig.V1MTConnectionWeights[i][j][k];
        }
      }
    }
  }
  Activation = (double**)malloc(sizeof(double*)*TotalTimeSteps);
  for(int i=0;i<TotalTimeSteps;i++){
    Activation[i] = (double*)malloc(sizeof(double)*Orientations);
    for(int j=0;j<Orientations;j++){
      Activation[i][j] = orig.Activation[i][j];
    }
  }
}
//------------------------------------------------------------------------------
//Parameter Static Operations---------------------------------------------------
//------------------------------------------------------------------------------
void MTNeuron::AddV1Link(V1Neuron &Neuron){
  V1Neuron **TemporalTotal = NULL;
  TemporalTotal = (V1Neuron**)malloc(sizeof(V1Neuron*)*(LinkedV1Neurons+1));
  for(int i=0;i<LinkedV1Neurons;i++){
    TemporalTotal[i] = V1LinksTotal[i];
  }
  TemporalTotal[LinkedV1Neurons] = &Neuron;
  if(V1LinksTotal!=NULL){
    free(V1LinksTotal);
  }
  V1LinksTotal = TemporalTotal;
  LinkedV1Neurons++;
}
void MTNeuron::CalculateV1MTConnectionWeights(double SigmaP, double AmplificationFactorP, double OrientationRangeP){
  double TemporalDistance;
  double Angle;
  double CosAperture = 5.33648681640625; //Manually Trained
  V1MTConnectionWeights = (double***)malloc(sizeof(double**)*Orientations);
  for(int i=0;i<Orientations;i++){
    V1MTConnectionWeights[i] = (double**)malloc(sizeof(double*)*LinkedV1Neurons);
    for(int j=0;j<LinkedV1Neurons;j++){
      TemporalDistance = sqrt((x-V1LinksTotal[j]->GetX())*(x-V1LinksTotal[j]->GetX())+(y-V1LinksTotal[j]->GetY())*(y-V1LinksTotal[j]->GetY()));
      V1MTConnectionWeights[i][j] = (double*)malloc(sizeof(double)*V1LinksTotal[j]->GetOrientations());
      for(int k=0;k<V1LinksTotal[j]->GetOrientations();k++){
        Angle = i*2*PI/(double)Orientations;
        Angle -= k*2*PI/(double)V1LinksTotal[j]->GetOrientations();
        Angle = (Angle<0)?-Angle:Angle;
        Angle = (Angle>=PI)?2*PI-Angle:Angle;
        if(Angle <= OrientationRangeP || Angle >= PI-OrientationRangeP){
          double CosResult = cos(Angle);
          CosResult = (CosResult<0)?-CosResult:CosResult;
          CosResult = pow(CosResult,CosAperture);
          CosResult *= cos(Angle);
          V1MTConnectionWeights[i][j][k] = AmplificationFactorP*exp(-(TemporalDistance)/(2*SigmaP*SigmaP))*CosResult;
        }
        else{
          V1MTConnectionWeights[i][j][k] = 0;
        }
      }
    }
  }
}
//------------------------------------------------------------------------------
//Simulation Operations---------------------------------------------------------
//------------------------------------------------------------------------------
void MTNeuron::CalculateActivation(){
  for(int i=0;i<Orientations;i++){
    for(int j=0;j<LinkedV1Neurons;j++){
      for(int k=0;k<V1LinksTotal[j]->GetOrientations();k++){
        double Temporal;
        Temporal = V1LinksTotal[j]->GetMTContribution(k);
        Temporal = (Temporal>0)?Temporal:0;
        Activation[CurrentTimeStep][i] += Temporal*V1MTConnectionWeights[i][j][k];
      }
    }
    Activation[CurrentTimeStep][i] = (Activation[CurrentTimeStep][i] < 0)?0:Activation[CurrentTimeStep][i];
  }
  CurrentTimeStep++;
}
//------------------------------------------------------------------------------
//Results Operations------------------------------------------------------------
//------------------------------------------------------------------------------
double** MTNeuron::GetActivation(){
  return Activation;
}
