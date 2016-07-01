#pragma once

#ifndef _PONGGAMECONTROLLER_H_
#define _PONGGAMECONTROLLER_H_

// Includes
#include <Windows/AbstractCustomSubApp.hpp>
#include <memory>
#include "PongGameWindow.hpp"
#include "Pong.hpp"


class PongGameController : public AbstractCustomSubApp
{
private:
	std::unique_ptr<PongGameWindow> window;
	Pong* world;
	PongGameState currentState;
	PongGameProperties properties;
protected:
	void prepareClose();
public:
	PongGameController(AbstractMainApp* mainApp, AbstractTrainingPlan* trainingPlan, AbstractWindow* parent = NULL);
	PongGameWindow* getWindow();
	void stopWatchMode();
	void startWatchMode();
	static std::string getLabel();
	PongGameState* getState();
	PongGameProperties* getProperties();
	void fieldChanged(Pong * pong);
};

#endif