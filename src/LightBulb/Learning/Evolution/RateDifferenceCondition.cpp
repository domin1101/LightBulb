// Includes
#include "LightBulb/Learning/Evolution/RateDifferenceCondition.hpp"
#include "LightBulb/Logging/AbstractLogger.hpp"
// Library includes

namespace LightBulb
{
	bool RateDifferenceCondition::evaluate(const std::vector<std::pair<double, AbstractIndividual*>>& highscore, const AbstractEvolutionLearningRule& learningRule)
	{
		if (highscore.size() > 0)
		{
			if (lastBestRate != -1) {
				// Determine if the difference between the current fitness and the last one is lower then the allowed difference
				bool result = (highscore.front().first >= lastBestRate && highscore.front().first - lastBestRate < difference);

				// If the difference is to small increase the counter
				if (result)
				{
					counter++;
					// Only set the result to true if the counter is high enough
					result = counter >= count;
				}
				else
					counter = 0;

				if (result)
					log("rateDifferenceCondition is true: " + std::to_string(lastBestRate) + " - " + std::to_string(highscore.front().first) + " < " + std::to_string(difference), LL_LOW);
				else
					log("rateDifferenceCondition is false: " + std::to_string(lastBestRate) + " - " + std::to_string(highscore.front().first) + " > " + std::to_string(difference), LL_LOW);

				// Remember the best fitness for the next generation
				lastBestRate = highscore.front().first;
				return result;
			}
			else {
				// Remember the best fitness for the next generation
				lastBestRate = highscore.front().first;
				return false;
			}
		}
		else
		{
			return false;
		}
	}

	AbstractExitCondition* RateDifferenceCondition::clone() const
	{
		return new RateDifferenceCondition(*this);
	}

	RateDifferenceCondition::RateDifferenceCondition(double difference_, int count_)
		: AbstractExitCondition()
	{
		difference = difference_;
		lastBestRate = -1;
		counter = 0;
		count = count_;
	}

}
