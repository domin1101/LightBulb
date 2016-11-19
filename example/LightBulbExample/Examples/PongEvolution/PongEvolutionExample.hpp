
#pragma once

#ifndef _PONGEVOLUTIONEXAMPLE_H_
#define _PONGEVOLUTIONEXAMPLE_H_

#include "TrainingPlans/AbstractCoevolutionTrainingPlan.hpp"
#include "NetworkTopology/FeedForwardNetworkTopology.hpp"
#include "Learning/Evolution/SharedSamplingCombiningStrategy.hpp"


class PongEvolutionExample : public LightBulb::AbstractCoevolutionTrainingPlan
{
private:
	LightBulb::AbstractHallOfFameAlgorithm* hof1;
	LightBulb::AbstractHallOfFameAlgorithm* hof2;
	LightBulb::SharedSamplingCombiningStrategy* cs1;
	LightBulb::SharedSamplingCombiningStrategy* cs2;
protected:
	LightBulb::AbstractLearningRule* createLearningRate() override;
	LightBulb::FeedForwardNetworkTopologyOptions getNetworkOptions();
	LightBulb::AbstractEvolutionEnvironment* createEnvironment() override;
	LightBulb::AbstractEvolutionEnvironment* createParasiteEnvironment() override;
public:
	PongEvolutionExample();
	std::string getOriginalName() const override;
	std::string getDescription() const override;
	AbstractTrainingPlan* createNewFromSameType() const override;
	std::string getLearningRuleName() const override;
};

USE_PARENT_SERIALIZATION(PongEvolutionExample, LightBulb::AbstractCoevolutionTrainingPlan, );

#endif
