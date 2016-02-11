#pragma once

#ifndef _SAMENEURONDESCRIPTIONFACTORY_H_
#define _SAMENEURONDESCRIPTIONFACTORY_H_

// Library Includes
#include <memory>

// Includes
#include "NeuronFactory/AbstractNeuronDescriptionFactory.hpp"

// Forward declarations
class InputNeuron;
class StandardNeuron;
class AbstractActivationFunction;
class AbstractInputFunction;
class AbstractOutputFunction;
class AbstractThreshold;

// This is the standard neuron factory, where every neuron has the same functions
class SameNeuronDescriptionFactory : public AbstractNeuronDescriptionFactory
{
private:
	std::unique_ptr<NeuronDescription> neuronDescription;
public:	
	SameNeuronDescriptionFactory(NeuronDescription* neuronDescription_);
	SameNeuronDescriptionFactory(const SameNeuronDescriptionFactory &obj);
	// Inherited:
	NeuronDescription* createInnerNeuronDescription();
	NeuronDescription* createOutputNeuronDescription();
	AbstractNeuronDescriptionFactory* getCopy();
};

#endif