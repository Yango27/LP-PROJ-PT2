#pragma once
#include "PuntDeInteresBase.h"

class PuntDeInteresRestaurantSolucio :public PuntDeInteresBase
{
public:
	PuntDeInteresRestaurantSolucio(std::string cuisine, std::string wheelchair, Coordinate coord, std::string name) : m_cuisine(cuisine), m_wheelchair(wheelchair), PuntDeInteresBase(coord, name) {}
	PuntDeInteresRestaurantSolucio() : m_cuisine(" "), m_wheelchair(" "), PuntDeInteresBase() {}
	PuntDeInteresRestaurantSolucio* clone() override { return new PuntDeInteresRestaurantSolucio(*this);}
	unsigned int getColor() override;
private:
	std::string m_cuisine;
	std::string m_wheelchair;
};
