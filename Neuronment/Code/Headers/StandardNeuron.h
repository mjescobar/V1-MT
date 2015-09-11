/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   StandardNeuron.h
 * Author: ptoledo
 *
 * Created on June 11, 2015, 8:18 PM
 */

#ifndef STANDARDNEURON_H
#define	STANDARDNEURON_H

class StandardNeuron {
public:
  ReturnType SetType(string TypeP);
  ReturnType SetGroup(string GroupP);
  ReturnType SetName(string NameP);
  ReturnType AddAttribute(string LabelP, double DefaultP);
  ReturnType SetAttribute(string LabelP, double ValueP);
  ReturnType SetActivationLevels(int LevelsP);
  ReturnType SetActivationFunction(int LevelP, double (*ActivationFunctionP)());
  ReturnType SetLink(StandardNeuron &LinkingNeuronP, vector<double> LinkingWeightsP);
  ReturnType GetAttribute(string LabelP, double &ParameterP);
  ReturnType GetType(string &TypeP);
  ReturnType GetGroup(string &GroupP);
  ReturnType GetName(string &NameP);
  ReturnType SetActivationCalculationOrder(vector<int> OrderP);
  ReturnType GetActivation(int LevelP, double &ActivationP, int StepsP = 0);
  ReturnType SetExternalExcitation(vector<vector<double> > ExternalExcitationP, vector<int> ExternalExcitationStepsCounterP);
  ReturnType CalculateExternalExcitation(int StepP, vector<double> &ExternalExcitationP);
  ReturnType CalculateActivationStep(int IterationP);


  StandardNeuron();
  StandardNeuron(const StandardNeuron& orig);
  virtual ~StandardNeuron();
private:
  string Name;
  string Type;
  string Group;
  vector<double> Attributes;
  vector<string> AttributeLabels;
  vector<vector<double> > Activation;
  vector<int> ActivationCalculationOrder;
  vector<double (*)() > ActivationFunctions;
  // Neuron External Excitation
  vector<vector<double> > ExternalExcitation;
  vector<int> ExternalExcitationStepsCounter;
  vector<StandardNeuron*> Links;
  vector<vector<double> > LinkingWeights;
};

#endif	/* STANDARDNEURON_H */

