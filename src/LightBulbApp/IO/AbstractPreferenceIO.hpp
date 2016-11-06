#pragma once

#ifndef _ABSTRACTPREFERENCEIO_H_
#define _ABSTRACTPREFERENCEIO_H_

// Includes
#include "TrainingPlans/Preferences/AbstractPreference.hpp"
// Libraray includes
#include <cereal/cereal.hpp>
#include <cereal/types/polymorphic.hpp>

namespace LightBulb
{
	/**
	* \brief Saves an AbstractPreference.
	* \tparam Archive The archive type.
	* \param archive The archive which should be used.
	* \param preference The AbstractPreference to save.
	*/
	template <class Archive>
	void save(Archive& archive, AbstractPreference const& preference)
	{
		archive(cereal::base_class<AbstractPreferenceElement>(&preference));
		archive(cereal::make_nvp("name", preference.name));
	}

	/**
	* \brief Loads an AbstractPreference.
	* \tparam Archive The archive type.
	* \param archive The archive which should be used.
	* \param preference The AbstractPreference to load.
	*/
	template <class Archive>
	void load(Archive& archive, AbstractPreference& preference)
	{
		archive(cereal::base_class<AbstractPreferenceElement>(&preference));
		archive(cereal::make_nvp("name", preference.name));
	}
}


#include "IO/UsedArchives.hpp"

CEREAL_REGISTER_TYPE(LightBulb::AbstractPreference);

#endif