#pragma once
#include "CamiBase.h"
#include <unordered_map>

class CamiSolucio : public CamiBase
{
public:
	std::vector<Coordinate> getCamiCoords() override;
	CamiSolucio(const XmlElement& x, const std::unordered_map<std::string, std::pair<double, double>>& n) : m_way(x), m_nodes(n), m_cami(false) {}
	CamiSolucio() {}
	CamiSolucio(std::vector<Coordinate> c) : m_cami(true), m_camiMesCurt(c) {}
	CamiSolucio(const CamiSolucio& c);
	CamiSolucio* clone() override { return new CamiSolucio(*this);}

private:
	XmlElement m_way;
	std::unordered_map<std::string, std::pair<double, double>> m_nodes;
	bool m_cami;
	std::vector<Coordinate> m_camiMesCurt;
};
