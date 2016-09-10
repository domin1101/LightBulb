// Includes
#include "Learning/Evolution/ConstantCoevolutionFitnessFunction.hpp"
#include "AbstractCoevolutionWorld.hpp"

namespace LightBulb
{
	std::map<AbstractEvolutionObject*, double>* ConstantCoevolutionFitnessFunction::execute(CombiningStrategyResults& results)
	{
		std::map<AbstractEvolutionObject*, double>* fitnessValues = new std::map<AbstractEvolutionObject*, double>();

		for (auto resultsPerObject = results.begin(); resultsPerObject != results.end(); resultsPerObject++)
		{
			for (auto resultsPerCombination = resultsPerObject->second.begin(); resultsPerCombination != resultsPerObject->second.end(); resultsPerCombination++)
			{
				for (auto result = resultsPerCombination->second.begin(); result != resultsPerCombination->second.end(); result++)
				{
					if (result->second)
						(*fitnessValues)[resultsPerObject->first]++;
				}
			}
		}

		return fitnessValues;
	}
}