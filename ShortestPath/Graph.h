#ifndef __GRAPH_H__
#define __GRAPH_H__

#pragma once

#include <string>
#include <vector>
#include <stack>

#include "Verticle.h"

#define MAX_VERTICLE 26

class Graph
{
public:

	Graph();
	virtual ~Graph();

	bool loadGraphFromFile(std::string filePath);
	void showGraph();
	bool findShortestPath(char srcID, char desID);

	std::vector<Verticle> verticles;

private:

	bool checkVerticleID(char ID);
	void convertAdjListToMatrix();
	void prepareToFindShortestPath();
	int findNextIndex();
	void printCurrentState();

	int matrixFormat[MAX_VERTICLE][MAX_VERTICLE];
	int num_ver;
	int parent[MAX_VERTICLE];
	int distance[MAX_VERTICLE];
	bool sptSet[MAX_VERTICLE];
	Verticle *consideringVer;
};

#endif // !__GRAPH_H__