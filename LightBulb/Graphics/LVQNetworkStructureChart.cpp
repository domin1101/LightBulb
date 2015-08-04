// Includes
#include "Graphics\LVQNetworkStructureChart.hpp"
#include "NetworkTopology\LVQNetwork.hpp"
#include "Neuron\AbstractNeuron.hpp"
#include "Neuron\StandardNeuron.hpp"
#include "Neuron\RBFThreshold.hpp"

LVQNetworkStructureChart::LVQNetworkStructureChart(LVQNetworkStructureChartOptions &options_)
{
	options = options_;
	// Check if all given options are correct
	// Check if the given neural network is valid
	if (options.lvqNetwork == NULL)
		throw std::invalid_argument("The given lvqNetwork is not valid");
	// Check if the indices are correct
	if (options.xRBFNeuronCenterCoordinateIndex >= options.lvqNetwork->getInputNeurons()->size())
		throw std::invalid_argument("Can't find any coordinate with index 'xRBFNeuronCenterCoordinateIndex'");
	if (options.yRBFNeuronCenterCoordinateIndex >= options.lvqNetwork->getInputNeurons()->size())
		throw std::invalid_argument("Can't find any coordinate with index 'yRBFNeuronCenterCoordinateIndex'");
}

void LVQNetworkStructureChart::recalculateAllValues()
{
	// Clear the shape list
	rbfNeuronShapes.clear();
	// Go through all rbfNeurons in the rbfNetwork
	for (auto neuron = options.lvqNetwork->getNeurons()->front().begin(); neuron != options.lvqNetwork->getNeurons()->front().end(); neuron++)
	{
		// Create a new circle shape
		sf::CircleShape newCircle;
		std::vector<double> centerVector = static_cast<StandardNeuron*>(*neuron)->getAfferentWeightsVector();
		// Set the radius to the width of the neuron converted into the view range
		newCircle.setRadius(20);
		// Set the position to the wished coordinates of the neuron center converted into the view range
		newCircle.setPosition((float)((centerVector[options.xRBFNeuronCenterCoordinateIndex] - options.xRangeStart) / (options.xRangeEnd - options.xRangeStart) * options.width), (float)((centerVector[options.yRBFNeuronCenterCoordinateIndex] - options.yRangeStart) / (options.yRangeEnd - options.yRangeStart) * options.height));
		// Add the offset position of the chart
		newCircle.move((float)options.posX, (float)options.posY);
		// Change the vertical scale depending of the view aspect ratio
		newCircle.setScale(1.0f, (float)(1.0f / options.width * (options.xRangeEnd - options.xRangeStart) / (options.yRangeEnd - options.yRangeStart) * options.height));

		// Set the style of the circle shape
		newCircle.setFillColor(sf::Color::Transparent);
		newCircle.setOutlineColor(sf::Color::White);
		newCircle.setOutlineThickness(1);
		newCircle.setOrigin(newCircle.getRadius() , newCircle.getRadius());
		newCircle.setPointCount(100);

		// Add the circle shape to the list
		rbfNeuronShapes.push_back(newCircle);
	}
}

void LVQNetworkStructureChart::draw(sf::RenderWindow &window)
{	
	// Outline the part of the window which will contain our chart
	sf::RectangleShape drawRect;
	drawRect.setPosition((float)options.posX, (float)options.posY);
	drawRect.setSize(sf::Vector2f((float)options.width, (float)options.height));
	drawRect.setFillColor(sf::Color::Transparent);
	drawRect.setOutlineColor(sf::Color::White);
	drawRect.setOutlineThickness(1);
	window.draw(drawRect);

	// Go through all neuron shapes
	for (auto neuronShape = rbfNeuronShapes.begin(); neuronShape != rbfNeuronShapes.end(); neuronShape++)
	{	
		// Draw the circle shape
		window.draw(*neuronShape);
	}

}
