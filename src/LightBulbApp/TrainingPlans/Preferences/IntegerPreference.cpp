﻿// Includes
#include "LightBulbApp/TrainingPlans/Preferences/IntegerPreference.hpp"

namespace LightBulb
{
	IntegerPreference::IntegerPreference(const std::string& name, int defaultValue, int min_, int max_)
		:AbstractVariablePreference(name, defaultValue)
	{
		min = min_;
		max = max_;
	}

	int IntegerPreference::getMin() const
	{
		return min;
	}

	int IntegerPreference::getMax() const
	{
		return max;
	}

	AbstractCloneable* IntegerPreference::clone() const
	{
		return new IntegerPreference(*this);
	}

	std::string IntegerPreference::getValueAsString() const
	{
		return std::to_string(value);
	}
}