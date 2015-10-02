
#include "FunctionsManager.h"
#include "Functions.h"

ReturnType FunctionsManager::InitializeManager()
{
  Functions.PutEntryQuick("IO_ReadFromFile", (void*) Function000000);
  Functions.PutEntryQuick("Operations_MultiplicationSum", (void*) Function000001);
  Functions.PutEntryQuick("Operations_Perceptron", (void*) Function000002);
  Functions.PutEntryQuick("Neuroscience_Diffusion", (void*) Function000003); //Lothar: von misses?? which is the right name?
  Functions.PutEntryQuick("Neuroscience_V1Neuron_act", (void*) Function000004);
  Functions.PutEntryQuick("Neuroscience_V1Neuron_dac", (void*) Function000005);
  Functions.PutEntryQuick("Neuroscience_MTNeuron_act", (void*) Function000006);
  Functions.PutEntryQuick("Operations_Vector_Average", (void*) Function000007);
  return ReturnSuccess;
}
