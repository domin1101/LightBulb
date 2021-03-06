﻿// Includes
#include "LightBulbApp/TrainingPlans/Preferences/PredefinedPreferenceGroups/Evolution/ConstantReuseCommandPreferenceGroup.hpp"
#include "LightBulbApp/TrainingPlans/Preferences/IntegerPreference.hpp"
#include "LightBulb/Learning/Evolution/ConstantReuseCommand.hpp"
#include "LightBulb/Learning/Evolution/BestReuseSelector.hpp"

namespace LightBulb
{
	#define PREFERENCE_INDIVIDUAL_COUNT "Individual count"

	ConstantReuseCommandPreferenceGroup::ConstantReuseCommandPreferenceGroup(const std::string& name)
		:PreferenceGroup(name)
	{
		addPreference(new IntegerPreference(PREFERENCE_INDIVIDUAL_COUNT, 1, 0, 20));
	}

	ConstantReuseCommand* ConstantReuseCommandPreferenceGroup::create() const
	{
		int individualCount = getIntegerPreference(PREFERENCE_INDIVIDUAL_COUNT);
		return new ConstantReuseCommand(new BestReuseSelector(), individualCount);
	}

	AbstractCloneable* ConstantReuseCommandPreferenceGroup::clone() const
	{
		return new ConstantReuseCommandPreferenceGroup(*this);
	}
}
