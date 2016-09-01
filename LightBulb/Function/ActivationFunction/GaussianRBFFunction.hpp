#pragma once

#ifndef _GAUSSIANRBFFUNCTION_H_
#define _GAUSSIANRBFFUNCTION_H_

// Library includes
#include <math.h>

// Includes
#include "Function/ActivationFunction/AbstractActivationFunction.hpp"
#include "Function/NeighborhoodFunction/AbstractNeighborhoodFunction.hpp"

class GaussianRBFFunction : public AbstractActivationFunction, public AbstractNeighborhoodFunction
{
private:
	Eigen::VectorXd* widths;
public:
	GaussianRBFFunction(Eigen::VectorXd* widths_);
	// Inherited:
	void execute(int layerNr, std::vector<std::unique_ptr<Eigen::VectorBlock<Eigen::VectorXd>>>& activations, std::vector<Eigen::VectorXd>& netInputs);
	double execute(double input);
	double executeDerivation(double input);
	AbstractActivationFunction* getActivationFunctionCopy();
	double getMaximum();
	double getMinimum();
	bool hasAMaxAndMinimum();
	double execute(StandardNeuron* neuron, StandardNeuron* activatedNeuron, AbstractSOMStructure* structure, NeuronCompareThreshold* threshold, double maxDistance);
	AbstractNeighborhoodFunction* getNeighborhoodFunctionCopy();
};

#include "IO/GaussianRBFFunctionIO.hpp"

#endif