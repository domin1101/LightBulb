#pragma once

#ifndef _ABSTRACTNEIGHBORHOODFUNCTION_H_
#define _ABSTRACTNEIGHBORHOODFUNCTION_H_

// Forward declaration
class AbstractSOMStructure;
class NeuronCompareThreshold;
class StandardNeuron;

// This abstract class describes a function, which can calculate the neighborhood factor in a som network
class AbstractNeighborhoodFunction
{
private:
public:
	// Calculate the neighborhood factor
	virtual double execute(StandardNeuron* neuron, AbstractSOMStructure* structure, NeuronCompareThreshold* threshold, double maxDistance) = 0;
	// Create a copy of the object
	virtual AbstractNeighborhoodFunction* getNeighborhoodFunctionCopy() = 0;
};

#endif