// Includes
#include "LightBulb/Learning/Evolution/FitnessSharingFitnessFunction.hpp"
#include "LightBulb/Learning/Evolution/AbstractIndividual.hpp"
#include "LightBulb/NeuralNetwork/NeuralNetwork.hpp"
#include "LightBulb/NetworkTopology/AbstractNetworkTopology.hpp"
// Library includes
#include <math.h>

namespace LightBulb
{
	FitnessSharingFitnessFunction::FitnessSharingFitnessFunction(double dissimilarityThreshold_, double exponent_)
	{
		exponent = exponent_;
		dissimilarityThreshold = dissimilarityThreshold_;
	}

	void FitnessSharingFitnessFunction::execute(std::vector<std::pair<double, AbstractIndividual*>>& highscore)
	{
		if (dissimilarityThreshold > 0)
		{
			for (auto entry = highscore.begin(); entry != highscore.end(); entry++)
			{
				double sharingValue = 1;

				for (auto otherEntry = highscore.begin(); otherEntry != highscore.end(); otherEntry++)
				{
					if (*otherEntry != *entry)
					{
						sharingValue += std::max(0.0, 1 - pow(entry->second->getNeuralNetwork().getNetworkTopology().calculateEuclideanDistance(otherEntry->second->getNeuralNetwork().getNetworkTopology()), exponent) / dissimilarityThreshold);
					}
				}

				entry->first = entry->first / sharingValue;
			}
		}
	}

	AbstractFitnessFunction* FitnessSharingFitnessFunction::clone() const
	{
		return new FitnessSharingFitnessFunction(*this);
	}
}
