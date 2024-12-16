#include "pch.h"
#include "PuntDeInteresBase.h"


PuntDeInteresBase::PuntDeInteresBase() {
	this->m_coord = Coordinate{ 0.0, 0.0 };
	this->m_name = "undefinit";
}

PuntDeInteresBase::PuntDeInteresBase(Coordinate coord, std::string name) {
	this->m_name = name;
	this->m_coord.lat = coord.lat;
	this->m_coord.lon = coord.lon;
}

unsigned int PuntDeInteresBase::getColor() {
	return 0xFFA500;
}


