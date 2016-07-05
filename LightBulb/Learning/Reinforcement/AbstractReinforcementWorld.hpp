#pragma once

#ifndef _ABSTRACTREINFORCEMENTWORLD_H_
#define _ABSTRACTREINFORCEMENTWORLD_H_

// Library Includes
#include <vector>
#include <memory>

// Includes
#include "IO/UseParentSerialization.hpp"
#include "NeuralNetwork/NeuralNetwork.hpp"

// Forward declarations
struct LayeredNetworkOptions;

class AbstractReinforcementWorld
{
private:
	std::vector<double> lastOutput;
	std::vector<double> lastInput;
	void buildOutputBuffer();
	void buildNeuralNetwork(LayeredNetworkOptions &options);
protected:
	// The NN of the object
	std::unique_ptr<NeuralNetwork> neuralNetwork;
	// This method should return the input for the neural network
	virtual void getNNInput(std::vector<double>& input) = 0;
	// This method should interpret and act depending on the given NN output
	virtual void interpretNNOutput(std::vector<double>& output) = 0;

	void doNNCalculation();
public:
	virtual ~AbstractReinforcementWorld() {}
	AbstractReinforcementWorld(LayeredNetworkOptions& options);
	// This method should execute one simulation step.
	// After each simulation step the evolution learning rule will execute each evolution command (selection, mutation, recombination...)
	virtual double doSimulationStep() = 0;
	void initializeForLearning();
	NeuralNetwork* getNeuralNetwork();
};

EMPTY_SERIALIZATION(AbstractReinforcementWorld);

#endif
