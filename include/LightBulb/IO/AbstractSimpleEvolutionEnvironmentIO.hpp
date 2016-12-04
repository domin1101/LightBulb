#pragma once

#ifndef _ABSTRACTSIMPLEEVOLUTIONENVIRONMENTIO_H_
#define _ABSTRACTSIMPLEEVOLUTIONENVIRONMENTIO_H_

// Includes
#include "LightBulb/Learning/Evolution/AbstractSimpleEvolutionEnvironment.hpp"
#include "LightBulb/Learning/Evolution/AbstractIndividual.hpp"
#include "LightBulb/IO/IOStorage.hpp"

// Libraray includes
#include <cereal/cereal.hpp>
#include <cereal/types/polymorphic.hpp>
#include <cereal/access.hpp>

namespace LightBulb
{
	/**
	* \brief Saves an AbstractSimpleEvolutionEnvironment
	* \tparam Archive The archive type.
	* \param archive The archive which should be used.
	* \param environment The AbstractSimpleEvolutionEnvironment to save.
	*/
	template <class Archive>
	void save(Archive& archive, AbstractSimpleEvolutionEnvironment const& environment)
	{
		std::vector<std::unique_ptr<AbstractIndividual>> individuals;
		for (auto individual = environment.individuals.begin(); individual != environment.individuals.end(); individual++)
			individuals.push_back(std::unique_ptr<AbstractIndividual>(*individual));

		archive(cereal::make_nvp("individuals", individuals));

		for (auto individual = individuals.begin(); individual != individuals.end(); individual++)
			individual->release();
	}

	/**
	* \brief Loads an AbstractSimpleEvolutionEnvironment
	* \tparam Archive The archive type.
	* \param archive The archive which should be used.
	* \param environment The AbstractSimpleEvolutionEnvironment to load.
	*/
	template <class Archive>
	void load(Archive& archive, AbstractSimpleEvolutionEnvironment& environment)
	{
		std::vector<std::unique_ptr<AbstractIndividual>> individuals;
		IOStorage<AbstractEvolutionEnvironment>::push(&environment);
		archive(cereal::make_nvp("individuals", individuals));
		IOStorage<AbstractEvolutionEnvironment>::clear();

		for (auto individual = individuals.begin(); individual != individuals.end(); individual++)
		{
			environment.individuals.push_back(individual->release());
		}
	}
}

#include "LightBulb/IO/UsedArchives.hpp"

CEREAL_REGISTER_TYPE(LightBulb::AbstractSimpleEvolutionEnvironment);

#endif