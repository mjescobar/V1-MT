/* 
 * File:   V1Neuron.cpp
 * Author: Pedro F. Toledo <pedrotoledocorrea@gmail.com>
 * 
 * Created on October 29, 2012, 5:20 PM
 */

#include "V1Neuron.h"

#define free(p) free(p);p=NULL;

//------------------------------------------------------------------------------
//Standard methods--------------------------------------------------------------
//------------------------------------------------------------------------------  
V1Neuron::V1Neuron(const V1Neuron& orig) {
  ConductanceLeak = orig.ConductanceLeak;
  InhibitionFactor = orig.InhibitionFactor;
  ExitatoryFactor = orig.ExitatoryFactor;
  CurrentTime = orig.CurrentTime;
  MaxTimeSteps = orig.MaxTimeSteps;
  Orientations = orig.Orientations;
  SpatialFrequencies = orig.SpatialFrequencies;
  TemporalFrequencies = orig.TemporalFrequencies;
  x = orig.x;
  y = orig.y;
  LinkedV1Neurons = orig.LinkedV1Neurons;
  SpatialFrequenciesReference = (double*)malloc(sizeof(double)*SpatialFrequencies);
  for(int i=0;i<SpatialFrequencies;i++){
    SpatialFrequenciesReference[i] = orig.SpatialFrequenciesReference[i];
  }
  TemporalFrequenciesReference = (double*)malloc(sizeof(double)*TemporalFrequencies);
  for(int i=0;i<TemporalFrequencies;i++){
    TemporalFrequenciesReference[i] = orig.TemporalFrequenciesReference[i];
  }
  InternalWeightsV1 = orig.InternalWeightsV1;
  CombinedWeights = NULL;
  if(orig.CombinedWeights != NULL){
    CombinedWeights = (double****)malloc(sizeof(double***)*Orientations);
    for(int i=0;i<Orientations;i++){
      CombinedWeights[i] = (double***)malloc(sizeof(double**)*SpatialFrequencies);
      for(int j=0;j<SpatialFrequencies;j++){
        CombinedWeights[i][j] = (double**)malloc(sizeof(double*)*TemporalFrequencies);
        for(int k=0;k<TemporalFrequencies;k++){
          CombinedWeights[i][j][k] = (double*)malloc(sizeof(double)*LinkedV1Neurons);
          for(int l=0;l<LinkedV1Neurons;l++){
            if(V1Links[i][j][k][l] != NULL){
              CombinedWeights[i][j][k][l] = orig.CombinedWeights[i][j][k][l];
            }
          }
        }
      }
    }
  }
  ExternalExitation = orig.ExternalExitation;
  V1LinksTotal = NULL;
  if(orig.V1LinksTotal != NULL){
    V1LinksTotal = (V1Neuron**)malloc(sizeof(V1Neuron*)*LinkedV1Neurons);
    for(int i=0;i<LinkedV1Neurons;i++){
      V1LinksTotal[i] = orig.V1LinksTotal[i];
    }
  }
  V1Links = NULL;
  if(orig.V1Links != NULL){
    V1Links = (V1Neuron*****)malloc(sizeof(V1Neuron****)*Orientations);
    for(int i=0;i<Orientations;i++){
      V1Links[i] = (V1Neuron****)malloc(sizeof(V1Neuron***)*SpatialFrequencies);
      for(int j=0;j<SpatialFrequencies;j++){
        V1Links[i][j] = (V1Neuron***)malloc(sizeof(V1Neuron**)*TemporalFrequencies);
        for(int k=0;k<TemporalFrequencies;k++){
          V1Links[i][j][k] = (V1Neuron**)malloc(sizeof(V1Neuron*)*(LinkedV1Neurons+1));
          for(int l=0;l<LinkedV1Neurons+1;l++){
            V1Links[i][j][k][l] = orig.V1Links[i][j][k][l];
          }
        }
      }
    }
  }
  Activation = (double****)malloc(sizeof(double***)*MaxTimeSteps);
  ActivationNonLinearity = (double****)malloc(sizeof(double***)*MaxTimeSteps);
  DActivation = (double****)malloc(sizeof(double***)*MaxTimeSteps);
  SumActivation = (double**)malloc(sizeof(double*)*MaxTimeSteps);
  for(int i=0;i<MaxTimeSteps;i++){
    Activation[i] = (double***)malloc(sizeof(double**)*Orientations);
    ActivationNonLinearity[i] = (double***)malloc(sizeof(double**)*Orientations);
    DActivation[i] = (double***)malloc(sizeof(double**)*Orientations);
    SumActivation[i] = (double*)malloc(sizeof(double)*Orientations);
    for(int j=0;j<Orientations;j++){
      Activation[i][j] = (double**)malloc(sizeof(double*)*SpatialFrequencies);
      ActivationNonLinearity[i][j] = (double**)malloc(sizeof(double*)*SpatialFrequencies);
      DActivation[i][j] = (double**)malloc(sizeof(double*)*SpatialFrequencies);
      SumActivation[i][j] = orig.SumActivation[i][j];
      for(int k=0;k<SpatialFrequencies;k++){
        Activation[i][j][k] = (double*)malloc(sizeof(double)*TemporalFrequencies);
        ActivationNonLinearity[i][j][k] = (double*)malloc(sizeof(double)*TemporalFrequencies);
        DActivation[i][j][k] = (double*)malloc(sizeof(double)*TemporalFrequencies);
        for(int l=0;l<TemporalFrequencies;l++){
          Activation[i][j][k][l] = orig.Activation[i][j][k][l];
          ActivationNonLinearity[i][j][k][l] = orig.ActivationNonLinearity[i][j][k][l];
          DActivation[i][j][k][l] = orig.DActivation[i][j][k][l];
        }
      }
    }
  }
}

V1Neuron::~V1Neuron() {
  free(SpatialFrequenciesReference);
  free(TemporalFrequenciesReference);
  if(CombinedWeights != NULL){
    for(int i=0;i<Orientations;i++){
      for(int j=0;j<SpatialFrequencies;j++){
        for(int k=0;k<TemporalFrequencies;k++){
          free(CombinedWeights[i][j][k]);
        }
        free(CombinedWeights[i][j]);
      }
      free(CombinedWeights[i]);
    }
    free(CombinedWeights);
  }
  if(V1LinksTotal != NULL){
    free(V1LinksTotal);
  }    
  if(V1Links != NULL){
    for(int i=0;i<Orientations;i++){
      for(int j=0;j<SpatialFrequencies;j++){
        for(int k=0;k<TemporalFrequencies;k++){
          free(V1Links[i][j][k]);
        }
        free(V1Links[i][j]);
      }
      free(V1Links[i]);
    }
    free(V1Links);
    free(V1LinksTotal);
  }
  for(int i=0;i<MaxTimeSteps;i++){
    for(int j=0;j<Orientations;j++){
      for(int k=0;k<SpatialFrequencies;k++){
        free(Activation[i][j][k]);
        free(ActivationNonLinearity[i][j][k]);
        free(DActivation[i][j][k]);
      }
      free(Activation[i][j]);
      free(ActivationNonLinearity[i][j]);
      free(DActivation[i][j]);
    }
    free(Activation[i]);
    free(ActivationNonLinearity[i]);
    free(DActivation[i]);
    free(SumActivation[i]);
  }
  free(Activation);
  free(ActivationNonLinearity);
  free(DActivation);
  free(SumActivation);
}

//------------------------------------------------------------------------------
//Constructors------------------------------------------------------------------
//------------------------------------------------------------------------------
V1Neuron::V1Neuron(int TimeStepsP, int OrientationsP, int SpatialFrequenciesP, int TemporalFrequenciesP, double xP, double yP, double V1ConductanceLeakP, double V1InhibitionFactorP, double V1ExitatoryFactorP){
  ConductanceLeak = V1ConductanceLeakP;
  InhibitionFactor = V1InhibitionFactorP;
  ExitatoryFactor = V1ExitatoryFactorP;
  CurrentTime = 0;
  MaxTimeSteps = TimeStepsP;
  Orientations = OrientationsP;
  SpatialFrequencies = SpatialFrequenciesP;
  TemporalFrequencies = TemporalFrequenciesP;
  x = xP;
  y = yP;
  LinkedV1Neurons = 0;
  SpatialFrequenciesReference = (double*)malloc(sizeof(double)*SpatialFrequencies);
  TemporalFrequenciesReference  = (double*)malloc(sizeof(double)*TemporalFrequencies);
  InternalWeightsV1 = NULL;
  CombinedWeights  = NULL;
  ExternalExitation = NULL;
  V1Links = NULL;
  V1LinksTotal = NULL;
  Activation = (double****)malloc(sizeof(double***)*TimeStepsP);
  ActivationNonLinearity = (double****)malloc(sizeof(double***)*TimeStepsP);
  DActivation = (double****)malloc(sizeof(double***)*TimeStepsP);
  SumActivation = (double**)malloc(sizeof(double*)*TimeStepsP);
  for(int i=0;i<TimeStepsP;i++){
    Activation[i] = (double***)malloc(sizeof(double**)*OrientationsP);
    ActivationNonLinearity[i] = (double***)malloc(sizeof(double**)*OrientationsP);
    DActivation[i] = (double***)malloc(sizeof(double**)*OrientationsP);
    SumActivation[i] = (double*)malloc(sizeof(double)*OrientationsP);
    for(int j=0;j<OrientationsP;j++){
      Activation[i][j] = (double**)malloc(sizeof(double*)*SpatialFrequenciesP);
      ActivationNonLinearity[i][j] = (double**)malloc(sizeof(double*)*SpatialFrequenciesP);
      DActivation[i][j] = (double**)malloc(sizeof(double*)*SpatialFrequenciesP);
      SumActivation[i][j] = 0;
      for(int k=0;k<SpatialFrequenciesP;k++){
        Activation[i][j][k] = (double*)malloc(sizeof(double)*TemporalFrequenciesP);
        ActivationNonLinearity[i][j][k] = (double*)malloc(sizeof(double)*TemporalFrequenciesP);
        DActivation[i][j][k] = (double*)malloc(sizeof(double)*TemporalFrequenciesP);
        for(int l=0;l<TemporalFrequenciesP;l++){
          Activation[i][j][k][l] = 0;
          ActivationNonLinearity[i][j][k][l] = 0;
          DActivation[i][j][k][l] = 0;
        }
      }
    }
  }
}

//------------------------------------------------------------------------------
//Parameter Static Operations---------------------------------------------------
//------------------------------------------------------------------------------

int V1Neuron::GetOrientations(){
  return Orientations;
}

void V1Neuron::SetInternalWeightsV1V1(double****** InternalWeightsV1P){
  InternalWeightsV1 = InternalWeightsV1P;
}

void V1Neuron::AddFilterResponseLink(FilterResponse* FacesP){
  ExternalExitation = FacesP;
}

void V1Neuron::SetSpatialFrequenciesReference(double* Reference){
  for(int i=0;i<SpatialFrequencies;i++){
    SpatialFrequenciesReference[i] = Reference[i];
  }
}

void V1Neuron::SetTemporalFrequenciesReference(double* Reference){
  for(int i=0;i<TemporalFrequencies;i++){
    TemporalFrequenciesReference[i] = Reference[i];
  }
}

double V1Neuron::GetX(){
  return x;
}

double V1Neuron::GetY(){
  return y;
}

double V1Neuron::CalculateDistanceWeightV1V1(double xP, double yP, int OrientationP, int SpatialFreqP, int TemporalFreqP){
  double Distance;
  double Sigma;
  double RFSize;
  Distance = sqrt((x-xP)*(x-xP)+(y-yP)*(y-yP));
  RFSize = 1.5*0.5622/SpatialFrequenciesReference[SpatialFreqP];
  Sigma = 2.2*RFSize/3.0;
  return exp(-(Distance)/(2*Sigma*Sigma));
}

//------------------------------------------------------------------------------
//Parameters Dynamic Operations-------------------------------------------------
//------------------------------------------------------------------------------

void V1Neuron::AddV1Link(V1Neuron &Neuron){
  V1Neuron  *****Temporal  = NULL;
  V1Neuron  **TemporalTotal = NULL;
  double    TempRFSize;
  double    TempDistance;
  Temporal = (V1Neuron*****)malloc(sizeof(V1Neuron****)*Orientations);
  for(int i=0;i<Orientations;i++){
    Temporal[i] = (V1Neuron****)malloc(sizeof(V1Neuron***)*SpatialFrequencies);
    for(int j=0;j<SpatialFrequencies;j++){
      Temporal[i][j] = (V1Neuron***)malloc(sizeof(V1Neuron**)*TemporalFrequencies);
      for(int k=0;k<TemporalFrequencies;k++){
        Temporal[i][j][k] = (V1Neuron**)malloc(sizeof(V1Neuron*)*(LinkedV1Neurons+1));
        for(int l=0;l<LinkedV1Neurons+1;l++){
          if(l==LinkedV1Neurons){
            Temporal[i][j][k][l] = NULL;
          }
          else{
            Temporal[i][j][k][l] = V1Links[i][j][k][l];
          }
        }
      }
    }
  }
  for(int i=0;i<Orientations;i++){
    for(int j=0;j<SpatialFrequencies;j++){
      for(int k=0;k<TemporalFrequencies;k++){
        for(int l=0;l<LinkedV1Neurons+1;l++){
          if(Temporal[i][j][k][l] == NULL){
            TempDistance = sqrt((Neuron.x-x)*(Neuron.x-x)+(Neuron.y-y)*(Neuron.y-y));
            TempRFSize = 1.1*1.5*0.5622/SpatialFrequenciesReference[j];
            if(TempDistance > TempRFSize){
              Temporal[i][j][k][l] = NULL;
            }
            else{
              Temporal[i][j][k][l] = &Neuron;
            }
            l = LinkedV1Neurons+1;
          }
        }
      }
    }
  }
  TemporalTotal = (V1Neuron**)malloc(sizeof(V1Neuron*)*(LinkedV1Neurons+1));
  for(int i=0;i<LinkedV1Neurons;i++){
    TemporalTotal[i] = V1LinksTotal[i];
  }
  TemporalTotal[LinkedV1Neurons] = &Neuron;
  if(V1Links != NULL){
    for(int i=0;i<Orientations;i++){
      for(int j=0;j<SpatialFrequencies;j++){
        for(int k=0;k<TemporalFrequencies;k++){
          free(V1Links[i][j][k]);
        }
        free(V1Links[i][j]);
      }
      free(V1Links[i]);
    }  
    free(V1Links);
    free(V1LinksTotal);
  }
  V1Links = Temporal;
  V1LinksTotal = TemporalTotal;
  LinkedV1Neurons++;
}

void V1Neuron::CalculateCombinedWeights(){
  int ConnectedNeurons = 1;
  CombinedWeights = (double****)malloc(sizeof(double***)*Orientations);
  for(int i=0;i<Orientations;i++){
    CombinedWeights[i] = (double***)malloc(sizeof(double**)*SpatialFrequencies);
    for(int j=0;j<SpatialFrequencies;j++){
      CombinedWeights[i][j] = (double**)malloc(sizeof(double*)*TemporalFrequencies);
      for(int k=0;k<TemporalFrequencies;k++){
        CombinedWeights[i][j][k] = (double*)malloc(sizeof(double)*LinkedV1Neurons);
        for(int l=0;l<LinkedV1Neurons;l++){
          if(V1Links[i][j][k][l] != NULL){
            CombinedWeights[i][j][k][l] = CalculateDistanceWeightV1V1(V1Links[i][j][k][l]->x,V1Links[i][j][k][l]->y,i,j,k);
            ConnectedNeurons++;
          }
          else{
            l = LinkedV1Neurons;
          }
        }
      }
    }
  }
  for(int i=0;i<Orientations;i++){
    for(int j=0;j<SpatialFrequencies;j++){
      for(int k=0;k<TemporalFrequencies;k++){
        for(int l=0;l<LinkedV1Neurons;l++){
          if(V1Links[i][j][k][l] != NULL){
            CombinedWeights[i][j][k][l] /= (double)ConnectedNeurons;
          }
          else{
            l = LinkedV1Neurons;
          }
        }
      }
    }
  }
}

void V1Neuron::CalculateDActivation(){
  double Temporal;
  for(int i=0;i<Orientations;i++){
    for(int j=0;j<SpatialFrequencies;j++){
      for(int k=0;k<TemporalFrequencies;k++){
        DActivation[CurrentTime+1][i][j][k] = ExitatoryFactor*ExternalExitation->GetCurrentArray()[i][j][k];
        Temporal = 0;
        for(int l=0;l<LinkedV1Neurons;l++){
          if(V1Links[i][j][k][l] != NULL){
            for(int m=0;m<Orientations;m++){      
              for(int n=0;n<SpatialFrequencies;n++){
                for(int o=0;o<TemporalFrequencies;o++){
                  Temporal += InternalWeightsV1[i][j][k][m][n][o]*CombinedWeights[m][n][o][l]*ExternalExitation->GetCurrentArray()[m][n][o];
                }
              }
            }
          }
          else{
            l = LinkedV1Neurons;
          }
        }
        DActivation[CurrentTime+1][i][j][k] = DActivation[CurrentTime+1][i][j][k]/(1+InhibitionFactor*Temporal);
      }
    }
  }
}

void V1Neuron::CalculateActivation(double StepP){
  CurrentTime++;
  for(int i=0;i<Orientations;i++){
    for(int j=0;j<SpatialFrequencies;j++){
      for(int k=0;k<TemporalFrequencies;k++){
        Activation[CurrentTime][i][j][k] =  DActivation[CurrentTime][i][j][k]; //Activation[CurrentTime-1][i][j][k]+StepP*DActivation[CurrentTime][i][j][k]
        ActivationNonLinearity[CurrentTime][i][j][k] = Activation[CurrentTime][i][j][k]; //V1NonLinearity(Activation[CurrentTime][i][j][k]);
        SumActivation[CurrentTime][i] += Activation[CurrentTime][i][j][k];//NonLinearityV1MT(Activation[CurrentTime][i][j][k]);
      }
    }
  }
}

double V1Neuron::GetMTContribution(int OrientationP){
  return SumActivation[CurrentTime][OrientationP];
}

double V1Neuron::V1NonLinearity(double ValueP){
  double Max  = 1;
  double a  = 5;//10;
  double b  = 0.17;//0.3;
  double Tem  = (Max/(1+exp(a*(b-ValueP)))-Max/(1+exp(a*(b-0))))*(Max/(Max-Max/(1+exp(a*(b-0)))));
  Tem = (Tem>0)?Tem:0;
  return Tem;
}

double V1Neuron::NonLinearityV1MT(double Activation){
  return V1NonLinearity(Activation);
}
