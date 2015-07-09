#pragma once

#ifndef _RBFINTERPOLATIONLEARNINGRULE_H_
#define _RBFINTERPOLATIONLEARNINGRULE_H_

// Library Includes
#include "EigenSrc\Dense"
#include "EigenSrc\Jacobi"

// Includes
#include "Learning\AbstractLearningRule.hpp"
#include "ClusterAnalysis\AbstractRBFNeuronPlacer.hpp"

// Forward declarations
class NeuralNetwork;
class Teacher;

struct RBFInterpolationLearningRuleOptions : AbstractLearningRuleOptions
{	
	// The neuronPlacer helps to replace all RBFNeurons before starting to learn
	AbstractRBFNeuronPlacer* neuronPlacer;
	RBFInterpolationLearningRuleOptions()
	{
		
	}
	~RBFInterpolationLearningRuleOptions()
	{
		delete(neuronPlacer);
	}
	RBFInterpolationLearningRuleOptions(const RBFInterpolationLearningRuleOptions &obj)
	{
		*this = obj;
		neuronPlacer = obj.neuronPlacer->getCopy();
	}
};

// The DeltaLearningRule can only be used to train SingleLayerPerceptronNetworks
class RBFInterpolationLearningRule : public AbstractLearningRule
{
private:
	// A matrix which will contain all outputValues from neurons in the second layer in every teachingLesson
	std::unique_ptr<Eigen::MatrixXf> m;
	// Inversion of m
	std::unique_ptr<Eigen::MatrixXf> mInverse;
	// A matrx which will contain all teachingInput values from all output neurons
	std::unique_ptr<Eigen::MatrixXf> t;
	// A vector which will contain all calculated weights
	std::unique_ptr<Eigen::VectorXf> w;	
	// Holds the actual teacher
	Teacher* actTeacher;
protected:
	// Returns our current options in form of a RBFInterpolatioLearningRuleOptions object
	RBFInterpolationLearningRuleOptions* getOptions();
	// Inherited:
	void adjustWeight(Edge* edge, float deltaWeight);
	void printDebugOutput();
	bool learningHasStopped();
	void initializeLearningAlgoritm(NeuralNetwork &neuralNetwork, Teacher &teacher, AbstractActivationOrder &activationOrder);
	AbstractActivationOrder* getNewActivationOrder(NeuralNetwork &neuralNetwork);
	float calculateDeltaWeightFromEdge(AbstractTeachingLesson& lesson, std::vector<StandardNeuron*>& layer, StandardNeuron& neuron, Edge& edge, int lessonIndex, int layerIndex, int neuronIndex, int edgeIndex, ErrorMap_t* errormap);
	void initializeNeuronWeightCalculation(AbstractTeachingLesson& lesson, std::vector<StandardNeuron*>& layer, StandardNeuron& neuron, int lessonIndex, int layerIndex, int neuronIndex, ErrorMap_t* errormap);
	void initializeTry(NeuralNetwork &neuralNetwork, Teacher &teacher);
public:
	RBFInterpolationLearningRule(RBFInterpolationLearningRuleOptions &options_);
};

#endif