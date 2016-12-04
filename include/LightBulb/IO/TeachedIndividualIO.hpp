#pragma once

#ifndef _TEACHEDINDIVIDUALIO_H_
#define _TEACHEDINDIVIDUALIO_H_

// Includes
#include "LightBulb/Learning/Evolution/TeachedIndividual.hpp"
#include "LightBulb/IO/IOStorage.hpp"
#include "LightBulb/Learning/Evolution/TeachingEvolutionEnvironment.hpp"

// Libraray includes
#include <cereal/cereal.hpp>
#include <cereal/types/polymorphic.hpp>
#include <cereal/types/vector.hpp>

namespace LightBulb
{
	/**
	* \brief Saves a TeachedIndividual.
	* \tparam Archive The archive type.
	* \param archive The archive which should be used.
	* \param individual The TeachedIndividual to save.
	*/
	template <class Archive>
	void save(Archive& archive, TeachedIndividual const& individual)
	{
		archive(cereal::base_class<AbstractIndividual>(&individual));
		archive(cereal::make_nvp("neuralNetwork", individual.neuralNetwork));
	}

	/**
	* \brief Loads a TeachedIndividual.
	* \tparam Archive The archive type.
	* \param archive The archive which should be used.
	* \param individual The TeachedIndividual to load.
	*/
	template <class Archive>
	void load(Archive& archive, TeachedIndividual& individual)
	{
		archive(cereal::base_class<AbstractIndividual>(&individual));
		archive(cereal::make_nvp("neuralNetwork", individual.neuralNetwork));
		individual.teachingEvolutionEnvironment = static_cast<TeachingEvolutionEnvironment*>(IOStorage<AbstractEvolutionEnvironment>::get());
		individual.doNNCalculation();
	}
}

#include "LightBulb/IO/UsedArchives.hpp"

CEREAL_REGISTER_TYPE(LightBulb::TeachedIndividual);

#endif