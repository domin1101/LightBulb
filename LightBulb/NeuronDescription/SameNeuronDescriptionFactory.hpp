#pragma once

#ifndef _SAMENEURONDESCRIPTIONFACTORY_H_
#define _SAMENEURONDESCRIPTIONFACTORY_H_

// Library Includes
#include <memory>

// Includes
#include "NeuronDescription/AbstractNeuronDescriptionFactory.hpp"

namespace LightBulb
{
	// Forward declarations

	// This is the standard neuron factory, where every neuron has the same functions
	class SameNeuronDescriptionFactory : public AbstractNeuronDescriptionFactory
	{
		template <class Archive>
		friend void serialize(Archive& archive, SameNeuronDescriptionFactory& descriptionFactory);
	private:
		std::unique_ptr<NeuronDescription> neuronDescription;
	public:
		SameNeuronDescriptionFactory(NeuronDescription* neuronDescription_);
		SameNeuronDescriptionFactory(const SameNeuronDescriptionFactory &obj);
		// Inherited:
		NeuronDescription* createInnerNeuronDescription() override;
		NeuronDescription* createOutputNeuronDescription() override;
		AbstractNeuronDescriptionFactory* getCopy() override;
		AbstractActivationFunction* getOutputActivationFunction() override;
		AbstractActivationFunction* getInnerActivationFunction() override;
	};
}

#include "IO/SameNeuronDescriptionFactoryIO.hpp"

#endif