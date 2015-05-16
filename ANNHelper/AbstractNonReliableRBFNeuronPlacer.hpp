#pragma once

#ifndef _ABSTRACTNONRELIABLERBFNEURONPLACER_H_
#define _ABSTRACTNONRELIABLERBFNEURONPLACER_H_

// Library Includes
#include <list>

// Includes
#include "AbstractRBFNeuronPlacer.hpp"

// Forward declarations
struct Cluster;

// This class contains all stuff needed to describe a RBFNeuronPlacer 
class AbstractNonReliableRBFNeuronPlacer : public AbstractRBFNeuronPlacer
{
protected:
	// Fills up the cluster list until there are exactly n (clusterCount) clusters
	void fillUpClusters(std::list<Point*>& points, std::list<Cluster> &clusters, int clusterCount, int dimensionCount);
public:
};

#endif