#pragma once

#ifndef _MOCKNEURONDESCRIPTIONFACTORY_H_
#define _MOCKNEURONDESCRIPTIONFACTORY_H_

#include "gmock/gmock.h"
#include <LightBulb/NeuronDescription/AbstractNeuronDescriptionFactory.hpp>
#include "LightBulb/Function/InputFunction/AbstractInputFunction.hpp"

class MockNeuronDescriptionFactory : public LightBulb::AbstractNeuronDescriptionFactory
{
public:
	MOCK_METHOD0(createInnerNeuronDescription, LightBulb::NeuronDescription* ());
	MOCK_METHOD0(createOutputNeuronDescription, LightBulb::NeuronDescription* ());
	MOCK_CONST_METHOD0(getOutputActivationFunction, const LightBulb::AbstractActivationFunction& ());
	MOCK_CONST_METHOD0(getInnerActivationFunction, const LightBulb::AbstractActivationFunction& ());
	MOCK_CONST_METHOD0(getOutputInputFunction, const LightBulb::AbstractInputFunction& ());
	MOCK_CONST_METHOD0(getInnerInputFunction, const LightBulb::AbstractInputFunction& ());
	AbstractCloneable* clone() const override { return new MockNeuronDescriptionFactory(); };
};

#endif
