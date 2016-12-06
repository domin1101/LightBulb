#pragma once

#ifndef _ABSTRACTMUTATIONALGORITHM_H_
#define _ABSTRACTMUTATIONALGORITHM_H_

// Includes
#include "LightBulb/Random/AbstractRandomGeneratorUser.hpp"
#include "LightBulb/Tools/AbstractCloneable.hpp"
#include "LightBulb/Random/ZigguratGenerator.hpp"

// Library Includes
#include <memory>
#include <vector>

namespace LightBulb
{
	// Forward declarations
	class AbstractIndividual;
	/**
	 * \brief Describes an algorithm which mutates individuals.
	 */
	class AbstractMutationAlgorithm : public virtual AbstractCloneable, public virtual AbstractRandomGeneratorUser
	{
	protected:
		ZigguratGenerator* zigguratGenerator;
	public:
		virtual ~AbstractMutationAlgorithm() {}
		friend void swap(AbstractMutationAlgorithm& lhs, AbstractMutationAlgorithm& rhs) noexcept {	}
		/**
		 * \brief Mutates the given individual.
		 * \param individual1 The individual to mutate.
		 */
		virtual void execute(AbstractIndividual& individual1) = 0;
		/**
		 * \brief Initializes the algorithm.
		 * \param highscore The current highscore.
		 */
		virtual void initialize(const std::vector<std::pair<double, AbstractIndividual*>>& highscore) {};
		void setZigguratGenerator(ZigguratGenerator& generator);
	};
}

#endif