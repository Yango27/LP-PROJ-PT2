#include "pch.h"
#include "PuntDeInteresBotigaSolucio.h"

unsigned int PuntDeInteresBotigaSolucio::getColor()
{
	int valor;
	if (m_shop == "supermarket")
	{
		valor = 0xA5BE00;
	}
	else
	{
		if (m_shop == "	tabacco")
		{
			valor = 0xFFAD69;
		}
		else
		{
			if (m_shop == "bakery")
			{
				if ((m_opening_hours == "06:00-22:00") && (m_wheelchair == "yes"))
				{
					valor = 0x4CB944;
				}
				else
				{
					valor = 0xE85D75;
				}
			}
			else
			{
				valor = 0xEFD6AC;
			}
		}
	}

	return valor;
}