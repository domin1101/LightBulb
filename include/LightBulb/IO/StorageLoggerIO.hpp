#pragma once

#ifndef _STORAGELOGGERIO_H_
#define _STORAGELOGGERIO_H_

// Libary includes
#include "LightBulb/Logging/StorageLogger.hpp"

#include <cereal/types/vector.hpp>
#include <cereal/types/utility.hpp>
#include <cereal/cereal.hpp>

namespace LightBulb
{
	/**
	* \brief Serializes a StorageLogger.
	* \tparam Archive The archive type.
	* \param archive The archive which should be used.
	* \param storageLogger The StorageLogger to serialize.
	*/
	template <class Archive>
	void serialize(Archive& archive, StorageLogger& storageLogger)
	{
		archive(cereal::make_nvp("messages", storageLogger.messages));
	}
}

#endif