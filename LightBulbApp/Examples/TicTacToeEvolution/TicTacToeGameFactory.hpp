#pragma once

#ifndef _TICTACTOEGAMEFACTORY_H_
#define _TICTACTOEGAMEFACTORY_H_

// Includes
#include <Windows/AbstractCustomSubAppFactory.hpp>

// Forward declarations
class TrainingPlanRepository;

class TicTacToeGameFactory : public AbstractCustomSubAppFactory
{
protected:
public:
	AbstractCustomSubApp* createCustomSupApp(AbstractTrainingPlan* trainingPlan, AbstractWindow* parent);
	std::string getLabel();
};

#endif