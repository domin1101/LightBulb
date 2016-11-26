#pragma once

#ifndef _CONSTANTRECOMBINATIONCOMMANDPREFERENCEGROUP_H_
#define _CONSTANTRECOMBINATIONCOMMANDPREFERENCEGROUP_H_

// Includes
#include "TrainingPlans/Preferences/PreferenceGroup.hpp"
#include "IO/UseParentSerialization.hpp"
#include "Learning/Evolution/ConstantRecombinationCommand.hpp"

namespace LightBulb
{
	/**
	* \brief Describes a predefined preference group for a constant recombination command.
	*/
	class ConstantRecombinationCommandPreferenceGroup : public PreferenceGroup
	{
	protected:
	public:
		/**
		* \brief Creates a constant recombination command preference group with standard default values.
		* \param name The name.
		*/
		ConstantRecombinationCommandPreferenceGroup(const std::string& name = "Constant recombination");
		/**
		 * \brief Creates a new constant recombination command object with the current preference values.
		 * \return The new constant recombination command.
		 */
		ConstantRecombinationCommand* create() const;
		// Inherited:
		AbstractCloneable* clone() const override;
	};
}

USE_PARENT_SERIALIZATION(LightBulb::ConstantRecombinationCommandPreferenceGroup, LightBulb::PreferenceGroup, LightBulb);

#endif
