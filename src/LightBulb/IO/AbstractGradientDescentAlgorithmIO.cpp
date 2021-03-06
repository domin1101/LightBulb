// Includes
#include "LightBulb/IO/AbstractGradientDescentAlgorithmIO.hpp"
#include "LightBulb/IO/TemplateDeclaration.hpp"
// Libraray includes
#include <cereal/cereal.hpp>

namespace LightBulb
{
	/**
	* \brief Serializes an AbstractGradientDescentAlgorithm
	* \tparam Archive The archive type.
	* \param archive The archive which should be used.
	* \param gradientDescentAlgorithm The AbstractGradientDescentAlgorithm to serialize.
	*/
	template <class Archive>
	void serialize(Archive& archive, AbstractGradientDescentAlgorithm& gradientDescentAlgorithm)
	{
		archive(cereal::make_nvp("initialized", gradientDescentAlgorithm.initialized));
	}

	DECLARE_SINGLE_SERIALIZATION_TEMPLATE(AbstractGradientDescentAlgorithm);
}