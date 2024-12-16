#pragma once
#include "MapaSolucio.h"
#include "Util.h"
#include <algorithm>
#include <stack>
#include <list>
#include <vector>

class GrafSolucio
{
public:
    GrafSolucio() : m_numNodes(0), m_numArestes(0) {}
    GrafSolucio(std::vector<CamiBase*>& caminsRetornats);
    ~GrafSolucio();
    void afegirNode(const Coordinate& node);
    void afegirAresta(const Coordinate& node1, const Coordinate& node2, double pes);
    std::vector<Coordinate> getNodes() { return m_nodes; }
    void dijkstra(size_t node1, size_t node2, std::vector<double>& dist, std::vector<int>& anterior);
    int minDistance(const std::vector<double>& dist, const std::vector<bool>& visitat) const;
    void camiMesCurt(const Coordinate& node1, const Coordinate& node2, std::stack<Coordinate>& cami);
    static const double DISTMAX;

private:
    std::vector<Coordinate> m_nodes;
    std::vector<std::list<std::pair<size_t, double>>> m_adjList;
    size_t m_numNodes;
    size_t m_numArestes;
};