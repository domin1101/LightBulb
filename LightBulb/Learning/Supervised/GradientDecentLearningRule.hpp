#pragma once

#ifndef _GRADIENTDECENTLEARNINGRULE_H_
#define _GRADIENTDECENTLEARNINGRULE_H_

// Library Includes
#include <vector>
#include <map>
#include <EigenSrc/Dense>

// Includes
#include "Learning/Supervised/AbstractSupervisedLearningRule.hpp"
#include <cereal/access.hpp>

// Forward declarations
class AbstractGradientCalculation;
class AbstractGradientDecentAlgorithm;

struct GradientDecentLearningRuleOptions : public AbstractSupervisedLearningRuleOptions
{	
	AbstractGradientCalculation* gradientCalculation;

	AbstractGradientDecentAlgorithm* gradientDecentAlgorithm;

	GradientDecentLearningRuleOptions()
	{
		offlineLearning = false;
		gradientCalculation = NULL;
		gradientDecentAlgorithm = NULL;
	}
};

// The BackpropagationLearningRule can  be used to train MultiPerceptronNetworks
class GradientDecentLearningRule : public AbstractSupervisedLearningRule
{
	friend class CascadeCorrelationLearningRule;
	template <class Archive>
	friend void serialize(Archive& archive, GradientDecentLearningRule& learningRule);
	friend struct cereal::LoadAndConstruct<GradientDecentLearningRule>;
private:	
	void initialize();
protected:
	// Adjusts the weights of an edge dependent on its gradient
	void adjustWeights(int layerIndex, Eigen::MatrixXd gradients);
	// Returns our current options in form of a AbstractBackpropagationLearningRuleOptions object
	GradientDecentLearningRuleOptions* getOptions();
	// Inherited:
	std::string printDebugOutput();
	bool learningHasStopped();
	std::vector<Eigen::MatrixXd> calculateDeltaWeight(AbstractTeachingLesson& lesson, int lessonIndex, ErrorMap_t* errormap);
	void initializeTry();
public:
	GradientDecentLearningRule(GradientDecentLearningRuleOptions& options_);
	GradientDecentLearningRule(GradientDecentLearningRuleOptions* options_);
	static std::string getName();
};

//#include "IO/BackpropagationLearningRuleIO.hpp"

#endif

