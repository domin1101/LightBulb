#pragma once

#ifndef _MINIMUMNETINPUTACTIVATIONFUNCTION_H_
#define _MINIMUMNETINPUTACTIVATIONFUNCTION_H_

// Library includes
#include <math.h>

// Includes
#include "Function/AbstractActivationFunction.hpp"

// The MinimumNetInputActivationFunction only activates the neuron with the lowest netInput
class MinimumNetInputActivationFunction : public AbstractActivationFunction
{
private:
public:
	// Inherited
	double execute(double input, AbstractThreshold* threshold);
	double executeDerivation(double input, AbstractThreshold* threshold);
	AbstractActivationFunction* getActivationFunctionCopy();
	double getMaximum();
	double getMinimum();
	bool hasAMaxAndMinimum();
};

#endif