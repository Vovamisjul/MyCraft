#include "Furnace.h"

Furnace::Furnace(glm::vec3 pos)
{
	timeofburning = 0;
	timeofmelting = 0;
	melting = false;
	this->pos = pos;
	for (int i = 0; i < 3; i++)
	{
		slots[i].id = 0;
		slots[i].num = 0;
	}
}

void Furnace::startMelt()
{
	if (!melting)
	{
		burningInd = -1;
		meltingInd = -1;
		for (int i = 0; i < sizeofburning; i++)
		{
			if (slots[1].id == burning[i])
			{
				burningInd = i;
				break;
			}
		}
		if (burningInd != -1)
		{
			for (int i = 0; i < sizeofmelted; i++)
				if (slots[0].id == melted[i])
				{
					meltingInd = i;
					break;
				}
		}
		if (meltingInd != -1 && (slots[2].id == 0 || slots[2].id == results[meltingInd] && slots[2].num < 64))
		{
			melting = true;
			if (timeofburning < 0)
				timeofburning = 0;
			timeofmelting = 0;
		}
	}
	/*else
	{
		if (slots[0].num == 0 || slots[0].id != melted[meltingInd])
		{
			cancelMelt();
			startMelt();
		}
	}*/
}

void Furnace::processMelt(float dT)
{
	if (timeofburning > 0)
		timeofburning -= dT;
	if (melting)
	{
		timeofmelting += dT;
		if (timeofmelting >= meltingTime)
		{
			timeofmelting = 0;
			giveResult();
		}
		if (slots[0].num == 0)
			melting = false;
		if (timeofburning <= 0)
		{
			slots[1].num--;
			if (slots[1].num < 0)
			{
				cancelMelt();
				slots[1].num = 0;
				slots[1].id = 0;
			}
			else
			{
				timeofburning = burningtime[burningInd];
			}
		}
	}
}

void Furnace::giveResult()
{
	slots[0].num--;
	if (slots[0].num <= 0)
		slots[0].id = 0;
	slots[2].id = results[meltingInd];
	slots[2].num++;
}

void Furnace::cancelMelt()
{
	timeofmelting = 0;
	timeofburning = 0;
	melting = false;
}

float Furnace::givePrcBurn()
{
	if (burningInd == -1)
		return 0;
	return timeofburning / burningtime[burningInd] * 100;
}

float Furnace::givePrcMelt()
{
	if (meltingInd == -1)
		return 0;
	return timeofmelting / 8 * 100;
}