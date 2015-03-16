#include "../ABFilter-v1.5/include/ABFilter.h"
#include <stdio.h>
#include <math.h>
#include <errno.h>

#define _USE_MATH_DEFINES

int main(int argc, char **argv) 
{ 
  //Setting variables
    //Video parameters
      int    N_rep           = 1;                    //Number of repetitions of each frame
      int    beginning_frame = 0;                    //beginning frame of input sequence
      int    end_frame       = 500;                  //ending frame of input sequence (not included) 
      double step            = 0.005;                //Time length of one step, in seconds
      double NormMin         = 0;                    //Video Normalization Minimum
      double NormMax         = 1;                    //Video Normalization Maximum
      bool   BinResult       = true;
      if(argc == 3){
        if(argv[2][0] == 'a'){
          BinResult = false;
        }
      }
    //V1 SpatialFrequencies Construction
      int     SpatialFrequencies     = 4;
      double  SpatialFrecuencyBase   = 0.025;
      double  SpatialFrequencyFactor = 2.0;
      double* SpatialFrequency       = (double*)malloc(sizeof(double)*SpatialFrequencies);
      for(int i=0;i<SpatialFrequencies;i++){
        SpatialFrequency[i] = SpatialFrecuencyBase*pow(SpatialFrequencyFactor,i);
      }
    //V1 Temporal Frequencies Construction
      int     TemporalFrequencies     = 4;
      double  TemporalFrequencyBase   = 1;
      double  TemporalFrequencyFactor = 2.0;
      double* TemporalFrequency       = (double*)malloc(sizeof(double)*TemporalFrequencies);
      for(int i=0;i<SpatialFrequencies;i++){
        TemporalFrequency[i] = TemporalFrequencyBase*pow(TemporalFrequencyFactor,i);
      }
    //V1 Orientations
      int     Orientations = 32;
      double* Orientation  = (double*)malloc(sizeof(double)*Orientations);
      Orientation[0] = 0;
      for(int i=1;i<Orientations;i++){
        Orientation[i] = 360.0 - ((double)i)*360.0/((double)Orientations);
      }
  //Creating the Filter Array
    ABFilter**** Filter = (ABFilter****)malloc(sizeof(ABFilter***)*Orientations);
    for(int i=0;i<Orientations;i++){
      Filter[i] = (ABFilter***)malloc(sizeof(ABFilter**)*SpatialFrequencies);
      for(int j=0;j<SpatialFrequencies;j++){
        Filter[i][j] = (ABFilter**)malloc(sizeof(ABFilter*)*TemporalFrequencies);
        for(int k=0;k<TemporalFrequencies;k++){
          Filter[i][j][k] = new ABFilter();
          Filter[i][j][k]->set_spatialOrient(Orientation[i]);
          Filter[i][j][k]->set_spatialFrequency(SpatialFrequency[j]);
          Filter[i][j][k]->set_temporalFrequency(TemporalFrequency[k]);
          Filter[i][j][k]->set_step(step);
          Filter[i][j][k]->filter_build();
        }
      }
    }
  //Reading and creating i/o files
    //Creating output file name
      char  *VideoFileInput = argv[1];
      char  VideoFileOutput[1024];
      if(BinResult){
        sprintf(VideoFileOutput, "%s.NM%07.3f-%07.3f_OR%02d_SF%d-%.3f-%.3f_TF%d-%.3f-%.3f.frb",VideoFileInput,NormMin,NormMax,Orientations,SpatialFrequencies,SpatialFrecuencyBase,SpatialFrequencyFactor,TemporalFrequencies,TemporalFrequencyBase,TemporalFrequencyFactor);
      }
      else{
        sprintf(VideoFileOutput, "%s.NM%07.3f-%07.3f_OR%02d_SF%d-%.3f-%.3f_TF%d-%.3f-%.3f.fra",VideoFileInput,NormMin,NormMax,Orientations,SpatialFrequencies,SpatialFrecuencyBase,SpatialFrequencyFactor,TemporalFrequencies,TemporalFrequencyBase,TemporalFrequencyFactor);
      }
    //Opening output file
      FILE  *File          = NULL;  
      if(BinResult){
        File = fopen(VideoFileOutput, "wb+");
      }
      else{
        File = fopen(VideoFileOutput, "w+");
      }
      if(File == NULL){
        printf("ERROR openining file %s (errno = %d).... aborting\n", VideoFileOutput, errno);
        return -1;
      }
    //Opening input file
      CImg<double> In(VideoFileInput);
      int s_sx = In.dimx(), s_sy = In.dimy();
      int beginfrm = 0, endfrm = In.dimz();
      if( (beginning_frame < end_frame) && (beginning_frame < endfrm) ){
        beginfrm = (beginning_frame > beginfrm) ? beginning_frame : beginfrm;
        endfrm = (end_frame < endfrm) ? end_frame : endfrm;
      }
    //Normalizing In to 1
      In.normalize(NormMin,NormMax);
  //Calculating Convolutions
    //printf("Calculating Convolutions\n");fflush(stdout);
    CImg<double> Seq(s_sx, s_sy);
    double ConvolutionResult;
    for (int t=0;t<endfrm-beginfrm;t++){     
      Seq = In.get_slice(beginfrm + t);
      for (int t1=0;t1<N_rep;t1++){
        for(int i=0;i<Orientations;i++){
          for(int j=0;j<SpatialFrequencies;j++){
            for(int k=0;k<TemporalFrequencies;k++){
              ConvolutionResult = Filter[i][j][k]->convolve(Seq, In.dimx()/2, In.dimy()/2);
              if(BinResult){
                fwrite(&ConvolutionResult,sizeof(double),1,File);
              }
              else{
                fprintf(File,"%lf\n",ConvolutionResult);
              }
            }
          }
        }
      }
    }
    fclose(File);
  //Finishing
    return 0;  
}
