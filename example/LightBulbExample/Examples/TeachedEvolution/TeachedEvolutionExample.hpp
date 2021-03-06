
#pragma once

#ifndef _TEACHEDEVOLUTIONEXAMPLE_H_
#define _TEACHEDEVOLUTIONEXAMPLE_H_

#include "LightBulbApp/TrainingPlans/AbstractEvolutionTrainingPlan.hpp"

class TeachedEvolutionExample : public LightBulb::AbstractEvolutionTrainingPlan
{
private:
protected:
	LightBulb::AbstractLearningRule* createLearningRate() override;
	LightBulb::AbstractEvolutionEnvironment* createEnvironment() override;
public:
	std::string getOriginalName() const override;
	std::string getDescription() const override;
	AbstractTrainingPlan* createNewFromSameType() const override;
	std::string getLearningRuleName() const override;
};

USE_PARENT_SERIALIZATION_WITHOUT_NAMESPACE(TeachedEvolutionExample, LightBulb::AbstractEvolutionTrainingPlan);

#endif
