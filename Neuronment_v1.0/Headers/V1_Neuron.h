/* 
 * @author  Pedro F. Toledo <pedrotoledocorrea@gmail.com>
 * @version 1.0
 */

#ifndef V1_NEURON_H
#define	V1_NEURON_H

class SimulationManager;

class V1_Neuron : public ND_Neuron {
public:
    /**
     * Empty constructor
     */
    V1_Neuron();

    /**
     * Ussual constructor
     * @param NameP Name of the neuron
     * @param Xp X position
     * @param Yp Y position
     * @param Zp Z position
     * @param OriP Preferred Orientation
     * @param SpaP Preferred Spatial Frequency
     * @param TemP Preferred Temporal Frequency
     * @param ActiP Time 0 Activation value
     * @param DactP Time 0 DActivation value
     */
    V1_Neuron(string NameP, double Xp, double Yp, double Zp, double OriP, double SpaP, double TemP, double ActiP, double DactP);

    /**
     * Copy constructor
     * @param orig original instance
     */
    V1_Neuron(const V1_Neuron& orig);

    /**
     * Default destructor
     */
    virtual ~V1_Neuron();

    /**
     * Adds a V1_Neuron link to the neuron
     * @param NeuronP The neuron to link
     * @param WeightP The weight for the linking
     * @return 
     */
    bool AddV1Link(V1_Neuron *NeuronP, SimulationManager SimulatorP);
    
    /**
     * Sets the external excitation for the neuron based on the simulation parameters
     * @return true if successful
     */
    bool SetExternalExcitation();

    /**
     * Calculates the DActivation of the current step
     * @return true if calculated correctly
     */
    double CalculateDActivation();

    /**
     * Calculates the Activation of the current step
     * @return true if calculated correctly
     */
    double CalculateActivation();
    
    /**
     * Simulates the step StepP
     * @param StepP the number of step to simulate
     * @return true if simulated correctly
     */
    //bool SimulateStep(int StepP);
    
    /**
     * Returns the preferred orientation
     * @return the preferred orientation value
     */
    double GetOri();

    /**
     * Returns the preferred spatial frequency
     * @return the preferred spatial frequency
     */
    double GetSpa();

    /**
     * Returns the preferred temporal frequency
     * @return the preferred temporal frequency
     */
    double GetTem();

    /**
     * Returns the activation value of the las calculated step
     * @return the activation value stored
     */
    double GetLastActivation();

    /**
     * Obtains the base weight defined by the simulator configuration
     * @param MethodP Method to obtain the value
     * @param DestinationP Destination neuron that configures the weight
     * @param OriginP Origin neuron that configures the weight
     * @return the retrieved value
     */
    double GetV1V1BaseWeight(string MethodP, string DestinationP, string OriginP);

private:
    double Ori;
    double Spa;
    double Tem;
};

/**
 * Allows comparison between V1_Neuron for sorting proposes
 * @param AP The neuron to compare
 * @param BP The neuron to compare with
 * @return true if AP lower
 */
bool CompareV1_NeuronForSorting(V1_Neuron AP, V1_Neuron BP);

#endif	/* V1_NEURON_H */
