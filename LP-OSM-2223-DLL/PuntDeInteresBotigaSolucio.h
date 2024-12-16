#pragma once
#include "PuntDeInteresBase.h"
class PuntDeInteresBotigaSolucio : public PuntDeInteresBase
{
public:
	unsigned int getColor() override;
	PuntDeInteresBotigaSolucio(std::string shop, std::string openH, std::string wheelchair, Coordinate c, std::string name) : m_shop(shop), m_opening_hours(openH), m_wheelchair(wheelchair), PuntDeInteresBase(c,name) {}
	PuntDeInteresBotigaSolucio() : m_shop(" "), m_opening_hours(" "), m_wheelchair(" ") {}
	PuntDeInteresBotigaSolucio* clone() override { return new PuntDeInteresBotigaSolucio(*this);}
	PuntDeInteresBotigaSolucio(const PuntDeInteresBotigaSolucio& p) : m_shop(p.m_shop), m_opening_hours(p.m_opening_hours), m_wheelchair(p.m_wheelchair), PuntDeInteresBase(p.getCoord(), p.getName()) {}

private:
	std::string m_shop;
	std::string m_opening_hours;
	std::string m_wheelchair;

};