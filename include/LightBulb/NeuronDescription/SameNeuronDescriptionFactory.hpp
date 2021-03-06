#pragma once

#ifndef _SAMENEURONDESCRIPTIONFACTORY_H_
#define _SAMENEURONDESCRIPTIONFACTORY_H_

// Library Includes
#include <memory>

// Includes
#include "LightBulb/NeuronDescription/AbstractNeuronDescriptionFactory.hpp"

namespace LightBulb
{
	// Forward declarations

	/**
	* \brief Describes a neuron description factory which provides the same neuron descriptions for all neurons.
	*/
	class SameNeuronDescriptionFactory : public AbstractNeuronDescriptionFactory
	{
		template <class Archive>
		friend void serialize(Archive& archive, SameNeuronDescriptionFactory& descriptionFactory);
	private:
		/**
		 * \brief Contains the neuron description for all neurons.
		 */
		std::unique_ptr<NeuronDescription> neuronDescription;
	public:
		SameNeuronDescriptionFactory();
		~SameNeuronDescriptionFactory();
		/**
		 * \brief Creates a new SameNeuronDescriptionFactory.
		 * \param neuronDescription_ The neuron description for all neurons.
		 */
		SameNeuronDescriptionFactory(NeuronDescription* neuronDescription_);
		/**
		 * \brief Copy constructor.
		 * \param other A SameNeuronDescriptionFactory which should be copied.
		 */
		SameNeuronDescriptionFactory(const SameNeuronDescriptionFactory& other);
		SameNeuronDescriptionFactory(SameNeuronDescriptionFactory&& other) noexcept;
		SameNeuronDescriptionFactory& operator=(SameNeuronDescriptionFactory other);
		friend void swap(SameNeuronDescriptionFactory& lhs, SameNeuronDescriptionFactory& rhs) noexcept;
		// Inherited:
		NeuronDescription* createInnerNeuronDescription() override;
		NeuronDescription* createOutputNeuronDescription() override;
		AbstractCloneable* clone() const override;
		const AbstractActivationFunction& getOutputActivationFunction() const override;
		const AbstractActivationFunction& getInnerActivationFunction() const override;
		const AbstractInputFunction& getOutputInputFunction() const override;
		const AbstractInputFunction& getInnerInputFunction() const override;
		void setCalculatorType(const CalculatorType& calculatorType) override;
	};
}

#include "LightBulb/IO/SameNeuronDescriptionFactoryIO.hpp"

#endif