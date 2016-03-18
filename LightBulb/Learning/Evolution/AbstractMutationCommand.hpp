#pragma once

#ifndef _ABSTRACTMUTATIONCOMMAND_H_
#define _ABSTRACTMUTATIONCOMMAND_H_

// Includes
#include "Learning/Evolution/AbstractMutationAlgorithm.hpp"
#include "Learning/Evolution/AbstractMutationSelector.hpp"

// Library Includes
#include <vector>

// Forward declarations
class AbstractEvolutionObject;
class AbstractEvolutionWorld;
class EvolutionLearningRule;

// A command which mutates a few of the given evolution objects.
class AbstractMutationCommand
{
protected:
	// Holds the chosen mutation algorithm
	std::unique_ptr<AbstractMutationAlgorithm> mutationAlgorithm;
	//
	std::unique_ptr<AbstractMutationSelector> mutationSelector;

	std::vector<AbstractEvolutionObject*> objectsToMutate;
	bool enableDebugOutput;
public:
	virtual ~AbstractMutationCommand() {};
	virtual void select(std::vector<std::pair<double, AbstractEvolutionObject*>>* highscore, std::map<AbstractEvolutionObject*, std::map<std::string, int>>* counter) = 0;

	void setMutationSelector(AbstractMutationSelector* mutationSelector);
	// Creates a new mutation command with the given mutation algorithm
	AbstractMutationCommand(AbstractMutationAlgorithm* mutationAlgorithm_, AbstractMutationSelector* mutationSelector_, bool enableDebugOutput_);
	// Executes the mutations. (The algorithm will take a few of the old objects, mutate them and insert them into the new object vector)
	void execute(std::vector<std::pair<double, AbstractEvolutionObject*>>* highscore, std::vector<AbstractEvolutionObject*>* newObjectVector);
};

#endif
