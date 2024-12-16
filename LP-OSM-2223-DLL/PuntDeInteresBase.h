#pragma once

#include <string>
#include "Common.h"

class PuntDeInteresBase {

	private:
		Coordinate m_coord;
		std::string m_name;

	public:		
		PuntDeInteresBase();
		PuntDeInteresBase(Coordinate coord, std::string name);
		Coordinate getCoord()const { return m_coord; }
		std::string getName()const { return m_name; }
		virtual PuntDeInteresBase* clone() {return new PuntDeInteresBase(*this);}
		virtual unsigned int getColor();

};