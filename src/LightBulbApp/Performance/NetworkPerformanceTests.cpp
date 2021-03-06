#include "LightBulbApp/Performance/NetworkPerformanceTests.hpp"
#include "LightBulb/NetworkTopology/FeedForwardNetworkTopology.hpp"
#include "LightBulb/NeuronDescription/SameNeuronDescriptionFactory.hpp"
#include "LightBulb/Function/InputFunction/WeightedSumFunction.hpp"
#include "LightBulb/Function/ActivationFunction/BinaryFunction.hpp"
#include "LightBulb/NeuralNetwork/NeuralNetwork.hpp"
#include "LightBulb/ActivationOrder/TopologicalOrder.hpp"
#include "LightBulb/NeuronDescription/NeuronDescription.hpp"

namespace LightBulb
{
	void doNetworkPerformanceTest()
	{
		FeedForwardNetworkTopologyOptions FeedForwardNetworkTopologyOptions;
		FeedForwardNetworkTopologyOptions.descriptionFactory = new SameNeuronDescriptionFactory(new NeuronDescription(new WeightedSumFunction(), new BinaryFunction()));
		FeedForwardNetworkTopologyOptions.neuronsPerLayerCount = std::vector<unsigned int>(3);
		FeedForwardNetworkTopologyOptions.neuronsPerLayerCount[0] = 8;
		FeedForwardNetworkTopologyOptions.neuronsPerLayerCount[1] = 3;
		FeedForwardNetworkTopologyOptions.neuronsPerLayerCount[2] = 8;

		FeedForwardNetworkTopology* networkTopology = new FeedForwardNetworkTopology(FeedForwardNetworkTopologyOptions);

		NeuralNetwork neuralNetwork(networkTopology);
		std::vector<double> input(8);
		std::vector<double> output(8);
		TopologicalOrder activationOrder;
		clock_t begin = clock();
		for (int i = 0; i < 1000000; i++) {
			neuralNetwork.calculate(input, output, activationOrder);
		}
		clock_t end = clock();
		double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
		std::cout << "Elapsed time:" << std::fixed << std::setprecision(4) << elapsed_secs << std::endl;
	}
}
