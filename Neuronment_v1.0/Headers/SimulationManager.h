/* 
 * @author  Pedro F. Toledo <pedrotoledocorrea@gmail.com>
 * @version 1.0
 */

#ifndef SIMULATIONMANAGER_H
#define	SIMULATIONMANAGER_H

class SimulationManager {
public:
    /**
     * Default constructor
     */
    SimulationManager();

    /**
     * Copy method
     * @param orig Original instance for copy
     */
    SimulationManager(const SimulationManager& orig);

    /**
     * Default destructor
     */
    virtual ~SimulationManager();

    /**
     * Reads the simulation settings and generates the required neuron instances
     * with the corresponding links pre established
     * @return true if success
     */
    bool InitializeNeurons();

    /**
     * Calculates the internal excitation of V1 with the diffusion technique according to the simulator settings
     * @return true if calculated correctly
     */
    bool AddV1Diffusion();

    /**
     * Simulates StepP steps with the previously configured simulator
     * @param StepsP Number of steps to calculate
     * @return true if simulated correctly
     */
    bool Simulate(int StepsP);

    /**
     * Prints the simulated V1 activation
     * @param OTypeP Sense for the printing
     * @return true if printed correctly
     */
    bool PrintV1Activation(OrientationType OTypeP);

    /**
     * Prints the simulated MT activation
     * @param OTypeP Sense for the printing
     * @return true if printed correctly
     */
    bool PrintMTActivation(OrientationType OTypeP);

    /**
     * Prints the simulated V1 activation redirected to a file
     * @param OTypeP Sense for the printing
     * @param DestinationP Destination file path
     * @return true if printed correctly
     */
    bool PrintV1Activation(OrientationType OTypeP, string DestinationP);

    /**
     * Prints the simulated MT activation redirected to a file
     * @param OTypeP Sense for the printing
     * @param DestinationP Destination file path
     * @return true if printed correctly
     */
    bool PrintMTActivation(OrientationType OTypeP, string DestinationP);

    /**
     * Prints the V1 external excitation set for time StepP redirected to a file
     * @param StepP Step for which the eternal excitation will be printed
     * @param DestinationP The destination file
     * @return true if printed correctly
     */
    bool PrintV1ExternalExcitation(int StepP, string DestinationP);

    /**
     * Prints the V1 external excitation set for time StepP
     * @param StepP Step for which the eternal excitation will be printed
     * @return true if printed correctly
     */
    bool PrintV1ExternalExcitation(int StepP);
    
    /**
     * Returns the current calculated value for the radius of V1 Neurons
     * @return the V!Radius value
     */
    double GetV1Radius();

private:
    /**
     * Fills the V1_Neurons vector with the required entities
     * @return true if successful
     */
    bool CreateV1NeuronVector();

    /**
     * Sets the V1 Activation Method
     * @return true if successful
     */
    bool SetV1ActMethod();

    /**
     * Sets the V1 DActivation Method
     * @return true if successful
     */
    bool SetV1DacMethod();

    /**
     * Fills the MT_Neurons vector with the required entities
     * @return true if successful
     */
    bool CreateMTNeuronVector();

    /**
     * Sets the MT Activation Method
     * @return true if successful
     */
    bool SetMTActMethod();

    /**
     * Sets the MT DActivation Method
     * @return true if successful
     */
    bool SetMTDacMethod();

    /**
     * Calculates and Sets the V1V1 links and their weights
     * @return true if successful
     */
    bool SetV1V1ConnectionLinks();

    /**
     * Calculates and Sets the V1MT links and their weights
     * @return true if successful
     */
    bool SetV1MTConnectionLinks();

    // V1 Parameters
    vector<V1_Neuron> V1_Neurons;
    double V1Radius;
    // MT Parameters
    vector<MT_Neuron> MT_Neurons;
    // Status
    bool Initialized;
};

#endif	/* SIMULATIONMANAGER_H */
