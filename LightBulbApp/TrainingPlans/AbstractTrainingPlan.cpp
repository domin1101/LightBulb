﻿// Includes
#include "TrainingPlans/AbstractTrainingPlan.hpp"
#include <thread>
#include <NeuralNetwork/AbstractNeuralNetwork.hpp>

AbstractTrainingPlan::AbstractTrainingPlan()
{
	threadShouldBeJoinedBeforeReuse = false;
	state = TP_IDLE;
}

void AbstractTrainingPlan::start(AbstractNeuralNetwork* network_)
{
	if (state == TP_IDLE)
	{
		if (network_ != NULL)
			network = network_;
		else
			network = createNeuralNetwork();
		network->setState(NN_STATE_TRAINED);
		state = TP_RUNNING;
		thread = std::thread(&AbstractTrainingPlan::runThread, this, true);
	}
	else if (state == TP_PAUSED)
	{
		state = TP_RUNNING;
		if (threadShouldBeJoinedBeforeReuse)
		{
			thread.join();
			threadShouldBeJoinedBeforeReuse = false;
		}
		thread = std::thread(&AbstractTrainingPlan::runThread, this, false);
	}
}

AbstractNeuralNetwork* AbstractTrainingPlan::getNeuralNetwork()
{
	return network;
}

std::string AbstractTrainingPlan::getStateAsString()
{
	switch (state)
	{
	case TP_IDLE:
		return "idle";
	case TP_PAUSING:
		return "pausing";
	case TP_RUNNING:
		return "running";
	case TP_PAUSED:
		return "paused";
	case TP_FINISHED :
		return "finished";
	default:
		return "";
	}
}

AbstractTrainingPlan* AbstractTrainingPlan::getCopyForExecute()
{
	AbstractTrainingPlan* copy = getCopy();
	copy->pattern = this;
	return copy;
}

AbstractTrainingPlan* AbstractTrainingPlan::getTrainingPlanPattern()
{
	return pattern;
}

void AbstractTrainingPlan::pause()
{
	if (state == TP_RUNNING)
	{
		state = TP_PAUSING;
		tryToPause();
	}
}

bool AbstractTrainingPlan::isPaused()
{
	return state == TP_PAUSED;
}

bool AbstractTrainingPlan::isPausing()
{
	return state == TP_PAUSING;
}

bool AbstractTrainingPlan::isRunning()
{
	return state == TP_RUNNING;
}

void AbstractTrainingPlan::runThread(bool initial)
{
	run(initial);
	threadShouldBeJoinedBeforeReuse = true;
}

void AbstractTrainingPlan::pausingFinished()
{
	state = TP_PAUSED;
	throwEvent(EVT_TP_PAUSED, this);
}

void AbstractTrainingPlan::finished()
{
	state = TP_FINISHED;
	throwEvent(EVT_TP_FINISHED, this);
}

void AbstractTrainingPlan::setLogger(AbstractLogger* newLogger)
{
	logger = newLogger;
}