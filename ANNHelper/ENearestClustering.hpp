#pragma once

#ifndef _KNEARESTCLUSTERING_H_
#define _KNEARESTCLUSTERING_H_

// Library includes
#include <vector>
#include <list>
#include <map>

// Includes
#include "AbstractNearestClustering.hpp"
#include "Point.hpp"

// Forward declarations
struct Cluster;

// This class contains all stuff needed to calculate clusters with the e-nearest cluster algorithm 
// This algorithm connects to every point all points with distance smaller than epsilon. By doing this it is possible that clusters/groups occur.
class ENearestClustering : public AbstractNearestClustering
{
private:
	// Caches the orderd distance between all points
	std::map<Point*, std::vector<std::pair<Point*, float>>> distanceToPoint;
	// Add all points of which the distance to pointToAdd is less than epsilon (nearestPointDistance)
	void addKNearestPointsToCluster(std::list<Point*>& points, Cluster& cluster, Point &pointToAdd, float nearestPointDistance);
public:
	// Refresh cache (nthNearestPointToPoint)
	void calculateCache(std::list<Point*>& points);
	float getBiggestDistance(std::list<Point*>& points);
};

#endif