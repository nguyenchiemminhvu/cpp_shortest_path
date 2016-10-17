#include "Graph.h"
#include <map>
#include <set>
#include <algorithm>
#include <fstream>
#include <cstdint>
#include <cstdio>


Graph::Graph()
{

}

Graph::~Graph()
{

}

bool Graph::loadGraphFromFile(std::string filePath)
{
	std::ifstream file;
	file.open(filePath);

	int num_of_verticle;
	file >> num_of_verticle;

	if (num_of_verticle > 26)
	{
		std::cout << "Too many verticles!" << std::endl;
		return false;
	}

	///////////////////////////////////////////////
	// Initialize verticle name
	this->verticles.resize(num_of_verticle);
	for (int i = 0; i < num_of_verticle; i++) {
		this->verticles[i].ID = i + 65;
		this->verticles[i].visited = false;
	}

	for (int i = 0; i < num_of_verticle; i++)
	{
		for (int j = 0; j < num_of_verticle; j++)
		{
			int distance;
			file >> distance;

			if (distance > 0)
				this->verticles[i].addAdjacencyVerticle(std::pair<Verticle, int>(verticles[j], distance));
			else
				this->verticles[i].addAdjacencyVerticle(std::pair<Verticle, int>(verticles[j], 0));
		}
	}

	return true;
}

void Graph::showGraph()
{
	std::cout << std::endl;
	for (int i = 0; i < verticles.size(); i++)
	{
		std::cout << verticles[i].ID << ": ";
		for (int j = 0; j < verticles[i].adjacency.size(); j++)
		{
			if (verticles[i].adjacency[j].second)
				std::cout << verticles[i].adjacency[j].first.ID << "(" << verticles[i].adjacency[j].second << ")" << " ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

bool Graph::findShortestPath(char srcID, char desID)
{
	if (!checkVerticleID(srcID) || !checkVerticleID(desID))
	{
		std::cout << "Wrong input!" << std::endl;
		return false;
	}

	prepareToFindShortestPath();
	distance[srcID - 65] = 0;

	while (sptSet[desID - 65] == false)
	{
		printCurrentState();

		int nextIndex = findNextIndex();
		if (nextIndex == -1)
		{
			std::cout << "Cannot find the path from " << srcID << " to " << desID << std::endl;
			return false;
		}
		sptSet[nextIndex] = true;
		consideringVer = &verticles[nextIndex];

		for (int i = 0; i < verticles.size(); i++)
		{
			if (
				!sptSet[i] && 
				matrixFormat[nextIndex][i] && 
				distance[nextIndex] + matrixFormat[nextIndex][i] < distance[i]
				)
			{
				distance[i] = distance[nextIndex] + matrixFormat[nextIndex][i];
				parent[i] = nextIndex;
			}
		}
	}
	printCurrentState();

	////////////////////////////////////////
	// Show shortest path
	int des = desID - 65;
	std::stack<Verticle> path;
	path.push(verticles[des]);
	while (parent[des] != des)
	{
		des = parent[des];
		path.push(verticles[des]);
	}

	std::cout << std::endl;
	while (!path.empty())
	{
		std::cout << path.top();
		if (path.size() > 1)
			std::cout << " -> ";
		path.pop();
	}
	std::cout << std::endl;

	return true;
}

bool Graph::checkVerticleID(char ID)
{
	return ID >= 65 && ID < (65 + verticles.size());
}

void Graph::convertAdjListToMatrix()
{
	for (int i = 0; i < verticles.size(); i++)
	{
		for (int j = 0; j < verticles.size(); j++)
		{
			matrixFormat[i][j] = verticles[i].adjacency[j].second;
		}
	}
}

void Graph::prepareToFindShortestPath()
{
	convertAdjListToMatrix();
	for (int i = 0; i < verticles.size(); i++)
	{
		parent[i] = i;
		sptSet[i] = false;
		distance[i] = INT_MAX;
	}
	consideringVer = NULL;
}

int Graph::findNextIndex()
{
	int nextIndex = -1, minDistance = INT_MAX;
	for (int i = 0; i < verticles.size(); i++)
	{
		if (!sptSet[i] && minDistance > distance[i])
		{
			minDistance = distance[i];
			nextIndex = i;
		}
	}
	return nextIndex;
}

void Graph::printCurrentState()
{
	if (!consideringVer)
	{
		printf("n \t adj(n) \t opening \t\t closed\n");
	}
	else
	{
		std::string space = "";
		int count = 0;

		printf("%c \t ", consideringVer->ID);

		for (int i = 0; i < consideringVer->adjacency.size(); i++)
		{
			if (consideringVer->adjacency[i].second)
			{
				std::cout << consideringVer->adjacency[i].first.ID << " ";
				count++;
			}
		}
		space.clear();
		space.assign(consideringVer->adjacency.size() * 2 - count * 2, ' ');
		std::cout << space;
		count = 0;

		for (int i = 0; i < consideringVer->adjacency.size(); i++)
		{
			if (!sptSet[consideringVer->adjacency[i].first.ID - 65] && distance[consideringVer->adjacency[i].first.ID - 65] != INT_MAX)
			{
				printf("%c(%d) ", consideringVer->adjacency[i].first.ID, distance[consideringVer->adjacency[i].first.ID - 65]);
				count++;
			}
		}
		space.clear();
		space.assign(consideringVer->adjacency.size() * 5 - count * 5, ' ');
		std::cout << space;
		count = 0;

		for (int i = 0; i < verticles.size(); i++)
		{
			if (sptSet[i])
			{
				printf("%c ", i + 65);
				count++;
			}
		}
		std::cout << std::endl;
	}
}
