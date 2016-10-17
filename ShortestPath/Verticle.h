#ifndef __VERTICLE_H__
#define __VERTICLE_H__

#pragma once

#include <iostream>
#include <fstream>
#include <vector>

class Verticle
{
public:

	Verticle();
	Verticle(char ID);
	virtual ~Verticle();

	Verticle& operator = (const Verticle &other);
	bool operator == (const Verticle &other);
	bool operator != (const Verticle &other);

	friend std::ostream& operator << (std::ostream &out, const Verticle &ver);

	void addAdjacencyVerticle(std::pair<Verticle, int>);

	char ID;
	bool visited;
	std::vector<std::pair<Verticle, int>> adjacency;

private:

};

std::ostream& operator << (std::ostream &out, const Verticle &ver);

#endif // !__VERTICLE_H__