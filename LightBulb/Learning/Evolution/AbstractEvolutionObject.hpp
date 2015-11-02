#pragma once

#ifndef _AbstractEvolutionObject_H_
#define _AbstractEvolutionObject_H_

// Library includes
#include <vector>

// Forward declarations
class EvolutionLearningRule;
class NeuralNetwork;

// This class describes an abstract object which "lives" inside an evolution world.
// The evolution object contains a NN which should calculate the actions from external and internal inputs.
class AbstractEvolutionObject 
{
protected:
	// This vector describes the mutation strength of every edge in the NN.
	// It can be used inside the mutation/recombination algorithm
	std::vector<double> mutationStrength;
	// Resize the mutation strength vector
	void resizeMutationStrength(int newSize);
	// Randomize all values inside the mutation strength vecor
	void randomizeMutationStrength();
public:	
	virtual ~AbstractEvolutionObject() {};
	virtual NeuralNetwork* getNeuralNetwork() = 0;
	virtual std::vector<double>* getMutationStrength();
	virtual void setMutationStrength(std::vector<double>* newMutationStrength);
	// This method should execute one NN calculation. (Mostly: Get input -> let the NN calculate -> react depending on the NN output)
	virtual void doNNCalculation(EvolutionLearningRule& learningRule) = 0;
	// Reset the NN (All activations to zero)
	virtual void resetNN() = 0;
	// This method should return a new evolution object which contains a NN which has the same edges/neurons as the NN of this object.
	virtual AbstractEvolutionObject* clone(bool addToWorld = true) = 0;
};
#endif