// Includes
#include "Teaching/AbstractTeachingLesson.hpp"
#include "NeuralNetwork/AbstractNeuralNetwork.hpp"
#include "NetworkTopology/AbstractNetworkTopology.hpp"
#include "NeuralNetwork/NeuralNetworkIO.hpp"
// Library includes
#include <math.h>
#include "NeuronDescription/NeuronDescription.hpp"

namespace LightBulb
{
	std::vector<std::vector<double>> AbstractTeachingLesson::tryLesson(AbstractNeuralNetwork& neuralNetwork, const AbstractActivationOrder& activationOrder, std::vector<std::map<AbstractNeuron*, double>>* outputValuesInTime, std::vector<std::map<AbstractNeuron*, double>>* netInputValuesInTime) const
	{
		std::vector<std::vector<double>> output(getTeachingPattern().size(), std::vector<double>(neuralNetwork.getNetworkTopology().getOutputSize()));
		// Let the network calculate
		neuralNetwork.calculate(getTeachingPattern(), output, activationOrder, 0, -1, outputValuesInTime, netInputValuesInTime);
		return output;
	}

	std::unique_ptr<ErrorMap_t> AbstractTeachingLesson::getErrormap(AbstractNeuralNetwork& neuralNetwork, const AbstractActivationOrder& activationOrder, std::vector<std::map<AbstractNeuron*, double>>* outputValuesInTime, std::vector<std::map<AbstractNeuron*, double>>* netInputValuesInTime, bool clipError) const
	{
		std::unique_ptr<ErrorMap_t> errorMap;

		// Try the lesson and extract the output
		std::vector<std::vector<double>> outputVector = tryLesson(neuralNetwork, activationOrder, outputValuesInTime, netInputValuesInTime);
		errorMap = getErrormapFromOutputVector(outputVector, neuralNetwork, clipError);

		return errorMap;
	}


	std::unique_ptr<ErrorMap_t> AbstractTeachingLesson::getErrormapFromOutputVector(const std::vector<std::vector<double>>& outputVector, AbstractNeuralNetwork& neuralNetwork, bool clipError) const
	{
		// Get the teachingInput
		const NeuralNetworkIO<double>& teachingInput = getTeachingInput(neuralNetwork.getNetworkTopology().getOutputNeuronDescription().getActivationFunction());

		// Create the errorMap
		std::unique_ptr<ErrorMap_t> errorMap(new ErrorMap_t(teachingInput.getMaxTimeStep() + 1, Eigen::VectorXd(teachingInput.getDimension())));

		// Calculate the error values (expected value - real value)
		for (int timestep = 0; timestep < teachingInput.size(); timestep++)
		{
			(*errorMap)[timestep].setZero();
			if (teachingInput.existsTimestep(timestep))
			{
				for (unsigned int i = 0; i < teachingInput.getDimension(); i++)
				{
					if (teachingInput.exists(timestep, i))
					{
						(*errorMap)[timestep][i] = teachingInput.get(timestep, i) - outputVector[timestep][i];
						if (clipError)
							(*errorMap)[timestep][i] = std::max(-1.0, std::min(1.0, (*errorMap)[timestep][i]));
					}
				}
			}
		}

		return errorMap;
	}


	double AbstractTeachingLesson::getSpecificError(AbstractNeuralNetwork& neuralNetwork, const AbstractActivationOrder& activationOrder, bool clipError) const
	{
		// Calculate the errorVector
		std::unique_ptr<ErrorMap_t> errorMap = getErrormap(neuralNetwork, activationOrder, nullptr, nullptr, clipError);

		double specificError = 0;

		for (auto errorValues = errorMap->begin(); errorValues != errorMap->end(); errorValues++)
		{
			// Add the square of every errorValue in the errorVector
			for (int i = 0; i < errorValues->rows(); i++)
			{
				specificError += pow((*errorValues)[i], 2.0);
			}
		}

		// Divide the specific error by two
		specificError /= 2;

		return specificError;
	}

}