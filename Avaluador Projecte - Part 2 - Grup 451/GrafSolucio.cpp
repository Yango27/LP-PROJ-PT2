#include "GrafSolucio.h"
#include "pch.h"

GrafSolucio::GrafSolucio(MapaSolucio& m)
{
	std::vector<CamiBase*> camins;
	m.getCamins(camins);

	for (auto cami : camins)
	{
		std::vector<Coordinate> coords;
		coords = cami->getCamiCoords();
		for (auto c : coords)
		{
			if (std::find(m_nodes.begin(), m_nodes.end(), c) == m_nodes.end())
			{
				afegirNode(c);
			}
		}
	}

	for (auto& vec : m_matriuAdj)
	{
		vec.resize(m_numNodes, 0);
	}

	for (size_t i = 0; i < m_numNodes; i++)
	{
		for (size_t j = i + 1; j < m_numNodes; j++)
		{
			afegirAresta(m_nodes[i], m_nodes[j], Util::DistanciaHaversine(m_nodes[i], m_nodes[j]));
		}
	}
}

void GrafSolucio::afegirNode(const Coordinate& node)
{
	m_nodes.push_back(node);
	m_matriuAdj.push_back(std::vector<double>(++m_numNodes, 0));
}

void GrafSolucio::afegirAresta(const Coordinate& node1, const Coordinate& node2, double pes)
{
	auto itNode1 = std::find(m_nodes.begin(), m_nodes.end(), node1);
	auto itNode2 = std::find(m_nodes.begin(), m_nodes.end(), node2);
	size_t index1 = std::distance(m_nodes.begin(), itNode1);
	size_t index2 = std::distance(m_nodes.begin(), itNode2);

	m_matriuAdj[index1][index2] = pes;
	m_matriuAdj[index2][index1] = pes;

	m_numArestes += 2;
}