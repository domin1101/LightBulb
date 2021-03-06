// Includes
#include "LightBulb/Learning/Evolution/AbstractEvolutionEnvironment.hpp"
//Library include
#include <algorithm>
#include <functional>
#include "LightBulb/LinearAlgebra/Scalar.hpp"

namespace LightBulb
{
	AbstractEvolutionEnvironment::AbstractEvolutionEnvironment()
	{
		recalculateHighscore = true;
	}

	Highscore& AbstractEvolutionEnvironment::getHighscoreList()
	{
		if (recalculateHighscore)
		{
			currentHighscore.clear();
			// Go through all individuals
			for (auto individual = getIndividuals().begin(); individual < getIndividuals().end(); individual++)
			{
				static Scalar<> fitness;
				getFitness(**individual, fitness);

				// Add the individuals paired with its fitness to the list
				currentHighscore.push_back(std::make_pair(fitness.getEigenValue(), *individual));

			}
			// Sort the list
			sort(currentHighscore.begin(), currentHighscore.end(), std::greater<std::pair<double, AbstractIndividual*>>());
			recalculateHighscore = false;
		}
		return currentHighscore;
	}

	std::vector<std::string> AbstractEvolutionEnvironment::getDataSetLabels() const
	{
		std::vector<std::string> labels;
		return labels;
	}

	void AbstractEvolutionEnvironment::setLearningState(LearningState& learningState_)
	{
		learningState = &learningState_;
	}

	void AbstractEvolutionEnvironment::refreshHighscore()
	{
		recalculateHighscore = true;
	}
}
