// Includes
#include "LightBulb/LinearAlgebra/AbstractLinearAlgebraUser.hpp"
#include "LightBulb/LinearAlgebra/AbstractLinearAlgebraObject.hpp"

namespace LightBulb
{
	AbstractLinearAlgebraUser::AbstractLinearAlgebraUser()
	{
		calculatorType = CT_CPU;
	}


	void AbstractLinearAlgebraUser::setCalculatorType(const CalculatorType& calculatorType_)
	{
		calculatorType = calculatorType_;
	}

	bool AbstractLinearAlgebraUser::isCalculatorType(const CalculatorType& calculatorType_) const
	{
		return calculatorType == calculatorType_;
	}

	const CalculatorType& AbstractLinearAlgebraUser::getCalculatorType() const
	{
		return calculatorType;
	}
}
