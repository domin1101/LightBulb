#pragma once

#ifndef _FEEDFORWARDNETWORKTOPOLOGYIO_H_
#define _FEEDFORWARDNETWORKTOPOLOGYIO_H_

// Libary includes
#include "IO/MatrixIO.hpp"
#include <NetworkTopology/FeedForwardNetworkTopology.hpp>
#include <NeuronDescription/AbstractNeuronDescriptionFactory.hpp>

#include <cereal/cereal.hpp>
#include <cereal/types/polymorphic.hpp>
#include <cereal/access.hpp>
#include <cereal/types/vector.hpp>

namespace LightBulb
{
	/**
	* \brief Saves FeedForwardNetworkTopologyOptions.
	* \tparam Archive The archive type.
	* \param archive The archive which should be used.
	* \param options The FeedForwardNetworkTopologyOptions to save.
	*/
	template <class Archive>
	void save(Archive& archive, FeedForwardNetworkTopologyOptions const & options)
	{
		archive(cereal::make_nvp("enableShortcuts", options.enableShortcuts));
		archive(cereal::make_nvp("neuronsPerLayerCount", options.neuronsPerLayerCount));
		archive(cereal::make_nvp("useBiasNeuron", options.useBiasNeuron));

		std::unique_ptr<AbstractNeuronDescriptionFactory> descriptionFactory(dynamic_cast<AbstractNeuronDescriptionFactory*>(options.descriptionFactory->clone()));
		archive(cereal::make_nvp("descriptionFactory", descriptionFactory));
	}
	
	/**
	* \brief Loads FeedForwardNetworkTopologyOptions.
	* \tparam Archive The archive type.
	* \param archive The archive which should be used.
	* \param options The FeedForwardNetworkTopologyOptions to load.
	*/
	template <class Archive>
	void load(Archive& archive, FeedForwardNetworkTopologyOptions& options)
	{
		archive(cereal::make_nvp("enableShortcuts", options.enableShortcuts));
		archive(cereal::make_nvp("neuronsPerLayerCount", options.neuronsPerLayerCount));
		archive(cereal::make_nvp("useBiasNeuron", options.useBiasNeuron));
		std::unique_ptr<AbstractNeuronDescriptionFactory> descriptionFactory;
		archive(cereal::make_nvp("descriptionFactory", descriptionFactory));
		options.descriptionFactory = descriptionFactory.release();
	}

	/**
	* \brief Saves a FeedForwardNetworkTopology.
	* \tparam Archive The archive type.
	* \param archive The archive which should be used.
	* \param feedForwardNetworkTopology The FeedForwardNetworkTopologyOptions to save.
	*/
	template <class Archive>
	void save(Archive& archive, FeedForwardNetworkTopology const & feedForwardNetworkTopology)
	{
		archive(cereal::make_nvp("options", feedForwardNetworkTopology.options));
		archive(cereal::make_nvp("netInputs", feedForwardNetworkTopology.netInputs));
		archive(cereal::make_nvp("activations", feedForwardNetworkTopology.activations));
		archive(cereal::make_nvp("weights", feedForwardNetworkTopology.weights));
	}

	/**
	* \brief Loads a FeedForwardNetworkTopology.
	* \tparam Archive The archive type.
	* \param archive The archive which should be used.
	* \param feedForwardNetworkTopology The FeedForwardNetworkTopologyOptions to load.
	*/
	template <class Archive>
	void load(Archive& archive, FeedForwardNetworkTopology & feedForwardNetworkTopology)
	{
		archive(cereal::make_nvp("options", feedForwardNetworkTopology.options));
		feedForwardNetworkTopology.buildNetwork();
		archive(cereal::make_nvp("netInputs", feedForwardNetworkTopology.netInputs));
		archive(cereal::make_nvp("activations", feedForwardNetworkTopology.activations));
		archive(cereal::make_nvp("weights", feedForwardNetworkTopology.weights));
		feedForwardNetworkTopology.rebuildActivationsPerLayer();
	}

}

#include "UsedArchives.hpp"

CEREAL_REGISTER_TYPE(LightBulb::FeedForwardNetworkTopology);

#endif