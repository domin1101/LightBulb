#pragma once

#ifndef _GAUSSIANRBFFUNCTION_H_
#define _GAUSSIANRBFFUNCTION_H_

// Library includes
#include <math.h>

// Includes
#include "AbstractActivationFunction.hpp"

// The IdentityFunction just returns the input without calculating anything
class GaussianRBFFunction : public AbstractActivationFunction
{
private:
public:
	// Just returns the given input
	float execute(float input, AbstractThreshold* threshold);
	// Returns always 0
	float executeDerivation(float input, AbstractThreshold* threshold);
	AbstractActivationFunction* getActivationFunctionCopy();
	float getMaximum();
	float getMinimum();
	bool isLinear();
};

#endif