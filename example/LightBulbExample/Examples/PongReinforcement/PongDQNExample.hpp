
#pragma once

#ifndef _PONGDQNEXAMPLE_H_
#define _PONGDQNEXAMPLE_H_

#include "TrainingPlans/AbstractReinforcementTrainingPlan.hpp"

class PongReinforcementEnvironment;

class PongDQNExample : public LightBulb::AbstractReinforcementTrainingPlan
{
private:
protected:
	LightBulb::AbstractLearningRule* createLearningRate() override;
	LightBulb::AbstractReinforcementEnvironment* createEnvironment() override;
public:
	PongDQNExample();
	std::string getOriginalName() const override;
	std::string getDescription() const override;
	AbstractTrainingPlan* createNewFromSameType() const override;
	std::string getLearningRuleName() const override;
};

USE_PARENT_SERIALIZATION(PongDQNExample, LightBulb::AbstractReinforcementTrainingPlan, );

#endif
