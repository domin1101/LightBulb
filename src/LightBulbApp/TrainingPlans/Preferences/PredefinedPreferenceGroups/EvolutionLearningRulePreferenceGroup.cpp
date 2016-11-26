﻿// Includes
#include "TrainingPlans/Preferences/PredefinedPreferenceGroups/EvolutionLearningRulePreferenceGroup.hpp"
#include "ConstantCreationCommandPreferenceGroup.hpp"
#include "BackpropagationPreferenceGroup.hpp"
#include "ConstantMutationCommandPreferenceGroup.hpp"
#include "ConstantReuseCommandPreferenceGroup.hpp"
#include "BestSelectionCommandPreferenceGroup.hpp"
#include "RateDifferenceConditionPreferenceGroup.hpp"
#include "ConstantRecombinationCommandPreferenceGroup.hpp"

namespace LightBulb
{
	EvolutionLearningRulePreferenceGroup::EvolutionLearningRulePreferenceGroup(const std::string& name)
		:AbstractEvolutionLearningRulePreferenceGroup(name)
	{
		EvolutionLearningRuleOptions options;
		initialize(options);
	}

	EvolutionLearningRulePreferenceGroup::EvolutionLearningRulePreferenceGroup(const EvolutionLearningRuleOptions& options, const std::string& name)
		:AbstractEvolutionLearningRulePreferenceGroup(options, name)
	{
		initialize(options);
	}

	void EvolutionLearningRulePreferenceGroup::initialize(const EvolutionLearningRuleOptions& options)
	{
		AbstractEvolutionLearningRulePreferenceGroup::initialize(options);

		addPreference(new RateDifferenceConditionPreferenceGroup());
		addPreference(new ConstantCreationCommandPreferenceGroup());
		addPreference(new BestSelectionCommandPreferenceGroup());
		addPreference(new ConstantMutationCommandPreferenceGroup());
		addPreference(new ConstantRecombinationCommandPreferenceGroup());
		addPreference(new ConstantReuseCommandPreferenceGroup());
	}
	
	EvolutionLearningRuleOptions EvolutionLearningRulePreferenceGroup::create() const
	{
		EvolutionLearningRuleOptions options;
		fillOptions(options);

		options.creationCommands.push_back(createFromGroup<ConstantCreationCommand*, ConstantCreationCommandPreferenceGroup>());
		options.mutationsCommands.push_back(createFromGroup<ConstantMutationCommand*, ConstantMutationCommandPreferenceGroup>());
		options.recombinationCommands.push_back(createFromGroup<ConstantRecombinationCommand*, ConstantRecombinationCommandPreferenceGroup>());
		options.reuseCommands.push_back(createFromGroup<ConstantReuseCommand*, ConstantReuseCommandPreferenceGroup>());
		options.selectionCommands.push_back(createFromGroup<BestSelectionCommand*, BestSelectionCommandPreferenceGroup>());
		options.exitConditions.push_back(createFromGroup<RateDifferenceCondition*, RateDifferenceConditionPreferenceGroup>());

		return options;
	}

	AbstractCloneable* EvolutionLearningRulePreferenceGroup::clone() const
	{
		return new EvolutionLearningRulePreferenceGroup(*this);
	}
}
