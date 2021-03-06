#include "PongDQNExample.hpp"
#include "Examples/PongEvolution/PongGameFactory.hpp"
#include "PongReinforcementEnvironment.hpp"
#include "LightBulbApp/TrainingPlans/Preferences/PredefinedPreferenceGroups/Reinforcement/DQNLearningRulePreferenceGroup.hpp"
#include "LightBulb/Learning/Reinforcement/DQNLearningRule.hpp"
#include "LightBulb/NeuronDescription/DifferentNeuronDescriptionFactory.hpp"
#include "LightBulb/Function/InputFunction/WeightedSumFunction.hpp"
#include "LightBulb/Function/ActivationFunction/RectifierFunction.hpp"
#include "LightBulb/Function/ActivationFunction/IdentityFunction.hpp"
#include "LightBulb/NetworkTopology/FeedForwardNetworkTopology.hpp"
#include "LightBulb/NeuronDescription/NeuronDescription.hpp"
#include "LightBulbApp/TrainingPlans/Preferences/BooleanPreference.hpp"
#include "LightBulbApp/TrainingPlans/Preferences/IntegerPreference.hpp"
#include "PongReinforcementIndividual.hpp"


#define PREFERENCE_SHORTCUT_ENABLE "Enable shortcut connections"
#define PREFERENCE_NEURON_COUNT_FIRST_LAYER "Neuron count in 1. layer"
#define PREFERENCE_SECOND_LAYER_ENABLE "Enable 2. layer"
#define PREFERENCE_NEURON_COUNT_SECOND_LAYER "Neuron count in 2. layer"
#define PREFERENCE_USE_BIAS_NEURON "Use bias neuron"
#define PREFERENCE_LEARNING_RATE "Learning rate"
#define PREFERENCE_MINIBATCH_SIZE "Minibatch size"
#define PREFERENCE_TARGET_NETWORK_UPDATE_FREQUENCY "Target network update frequency"
#define PREFERENCE_REPLAY_MEMORY_SIZE "replay memory size"
#define PREFERENCE_FINAL_EXPLORATION_FRAME "final exploration frame"
#define PREFERENCE_CLIP_ERROR "Clip error"
#define PREFERENCE_RMSMPROP_LEARNING_RATE "RMSProp learning rate"
#define PREFERENCE_MOMENTUM "Momentum"
#define PREFERENCE_REPLAY_START_SIZE "Replay start size"
#define PREFERENCE_DISCOUNT_FACTOR "Discount factor"
#define PREFERENCE_REPLACE_STORED_TRANSITIONS "Replace stored transitions"

using namespace LightBulb;

AbstractLearningRule* PongDQNExample::createLearningRate()
{
	DQNLearningRuleOptions options = createOptions<DQNLearningRuleOptions, DQNLearningRulePreferenceGroup>();
	//options.dataSaveInterval = 100;
	fillDefaultLearningRuleOptions(options);

	return new DQNLearningRule(options);
}


AbstractReinforcementEnvironment* PongDQNExample::createEnvironment()
{
	return new PongReinforcementEnvironment();
}

LightBulb::AbstractReinforcementIndividual* PongDQNExample::createIndividual()
{
	FeedForwardNetworkTopologyOptions options;
	options.enableShortcuts = getBooleanPreference(PREFERENCE_SHORTCUT_ENABLE);
	options.useBiasNeuron = getBooleanPreference(PREFERENCE_USE_BIAS_NEURON);

	options.neuronsPerLayerCount.push_back(6);
	options.neuronsPerLayerCount.push_back(getIntegerPreference(PREFERENCE_NEURON_COUNT_FIRST_LAYER));
	if (getBooleanPreference(PREFERENCE_SECOND_LAYER_ENABLE))
		options.neuronsPerLayerCount.push_back(getIntegerPreference(PREFERENCE_NEURON_COUNT_SECOND_LAYER));
	options.neuronsPerLayerCount.push_back(3);

	options.descriptionFactory = new DifferentNeuronDescriptionFactory(new NeuronDescription(new WeightedSumFunction(), new RectifierFunction()), new NeuronDescription(new WeightedSumFunction(), new IdentityFunction()));
	
	return new PongReinforcementIndividual(&getEnvironment(), options, true, 1);
}


PongDQNExample::PongDQNExample()
{
	addCustomSubApp(new PongGameFactory());
	addPreference(new BooleanPreference(PREFERENCE_SHORTCUT_ENABLE, false));
	addPreference(new BooleanPreference(PREFERENCE_USE_BIAS_NEURON, true));
	addPreference(new IntegerPreference(PREFERENCE_NEURON_COUNT_FIRST_LAYER, 256, 1, 30));
	addPreference(new BooleanPreference(PREFERENCE_SECOND_LAYER_ENABLE, false));
	addPreference(new IntegerPreference(PREFERENCE_NEURON_COUNT_SECOND_LAYER, 1, 1, 30));

	DQNLearningRuleOptions options;
	options.rmsPropOptions.learningRate = 0.0005;
	options.finalExplorationFrame = 500000;
	options.rmsPropOptions.deltaWeightsMomentum = 0;
	addPreferenceGroup(new DQNLearningRulePreferenceGroup(options));
}

std::string PongDQNExample::getOriginalName() const
{
	return "Pong DQN example";
}

std::string PongDQNExample::getDescription() const
{
	return "Evolution of a Pong AI with DQN.";
}

AbstractTrainingPlan* PongDQNExample::createNewFromSameType() const
{
	return new PongDQNExample();
}

std::string PongDQNExample::getLearningRuleName() const
{
	return getName();
}
