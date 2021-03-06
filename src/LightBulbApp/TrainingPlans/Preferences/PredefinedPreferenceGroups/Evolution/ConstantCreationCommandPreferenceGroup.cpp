﻿// Includes
#include "LightBulbApp/TrainingPlans/Preferences/PredefinedPreferenceGroups/Evolution/ConstantCreationCommandPreferenceGroup.hpp"
#include "LightBulbApp/TrainingPlans/Preferences/IntegerPreference.hpp"
#include "LightBulb/Learning/Evolution/ConstantCreationCommand.hpp"


namespace LightBulb
{
	#define PREFERENCE_INDIVIDUAL_COUNT "Individual count"

	ConstantCreationCommandPreferenceGroup::ConstantCreationCommandPreferenceGroup(const std::string& name)
		:PreferenceGroup(name)
	{
		addPreference(new IntegerPreference(PREFERENCE_INDIVIDUAL_COUNT, 20, 1, 100));
	}

	ConstantCreationCommand* ConstantCreationCommandPreferenceGroup::create() const
	{
		int individualCount = getIntegerPreference(PREFERENCE_INDIVIDUAL_COUNT);
		return new ConstantCreationCommand(individualCount);
	}

	AbstractCloneable* ConstantCreationCommandPreferenceGroup::clone() const
	{
		return new ConstantCreationCommandPreferenceGroup(*this);
	}
}
