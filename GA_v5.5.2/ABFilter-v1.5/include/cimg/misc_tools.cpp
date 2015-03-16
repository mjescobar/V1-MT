
#include <misc_tools.h>

//Approximation of instantaneous firing rate for a conductance-driven neuron:
double instantFiringRate(double I, double tauRefr, double gLeak, double Ginh, double Einh, double  Gexc, double Eexc)
{
double gInf=gLeak+Gexc+Ginh;
double Itot=I+Gexc*Eexc+Ginh*Einh;
if(gInf<Itot)
	return 1.0 / (tauRefr - log(1.0-gInf/Itot)/gInf) ;
else
 	return 0.0;
}




