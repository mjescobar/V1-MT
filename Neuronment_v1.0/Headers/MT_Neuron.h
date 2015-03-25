/* 
 * @author  Pedro F. Toledo <pedrotoledocorrea@gmail.com>
 * @version 1.0
 */

#ifndef MT_NEURON_H
#define	MT_NEURON_H

class SimulationManager;

class MT_Neuron : public ND_Neuron {
public:
    /**
     * MT Neuron empty constructor
     */
    MT_Neuron();

    /**
     * Base MT neuron constructor
     * @param NameP Name of the neuron
     * @param Xp X position
     * @param Yp Y position
     * @param Zp Z position
     * @param OriP Preferred orientation
     * @param ActiP Activation on time 0
     * @param DactP Dactivation on time 0
     */
    MT_Neuron(string NameP, double Xp, double Yp, double Zp, double OriP, double ActiP, double DactP);

    /**
     * Copy method
     * @param orig original isntance
     */
    MT_Neuron(const MT_Neuron& orig);

    /**
     * Default destructor
     */
    virtual ~MT_Neuron();

    /**
     * Adds a neuron to the connection list
     * @param NeuronP the neuron to link
     * @return true if connected
     */
    bool AddV1Link(V1_Neuron* NeuronP, SimulationManager SimulatorP);

    /**
     * Calculates the activation for the step StepP
     * @return true if calculated successfully
     */
    //bool SimulateStep(int StepP);
    
    /**
     * Gets the neuron preferred orientation
     * @return the preferred orientation value in deg
     */
    double GetOri();

private:
     /**
     * Calculates the activation for a new step
     * @return the calculated value
     */
    double CalculateActivation();
    
    double Ori;
};

/**
 * Allows the MT neurons comparison for sorting
 * @param AP The neuron to compare
 * @param BP The neuron to compare with
 * @return true if AP lower than BP
 */
bool CompareMT_NeuronForSorting(MT_Neuron AP, MT_Neuron BP);

#endif	/* MT_NEURON_H */
