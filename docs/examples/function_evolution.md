# Function evolution

*The example is integrated into LightBulbExample and its code can be found in [FunctionEvolution](https://github.com/domin1101/LightBulb/tree/master/example/LightBulbExample/Examples/FunctionEvolution).*

A simple example how to use evolution in LightBulb. Our goal is to find the global minimum of the [six-hump camel-back function](https://www.sfu.ca/~ssurjano/camel6.html).

## Introduction

To make this example working we need two extra classes. An evolution environment and one for individuals which "live" in this environment.
The algorithm will then create a bunch of random individuals, test them and selects the best ones. After doing this evolution process a few times, we get a few good ones which solved our problem.

## Individuals

We call our individual class "Position" and let it inherit from AbstractDefaultIndividual.

```cpp
class Position : public LightBulb::AbstractDefaultIndividual
{
protected:
	FunctionSimulator* functionSimulator;
	std::vector<float> position;
	void getNNInput(std::vector<double>& input) override;
	void interpretNNOutput(std::vector<double>& output) override;
public:	
	Position(FunctionSimulator& functionSimulator_);
	std::vector<float> getPosition() const;
};
```

In the constructor we simply set the corresponding environment (the FunctionSimulator) and create our neural network:

```cpp
Position::Position(FunctionSimulator& functionSimulator_)
	: AbstractDefaultIndividual(functionSimulator_)
{
	functionSimulator = &functionSimulator_;
	position.resize(2);

	FeedForwardNetworkTopologyOptions options;
	options.useBiasNeuron = false;
	options.neuronsPerLayerCount.push_back(1);
	options.neuronsPerLayerCount.push_back(2);
	options.descriptionFactory = new SameNeuronDescriptionFactory(new NeuronDescription(new WeightedSumFunction(), new IdentityFunction()));
	buildNeuralNetwork(options);
}
```

In this case we use just two weights, which represent the coordinates of a point on the six-hump camel-back function. We want to optimize those weights, so that they point on the global minium of the function.

The individual class should also describe how the input of the neural network - the brain of the individual - should look like and how its output should be interpreted.


```cpp
void Position::getNNInput(std::vector<double>& input)
{
	input.resize(1);
	input[0] = 1;
}
```

We always set the input of the network to 1, so the output of the neural network will be equal to its weights.
This is of course not the normal case, but in this very simple example its necessary.


```cpp
void Position::interpretNNOutput(std::vector<double>& output)
{
	for (int i = 0; i < 2; i++)
	{	
		position[i] = output[i];
	}
}
```

We also don't have to interpret the output that much. We only store it into an extra vector, so we can use it later.

Thats all. Thats our individual class.


## Environment

Now lets form the environment class. We call it "FunctionSimulator" and let it inherit from AbstractDefaultEvolutionEnvironment.

```cpp
class FunctionSimulator : public LightBulb::AbstractSimpleEvolutionEnvironment
{
protected:
	LightBulb::AbstractIndividual* createNewIndividual() override;
    double sixHumpCamelFunction(std::vector<float> pos);
public:
	bool doSimulationStep() override;
	double getFitness(const LightBulb::AbstractIndividual& individual) const override;
};
```

The environment manages the whole simulation process and determines the fitness (=rating) value of our individuals.

```cpp
AbstractIndividual* FunctionSimulator::createNewIndividual()
{
	return new Position(*this);
}
```

We need one method for creating new individuals.

```cpp
bool FunctionSimulator::doSimulationStep()
{
	for (auto position = individuals.begin(); position != individuals.end(); position++)
	{
		(*position)->doNNCalculation();
	}

	return false;
}
```

In the simulation we just go through all individuals and execute one network calculation.

```cpp
double FunctionSimulator::getFitness(const AbstractIndividual& individual) const
{
	std::vector<float> pos = static_cast<const Position&>(individual).getPosition();
	return -1 * sixHumpCamelFunction(pos);
}
double FunctionSimulator::sixHumpCamelFunction(std::vector<float> pos)
{
	return 4 * pow(pos[0], 2) - 2.1 * pow(pos[0], 4) + pow(pos[0], 6) / 3 + pos[0] * pos[1] - 4 * pow(pos[1], 2) + 4 * pow(pos[1], 4);
}
```

For rating individuals we just extract their position and compute the function value at this position.
As we want to find the minium of the function, we have to negate the function value. So the minimal function value will get the highest fitness value.


## Learning rule

Now we are ready to construct the learning rule.

```cpp
FunctionSimulator environment;
```

Thats our environment.

```cpp
EvolutionLearningRuleOptions options;

options.creationCommands.push_back(new ConstantCreationCommand(20));
````
At first we set the creation command which creates up to 20 individual per evolution step.

```cpp
MutationAlgorithm* mutationAlgorithm = new MutationAlgorithm(1.6);
options.mutationsCommands.push_back(new ConstantMutationCommand(mutationAlgorithm, new StochasticUniversalSamplingSelector(), 1.8));
```

We add a mutation command which mutates individuals to increase the population by 180%. 

```cpp
options.recombinationCommands.push_back(new ConstantRecombinationCommand(new RecombinationAlgorithm(), new StochasticUniversalSamplingSelector(), 0.3));
```

We will recombine 30%.

```cpp
options.reuseCommands.push_back(new ConstantReuseCommand(new BestReuseSelector(), 1));
```

And reuse the best individual.

```cpp
options.exitConditions.push_back(new RateDifferenceCondition(0.00001, 10));
```

The learning process should end, if the best individual does not improve very much for ten rounds.

```cpp
options.selectionCommands.push_back(new BestSelectionCommand(20));
```

The best 20 individuals should be selected for mutation, recombination and reuse.

```cpp
options.environment = &environment;
EvolutionLearningRule learningRule(options);
```
Set the environment and create the learning rule.

## Run it!

Now we are ready to start!
```cpp
std::unique_ptr<EvolutionLearningResult> result(static_cast<EvolutionLearningResult*>(learningRule.start()));
```

Let's test if the global minium has been found:

```cpp
Position* bestPosition = static_cast<Position*>(result.bestIndividuals[0].get());
std::vector<float> minimum = bestPosition.getPosition();
std::cout << minimum[0] << ", " << minium[1] << std::endl;
```

You should now see something like:

```
0.0898, -0.7126
```

or

```
-0.0898, 0.7126
```

This should be the global minimum of the six-hump camel-back function. We have found it just by calculating a few function values.

