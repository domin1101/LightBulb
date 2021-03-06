#pragma once

#ifndef _CONSTANTCREATIONCOMMAND_H_
#define _CONSTANTCREATIONCOMMAND_H_

// Library Includes

// Includes
#include "LightBulb/Learning/Evolution/AbstractCreationCommand.hpp"

namespace LightBulb
{
	/**
	 * \brief Adds individuals to the environment as long as it contains less individuals than wished.
	 */
	class ConstantCreationCommand : public AbstractCreationCommand
	{
	private:
		/**
		 * \brief Holds the amount of individuals up to which they should be created.
		 */
		int individualCount;
	public:
		virtual ~ConstantCreationCommand() {};
		/**
		 * \brief Creates the constant creation command.
		 * \param individualCount_ The amount of individuals up to which they should be created.
		 */
		ConstantCreationCommand(int individualCount_);
		// Inherited:
		void execute(AbstractEvolutionEnvironment& environment, std::vector<AbstractIndividual*>& notUsedIndividuals) override;
		AbstractCloneable* clone() const override;
	};
}

#endif
