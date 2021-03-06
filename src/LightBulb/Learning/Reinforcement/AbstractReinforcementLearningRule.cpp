// Includes
#include "LightBulb/Learning/Reinforcement/AbstractReinforcementLearningRule.hpp"
// Library includes
#include "LightBulb/Learning/Reinforcement/AbstractReinforcementEnvironment.hpp"
#include "LightBulb/Learning/Reinforcement/AbstractReinforcementIndividual.hpp"

namespace LightBulb
{
	AbstractReinforcementLearningRule::AbstractReinforcementLearningRule(AbstractReinforcementLearningRuleOptions* options_)
		: AbstractLearningRule(options_)
	{
		randomGeneratorHasChanged();
	}

	void AbstractReinforcementLearningRule::randomGeneratorHasChanged()
	{
		if (getOptions().environment)
			getOptions().environment->setRandomGenerator(*randomGenerator.get());
		if (getOptions().individual)
			getOptions().individual->setRandomGenerator(*randomGenerator.get());
	}

	bool AbstractReinforcementLearningRule::hasLearningSucceeded()
	{
		return false;
	}

	std::vector<std::string> AbstractReinforcementLearningRule::getDataSetLabels() const
	{
		std::vector<std::string> labels = AbstractLearningRule::getDataSetLabels();
		labels.push_back(DATA_SET_REWARD);
		std::vector<std::string> environmentLabels = getOptions().environment->getDataSetLabels();
		labels.insert(labels.end(), environmentLabels.begin(), environmentLabels.end());
		return labels;
	}


	const AbstractReinforcementLearningRuleOptions& AbstractReinforcementLearningRule::getOptions() const
	{
		return static_cast<AbstractReinforcementLearningRuleOptions&>(*options.get());
	}
}
