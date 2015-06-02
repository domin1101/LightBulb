#include "FreeNetwork.hpp"
#include "InputNeuron.hpp"
#include "StandardNeuron.hpp"
#include "BiasNeuron.hpp"
#include "Edge.hpp"
#include "AbstractNeuronFactory.hpp"
#include <exception>

FreeNetworkOptions::FreeNetworkOptions()
{
	enableShortcuts = false;
	neuronFactory = NULL;
	neuronsPerLayerCount = std::vector<unsigned int>();
	useBiasNeuron = false;
}

FreeNetworkOptions::~FreeNetworkOptions()
{
	delete(neuronFactory);
}

FreeNetworkOptions::FreeNetworkOptions(const FreeNetworkOptions &obj)
{
	*this = obj;
	neuronFactory = obj.neuronFactory->getCopy();
}



FreeNetwork::~FreeNetwork()
{
	// Go through all layers
	for (std::vector<std::vector<AbstractNeuron*>>::iterator layer = neurons.begin(); layer != neurons.end(); layer++)
	{
		// Go through all neurons in this layer
		for (std::vector<AbstractNeuron*>::iterator neuron = (*layer).begin(); neuron != (*layer).end(); neuron++)
		{
			delete(*neuron);
		}
	}
}

FreeNetwork::FreeNetwork()
{
}

FreeNetwork::FreeNetwork(LayeredNetworkOptions_t &options_)
{
	// Copy all options
	options.reset(new LayeredNetworkOptions(options_));
	// Build the network
	buildNetwork();		
}


void FreeNetwork::getAllNeuronOutputs(std::map<AbstractNeuron*, float>& neuronOutputs)
{
	// Go through all layers
	for (std::vector<std::vector<AbstractNeuron*>>::iterator layer = getNeurons()->begin(); layer != getNeurons()->end(); layer++)
	{
		// Go through all neurons in the current layer
		for (std::vector<AbstractNeuron*>::iterator neuron = layer->begin(); neuron != layer->end(); neuron++)
		{
			// Set the value in the map to the current activation of the neuron
			neuronOutputs[*neuron] = (*neuron)->getActivation();
		}
	}
	// Also consider the bias neuron!
	if (options->useBiasNeuron)
		neuronOutputs[&biasNeuron] = 1;
}

void FreeNetwork::getAllNeuronNetInputs(std::map<AbstractNeuron*, float>& neuronNetInputs)
{
	// Go through all layers
	for (std::vector<std::vector<AbstractNeuron*>>::iterator layer = getNeurons()->begin(); layer != getNeurons()->end(); layer++)
	{
		// Go through all neurons in the current layer
		for (std::vector<AbstractNeuron*>::iterator neuron = layer->begin(); neuron != layer->end(); neuron++)
		{
			// Cast the neuron into a standard neuron
			StandardNeuron* standardNeuron = dynamic_cast<StandardNeuron*>(*neuron);
			// If the cast was successful and this is not a input neuron, set the value in the map to the current net input of the neuron
			if (standardNeuron)
				neuronNetInputs[*neuron] = standardNeuron->getNetInput();
		}
	}
}


void v::buildNetwork()
{
	// Check if all given options are correct
	if (getLayerCount() < 2)
		throw std::invalid_argument("A layered network must always contain at least two layers (one input and one output layer)");
	for (int l = 0; l < getLayerCount(); l++)
		if (options->neuronsPerLayerCount[l] == 0)
			throw std::invalid_argument("Every layer has to contain at least one neuron");
	if (!options->neuronFactory)
		throw std::invalid_argument("The given neuronFactory is not valid");

	// Clear all neurons
	neurons.clear();

	// Add all neurons
	for (int l = 0; l < getLayerCount(); l++)
	{
		// Add a new list for every layer
		neurons.push_back(std::vector<AbstractNeuron*>());

		// Add the neurons to the current layer
		for (int i = 0; i < options->neuronsPerLayerCount[l]; i++)
		{
			addNeuronIntoLayer(l, false);
		}		
	}

}

std::vector<AbstractNeuron*>* FreeNetwork::getInputNeurons()
{
	// Return the first layer
	return &neurons.front();
}

std::vector<AbstractNeuron*>* FreeNetwork::getOutputNeurons()
{
	// Return the last layer
	return &neurons.back();
}

std::vector<std::vector<AbstractNeuron*>>* FreeNetwork::getNeurons()
{
	return &neurons;
}

void FreeNetwork::randomizeWeights(float randStart, float randEnd)
{
	// Go through all layers
	for (std::vector<std::vector<AbstractNeuron*>>::iterator layer = neurons.begin(); layer != neurons.end(); layer++)
	{
		// Go through all neurons in this layer
		for (std::vector<AbstractNeuron*>::iterator neuron = (*layer).begin(); neuron != (*layer).end(); neuron++)
		{
			// Go through all effernetEdges of this neuron
			std::list<Edge*>* efferentEdges = (*neuron)->getEfferentEdges();
			for (std::list<Edge*>::iterator edge = efferentEdges->begin(); edge != efferentEdges->end(); edge++)
			{
				do{
					// Set the weight to a new random value
					(*edge)->setWeight((float)rand() / RAND_MAX * (randEnd - randStart) + randStart);
				} while ((*edge)->getWeight()==0); // If the new weight is 0 => retry
			}
		}
	}

	// If a bias neuron is used also randomize its weights
	if (options->useBiasNeuron)
	{
		// Go through all effernetEdges of the bias neuron
		std::list<Edge*>* efferentEdges = biasNeuron.getEfferentEdges();
		for (std::list<Edge*>::iterator edge = efferentEdges->begin(); edge != efferentEdges->end(); edge++)
		{
			do{
				// Set the weight to a new random value
				(*edge)->setWeight((float)rand() / RAND_MAX * (randEnd - randStart) + randStart);
			} while ((*edge)->getWeight()==0); // If the new weight is 0 => retry
		}		
	}
}

int FreeNetwork::getEdgeCount()
{
	int edgeCounter = 0;
	// Go through all layers
	for (std::vector<std::vector<AbstractNeuron*>>::iterator layer = neurons.begin(); layer != neurons.end(); layer++)
	{
		// Go through all neurons in this layer
		for (std::vector<AbstractNeuron*>::iterator neuron = (*layer).begin(); neuron != (*layer).end(); neuron++)
		{
			// Add the count of the efferent edges of the current neuron
			edgeCounter += (*neuron)->getEfferentEdges()->size();
		}
	}

	// If a bias neuron is used add also its efferent edges
	edgeCounter += biasNeuron.getEfferentEdges()->size();

	return edgeCounter;
}

void FreeNetwork::resetActivation()
{
	// Go through all layers
	for (std::vector<std::vector<AbstractNeuron*>>::iterator layer = neurons.begin(); layer != neurons.end(); layer++)
	{
		// Go through all neurons in this layer
		for (std::vector<AbstractNeuron*>::iterator neuron = (*layer).begin(); neuron != (*layer).end(); neuron++)
		{
			// Reset the activation of the current neuron
			(*neuron)->resetActivation();
		}
	}
}

void FreeNetwork::mergeWith(LayeredNetwork& otherNetwork)
{
	// If a bias neuron is used in the other network
	if (otherNetwork.options->useBiasNeuron)
	{
		// Go through all efferent edges of the bias neuron of the other network
		for (std::list<Edge*>::iterator edge = otherNetwork.biasNeuron.getEfferentEdges()->begin(); edge != otherNetwork.biasNeuron.getEfferentEdges()->end(); edge++)
		{
			// If the current network also uses a bias neuron
			if (options->useBiasNeuron)
			{
				// Reconnect the edge to the bias neuron of the current network
				(*edge)->setPrevNeuron(&biasNeuron);
				// Add the edge to the bias neuron of the current network
				biasNeuron.addNextNeuron(*edge);
			}
			else
			{
				// Else just delete the edge from the neuron which is connected with the bias neuron of the other network
				(*edge)->getNextNeuron()->removeAfferentEdge(*edge);
			}
		}
		// Clear all edges of the bias neuron of the other network, so they won't be deleted
		otherNetwork.biasNeuron.getEfferentEdges()->clear();		
	}
	else if (options->useBiasNeuron)
	{
		// Else if the other network does not have a bias neuron, but the current does
		// Go through all layers
		for (std::vector<std::vector<AbstractNeuron*>>::iterator layer = neurons.begin(); layer != neurons.end(); layer++)
		{
			// Go through all neurons in this layer
			for (std::vector<AbstractNeuron*>::iterator neuron = (*layer).begin(); neuron != (*layer).end(); neuron++)
			{
				// Add a edge from our bias neuron to the current neuron in the other network
				biasNeuron.addNextNeuron(static_cast<StandardNeuron*>(*neuron), 1);
			}
		}
	}

	// Insert all input neurons from the otherNetwork into the first layer of this network
	neurons[0].insert(neurons[0].end(), otherNetwork.neurons[0].begin(), otherNetwork.neurons[0].end());

	// Append every layer (except the first one) from the other network to the layer list of this network
	for (int l = 1; l < otherNetwork.neurons.size(); l++)
	{
		neurons.push_back(otherNetwork.neurons[l]);
	}

	// Clear all neurons of other network so they won't be deleted
	otherNetwork.neurons.clear();

	// Refresh the counters
	refreshNeuronsPerLayerCounters();
}

void FreeNetwork::copyWeightsFrom(LayeredNetwork& otherNetwork)
{
	// Go through all layers of the deeper network
	int lOther = otherNetwork.getLayerCount() - 1;
	for (int l = getLayerCount() - 1; l > 0 && lOther > 0;)
	{
		// Extract the neurons in the current layer of both networks
		std::vector<AbstractNeuron*>* neuronsInLayer = getNeuronsInLayer(l);
		std::vector<AbstractNeuron*>* neuronsInLayerOther = otherNetwork.getNeuronsInLayer(lOther);
		// Go through all neurons in the current network
		int neuronIndex = 0;
		std::vector<AbstractNeuron*>::iterator neuronOther = neuronsInLayerOther->begin();
		for (std::vector<AbstractNeuron*>::iterator neuron = neuronsInLayer->begin(); neuron != neuronsInLayer->end() && neuronOther != neuronsInLayerOther->end(); neuron++, neuronOther++, neuronIndex++)
		{
			// Extract all afferent edges of the current neurons
			std::list<Edge*>* afferentEdges = (dynamic_cast<StandardNeuron*>(*neuron))->getAfferentEdges();
			std::list<Edge*>* afferentEdgesOther = (dynamic_cast<StandardNeuron*>(*neuronOther))->getAfferentEdges();
			// Go through all afferentEdges of the actual neurons
			std::list<Edge*>::iterator edgeOther = afferentEdgesOther->begin();
			for (std::list<Edge*>::iterator edge = afferentEdges->begin(); edge != afferentEdges->end() && edgeOther != afferentEdgesOther->end(); edge++, edgeOther++)
			{	
				// Copy the weight from the edge from the other network into the edge of the own one
				(*edge)->setWeight((*edgeOther)->getWeight());
			}
		}

		// Go one layer backwards in the other network
		lOther--;
		// If we reached the input layer and the otherNetwork is not as deep as the own one, then start from the last layer in the other network again
		if (lOther == 0 && otherNetwork.getLayerCount() < getLayerCount())
			lOther = otherNetwork.getLayerCount() - 1;

		// Go one layer backwards in the own network
		l--;
		// If we reached the input layer and the own network is not as deep as the other one, then start from the last layer in the own network again
		if (l == 0 && getLayerCount() < otherNetwork.getLayerCount())
			l = getLayerCount() - 1;
	}
}

std::unique_ptr<std::map<Edge*, bool>> FreeNetwork::getNonRecurrentEdges()
{
	// Create a map
	std::unique_ptr<std::map<Edge*, bool>> nonRecurrentEdges(new std::map<Edge*, bool>());

	// Go through all layers
	for (std::vector<std::vector<AbstractNeuron*>>::iterator layer = neurons.begin(); layer != neurons.end(); layer++)
	{
		// Go through all neurons in this layer
		for (std::vector<AbstractNeuron*>::iterator neuron = (*layer).begin(); neuron != (*layer).end(); neuron++)
		{
			// Go through all effernetEdges of this neuron
			std::list<Edge*>* efferentEdges = (*neuron)->getEfferentEdges();
			for (std::list<Edge*>::iterator edge = efferentEdges->begin(); edge != efferentEdges->end(); edge++)
			{
				// In a feed forward layered network are only non recurrent edges, so always set the value to true
				(*nonRecurrentEdges)[*edge] = true;
			}
		}
	}

	// If a bias neuron is used
	if (options->useBiasNeuron)
	{
		// Go through all effernetEdges of the bias neuron
		std::list<Edge*>* efferentEdges = biasNeuron.getEfferentEdges();
		for (std::list<Edge*>::iterator edge = efferentEdges->begin(); edge != efferentEdges->end(); edge++)
		{
			// Also all edges from the bias neuron are non recurrent
			(*nonRecurrentEdges)[*edge] = true;
		}		
	}

	return nonRecurrentEdges;
}