#pragma once

#ifndef _CONSTANTMUTATIONCOMMAND_H_
#define _CONSTANTMUTATIONCOMMAND_H_

// Library Includes

// Includes
#include "Learning/Evolution/AbstractMutationCommand.hpp"
#include "Function/RankBasedRandomFunction.hpp"

// Forward declarations

// Mutates a constant amount of objects
class ConstantMutationCommand : public AbstractMutationCommand
{
private:
	// Holds amount of objects which should be mutated
	int objectCount;
	// Alternative: Holds the percentage of objects which should be mutated
	double mutationPercentage;
public:
	virtual ~ConstantMutationCommand() {};
	void setMutationPercentage(double newMutationPercentage);
	// Creates a command which mutates a static amount of objects
	ConstantMutationCommand(AbstractMutationAlgorithm* mutationAlgorithm_, AbstractMutationSelector* mutationSelector_, int objectCount_, bool enableDebugOutput_ = false);
	// Creates a command which mutates a percentage of objects
	ConstantMutationCommand(AbstractMutationAlgorithm* mutationAlgorithm_, AbstractMutationSelector* mutationSelector_, double mutationPercentage_, bool enableDebugOutput_ = false);

	void select(std::vector<std::pair<double, AbstractEvolutionObject*>>* highscore, std::map<AbstractEvolutionObject*, std::map<std::string, int>>* counter);
};

#endif
