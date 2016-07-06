// Includes
#include "Examples/PongReinforcement/PongReinforcementWorld.hpp"
//Library includes

PongReinforcementWorld::PongReinforcementWorld(LayeredNetworkOptions& options_)
	: AbstractReinforcementWorld(options_)
{
	watchMode = false;
}

double PongReinforcementWorld::doSimulationStep()
{
	if (game.whoHasWon() != 0 || time >= game.getProperties().maxTime || time == -1)
	{
		time = 0;
		game.reset();
	}

	game.setPlayer(1);
	doNNCalculation();
	game.setPlayer(-1);
	executeCompareAI();
	game.advanceBall(1);

	time++;

	if (watchMode)
	{
		throwEvent(EVT_FIELD_CHANGED, this);
		std::this_thread::sleep_for(std::chrono::milliseconds(20));
	}

	return game.whoHasWon();
}

void PongReinforcementWorld::getNNInput(std::vector<double>& input)
{
	input.resize(6);
	input[0] = game.getPlayer() * game.getState().ballPosX / game.getProperties().width;
	input[1] = game.getState().ballPosY / game.getProperties().height;
	input[2] = game.getPlayer() * game.getState().ballVelX / game.getProperties().maxBallSpeed;
	input[3] = game.getState().ballVelY / game.getProperties().maxBallSpeed;
	input[4] = game.getState().paddle1Pos / (game.getProperties().height - game.getProperties().paddleHeight);
	input[5] = game.getState().paddle2Pos / (game.getProperties().height - game.getProperties().paddleHeight);
}

void PongReinforcementWorld::interpretNNOutput(std::vector<double>& output)
{
	if (output[0] > 0.5)
		game.movePaddle(1);
	else if (output[1] > 0.5)
		game.movePaddle(-1);
}


void PongReinforcementWorld::executeCompareAI()
{
	if (game.getState().ballPosY > game.getState().paddle2Pos + game.getProperties().paddleHeight / 2)
		game.movePaddle(1);
	else
		game.movePaddle(-1);
}

void PongReinforcementWorld::initializeForLearning()
{
	AbstractReinforcementWorld::initializeForLearning();
	time = -1;
}
