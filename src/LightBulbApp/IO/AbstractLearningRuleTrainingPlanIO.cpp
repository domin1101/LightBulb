#include "LightBulbApp/IO/AbstractLearningRuleTrainingPlanIO.hpp"
#include "LightBulb/IO/IOStorage.hpp"
#include "LightBulb/Learning/AbstractLearningRule.hpp"
// Libraray includes
#include <cereal/cereal.hpp>
#include <cereal/types/polymorphic.hpp>

namespace LightBulb
{
	/**
	* \brief Saves an AbstractLearningRuleTrainingPlan.
	* \tparam Archive The archive type.
	* \param archive The archive which should be used.
	* \param trainingPlan The AbstractLearningRuleTrainingPlan to save.
	*/
	template <class Archive>
	void save(Archive& archive, AbstractLearningRuleTrainingPlan const& trainingPlan)
	{
		archive(cereal::base_class<AbstractTrainingPlan>(&trainingPlan));
		archive(cereal::make_nvp("learningRule", trainingPlan.learningRule));
	}

	/**
	* \brief Loads an AbstractLearningRuleTrainingPlan.
	* \tparam Archive The archive type.
	* \param archive The archive which should be used.
	* \param trainingPlan The AbstractLearningRuleTrainingPlan to load.
	*/
	template <class Archive>
	void load(Archive& archive, AbstractLearningRuleTrainingPlan& trainingPlan)
	{
		archive(cereal::base_class<AbstractTrainingPlan>(&trainingPlan));

		IOStorage<AbstractLearningRule>::push(trainingPlan.createLearningRate());
		archive(cereal::make_nvp("learningRule", trainingPlan.learningRule));
		trainingPlan.learningRule.reset(IOStorage<AbstractLearningRule>::pop());
	}

	DECLARE_SERIALIZATION_TEMPLATE(AbstractLearningRuleTrainingPlan);
}

#include "LightBulb/IO/UsedArchives.hpp"

CEREAL_REGISTER_TYPE(LightBulb::AbstractLearningRuleTrainingPlan);

CEREAL_REGISTER_DYNAMIC_INIT(AbstractLearningRuleTrainingPlan)