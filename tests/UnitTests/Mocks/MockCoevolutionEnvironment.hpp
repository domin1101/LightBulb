#pragma once

#ifndef _MOCKEVOLUTIONENVIRONMENT_H_
#define _MOCKEVOLUTIONENVIRONMENT_H_

#include "gmock/gmock.h"
#include <LightBulb/Learning/Evolution/AbstractCoevolutionEnvironment.hpp>
#include <LightBulb/Learning/Evolution/AbstractCombiningStrategy.hpp>
#include <LightBulb/Learning/Evolution/AbstractIndividual.hpp>
#include <LightBulb/Random/AbstractRandomGenerator.hpp>
#include <LightBulb/Logging/AbstractLogger.hpp>

class MockCoevolutionEnvironment : public LightBulb::AbstractCoevolutionEnvironment
{
public:
	MOCK_METHOD0(getHighscoreList, LightBulb::Highscore& ());
	MOCK_METHOD0(initializeForLearning, void ());
	MOCK_METHOD0(createNewIndividual, LightBulb::AbstractIndividual* ());
	MOCK_METHOD0(resetEnvironment, void ());
	MOCK_METHOD1(addNewIndividual, LightBulb::AbstractIndividual* (bool));
	MOCK_METHOD0(getIndividuals, std::vector<LightBulb::AbstractIndividual*>& ());
	MOCK_METHOD1(setIndividuals, void (const std::vector<LightBulb::AbstractIndividual*>&));
	MOCK_METHOD0(reset, void ());
	MOCK_CONST_METHOD0(getPopulationSize, int ());
	MOCK_METHOD0(clearPopulation, void ());
	MOCK_METHOD1(addExistingIndividual, void (LightBulb::AbstractIndividual*));
	MOCK_METHOD0(doSimulationStep, void());
	MOCK_CONST_METHOD1(getFitness, double (const LightBulb::AbstractIndividual&));
	MOCK_METHOD1(rateIndividual, int (LightBulb::AbstractIndividual&));
	MOCK_CONST_METHOD0(getCombiningStrategy, LightBulb::AbstractCombiningStrategy& ());
	MOCK_METHOD1(setLogger, void (LightBulb::AbstractLogger&));
	MOCK_CONST_METHOD0(getDataSetLabels, std::vector<std::string> ());
	MOCK_CONST_METHOD0(isParasiteEnvironment, bool ());
	MOCK_CONST_METHOD0(getRoundCount, int ());
	MOCK_METHOD1(setRandomGenerator, void (LightBulb::AbstractRandomGenerator&));
	MOCK_METHOD4(doCompare, void (LightBulb::AbstractIndividual&, LightBulb::AbstractIndividual&, int, LightBulb::Scalar<bool>&));
	MOCK_METHOD4(compareIndividuals, void (LightBulb::AbstractIndividual&, LightBulb::AbstractIndividual&, int, LightBulb::Scalar<bool>&));
};

#endif
