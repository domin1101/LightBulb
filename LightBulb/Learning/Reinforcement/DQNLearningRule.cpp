// Includes
#include "Learning/Reinforcement/DQNLearningRule.hpp"
#include "NeuralNetwork/NeuralNetwork.hpp"
#include "NetworkTopology/AbstractNetworkTopology.hpp"
#include "NetworkTopology/LayeredNetwork.hpp"
// Library includes
#include <Learning/EvolutionLearningResult.hpp>
#include "AbstractReinforcementWorld.hpp"
#include <Teaching/TeachingLessonLinearInput.hpp>
#include <ActivationOrder/TopologicalOrder.hpp>

AbstractLearningResult* DQNLearningRule::getLearningResult()
{
	EvolutionLearningResult* learningResult = new EvolutionLearningResult();
	
	return learningResult;
}

DQNLearningRule::DQNLearningRule(DQNLearningRuleOptions& options_)
	: AbstractReinforcementLearningRule(new DQNLearningRuleOptions(options_))
{
	initialize();
}

DQNLearningRule::DQNLearningRule(DQNLearningRuleOptions* options_)
	: AbstractReinforcementLearningRule(options_)
{
	initialize();
}

DQNLearningRule::DQNLearningRule()
	: AbstractReinforcementLearningRule(new DQNLearningRuleOptions())
{
	initialize();
}

void DQNLearningRule::initializeTry()
{
	getOptions()->world->setLearningState(learningState.get());
	getOptions()->world->initializeForLearning();
	steadyNetwork->getNetworkTopology()->copyWeightsFrom(*getOptions()->world->getNeuralNetwork()->getNetworkTopology());
	nextTransitionIndex = 0;
	waitUntilLearningStarts = getOptions()->replayStartSize;
	getOptions()->world->setEpsilon(getOptions()->initialExploration);
}

void DQNLearningRule::initialize()
{
	getOptions()->backpropagationOptions.teacher = &teacher;
	getOptions()->backpropagationOptions.neuralNetwork = getOptions()->world->getNeuralNetwork();
	getOptions()->backpropagationOptions.logger = getOptions()->logger;
	backpropagationLearningRule.reset(new BackpropagationLearningRule(getOptions()->backpropagationOptions));

	steadyNetwork.reset(getOptions()->world->getNeuralNetwork()->clone());
}

void DQNLearningRule::storeTransition(AbstractNetworkTopology* networkTopology, double reward)
{
	Transition transition;
	auto patternVector = networkTopology->getActivationVector(0);
	transition.state = std::vector<double>(patternVector.data() + networkTopology->usesBiasNeuron(), patternVector.data() + patternVector.size());

	if (!getOptions()->world->isTerminalState()) {
		 getOptions()->world->getNNInput(transition.nextState);
	}

	transition.reward = reward;	
	
	for (int i = 0; i < getOptions()->world->getLastBooleanOutput().size(); i++)
	{
		if (getOptions()->world->getLastBooleanOutput()[i])
		{
			transition.action = i;
			break;
		}
	}

	if (transitions.size() < getOptions()->replayMemorySize)
	{
		transitions.push_back(transition);
	} 
	else
	{
		transitions[nextTransitionIndex++] = transition;
		nextTransitionIndex %= transitions.size();
	}

}

void DQNLearningRule::doSupervisedLearning()
{
	teacher.getTeachingLessons()->clear();

	for (int i = 0; i < getOptions()->minibatchSize; i++)
	{
		int r = rand() % transitions.size();

		double y = transitions[r].reward;

		if (!transitions[r].nextState.empty())
		{
			std::vector<double> output(steadyNetwork->getNetworkTopology()->getOutputSize());
			steadyNetwork->calculate(transitions[r].nextState, output, TopologicalOrder());
			double q = *std::max_element(output.begin(), output.end());
			y += 0.99 * q;
		}

		NeuralNetworkIO<double>* input = new NeuralNetworkIO<double>(steadyNetwork->getNetworkTopology()->getOutputSize());

		input->set(0, transitions[r].action, y);

		teacher.addTeachingLesson(new TeachingLessonLinearInput(std::vector<std::vector<double>>(1, transitions[r].state), input));
	}

	//auto gradient = checkGradient(&teacher, getOptions()->world->getNeuralNetwork()->getNetworkTopology());

	std::unique_ptr<AbstractLearningResult> result(backpropagationLearningRule->start());
	currentTotalError += result->quality;
}

std::string DQNLearningRule::getName()
{
	return "DQNLearningRule";
}

std::vector<std::string> DQNLearningRule::getDataSetLabels()
{
	std::vector<std::string> labels = AbstractReinforcementLearningRule::getDataSetLabels();
	labels.push_back(DATA_SET_TRAINING_ERROR);
	return labels;
}


std::vector<Eigen::MatrixXd> DQNLearningRule::checkGradient(Teacher* teacher, AbstractNetworkTopology* networkTopology)
{
	double error = teacher->getTotalError(*getOptions()->world->getNeuralNetwork(), TopologicalOrder());
	double epsilon = 0.0001;
	auto weights = networkTopology->getWeights();
	std::vector<Eigen::MatrixXd> gradientApprox(weights->size());
	for (int l = weights->size() - 1; l >= 0; l--)
	{
		gradientApprox[l].resizeLike(weights->at(l));
		for (int n1 = 0; n1 < weights->at(l).rows(); n1++)
		{
			for (int n2 = 0; n2 < weights->at(l).cols(); n2++)
			{
				weights->at(l)(n1, n2) += epsilon;
				double firstError = teacher->getTotalError(*getOptions()->world->getNeuralNetwork(), TopologicalOrder());

				weights->at(l)(n1, n2) -= epsilon * 2;
				double secondError = teacher->getTotalError(*getOptions()->world->getNeuralNetwork(), TopologicalOrder());
				gradientApprox[l](n1, n2) = (firstError - secondError) / (2 * epsilon);

				weights->at(l)(n1, n2) += epsilon;
			}
		}
	}
	return gradientApprox;
}

bool DQNLearningRule::doIteration()
{
	currentTotalError = 0;
	int rewardCounter = 0;
	double totalReward = 0;
	int totalEpisodes = 1;
	AbstractNetworkTopology* networkTopology = getOptions()->world->getNeuralNetwork()->getNetworkTopology();

	for (int i = 0; i < getOptions()->targetNetworkUpdateFrequency; i++) {
		double reward = getOptions()->world->doSimulationStep();
		totalReward += reward;
		if (getOptions()->world->isTerminalState())
			totalEpisodes++;

		storeTransition(networkTopology, reward);

		if (waitUntilLearningStarts > 0)
			waitUntilLearningStarts--;
		else
			doSupervisedLearning();

		double e = getOptions()->world->getEpsilon();
		if (e > getOptions()->finalExploration)
			getOptions()->world->setEpsilon(e - (getOptions()->initialExploration - getOptions()->finalExploration) / getOptions()->finalExplorationFrame);
	}


	learningState->addData(DATA_SET_REWARD, totalReward / totalEpisodes);
	
	learningState->addData(DATA_SET_TRAINING_ERROR, currentTotalError / getOptions()->targetNetworkUpdateFrequency);
		
	steadyNetwork->getNetworkTopology()->copyWeightsFrom(*getOptions()->world->getNeuralNetwork()->getNetworkTopology());


	// Continue with the next generation
	learningState->iterations++;

	double e = getOptions()->world->getEpsilon();
	getOptions()->world->setEpsilon(0);
	getOptions()->world->rateKI();	
	getOptions()->world->setEpsilon(e);

	return true;
}


DQNLearningRuleOptions* DQNLearningRule::getOptions()
{
	return static_cast<DQNLearningRuleOptions*>(options.get());
}
