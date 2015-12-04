/* 
 * File:   FilterResponse.cpp
 * Author: Pedro F. Toledo <pedrotoledocorrea@gmail.com>
 * 
 * Created on October 29, 2012, 5:43 PM
 */

#include "FilterResponse.h"

#define free(p) free(p);p=NULL;

//------------------------------------------------------------------------------
//Standard methods--------------------------------------------------------------
//------------------------------------------------------------------------------

FilterResponse::FilterResponse(){
  CurrentStep         = -1;
  Orientations        = -1;
  SpatialFrequencies  = -1;
  TemporalFrequencies = -1;
  TotalFaces          = -1;
  FacesSteps          = NULL;
  CurrentArray        = NULL;  
  Array               = NULL;
  InfluenceMask       = NULL;
}
FilterResponse::FilterResponse(const FilterResponse& orig){
  CurrentStep = orig.CurrentStep;
  Orientations = orig.Orientations;
  SpatialFrequencies = orig.SpatialFrequencies;
  TemporalFrequencies = orig.TemporalFrequencies;
  TotalFaces = orig.TotalFaces;
  FacesSteps = (int*)malloc(sizeof(int)*TotalFaces);
  for(int i=0;i<TotalFaces;i++){
    FacesSteps[i] = orig.FacesSteps[i];
  }
  Array = (double****)malloc(sizeof(double***)*TotalFaces);
  for(int i=0;i<TotalFaces;i++){
    Array[i] = (double***)malloc(sizeof(double**)*Orientations);
    for(int j=0;j<Orientations;j++){
      Array[i][j]=(double**)malloc(sizeof(double*)*SpatialFrequencies);
      for(int k=0;k<SpatialFrequencies;k++){
        Array[i][j][k]=(double*)malloc(sizeof(double)*TemporalFrequencies);
        for(int l=0;l<TemporalFrequencies;l++){
          Array[i][j][k][l] = orig.Array[i][j][k][l];
        }
      }
    }
  }
  CurrentArray = orig.CurrentArray;
  InfluenceMask = (bool******)malloc(sizeof(bool*****)*Orientations);
  for(int i=0;i<Orientations;i++){
    InfluenceMask[i] = (bool*****)malloc(sizeof(bool****)*SpatialFrequencies);
    for(int j=0;j<SpatialFrequencies;j++){
      InfluenceMask[i][j] = (bool****)malloc(sizeof(bool***)*TemporalFrequencies);
      for(int k=0;k<TemporalFrequencies;k++){
        InfluenceMask[i][j][k] = (bool***)malloc(sizeof(bool**)*Orientations);
        for(int l=0;l<Orientations;l++){
          InfluenceMask[i][j][k][l] = (bool**)malloc(sizeof(bool*)*SpatialFrequencies);
          for(int m=0;m<SpatialFrequencies;m++){
            InfluenceMask[i][j][k][l][m] = (bool*)malloc(sizeof(bool)*TemporalFrequencies);
            for(int n=0;n<TemporalFrequencies;n++){
              InfluenceMask[i][j][k][l][m][n] = orig.InfluenceMask[i][j][k][l][m][n];
            }
          }
        }
      }
    }
  }
}

FilterResponse::~FilterResponse(){
  for(int i=0;i<TotalFaces;i++){
    for(int j=0;j<Orientations;j++){
      for(int k=0;k<SpatialFrequencies;k++){
        free(Array[i][j][k]);
      }
      free(Array[i][j]);
    }
    free(Array[i]);
  }
  for(int i=0;i<Orientations;i++){
    for(int j=0;j<SpatialFrequencies;j++){
      for(int k=0;k<TemporalFrequencies;k++){
        for(int l=0;l<Orientations;l++){
          for(int m=0;m<SpatialFrequencies;m++){
            free(InfluenceMask[i][j][k][l][m]);
          }
          free(InfluenceMask[i][j][k][l]);
        }
        free(InfluenceMask[i][j][k]);
      }
      free(InfluenceMask[i][j]);
    }
    free(InfluenceMask[i]);
  }
  free(InfluenceMask);
  free(Array);
  free(FacesSteps);
}

FilterResponse  &FilterResponse::operator=(const FilterResponse FilterResponseP){
  CurrentStep = 0;
  Orientations = FilterResponseP.Orientations;
  SpatialFrequencies = FilterResponseP.SpatialFrequencies;
  TemporalFrequencies = FilterResponseP.TemporalFrequencies;
  TotalFaces = FilterResponseP.TotalFaces;
  FacesSteps = (int*)malloc(sizeof(int)*TotalFaces);
  for(int i=0;i<TotalFaces;i++){
    FacesSteps[i] = FilterResponseP.FacesSteps[i];
  }
  Array = (double****)malloc(sizeof(double***)*TotalFaces);
  for(int i=0;i<TotalFaces;i++){
    Array[i] = (double***)malloc(sizeof(double**)*Orientations);
    for(int j=0;j<Orientations;j++){
      Array[i][j]=(double**)malloc(sizeof(double*)*SpatialFrequencies);
      for(int k=0;k<SpatialFrequencies;k++){
        Array[i][j][k]=(double*)malloc(sizeof(double)*TemporalFrequencies);
        for(int l=0;l<TemporalFrequencies;l++){
          Array[i][j][k][l] = FilterResponseP.Array[i][j][k][l];
        }
      }
    }
  }
  CurrentArray = Array[0];
  InfluenceMask = (bool******)malloc(sizeof(bool*****)*Orientations);
  for(int i=0;i<Orientations;i++){
    InfluenceMask[i] = (bool*****)malloc(sizeof(bool****)*SpatialFrequencies);
    for(int j=0;j<SpatialFrequencies;j++){
      InfluenceMask[i][j] = (bool****)malloc(sizeof(bool***)*TemporalFrequencies);
      for(int k=0;k<TemporalFrequencies;k++){
        InfluenceMask[i][j][k] = (bool***)malloc(sizeof(bool**)*Orientations);
        for(int l=0;l<Orientations;l++){
          InfluenceMask[i][j][k][l] = (bool**)malloc(sizeof(bool*)*SpatialFrequencies);
          for(int m=0;m<SpatialFrequencies;m++){
            InfluenceMask[i][j][k][l][m] = (bool*)malloc(sizeof(bool)*TemporalFrequencies);
            for(int n=0;n<TemporalFrequencies;n++){
              InfluenceMask[i][j][k][l][m][n] = FilterResponseP.InfluenceMask[i][j][k][l][m][n];
            }
          }
        }
      }
    }
  }
  return *this;
}

//------------------------------------------------------------------------------
//Constructors------------------------------------------------------------------
//------------------------------------------------------------------------------

FilterResponse::FilterResponse(int OrientationsP, int SpatialFrequenciesP, int TemporalFrequenciesP, char* FileNameP, int& FacesR){
  double  FromFile = 0;
  long TotalFacesP = 0;
  long StepSize = OrientationsP*SpatialFrequenciesP*TemporalFrequenciesP;
  FILE *File = fopen(FileNameP,"rb");
  while(fread(&FromFile,sizeof(double),1,File)){
    TotalFacesP++;
  }
  if(TotalFacesP%StepSize!=0){
    printf("Corrupt FilterResponse File\n  Count:  %ld\n  Sample: %ld\n  Error: %ld)\n",TotalFacesP,StepSize,TotalFacesP%StepSize);
    exit(EXIT_FAILURE);
  }
  else{
    TotalFacesP /= StepSize;
    FacesR = TotalFacesP;
  }
  fclose(File);
  File = fopen(FileNameP,"rb");
  Array = (double****)malloc(sizeof(double***)*TotalFacesP);
  for(int i=0;i<TotalFacesP;i++){
    Array[i] = (double***)malloc(sizeof(double**)*OrientationsP);
    for(int j=0;j<OrientationsP;j++){
      Array[i][j]=(double**)malloc(sizeof(double*)*SpatialFrequenciesP);
      for(int k=0;k<SpatialFrequenciesP;k++){
        Array[i][j][k]=(double*)malloc(sizeof(double)*TemporalFrequenciesP);
        for(int l=0;l<TemporalFrequenciesP;l++){
          fread(&FromFile,sizeof(double),1,File);
          Array[i][j][k][l] = FromFile;
        }
      }
    }
  }
  fclose(File);
  Orientations = OrientationsP;
  SpatialFrequencies = SpatialFrequenciesP;
  TemporalFrequencies = TemporalFrequenciesP;
  TotalFaces = TotalFacesP;
  FacesSteps = (int*)malloc(sizeof(int)*TotalFacesP);
  for(int i=0;i<TotalFacesP;i++){
    FacesSteps[i] = 1;
  }
  CurrentStep = 0;
  CurrentArray = Array[CurrentStep];
  InfluenceMask = (bool******)malloc(sizeof(bool*****)*OrientationsP);
  for(int i=0;i<OrientationsP;i++){
    InfluenceMask[i] = (bool*****)malloc(sizeof(bool****)*SpatialFrequenciesP);
    for(int j=0;j<SpatialFrequenciesP;j++){
      InfluenceMask[i][j] = (bool****)malloc(sizeof(bool***)*TemporalFrequenciesP);
      for(int k=0;k<TemporalFrequenciesP;k++){
        InfluenceMask[i][j][k] = (bool***)malloc(sizeof(bool**)*OrientationsP);
        for(int l=0;l<OrientationsP;l++){
          InfluenceMask[i][j][k][l] = (bool**)malloc(sizeof(bool*)*SpatialFrequenciesP);
          for(int m=0;m<SpatialFrequenciesP;m++){
            InfluenceMask[i][j][k][l][m] = (bool*)malloc(sizeof(bool)*TemporalFrequenciesP);
            for(int n=0;n<TemporalFrequenciesP;n++){
              InfluenceMask[i][j][k][l][m][n] = true;
            }
          }
        }
      }
    }
  }
}

FilterResponse::FilterResponse(int OrientationsP, int SpatialFrequenciesP, int TemporalFrequenciesP, int TotalFacesP, int* FacesStepsP, double**** ArrayP){
  Array = (double****)malloc(sizeof(double***)*TotalFacesP);
  for(int i=0;i<TotalFacesP;i++){
    Array[i] = (double***)malloc(sizeof(double**)*OrientationsP);
    for(int j=0;j<OrientationsP;j++){
      Array[i][j]=(double**)malloc(sizeof(double*)*SpatialFrequenciesP);
      for(int k=0;k<SpatialFrequenciesP;k++){
        Array[i][j][k]=(double*)malloc(sizeof(double)*TemporalFrequenciesP);
        for(int l=0;l<TemporalFrequenciesP;l++){
          if(FacesStepsP == NULL || ArrayP == NULL){
            Array[i][j][k][l] = 0;
          }
          else{
            Array[i][j][k][l] = ArrayP[i][j][k][l];
          }
        }
      }
    }
  }
  Orientations = OrientationsP;
  SpatialFrequencies = SpatialFrequenciesP;
  TemporalFrequencies = TemporalFrequenciesP;
  TotalFaces = TotalFacesP;
  if(FacesStepsP == NULL || ArrayP == NULL){
    FacesSteps = (int*)malloc(sizeof(int)*TotalFacesP);
    for(int i=0;i<TotalFacesP;i++){
      FacesSteps[i] = 0;
    }
  }
  else{
    FacesSteps = FacesStepsP;
  }
  CurrentStep = 0;
  CurrentArray = Array[CurrentStep];
  InfluenceMask = (bool******)malloc(sizeof(bool*****)*OrientationsP);
  for(int i=0;i<OrientationsP;i++){
    InfluenceMask[i] = (bool*****)malloc(sizeof(bool****)*SpatialFrequenciesP);
    for(int j=0;j<SpatialFrequenciesP;j++){
      InfluenceMask[i][j] = (bool****)malloc(sizeof(bool***)*TemporalFrequenciesP);
      for(int k=0;k<TemporalFrequenciesP;k++){
        InfluenceMask[i][j][k] = (bool***)malloc(sizeof(bool**)*OrientationsP);
        for(int l=0;l<OrientationsP;l++){
          InfluenceMask[i][j][k][l] = (bool**)malloc(sizeof(bool*)*SpatialFrequenciesP);
          for(int m=0;m<SpatialFrequenciesP;m++){
            InfluenceMask[i][j][k][l][m] = (bool*)malloc(sizeof(bool)*TemporalFrequenciesP);
            for(int n=0;n<TemporalFrequenciesP;n++){
              InfluenceMask[i][j][k][l][m][n] = true;
            }
          }
        }
      }
    }
  }
}

//------------------------------------------------------------------------------
//Array Operations--------------------------------------------------------------
//------------------------------------------------------------------------------

void FilterResponse::Step(){
  CurrentStep++;
  int Advanced = 0;
  int  Pointer = 0;
  do{
    if(Pointer<TotalFaces){
      Advanced += FacesSteps[Pointer];
      Pointer++;
    }
    else{
      break;
    }
  }while(CurrentStep>=Advanced);
  CurrentArray = Array[Pointer-1];
}

void FilterResponse::StepReset(){
  CurrentStep = 0;
  CurrentArray = Array[CurrentStep];
}

void FilterResponse::SetActivationBase(double ValueP){
  for(int i=0;i<TotalFaces;i++){
    for(int j=0;j<Orientations;j++){
      for(int k=0;k<SpatialFrequencies;k++){
        for(int l=0;l<TemporalFrequencies;l++){
          Array[i][j][k][l] = ValueP;
        }
      }
    }
  }
}

void FilterResponse::SetValues(double ****FilterExitationP){
  for(int h=0;h<TotalFaces;h++){
    for(int i=0;i<Orientations;i++){
      for(int j=0;j<SpatialFrequencies;j++){
        for(int k=0;k<TemporalFrequencies;k++){
          Array[h][i][j][k] = FilterExitationP[h][i][j][k];
        }
      }
    }
  }
}

void FilterResponse::SetFaceLenght(int FaceP, int LenghtP){
  FacesSteps[FaceP] = LenghtP;
}

void FilterResponse::SetActivation(int FaceP, int OrientationP, int SpatialFrequencyP, int TemporalFrequency, double ValueP){
  Array[FaceP][OrientationP][SpatialFrequencyP][TemporalFrequency] = ValueP;
}

void FilterResponse::SuperposeActivationDifuse(int FaceP, int OrientationP, int SpatialFrequencyP, int TemporalFrequency, double MagnitudeP, double aP, double bP){
  double TemporalAngle = 0;
  for(int i=0;i<Orientations;i++){
    TemporalAngle = (Orientations+OrientationP-i)%Orientations;
    TemporalAngle *= 2*3.14159/Orientations;
    TemporalAngle = MagnitudeP*(exp(aP*cos(TemporalAngle))+bP*exp(aP*cos(TemporalAngle+3.14159)))/exp(aP);
    Array[FaceP][i][SpatialFrequencyP][TemporalFrequency] = (Array[FaceP][i][SpatialFrequencyP][TemporalFrequency]>TemporalAngle)?Array[FaceP][i][SpatialFrequencyP][TemporalFrequency]:TemporalAngle;
	printf("InputAct: %lf\n",Array[FaceP][i][SpatialFrequencyP][TemporalFrequency]);
  }
}

void FilterResponse::AddActivationDifuse(int FaceP, int OrientationP, int SpatialFrequencyP, int TemporalFrequency, double MagnitudeP, double RatioP, double SelectivityP){
  double SelectiveCosine = 0;
  double CosinoidalSigmoid = 0;
  double TemporalAngle = 0;
  for(int i=0;i<Orientations;i++){
    TemporalAngle = (Orientations+OrientationP-i)%Orientations;
    TemporalAngle *= 2*3.14159/Orientations;
    SelectiveCosine = (cos(TemporalAngle)>0)?cos(TemporalAngle):-cos(TemporalAngle);
    SelectiveCosine = pow(SelectiveCosine,SelectivityP);
    CosinoidalSigmoid = (1-RatioP)/(1+exp(100*cos(TemporalAngle+3.14159)))+RatioP;
    Array[FaceP][i][SpatialFrequencyP][TemporalFrequency] += SelectiveCosine*CosinoidalSigmoid*MagnitudeP;
  }
}

void FilterResponse::FillInfluenceMask(){
  for(int i=0;i<Orientations;i++){
    for(int j=0;j<SpatialFrequencies;j++){
      for(int k=0;k<TemporalFrequencies;k++){
        bool Tmp1 = false;
        for(int o=0;o<TotalFaces;o++){
          if(Array[o][i][j][k]!=0){
            Tmp1 = true;
          }
        }
        for(int l=0;l<Orientations;l++){
          for(int m=0;m<SpatialFrequencies;m++){
            for(int n=0;n<TemporalFrequencies;n++){
              bool Tmp2 = false;
              for(int o=0;o<TotalFaces;o++){
                if(Array[o][l][m][n]!=0){
                  Tmp2 = true;
                }
              }
              InfluenceMask[i][j][k][l][m][n] = Tmp1 & Tmp2;
            }
          }
        }
      }
    }
  }
}

double*** FilterResponse::GetCurrentArray(){
  return CurrentArray;
}

bool* FilterResponse::GetInfluenceMask(){
  bool* ToReturn = (bool*)malloc(sizeof(bool)*Orientations*Orientations*SpatialFrequencies*SpatialFrequencies*TemporalFrequencies*TemporalFrequencies);
  int Iterator = 0;
  for(int i=0;i<Orientations;i++){
    for(int j=0;j<SpatialFrequencies;j++){
      for(int k=0;k<TemporalFrequencies;k++){
        for(int l=0;l<Orientations;l++){
          for(int m=0;m<SpatialFrequencies;m++){
            for(int n=0;n<TemporalFrequencies;n++){
              ToReturn[Iterator++] = InfluenceMask[i][j][k][l][m][n];
            }
          }
        }
      }
    }
  }
  return ToReturn;
}
