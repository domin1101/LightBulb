#include "gtest/gtest.h"
#include "Function/FermiFunction.hpp"
#include <Mocks/MockmutationSelector.hpp>
#include <Mocks/MockEvolutionObject.hpp>
#include <Learning/Evolution/StandardDeviationFitnessFunction.hpp>

class StandardDeviationFitnessFunctionTest : public testing::Test {
public:
	StandardDeviationFitnessFunction* standardDeviationFitnessFunction;

	void SetUp() {
		
	}

	virtual ~StandardDeviationFitnessFunctionTest()
	{
		delete standardDeviationFitnessFunction;
	}
};

TEST_F(StandardDeviationFitnessFunctionTest, execute)
{
	standardDeviationFitnessFunction = new StandardDeviationFitnessFunction(1);

	std::vector<std::pair<double, AbstractEvolutionObject*>> highscore;
	highscore.push_back(std::make_pair(10, (AbstractEvolutionObject*)NULL));
	highscore.push_back(std::make_pair(6, (AbstractEvolutionObject*)NULL));
	highscore.push_back(std::make_pair(2, (AbstractEvolutionObject*)NULL));

	standardDeviationFitnessFunction->execute(&highscore);
	EXPECT_NEAR(7.26599, highscore[0].first, 0.00001);
	EXPECT_NEAR(3.26599, highscore[1].first, 0.00001);
	EXPECT_NEAR(-0.734014, highscore[2].first, 0.00001);

}


TEST_F(StandardDeviationFitnessFunctionTest, executeFails)
{
	standardDeviationFitnessFunction = new StandardDeviationFitnessFunction(5);

	std::vector<std::pair<double, AbstractEvolutionObject*>> highscore;
	highscore.push_back(std::make_pair(10, (AbstractEvolutionObject*)NULL));
	highscore.push_back(std::make_pair(6, (AbstractEvolutionObject*)NULL));
	highscore.push_back(std::make_pair(2, (AbstractEvolutionObject*)NULL));

	EXPECT_THROW(standardDeviationFitnessFunction->execute(&highscore), std::logic_error);
}