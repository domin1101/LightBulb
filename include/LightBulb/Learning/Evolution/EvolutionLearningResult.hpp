#ifndef _EVOLUTIONLEARNINGRESULT_H_
#define _EVOLUTIONLEARNINGRESULT_H_

#include "LightBulb/Learning/AbstractLearningResult.hpp"
#include <vector>
#include <memory>

namespace LightBulb
{
	class AbstractIndividual;
	/**
	 * \brief Describes the learning result of an evolution learning rule.
	 */
	struct EvolutionLearningResult : public AbstractLearningResult
	{
		/**
		 * \brief A vector of the best individuals that were produced by the evolution learning rule.
		 */
		std::vector<std::unique_ptr<AbstractIndividual>> bestIndividuals;
		double bestFitness;
		EvolutionLearningResult();
		~EvolutionLearningResult();
	};
}


#endif
