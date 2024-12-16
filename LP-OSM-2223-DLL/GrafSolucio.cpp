#include "pch.h"
#include "GrafSolucio.h"
#include <limits>

const double GrafSolucio::DISTMAX = 1.7976931348623158e+308;

GrafSolucio::GrafSolucio(std::vector<CamiBase*>& caminsRetornats)
{
    m_numArestes = 0;
    m_numNodes = 0;

    std::vector<std::vector<Coordinate>> coordsCamins;
    for (auto cami : caminsRetornats)
    {
        std::vector<Coordinate> coords = cami->getCamiCoords();
        coordsCamins.push_back(coords);
        for (auto c : coords)
        {
            if (std::find(m_nodes.begin(), m_nodes.end(), c) == m_nodes.end())
            {
                afegirNode(c);
            }
        }
    }
    m_adjList.resize(m_numNodes);

    for (auto& cami : coordsCamins)
    {
        for (int i = 0; i < cami.size() - 1; i++)
        {
            afegirAresta(cami[i], cami[i + 1], Util::DistanciaHaversine(cami[i], cami[i + 1]));
        }
    }
}

void GrafSolucio::afegirNode(const Coordinate& node)
{
    m_nodes.push_back(node);
    m_numNodes++;
    m_adjList.emplace_back();
}

void GrafSolucio::afegirAresta(const Coordinate& node1, const Coordinate& node2, double pes)
{
    auto itNode1 = std::find(m_nodes.begin(), m_nodes.end(), node1);
    auto itNode2 = std::find(m_nodes.begin(), m_nodes.end(), node2);
    size_t index1 = std::distance(m_nodes.begin(), itNode1);
    size_t index2 = std::distance(m_nodes.begin(), itNode2);

    m_adjList[index1].emplace_back(index2, pes);
    m_adjList[index2].emplace_back(index1, pes);

    m_numArestes += 2;
}

int GrafSolucio::minDistance(const std::vector<double>& dist, const std::vector<bool>& visitat) const
{
    double min = DISTMAX;
    int minIndex = -1;

    for (size_t i = 0; i < dist.size(); i++)
    {
        if (dist[i] < min && !visitat[i])
        {
            min = dist[i];
            minIndex = i;
        }
    }

    return minIndex;
}

void GrafSolucio::dijkstra(size_t node1, size_t node2, std::vector<double>& dist, std::vector<int>& anterior)
{
    dist.resize(m_numNodes, DISTMAX);
    std::vector<bool> visitat(m_numNodes, false);
    dist[node1] = 0;
    anterior.resize(m_numNodes, -1);

    int pivot = node1;

    while (pivot != node2 && pivot != -1)
    {
        visitat[pivot] = true;

        for (const auto& adjPair : m_adjList[pivot])
        {
            size_t adjNode = adjPair.first;
            double pes = adjPair.second;

            if (!visitat[adjNode] && dist[pivot] + pes < dist[adjNode])
            {
                dist[adjNode] = dist[pivot] + pes;
                anterior[adjNode] = pivot;
            }
        }
        pivot = minDistance(dist, visitat);
    }
}

void GrafSolucio::camiMesCurt(const Coordinate& node1, const Coordinate& node2, std::stack<Coordinate>& cami)
{
    std::vector<double> dist;
    std::vector<int> anterior;
    auto it1 = std::find(m_nodes.begin(), m_nodes.end(), node1);
    auto it2 = std::find(m_nodes.begin(), m_nodes.end(), node2);

    if (it1 != m_nodes.end() && it2 != m_nodes.end())
    {
        size_t n1 = std::distance(m_nodes.begin(), it1);
        size_t n2 = std::distance(m_nodes.begin(), it2);
        dijkstra(n1, n2, dist, anterior);

        size_t nActual = n2;

        while (nActual != n1)
        {
            cami.push(m_nodes[nActual]);
            nActual = anterior[nActual];
        }
        cami.push(m_nodes[n1]);
    }
}

GrafSolucio::~GrafSolucio()
{
    m_nodes.clear();
    m_adjList.clear();
    m_numNodes = 0;
    m_numArestes = 0;
}