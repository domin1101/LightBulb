// Includes
#include "LightBulbApp/Windows/SimulatorFactory.hpp"
#include "LightBulbApp/Windows/SimulatorController.hpp"
#include "LightBulbApp/Windows/SimulatorWindow.hpp"

namespace LightBulb
{
	SimulatorFactory::SimulatorFactory(NeuralNetworkRepository& neuralNetworkRepository_)
	{
		neuralNetworkRepository = &neuralNetworkRepository_;
	}

	AbstractSubApp* SimulatorFactory::createSupApp(AbstractMainApp& mainApp, AbstractWindow& parent) const
	{
		SimulatorController* controller = new SimulatorController(mainApp, *neuralNetworkRepository, parent);
		controller->getWindow().Show();
		return controller;
	}

	std::string SimulatorFactory::getLabel() const
	{
		return SimulatorController::getLabel();
	}
}
