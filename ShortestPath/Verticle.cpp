#include "Verticle.h"

Verticle::Verticle()
{
	this->ID = 0;
	visited = false;
}


Verticle::Verticle(char ID)
{
	this->ID = ID;
	visited = false;
}


Verticle::~Verticle()
{

}

Verticle & Verticle::operator=(const Verticle & other)
{
	if (this == &other)
		return *this;

	this->ID = other.ID;
	return *this;
}

bool Verticle::operator==(const Verticle & other)
{
	return this->ID == other.ID;
}

bool Verticle::operator!=(const Verticle & other)
{
	return this->ID != other.ID;
}

void Verticle::addAdjacencyVerticle(std::pair<Verticle, int> adj)
{
	adjacency.push_back(adj);
}

std::ostream & operator<<(std::ostream & out, const Verticle & ver)
{
	out << ver.ID;
	return out;
}
