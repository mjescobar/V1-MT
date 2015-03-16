/* 
 * File:   FilterResponse.h
 * Author: Pedro F. Toledo <pedrotoledocorrea@gmail.com>
 *
 * Created on October 29, 2012, 5:43 PM
 */

#ifndef FILTERRESPONSE_H
#define  FILTERRESPONSE_H

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

class FilterResponse {
public:
//------------------------------------------------------------------------------
//Standard methods--------------------------------------------------------------
//------------------------------------------------------------------------------
                  FilterResponse();
                  FilterResponse(const FilterResponse& orig);
  virtual        ~FilterResponse();
  FilterResponse &operator=(const FilterResponse FilterResponseP);
//------------------------------------------------------------------------------
//Constructors------------------------------------------------------------------
//------------------------------------------------------------------------------  
            FilterResponse(int OrientationsP, int SpatialFrequenciesP, int TemporalFrequenciesP, int TotalFacesP, int* FacesStepsP, double**** ArrayP);
            FilterResponse(int OrientationsP, int SpatialFrequenciesP, int TemporalFrequenciesP, char* FileNameP, int& FacesR);
//------------------------------------------------------------------------------
//Array Operations--------------------------------------------------------------
//------------------------------------------------------------------------------
  void      Step();
  void      StepReset();
  void      SetActivationBase(double ValueP);
  void      SetValues(double ****FilterExitationP);
  void      SetFaceLenght(int FaceP, int LenghtP);
  void      SetActivation(int FaceP, int OrientationP, int SpatialFrequencyP, int TemporalFrequency, double ValueP);
  void      SuperposeActivationDifuse(int FaceP, int OrientationP, int SpatialFrequencyP, int TemporalFrequency, double MagnitudeP, double a, double b);
  void      AddActivationDifuse(int FaceP, int OrientationP, int SpatialFrequencyP, int TemporalFrequency, double MagnitudeP, double RatioP, double SelectivityP);
  void      FillInfluenceMask();
  void      PrintInfluenceMask();
  double*** GetCurrentArray();
  bool*     GetInfluenceMask();
private:
  int        CurrentStep;
  int        Orientations;
  int        SpatialFrequencies;
  int        TemporalFrequencies;
  int        TotalFaces;
  int*       FacesSteps;
  double***  CurrentArray;  
  double**** Array;
  bool****** InfluenceMask;
};

#endif  /* FILTERRESPONSE_H */
