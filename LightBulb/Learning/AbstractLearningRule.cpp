// Includes
#include "Learning/AbstractLearningRule.hpp"
#include "NeuralNetwork/AbstractNeuralNetwork.hpp"
#include "NetworkTopology/LayeredNetwork.hpp"
#include "Teaching/Teacher.hpp"
#include "Teaching/AbstractTeachingLesson.hpp"
#include "ActivationOrder/AbstractActivationOrder.hpp"
// Library includes
#include <iomanip>
#include <iostream>
#include <vector>
#include <limits>
#include <list>

AbstractLearningRule::AbstractLearningRule(AbstractLearningRuleOptions* options_)
{
	options.reset(options_);

	// Check if all given options are correct

	if (options->maxTotalErrorValue <= options->totalErrorGoal)
		throw std::invalid_argument("The maxTotalErrorValue has to be greater than the totalErrorGoal");
	if (!options->logger)
		throw std::invalid_argument("The given logger is invalid.");
}

bool AbstractLearningRule::doLearning(AbstractNeuralNetwork &neuralNetwork, Teacher &teacher)
{
	// Check if all given options are correct
	if (teacher.getTeachingLessons()->size() == 0)
		throw std::invalid_argument("The given teacher does not contain any teachingLessons. So what should i learn??");

	Teacher& initializedTeacher = *initializeTeacher(teacher);
	AbstractNeuralNetwork& initializedNeuralNetwork = *initializeNeuralNetwork(neuralNetwork);
	
	// Ask for the used activation order
	std::unique_ptr<AbstractActivationOrder> activationOrder(getNewActivationOrder(initializedNeuralNetwork));

	// Let the learning algorithm do stuff before starting
	initializeLearningAlgoritm(initializedNeuralNetwork, initializedTeacher, *activationOrder);

	// Create a vector which will contain all weights for offline learning
	std::vector<Eigen::MatrixXd> offlineLearningWeights(initializedNeuralNetwork.getNetworkTopology()->getLayerCount());

	// Reset all counter
	tryCounter = 0;
	totalError = 0;
	
	currentNetworkTopology = initializedNeuralNetwork.getNetworkTopology();
	currentNeuralNetwork = &initializedNeuralNetwork;
	currentTeacher = &initializedTeacher;
	
	// Start a new try
	do
	{
		// Reset the iteration counter
		iteration = 0;

		// Initialize a new try
		initializeTry(initializedNeuralNetwork, initializedTeacher);
		
		// If debug is enabled, print every n-th iteration a short debug info
		log("--------------\nStart Try: " + std::to_string(tryCounter), LL_HIGH);

		
		// Do while the totalError is not zero
		while ((totalError = initializedTeacher.getTotalError(initializedNeuralNetwork, *activationOrder)) > options->totalErrorGoal  && iteration++ < options->maxIterationsPerTry)
		{			
			// If its not the first iteration and the learning process has stopped, skip that try
			if (iteration > 1 && learningHasStopped())
			{	
				// If debug is enabled, print a short debug info
				log("Skip that try (learning has stopped with totalError: " + std::to_string(totalError) + ")", LL_MEDIUM);
				break;
			}

			// If we had more iterations than minIterationsPerTry and the totalError is still greater than the maxTotalErrorValue, skip that try
			if (iteration > options->minIterationsPerTry && totalError > options->maxTotalErrorValue)
			{
				// If debug is enabled, print a short debug info
				log("Skip that try (totalError: " + std::to_string(totalError) +  " > " + std::to_string(options->maxTotalErrorValue) + ")", LL_MEDIUM);
				break;
			}

			// If debug is enabled, print every n-th iteration a short debug info
			if (iteration % options->debugOutputInterval == 0)
			{
				log("TotalError: " + std::to_string(totalError) + " Iteration: " + std::to_string(iteration) + " " + printDebugOutput() + "\n", LL_LOW);
			}

			// If offlineLearning is activated, reset the offlineLearningGradients
			if (options->offlineLearning)
			{
				offlineLearningWeights = *neuralNetwork.getNetworkTopology()->getWeights();
				// Adjust all hidden/output layers except 
				for (int l = 0; l < offlineLearningWeights.size(); l++)
				{
					offlineLearningWeights[l].setZero();
				}
			}

			// Do some work before every iteration
			initializeIteration(initializedNeuralNetwork, initializedTeacher, *activationOrder);

			// Go through every TeachingLesson
			int lessonIndex = 0;
			for (auto teachingLesson = initializedTeacher.getTeachingLessons()->begin(); teachingLesson != initializedTeacher.getTeachingLessons()->end(); teachingLesson++, lessonIndex++)
			{
				// Do some work before every teaching lesson
				initializeTeachingLesson(initializedNeuralNetwork, **teachingLesson);

				// Do some work before all weights will be adjusted
				if (!options->offlineLearning)
					initializeAllWeightAdjustments(initializedNeuralNetwork);

				// Set start and time counter to default values
				int nextStartTime = -1;
				int nextTimeStepCount = -1;

				// While the learning rule wants do some calculation with the current teaching lesson
				while(configureNextErroMapCalculation(&nextStartTime, &nextTimeStepCount, **teachingLesson))
				{
					// Calculate the errormap and also fill - if needed - the output and netInput values map
					std::unique_ptr<ErrorMap_t> errormap = (*teachingLesson)->getErrormap(initializedNeuralNetwork, *activationOrder, /*nextStartTime, nextTimeStepCount,*/  getOutputValuesInTime(), getNetInputValuesInTime());
				
					// Adjust all hidden/output layers except 
					for (int l = initializedNeuralNetwork.getNetworkTopology()->getLayerCount() - 1; l > 0; l--)
					{			
						// Let the algorithm do some work for the actual neuron
						initializeLayerCalculation(*teachingLesson->get(), lessonIndex, l, errormap.get());

						// Calculate the deltaWeight
						Eigen::MatrixXd deltaWeight = calculateDeltaWeightFromLayer(*teachingLesson->get(), lessonIndex, l, errormap.get());

						// If offline learning is activated, add the weight to the offlineLearningWeight, else adjust the weight right now
						if (options->offlineLearning)
							offlineLearningWeights[l - 1] += deltaWeight;
						else
							offlineLearningWeights[l - 1] = deltaWeight;
					}

					// If offline learning is activated, adjust all weights
					if (!options->offlineLearning)
					{
						// Adjust the every hidden/output layer
						for (int l = initializedNeuralNetwork.getNetworkTopology()->getLayerCount() - 1; l > 0; l--)
						{
							// Adjust the weight depending on the sum of all calculated gradients
							adjustWeights(l, offlineLearningWeights[l - 1]);
						}
					}		

				}
				
				// Do some work after all weights were adjusted
				if (!options->offlineLearning)
					doCalculationAfterAllWeightAdjustments(initializedNeuralNetwork);
			}

			// If offline learning is activated, adjust all weights
			if (options->offlineLearning)
			{
				// Do some work before all weights will be adjusted
				initializeAllWeightAdjustments(initializedNeuralNetwork);

				// Adjust the every hidden/output layer
				for (int l = initializedNeuralNetwork.getNetworkTopology()->getLayerCount() - 1; l > 0; l--)
				{
					// Adjust the weight depending on the sum of all calculated gradients
					adjustWeights(l, offlineLearningWeights[l - 1]);
				}

				// Do some work after all weights were adjusted
				doCalculationAfterAllWeightAdjustments(initializedNeuralNetwork);
			}
		}
	} while ((totalError > options->totalErrorGoal || abs(totalError) == std::numeric_limits<double>::infinity()) && ++tryCounter < options->maxTries);
	

	if (totalError <= options->totalErrorGoal)
		log("Try (No. " + std::to_string(tryCounter) + ", " + std::to_string(iteration) + " iterations needed) was successful (totalError: " + std::to_string(totalError) + " < " + std::to_string(options->totalErrorGoal) + ")\n", LL_HIGH);
	else
		log("All tries failed => stop learning", LL_HIGH);
	
	doCalculationAfterLearningProcess(initializedNeuralNetwork, initializedTeacher);

	// Return if learning was successful
	return (totalError <= options->totalErrorGoal);
}

bool AbstractLearningRule::configureNextErroMapCalculation(int* nextStartTime, int* nextTimeStepCount, AbstractTeachingLesson& teachingLesson)
{
	// Per default only calculate every teaching lesson once in all possible timesteps
	if (*nextStartTime != -1)
		return false;
	else
	{
		*nextStartTime = 0;
		*nextTimeStepCount = -1;
		return true;
	}
}

void AbstractLearningRule::log(std::string message, LogLevel level)
{
	if (options->logger)
		options->logger->log(message, level);
}
