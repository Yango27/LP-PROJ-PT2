#include "pch.h"
#include "PuntDeInteresRestaurantSolucio.h"


unsigned int PuntDeInteresRestaurantSolucio::getColor()
{
	int valor;
	if (m_cuisine == "pizza")
	{
		valor = 0x03FCBA;
	}
	else
	{
		if (m_cuisine == "chinese")
		{
			valor = 0xA6D9F7;
		}
		else
		{
			if (m_wheelchair == "yes")
			{
				valor = 0x251351;
			}
			else
			{
				valor = PuntDeInteresBase::getColor(); //predefinit
			}
		}
	}

	return valor;
}