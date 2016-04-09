#pragma once

#ifndef _TRAININGCONTROLLERIO_H_
#define _TRAININGCONTROLLERIO_H_

// Includes
#include "IO/NeuralNetworkRepositoryIO.hpp"
#include "IO/TrainingPlanRepositoryIO.hpp"
#include "Windows/TrainingController.hpp"
// Libraray includes
#include <cereal/cereal.hpp>

template <class Archive>
void serialize(Archive& archive, TrainingController& trainingController)
{
	serialize(archive, *trainingController.neuralNetworkRepository);

	IOStorage<std::vector<std::unique_ptr<AbstractNeuralNetwork>>>::push(trainingController.neuralNetworkRepository->getNeuralNetworks());
	serialize(archive, *trainingController.trainingPlanRepository);
	IOStorage<std::vector<std::unique_ptr<AbstractNeuralNetwork>>>::clear();
}


#endif