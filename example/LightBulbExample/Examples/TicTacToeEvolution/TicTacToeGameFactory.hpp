#pragma once

#ifndef _TICTACTOEGAMEFACTORY_H_
#define _TICTACTOEGAMEFACTORY_H_

// Includes
#include "LightBulbApp/Windows/AbstractCustomSubAppFactory.hpp"

// Forward declarations
class TrainingPlanRepository;

class TicTacToeGameFactory : public LightBulb::AbstractCustomSubAppFactory
{
protected:
public:
	LightBulb::AbstractCustomSubApp* createCustomSupApp(LightBulb::AbstractMainApp& mainApp, LightBulb::AbstractTrainingPlan& trainingPlan, LightBulb::AbstractWindow& parent) const override;
	std::string getLabel() const override;
};

#endif
