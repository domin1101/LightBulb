#pragma once

#ifndef _TICTACTOE_H_
#define _TICTACTOE_H_

// Library Includes
#include <vector>
#include <array>
#include <mutex>
#include <condition_variable>

// Include
#include "LightBulb/Learning/Evolution/AbstractCoevolutionEnvironment.hpp"
#include "LightBulb/IO/UseParentSerialization.hpp"
#include "LightBulb/NetworkTopology/FeedForwardNetworkTopology.hpp"
#include "LightBulb/LinearAlgebra/Kernel.hpp"

// Forward declarations
class TicTacToeAI;
class AbstractTile;

enum TicTacToeEvents : unsigned int
{
	EVT_FIELD_CHANGED
};

#define DATASET_TICTACTOE_RATING "TicTacToe rating"

class TicTacToe : public LightBulb::AbstractCoevolutionEnvironment, public LightBulb::Observable<TicTacToeEvents, TicTacToe>
{
private:
	std::unique_ptr<LightBulb::Kernel> setWinnerKernel;
	std::unique_ptr<LightBulb::Kernel> calcWhoHasWonKernel;
	std::unique_ptr<LightBulb::Kernel> setFieldsFromOutputKernel;
	std::unique_ptr<LightBulb::Kernel> resetEnvironmentKernel;
	std::unique_ptr<LightBulb::Kernel> getSightKernel;
	void initialize();
protected:
	LightBulb::Matrix<int> fields;
	LightBulb::Scalar<int> whoHasWon;
	LightBulb::AbstractIndividual* createNewIndividual() override;
	void resetEnvironment() override;
	void calcWhoHasWon();
	int currentPlayer;
	LightBulb::Scalar<bool> illegalMove;
	bool nextDecisionCombination(std::vector<int>& decisionNr, int b, int level = 0);
	void simulateGame(TicTacToeAI& ai1, TicTacToeAI& ai2, bool secondPlayerStarts, LightBulb::Scalar<bool>& firstPlayerHasWon);
	bool stepMode;
	std::condition_variable doNextStep;
	std::mutex doNextStepMutex;
	std::unique_ptr<LightBulb::FeedForwardNetworkTopologyOptions> options;
	void doCompare(LightBulb::AbstractIndividual& obj1, LightBulb::AbstractIndividual& obj2, int round, LightBulb::Scalar<bool>& firstPlayerHasWon) override;
public:
	TicTacToe(LightBulb::FeedForwardNetworkTopologyOptions& options_, bool isParasiteEnvironment, LightBulb::AbstractCombiningStrategy* combiningStrategy_, LightBulb::AbstractCoevolutionFitnessFunction* fitnessFunction_, const std::shared_ptr<LightBulb::AbstractHallOfFameAlgorithm>* hallOfFameToAddAlgorithm_ = nullptr, const std::shared_ptr<LightBulb::AbstractHallOfFameAlgorithm>* hallOfFameToChallengeAlgorithm_ = nullptr);
	TicTacToe();
	void getSight(LightBulb::Vector<>& sight);
	void setField(int x, int y);
	void setFieldsFromOutput(const LightBulb::Vector<>& output);
	bool isFree(int x, int y);
	int rateIndividual(LightBulb::AbstractIndividual& rateKI) override;
	void startNewGame(int firstPlayer);
	void initializeForLearning() override;
	bool hasGameFinished();
	LightBulb::Matrix<int>& getFields();
	void startStepMode();
	void stopStepMode();
	std::vector<std::string> getDataSetLabels() const override;
	void nextStep();
	int getRoundCount() const override;
};

USE_EXISTING_PARENT_SERIALIZATION_WITHOUT_NAMESPACE(TicTacToe, LightBulb::AbstractCoevolutionEnvironment, LightBulb::AbstractEvolutionEnvironment);

#endif
