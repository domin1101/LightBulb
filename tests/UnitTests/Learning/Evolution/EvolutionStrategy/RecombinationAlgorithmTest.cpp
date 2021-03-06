#include "LightBulb/Function/ActivationFunction/FermiFunction.hpp"
#include <Mocks/MockMutationSelector.hpp>
#include <Mocks/MockIndividual.hpp>
#include <LightBulb/Learning/Evolution/EvolutionStrategy/RecombinationAlgorithm.hpp>
#include <Mocks/MockNeuralNetwork.hpp>
#include <Mocks/MockNetworkTopology.hpp>
#include "Mocks/MockRandomGenerator.hpp"
#include "LightBulb/LinearAlgebra/Matrix.hpp"

using namespace LightBulb;

class RecombinationAlgorithmTest : public testing::TestWithParam<bool> {
public:
	RecombinationAlgorithm* recombinationAlgorithm;
	MockIndividual individual1;
	MockIndividual individual2;
	Vector<> mutationStrength1, mutationStrength2;
	std::vector<Matrix<>> weights1, weights2;
	MockNeuralNetwork neuralNetwork1, neuralNetwork2;
	MockNetworkTopology networkTopology1, networkTopology2;
	MockRandomGenerator mockRandomGenerator;
	void SetUp() {
		mutationStrength1.getEigenValueForEditing().resize(2);
		mutationStrength1.getEigenValueForEditing() << 2, -5;
		EXPECT_CALL(individual1, getMutationStrength()).WillRepeatedly(testing::ReturnRef(mutationStrength1));
		
		
		EXPECT_CALL(individual1, getNeuralNetwork()).WillRepeatedly(testing::ReturnRef(neuralNetwork1));
		EXPECT_CALL(neuralNetwork1, getNetworkTopology()).WillRepeatedly(testing::ReturnRef(networkTopology1));
		EXPECT_CALL(networkTopology1, getAllWeights()).WillRepeatedly(testing::ReturnRef(weights1));

		weights1.push_back(Matrix<>(1, 2));
		weights1[0].getEigenValueForEditing()(0, 0) = 2;
		weights1[0].getEigenValueForEditing()(0, 1) = -3;
		weights1.push_back(Matrix<>(1, 1));
		weights1[1].getEigenValueForEditing()(0, 0) = 10;

		mutationStrength2.getEigenValueForEditing().resize(2);
		mutationStrength2.getEigenValueForEditing() << 0.3, 3;
		EXPECT_CALL(individual2, getMutationStrength()).WillRepeatedly(testing::ReturnRef(mutationStrength2));

		EXPECT_CALL(individual2, getNeuralNetwork()).WillRepeatedly(testing::ReturnRef(neuralNetwork2));
		EXPECT_CALL(neuralNetwork2, getNetworkTopology()).WillRepeatedly(testing::ReturnRef(networkTopology2));
		EXPECT_CALL(networkTopology2, getAllWeights()).WillRepeatedly(testing::ReturnRef(weights2));

		weights2.push_back(Matrix<>(1, 2));
		weights2[0].getEigenValueForEditing()(0, 0) = -6;
		weights2[0].getEigenValueForEditing()(0, 1) = 1;
		weights2.push_back(Matrix<>(1, 1));
		weights2[1].getEigenValueForEditing()(0, 0) = 3;
	}

	void addExtraNeuronsForDifferentSizes()
	{
		weights1[0] = Matrix<>(2, 3);
		weights1[0].getEigenValueForEditing()(0, 0) = 2;
		weights1[0].getEigenValueForEditing()(0, 1) = -3;
		weights1[0].getEigenValueForEditing()(0, 2) = 5;
		weights1[0].getEigenValueForEditing()(1, 0) = -2;
		weights1[0].getEigenValueForEditing()(1, 1) = 3;
		weights1[0].getEigenValueForEditing()(1, 2) = -5;

		weights1[1] = Matrix<>(1, 2);
		weights1[1].getEigenValueForEditing()(0, 0) = 10;
		weights1[1].getEigenValueForEditing()(0, 1) = -1;

		mutationStrength1.getEigenValueForEditing().conservativeResize(mutationStrength1.getEigenValue().size() + 1);
		mutationStrength1.getEigenValueForEditing()(mutationStrength1.getEigenValue().size() - 1) = 0.1;

		weights2[1] = Matrix<>(2, 1);
		weights2[1].getEigenValueForEditing()(0, 0) = 3;
		weights2[1].getEigenValueForEditing()(1, 0) = 6;

	}

	virtual ~RecombinationAlgorithmTest()
	{
		delete recombinationAlgorithm;
	}
};

INSTANTIATE_TEST_CASE_P(RecombinationAlgorithmTestMultDev, RecombinationAlgorithmTest, testing::Bool());

TEST_P(RecombinationAlgorithmTest, executeWithAverage)
{
	recombinationAlgorithm = new RecombinationAlgorithm(true, true);
	if (GetParam())
		recombinationAlgorithm->setCalculatorType(CT_GPU);
	recombinationAlgorithm->execute(individual1, individual2);

	EXPECT_NEAR(1.15, mutationStrength1.getEigenValue()[0], 0.00001);
	EXPECT_NEAR(-1, mutationStrength1.getEigenValue()[1], 0.00001);

	EXPECT_NEAR(-2, weights1[0].getEigenValue()(0, 0), 0.00001);
	EXPECT_NEAR(-1, weights1[0].getEigenValue()(0, 1), 0.00001);
	EXPECT_NEAR(6.5, weights1[1].getEigenValue()(0, 0), 0.00001);
}


TEST_P(RecombinationAlgorithmTest, executeWithoutAverage)
{
	recombinationAlgorithm = new RecombinationAlgorithm(false, false);
	if (GetParam())
		recombinationAlgorithm->setCalculatorType(CT_GPU);
	recombinationAlgorithm->setRandomGenerator(mockRandomGenerator);
	testing::InSequence s;
	EXPECT_CALL(mockRandomGenerator, randFloat()).WillOnce(testing::Return(0));
	EXPECT_CALL(mockRandomGenerator, randFloat()).WillOnce(testing::Return(1));
	EXPECT_CALL(mockRandomGenerator, randFloat()).WillOnce(testing::Return(0));
	EXPECT_CALL(mockRandomGenerator, randFloat()).WillOnce(testing::Return(1));
	EXPECT_CALL(mockRandomGenerator, randFloat()).WillOnce(testing::Return(1));

	recombinationAlgorithm->execute(individual1, individual2);

	EXPECT_NEAR(0.3, mutationStrength1.getEigenValue()[0], 0.00001);
	EXPECT_NEAR(3, mutationStrength1.getEigenValue()[1], 0.00001);

	EXPECT_NEAR(2, weights1[0].getEigenValue()(0, 0), 0.00001);
	EXPECT_NEAR(1, weights1[0].getEigenValue()(0, 1), 0.00001);
	EXPECT_NEAR(10, weights1[1].getEigenValue()(0, 0), 0.00001);
}

TEST_P(RecombinationAlgorithmTest, executeWithAverageWithDifferentSizes)
{
	addExtraNeuronsForDifferentSizes();

	recombinationAlgorithm = new RecombinationAlgorithm(true, true);
	if (GetParam())
		recombinationAlgorithm->setCalculatorType(CT_GPU);
	recombinationAlgorithm->execute(individual1, individual2);

	EXPECT_NEAR(1.15, mutationStrength1.getEigenValue()[0], 0.00001);
	EXPECT_NEAR(-1, mutationStrength1.getEigenValue()[1], 0.00001);
	EXPECT_NEAR(0.1, mutationStrength1.getEigenValue()[2], 0.00001);

	EXPECT_NEAR(-2, weights1[0].getEigenValue()(0, 0), 0.00001);
	EXPECT_NEAR(-1, weights1[0].getEigenValue()(0, 1), 0.00001);
	EXPECT_NEAR(5, weights1[0].getEigenValue()(0, 2), 0.00001);
	EXPECT_NEAR(-2, weights1[0].getEigenValue()(1, 0), 0.00001);
	EXPECT_NEAR(3, weights1[0].getEigenValue()(1, 1), 0.00001);
	EXPECT_NEAR(-5, weights1[0].getEigenValue()(1, 2), 0.00001);
	EXPECT_NEAR(6.5, weights1[1].getEigenValue()(0, 0), 0.00001);
	EXPECT_NEAR(-1, weights1[1].getEigenValue()(0, 1), 0.00001);
}


TEST_P(RecombinationAlgorithmTest, executeWithoutAverageWithDifferentSizes)
{
	srand(1);
	addExtraNeuronsForDifferentSizes();

	recombinationAlgorithm = new RecombinationAlgorithm(false, false);
	if (GetParam())
		recombinationAlgorithm->setCalculatorType(CT_GPU);
	recombinationAlgorithm->setRandomGenerator(mockRandomGenerator);
	testing::InSequence s;
	EXPECT_CALL(mockRandomGenerator, randFloat()).WillOnce(testing::Return(0));
	EXPECT_CALL(mockRandomGenerator, randFloat()).WillOnce(testing::Return(1));
	EXPECT_CALL(mockRandomGenerator, randFloat()).WillOnce(testing::Return(0));
	EXPECT_CALL(mockRandomGenerator, randFloat()).WillOnce(testing::Return(1));
	EXPECT_CALL(mockRandomGenerator, randFloat()).WillOnce(testing::Return(1));
	
	recombinationAlgorithm->execute(individual1, individual2);
	
	EXPECT_NEAR(0.3, mutationStrength1.getEigenValue()[0], 0.00001);
	EXPECT_NEAR(3, mutationStrength1.getEigenValue()[1], 0.00001);
	EXPECT_NEAR(0.1, mutationStrength1.getEigenValue()[2], 0.00001);

	EXPECT_NEAR(2, weights1[0].getEigenValue()(0, 0), 0.00001);
	EXPECT_NEAR(1, weights1[0].getEigenValue()(0, 1), 0.00001);
	EXPECT_NEAR(5, weights1[0].getEigenValue()(0, 2), 0.00001);
	EXPECT_NEAR(-2, weights1[0].getEigenValue()(1, 0), 0.00001);
	EXPECT_NEAR(3, weights1[0].getEigenValue()(1, 1), 0.00001);
	EXPECT_NEAR(-5, weights1[0].getEigenValue()(1, 2), 0.00001);
	EXPECT_NEAR(10, weights1[1].getEigenValue()(0, 0), 0.00001);
	EXPECT_NEAR(-1, weights1[1].getEigenValue()(0, 1), 0.00001);
}
