#include "StandardNeuron.hpp"
#include "Edge.hpp"
#include "InputFunction.hpp"
#include "ActivationFunction.hpp"
#include "OutputFunction.hpp"

StandardNeuron::~StandardNeuron()
{
	delete(inputFunction);
	delete(activationFunction);
	delete(outputFunction);
}

StandardNeuron::StandardNeuron(InputFunction* inputFunction_, ActivationFunction* activationFunction_, OutputFunction* outputFunction_)
{
	inputFunction = inputFunction_->getInputFunctionCopy();
	activationFunction = activationFunction_->getActivationFunctionCopy();
	outputFunction = outputFunction_->getOutputFunctionCopy();
	threshold = 0;
	netInput = 0;
}

void StandardNeuron::addPrevNeuron(Neuron* newPrevNeuron, float weight)
{
	// Create a new edge between this and the newPrevNeuron
	Edge* newEdge = new Edge(newPrevNeuron, this, weight);
	// Add the newEdge to the afferentEdge list
	afferentEdges.push_back(newEdge);
	// Add the newEdge also to the newPrevNeuron
	newPrevNeuron->addNextNeuron(newEdge);	
}

void StandardNeuron::addPrevNeuron(Edge* newEdge)
{
	// Add the newEdge to the afferentEdge list
	afferentEdges.push_back(newEdge);
}

void StandardNeuron::refreshActivation()
{
	// Calc the input from all afferentEdges
	netInput = inputFunction->execute(afferentEdges);
	// Calc the activation from the input
	activation = activationFunction->execute(netInput, threshold);
	// Calc the output activation from the activation
	activation = outputFunction->execute(activation);
}

std::vector<Edge*>* StandardNeuron::getAfferentEdges()
{
	return &afferentEdges;
}

float StandardNeuron::getNetInput()
{
	return netInput;
}

float StandardNeuron::executeDerivationOnActivationFunction(float input)
{
	return activationFunction->executeDerivation(input, threshold);
}
