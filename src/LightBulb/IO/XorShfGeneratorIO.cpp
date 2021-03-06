// Includes
#include "LightBulb/IO/XorShfGeneratorIO.hpp"
#include "LightBulb/IO/TemplateDeclaration.hpp"
// Libraray includes
#include <cereal/cereal.hpp>
#include <cereal/types/polymorphic.hpp>
#include <cereal/types/vector.hpp>

namespace LightBulb
{
	/**
	* \brief Saves a XorShfGenerator.
	* \tparam Archive The archive type.
	* \param archive The archive which should be used.
	* \param xorShfGenerator The XorShfGenerator to save.
	*/
	template <class Archive>
	void save(Archive& archive, XorShfGenerator const& xorShfGenerator)
	{
		archive(cereal::base_class<AbstractRandomGenerator>(&xorShfGenerator));

		archive(cereal::make_nvp("x", xorShfGenerator.x));
		archive(cereal::make_nvp("y", xorShfGenerator.y));
		archive(cereal::make_nvp("z", xorShfGenerator.z));
	}

	/**
	* \brief Loads a XorShfGenerator.
	* \tparam Archive The archive type.
	* \param archive The archive which should be used.
	* \param xorShfGenerator The XorShfGenerator to load.
	*/
	template <class Archive>
	void load(Archive& archive, XorShfGenerator& xorShfGenerator)
	{
		archive(cereal::base_class<AbstractRandomGenerator>(&xorShfGenerator));

		archive(cereal::make_nvp("x", xorShfGenerator.x));
		archive(cereal::make_nvp("y", xorShfGenerator.y));
		archive(cereal::make_nvp("z", xorShfGenerator.z));
	}

	DECLARE_SERIALIZATION_TEMPLATE(XorShfGenerator);
}

#include "LightBulb/IO/UsedArchives.hpp"

CEREAL_REGISTER_TYPE(LightBulb::XorShfGenerator)

CEREAL_REGISTER_DYNAMIC_INIT(XorShfGenerator)