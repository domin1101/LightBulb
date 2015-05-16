#pragma once

#ifndef _CLUSTER_H_
#define _CLUSTER_H_

// Library includes
#include <vector>
#include <list>

// Includes
#include "ValuePosition.hpp"

// Forward declaration
struct Point;

// This class contains all stuff needed to describe a Cluster 
struct Cluster
{
	// The position of the cluster
	ValuePosition center;
	// All points contained by the cluster
	std::list<Point*> points;
	// The radius of the cluster
	float radius;
	Cluster()
	{
		radius = 0;
	}
	Cluster(ValuePosition &center_, float radius_)
	{
		center = center_;
		radius = radius_;
	}
};

#endif