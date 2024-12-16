#include "pch.h"
#include "CamiSolucio.h"


CamiSolucio::CamiSolucio(const CamiSolucio& c)
{
	m_way = c.m_way;
	m_nodes = c.m_nodes;
}
std::vector<Coordinate> CamiSolucio::getCamiCoords()
{
	std::vector<Coordinate> coords; //llista amb les coordenades dels nodes
	if (!m_cami)
	{
		for (int i = 0; i < m_way.fills.size(); i++)
		{
			if (m_way.fills[i].first == "nd") //iterem tots els nodes del cami
			{
				std::string nodeRef = m_way.fills[i].second[0].second; //agafem el id del node
				if (m_nodes.find(nodeRef) != m_nodes.end())
				{
					double lat = m_nodes[nodeRef].first;
					double lon = m_nodes[nodeRef].second;
					Coordinate c;
					c.lat = lat;
					c.lon = lon;
					coords.push_back(c);
				}

			}
		}
		return coords;
	}
	else
		return m_camiMesCurt;
	
}

