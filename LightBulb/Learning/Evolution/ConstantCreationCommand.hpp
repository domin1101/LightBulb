#pragma once

#ifndef _CONSTANTCREATIONCOMMAND_H_
#define _CONSTANTCREATIONCOMMAND_H_

// Library Includes

// Includes
#include "Learning/Evolution/AbstractCreationCommand.hpp"

// Forward declarations

// Adds objects to the world as long as it contains lower objects than chosen
class ConstantCreationCommand : public AbstractCreationCommand
{
private:
	// Holds amount of objects up to which they should be created
	int objectCount;
public:
	virtual ~ConstantCreationCommand() {};
	void setObjectCount(int newObjectCount);
	// Creates a command which creates up to a static amount of objects
	ConstantCreationCommand(int objectCount_, bool enableDebugOutput_ = false);
	// Inherited:
	void execute(AbstractEvolutionWorld& world);
};

#endif