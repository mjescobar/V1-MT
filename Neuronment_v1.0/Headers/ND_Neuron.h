/* 
 * @author  Pedro F. Toledo <pedrotoledocorrea@gmail.com>
 * @version 1.0
 */

#ifndef ND_NEURON_H
#define	ND_NEURON_H

class ND_Neuron {
public:
    /**
     * Non differentiated neuron constructor
     */
    ND_Neuron();

    /**
     * Pre differentiated neuron constructor
     * @param FutureType Future type that the neuron will take
     */
    ND_Neuron(NeuronType FutureType);

    /**
     * Copy method
     * @param orig Original neuron
     */
    ND_Neuron(const ND_Neuron& orig);

    /**
     * Default destructor
     */
    virtual ~ND_Neuron();

    /**
     * Returns the name of the neuron
     * @return The string with the neuron name
     */
    string GetName();

    /**
     * Stores the weight associated to a neuron link
     * If weights over the threshold set by a simulation setting
     * the neuron is also added to the linked neurons list
     * @param SourceP The influence source neuron name
     * @param WeightP The influence weight
     * @return true if successfully added
     */
    bool SetNewLink_Activation(string SourceP, double WeightP);

    /**
     * Sets the activation method calculation for the neuron
     * @param MethodP The name of the activation method calculation
     * @return True if successfull
     */
    bool SetActivationMethod(string MethodP);

    /**
     * Sets the dactivation method calculation for the neuron
     * @param MethodP The name of the dactivation method calculation
     * @return True if successful
     */
    bool SetDActivationMethod(string MethodP);

    /**
     * Returns the neuron X position
     * @return the X position
     */
    double GetXPos();

    /**
     * Returns the neuron Y position
     * @return the Y position
     */
    double GetYPos();

    /**
     * Returns the neuron Z position
     * @return the Z position
     */
    double GetZPos();

    /**
     * Returns the neuron type
     * @return the neuron type
     */
    NeuronType GetType();

    /**
     * Returns the external excitation for a defined step
     * @param TimingP The step under inspection
     * @return the external excitation value
     */
    double GetExternalExcitation(int StepP);

    /**
     * Returns the neuron activation for the StepP step
     * @return the activation value
     */
    double GetActivation(int StepP);

    /**
     * Gets the amount of activation steps calculated for the neuron
     * @return the amount of steps
     */
    int GetActivationSteps();

    /**
     * Calculates the cartesian distance to a destination neuron location
     * @param DestinationP
     * @return 
     */
    double DistanceToNeuron(ND_Neuron DestinationP);

    /**
     * Counts the amount of neuron of an specific type connected to the neuron
     * @param TypeP Type of the neuron to be counted
     * @return the counted value
     */
    int ConnectionCount(NeuronType TypeP);

    /**
     * Gets the weight that links 2 neurons
     * @param NeuronNameP Influence origin neuron name
     * @return the weight value
     */
    double GetLinkingWeight(string NeuronNameP);

    /**
     * Sets the linking weight with another neuron
     * @param NeuronNameP Name of the neuron that provides the influence
     * @param WeightP weight value to set
     * @return true if successful
     */
    bool SetLinkingWeight(string NeuronNameP, double WeightP);

protected:
    int ExternalExcitationPointer;
    double XPos;
    double YPos;
    double ZPos;
    string Name;
    string ActivationMethod;
    string DActivationMethod;
    vector<int> ExternalExcitationTiming;
    vector<double> Activation;
    vector<double> DActivation;
    vector<double> ExternalExcitationValue;
    vector<ND_Neuron*> ActivationLinkingList;
    HashTable ActivationLinkingWeights;
    NeuronType Type;
private:
};

#endif	/* ND_NEURON_H */
