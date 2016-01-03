#pragma once

#ifndef _TOURNAMENTCOMBININGSTRATEGY_H_
#define _TOURNAMENTCOMBININGSTRATEGY_H_

// Library Includes
#include <map>
#include <vector>

// Include
#include "Learning/Evolution/AbstractCombiningStrategy.hpp"

// Forward declarations

class TournamentCombiningStrategy : public AbstractCombiningStrategy
{
private:
	std::unique_ptr<std::vector<AbstractEvolutionObject*>> cachedObjects;
	std::unique_ptr<std::vector<AbstractEvolutionObject*>> currentLevel;
	std::unique_ptr<std::vector<AbstractEvolutionObject*>> nextLevel;
	void processLevel(AbstractCoevolutionWorld* world);
	void combine(AbstractCoevolutionWorld* world);
public:	
	TournamentCombiningStrategy(AbstractCoevolutionFitnessFunction* fitnessFunction_);	
};

#endif
