#pragma once

#ifndef _LOGGERCONTROLLER_H_
#define _LOGGERCONTROLLER_H_

// Library includes
#include <vector>
#include <NeuralNetwork/AbstractNeuralNetwork.hpp>

// Includes
#include "TrainingPlans/AbstractTrainingPlan.hpp"
#include "LoggerWindow.hpp"
#include "AbstractSubApp.hpp"

// Forward declarations
class TrainingWindow;
class TrainingPlanRepository;

class LoggerController : public AbstractSubApp
{
private:
	std::unique_ptr<LoggerWindow> window;
	TrainingPlanRepository* trainingPlanRepository;
	AbstractTrainingPlan* selectedTrainingPlan;
	int lastLogMessageIndex;
	void reloadLog();
	void addLogMessage(std::string message);
	void addNewLogMessages();
public:
	LoggerController(TrainingPlanRepository* trainingPlanRepository, AbstractWindow* parent = NULL);
	void show();
	void trainingPlansChanged(TrainingPlanRepository* trainingPlanRepository);
	std::vector<std::unique_ptr<AbstractTrainingPlan>>* getTrainingPlans();
	LoggerWindow* getWindow();
	void setLogLevel(int level);
	void logChanged(AbstractLogger* logger);
	static std::string getLabel();
	void selectTrainingPlan(int trainingPlanIndex);
};

#endif
