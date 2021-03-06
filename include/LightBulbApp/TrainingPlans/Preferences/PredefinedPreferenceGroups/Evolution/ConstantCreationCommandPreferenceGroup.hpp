#pragma once

#ifndef _CONSTANTCREATIONCOMMANDPREFERENCEGROUP_H_
#define _CONSTANTCREATIONCOMMANDPREFERENCEGROUP_H_

// Includes
#include "LightBulbApp/TrainingPlans/Preferences/PreferenceGroup.hpp"
#include "LightBulb/IO/UseParentSerialization.hpp"

namespace LightBulb
{
	class ConstantCreationCommand;
	/**
	* \brief Describes a predefined preference group for a constant creation command.
	*/
	class ConstantCreationCommandPreferenceGroup : public PreferenceGroup
	{
	protected:
	public:
		/**
		* \brief Creates a constant creation command preference group with standard default values.
		* \param name The name.
		*/
		ConstantCreationCommandPreferenceGroup(const std::string& name = "Constant creation");
		/**
		 * \brief Creates a new constant creation command object with the current preference values.
		 * \return The new constant creation command.
		 */
		ConstantCreationCommand* create() const;
		// Inherited:
		AbstractCloneable* clone() const override;
	};
}

USE_PARENT_SERIALIZATION(LightBulb::ConstantCreationCommandPreferenceGroup, LightBulb::PreferenceGroup, LightBulb);

#endif
