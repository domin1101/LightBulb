#pragma once

#ifndef _POSITION_H_
#define _POSITION_H_

// Library Includes

// Includes
#include "LightBulb/Learning/Evolution/AbstractDefaultIndividual.hpp"

// Forward declarations
class FunctionSimulator;

class Position : public LightBulb::AbstractDefaultIndividual
{
	template <class Archive>
	friend void save(Archive& archive, Position const& individual);
	template <class Archive>
	friend void load(Archive& archive, Position& individual);
protected:
	FunctionSimulator* functionSimulator;
	LightBulb::Vector<> position;
	bool inputIsSet;
	void getNNInput(LightBulb::Vector<>& input) override;
	void interpretNNOutput(const LightBulb::Vector<>& output) override;
public:	
	Position(FunctionSimulator& functionSimulator_);
	Position() = default;
	~Position();
	const LightBulb::Vector<>& getPosition() const;
};

#include "IO/PositionIO.hpp"

#endif
