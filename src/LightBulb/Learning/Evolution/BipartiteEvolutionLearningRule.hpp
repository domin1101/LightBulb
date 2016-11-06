#pragma once

#ifndef _BIPARTITEEVOLUTIONLEARNINGRULE_H_
#define _BIPARTITEEVOLUTIONLEARNINGRULE_H_

// Includes
#include "Learning/Evolution/AbstractEvolutionLearningRule.hpp"

// Library Includes

namespace LightBulb
{
	// Forward declarations


	struct BipartiteEvolutionLearningRuleOptions : public AbstractEvolutionLearningRuleOptions
	{
		AbstractEvolutionLearningRule* learningRule1;
		AbstractEvolutionLearningRule* learningRule2;

		BipartiteEvolutionLearningRuleOptions()
		{
			learningRule1 = nullptr;
			learningRule2 = nullptr;
		}
	};

	class BipartiteEvolutionLearningRule : public AbstractEvolutionLearningRule
	{
		template <class Archive>
		friend void serialize(Archive& archive, BipartiteEvolutionLearningRule& learningRule);
		friend struct cereal::LoadAndConstruct<BipartiteEvolutionLearningRule>;
	protected:
		const BipartiteEvolutionLearningRuleOptions& getOptions() const;
		bool doIteration() override;
		void initializeTry() override;
		bool hasLearningSucceeded() override;
		void initializeStartLearningAlgoritm() override;
		bool exitConditionReached;
		AbstractLearningResult* getLearningResult() override;
	public:
		BipartiteEvolutionLearningRule(BipartiteEvolutionLearningRuleOptions& options_);
		BipartiteEvolutionLearningRule(BipartiteEvolutionLearningRuleOptions* options_);
		static std::string getName();
		std::vector<std::string> getDataSetLabels() const override;
		AbstractEvolutionLearningRule& getFirstLearningRule();
		AbstractEvolutionLearningRule& getSecondLearningRule();

	};
}

#include "IO/BipartiteEvolutionLearningRuleIO.hpp"

#endif