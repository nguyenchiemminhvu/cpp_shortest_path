#include "Graph.h"
#include <cstdlib>

int main(int argc, char **argv) {

	Graph graph;
	if (!graph.loadGraphFromFile("graph.txt"))
	{
		exit(EXIT_FAILURE);
	}

	graph.showGraph();
	graph.findShortestPath('A', 'D');

	return 0;
}