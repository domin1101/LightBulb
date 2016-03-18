// Includes
#include "Learning/Evolution/AbstractMutationSelector.hpp"

void AbstractMutationSelector::addObjectToMutate(AbstractEvolutionObject* object)
{
	selectedObjects.push_back(object);
	(*currentCounter)[object]["mutate"]++;
}

void AbstractMutationSelector::executeMutationSelection(int mutationCount, std::vector<std::pair<double, AbstractEvolutionObject*>>* highscore, std::map<AbstractEvolutionObject*, std::map<std::string, int>>* counter)
{
	selectedObjects.clear();
	if (mutationCount > 0) {
		currentCounter = counter;
		selectForMutation(mutationCount, highscore);
	}

	if (selectedObjects.size() != mutationCount)
		throw std::logic_error("The mutation selection was not successful");
}

std::vector<AbstractEvolutionObject*>* AbstractMutationSelector::getMutationSelection()
{
	return &selectedObjects;
}