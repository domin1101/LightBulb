#pragma once

#ifndef _HYPERBOLICTANGENTFUNCTION_H_
#define _HYPERBOLICTANGENTFUNCTION_H_

// Library includes
#include <math.h>

// Includes
#include "LightBulb/Function/ActivationFunction/AbstractActivationFunction.hpp"
#include "LightBulb/IO/UseParentSerialization.hpp"

namespace LightBulb
{
	/**
	 * \brief The HyperbolicTangentFunction is a sigmoid function between -1 and 1
	 * \details Describes: \n \n \f$f(x)=\tanh(x)\f$ \n \n
	 * Derivative: \n \n \f$ f'(x) = \frac{1}{\cosh(x)^2} \f$
	 */
	class HyperbolicTangentFunction : public AbstractActivationFunction
	{
	private:
	public:
		// Inherited
		double execute(double input) const override;
		double executeDerivation(double input) const override;
		AbstractCloneable* clone() const override;
		double getMaximum() const override;
		double getMinimum() const override;
		bool hasAMaxAndMinimum() const override;
	};
}

USE_PARENT_SINGLE_SERIALIZATION(LightBulb::HyperbolicTangentFunction, LightBulb::AbstractActivationFunction, LightBulb);
#endif