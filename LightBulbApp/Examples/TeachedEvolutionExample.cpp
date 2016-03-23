#include "TeachedEvolutionExample.hpp"
#include <Diagnostic/LearningRuleAnalyser.hpp>
#include <Examples/NetworkSimulator.hpp>
#include <Learning/Evolution/RateDifferenceCondition.hpp>
#include <Learning/Evolution/ConstantMutationCommand.hpp>
#include <Learning/Evolution/EvolutionStrategy/MutationAlgorithm.hpp>
#include <Learning/Evolution/BestSelectionCommand.hpp>
#include <Learning/Evolution/ConstantReuseCommand.hpp>
#include <Learning/Evolution/ConstantRecombinationCommand.hpp>
#include <Learning/Evolution/EvolutionStrategy/RecombinationAlgorithm.hpp>
#include <Learning/Evolution/ConstantCreationCommand.hpp>
#include <Diagnostic/ChangeableNumber.hpp>
#include <Learning/Evolution/EvolutionLearningRule.hpp>
#include <Graphics/NeuralNetworkResultChart.hpp>
#include <Teaching/TeachingLessonBooleanInput.hpp>
#include <Teaching/Teacher.hpp>
#include <NetworkTopology/LayeredNetwork.hpp>
#include <NeuronFactory/DifferentNeuronDescriptionFactory.hpp>
#include <Function/WeightedSumFunction.hpp>
#include <Function/FermiFunction.hpp>
#include <Learning/Evolution/TeachingEvolutionWorld.hpp>
#include <ActivationOrder/TopologicalOrder.hpp>
#include <NeuralNetwork/NeuralNetwork.hpp>
#include <Learning/Evolution/RandomSelector.hpp>
#include <Neuron/NeuronDescription.hpp>
#include <Learning/Evolution/AbstractEvolutionObject.hpp>
#include <Learning/Evolution/BestReuseSelector.hpp>


void doTeachedEvolutionExample()
{

	LayeredNetworkOptions layeredNetworkOptions;
	layeredNetworkOptions.descriptionFactory = new DifferentNeuronDescriptionFactory(new NeuronDescription(new WeightedSumFunction(), new FermiFunction(1)), new NeuronDescription(new WeightedSumFunction(), new FermiFunction(1)));
	layeredNetworkOptions.neuronsPerLayerCount = std::vector<unsigned int>(3);
	layeredNetworkOptions.neuronsPerLayerCount[0] = 8;
	layeredNetworkOptions.neuronsPerLayerCount[1] = 3;
	layeredNetworkOptions.neuronsPerLayerCount[2] = 8;
	layeredNetworkOptions.useBiasNeuron = true;

	Teacher teacher;
	for (int i = 0; i<8; i += 1)
	{
		std::vector<std::vector<double>> teachingPattern(1, std::vector<double>(8));
		NeuralNetworkIO<bool>* teachingInput = new NeuralNetworkIO<bool>(8);
		for (int l = 0; l<8; l += 1)
		{
			teachingPattern[0][l] = i == l;
			(*teachingInput).set(0, l, i == l);
		}

		teacher.addTeachingLesson(new TeachingLessonBooleanInput(teachingPattern, teachingInput));
	}

	LayeredNetwork layeredNetwork(layeredNetworkOptions);

	NeuralNetwork neuralNetwork(&layeredNetwork);

	TeachingEvolutionWorld world(&teacher, layeredNetworkOptions);

	EvolutionLearningRuleOptions options;
	RateDifferenceCondition* rateDifferenceCondition = new RateDifferenceCondition(0.00001, 50);
	options.exitConditions.push_back(rateDifferenceCondition);
	ConstantCreationCommand* constantCreationCommand = new ConstantCreationCommand(80);
	options.creationCommands.push_back(constantCreationCommand);
	options.reuseCommands.push_back(new ConstantReuseCommand(new BestReuseSelector(), 1));
	BestSelectionCommand* bestSelectionCommand = new BestSelectionCommand(80);
	options.selectionCommands.push_back(bestSelectionCommand);
	MutationAlgorithm* mutationAlgorithm = new MutationAlgorithm(1.6);
	ConstantMutationCommand* constantMutationCommand = new ConstantMutationCommand(mutationAlgorithm, new RandomSelector(new RankBasedRandomFunction()), 2.0);
	options.mutationsCommands.push_back(constantMutationCommand);
	options.recombinationCommands.push_back(new ConstantRecombinationCommand(new RecombinationAlgorithm(), new RandomSelector(new RankBasedRandomFunction()), 0));
	options.world = &world;
	options.enableDebugOutput = true;
	options.scoreGoal = -0.1;
	options.maxTries = 100;
	EvolutionLearningRule learningRule(options);

	learningRule.doLearning();

	NeuralNetwork* bestNetwork = world.getEvolutionObjects()->front()->getNeuralNetwork();

	TopologicalOrder topologicalOrder;
	double totalError = teacher.getTotalError(*bestNetwork, topologicalOrder);

	std::vector<double> teachingPattern = std::vector<double>(8);
	teachingPattern[0] = 0;
	teachingPattern[1] = 1;
	teachingPattern[2] = 0;
	teachingPattern[3] = 0;
	teachingPattern[4] = 0;
	teachingPattern[5] = 0;
	teachingPattern[6] = 0;
	teachingPattern[7] = 0;

	std::vector<double> output(8);

	bestNetwork->calculate(teachingPattern, output, topologicalOrder);

	std::cout << "end";

	NeuralNetworkResultChartOptions neuralNetworkResultChartOptions;
	neuralNetworkResultChartOptions.neuralNetwork = bestNetwork;
	neuralNetworkResultChartOptions.binaryInterpretation = true;
	neuralNetworkResultChartOptions.xRangeEnd = 1000;
	neuralNetworkResultChartOptions.yRangeEnd = 1000;
	neuralNetworkResultChartOptions.activationOrder = new TopologicalOrder();

	NeuralNetworkResultChart neuralNetworkResultChart(neuralNetworkResultChartOptions);
	neuralNetworkResultChart.recalculateAllValues();


	//AbstractNetworkTopologyDrawerOptions networkTopologyDrawerOptions;
	//networkTopologyDrawerOptions.width = 700;
	//networkTopologyDrawerOptions.height = 600;
	//networkTopologyDrawerOptions.posY = 100;
	//networkTopologyDrawerOptions.network = bestNetwork;
	//LayeredNetworkTopologyDrawer networkTopologyDrawer(networkTopologyDrawerOptions);
	//networkTopologyDrawer.refresh();

	sf::RenderWindow window(sf::VideoMode(800, 700), "LightBulb!");

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		neuralNetworkResultChart.draw(window);
		//networkTopologyDrawer.draw(window);
		window.display();
	}
}