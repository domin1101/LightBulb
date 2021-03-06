#pragma once

#ifndef _ABSTRACTREINFORCEMENTTRAININGPLAN_H_
#define _ABSTRACTREINFORCEMENTTRAININGPLAN_H_

// Includes
#include "LightBulbApp/TrainingPlans/AbstractLearningRuleTrainingPlan.hpp"

// Library includes

namespace LightBulb
{
	// Forward declarations
	class AbstractNeuralNetwork;
	struct AbstractReinforcementLearningRuleOptions;
	class AbstractReinforcementEnvironment;
	class AbstractReinforcementIndividual;
	/**
	* \brief Describes a training plan which uses reinforcement learning.
	*/
	class AbstractReinforcementTrainingPlan : public AbstractLearningRuleTrainingPlan
	{
		template <class Archive>
		friend void save(Archive& archive, AbstractReinforcementTrainingPlan const& trainingPlan);
		template <class Archive>
		friend void load(Archive& archive, AbstractReinforcementTrainingPlan& trainingPlan);
	protected:
		/**
		 * \brief The reinforcement environment which is used.
		 */
		std::unique_ptr<AbstractReinforcementEnvironment> environment;
		std::unique_ptr<AbstractReinforcementIndividual> individual;
		/**
		 * \brief Creates the reinforcement environment.
		 * \return The new environment.
		 */
		virtual AbstractReinforcementEnvironment* createEnvironment() = 0;
		virtual AbstractReinforcementIndividual* createIndividual() = 0;
		/**
		* \brief Fills all learning rule options which are the same for all reinforcement learning rule training plans.
		* \param options The options to fill.
		*/
		void fillDefaultLearningRuleOptions(AbstractReinforcementLearningRuleOptions& options) const;
	public:
		~AbstractReinforcementTrainingPlan();
		/**
		 * \brief Creates the reinforcement training plan.
		 */
		AbstractReinforcementTrainingPlan();
		/**
		 * \brief Returns the reinforcement environment.
		 * \return The environment.
		 */
		AbstractReinforcementEnvironment& getEnvironment();
		AbstractReinforcementIndividual& getIndividual();
		// Inherited:
		void initializeStart() override;
	};
}

#include "LightBulbApp/IO/AbstractReinforcementTrainingPlanIO.hpp"

#endif
