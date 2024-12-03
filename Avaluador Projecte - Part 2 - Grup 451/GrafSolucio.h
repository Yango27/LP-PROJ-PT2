#pragma once
#include "MapaSolucio.h"
#include "Util.h"
#include <algorithm>
class GrafSolucio
{
public:
	GrafSolucio() : m_numNodes(0), m_numArestes(0) {}
	GrafSolucio(MapaSolucio& m);
	void afegirNode(const Coordinate& node);
	void afegirAresta(const Coordinate& node1, const Coordinate& node2, double pes);
private:
	std::vector<Coordinate> m_nodes;
	std::vector<std::vector<double>> m_matriuAdj;
	size_t m_numNodes;
	size_t m_numArestes;
};