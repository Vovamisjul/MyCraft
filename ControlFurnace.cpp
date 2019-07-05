#include "ControlFurnace.h"

void ControlFurnace::processLeftMouse(Player *player, Furnace *furnace, float x, float y)
{
	bool isFurnace;
	int chosenslot = defSlot(x, y, &isFurnace);
	if (player->buf.id == 0)																	//take
	{
		if (chosenslot >= 0)
		{
			player->isCraft = isFurnace;
			if (!isFurnace)
			{

				player->bufslot = chosenslot;
				player->buf = player->slots[chosenslot];
				player->slots[chosenslot].id = 0;
				player->slots[chosenslot].num = 0;
			}
			else
			{
				player->bufslot = chosenslot;
				player->buf = furnace->slots[chosenslot];
				furnace->slots[chosenslot].id = 0;
				furnace->slots[chosenslot].num = 0;
			}
		}
	}
	else																						//put
	{
		if (chosenslot >= 0)
		{
			if (!isFurnace)
			{
				if (player->slots[chosenslot].id == 0)
				{
					player->slots[chosenslot] = player->buf;
					player->buf.id = 0;
					player->buf.num = 0;
				}
				else
				{
					if (player->slots[chosenslot].id == player->buf.id && player->slots[chosenslot].num + player->buf.num <= 64)
					{
						player->slots[chosenslot].num += player->buf.num;
						player->buf.id = 0;
						player->buf.num = 0;
					}
					else
					{
						slot temp = player->slots[chosenslot];
						player->slots[chosenslot] = player->buf;
						player->slots[player->bufslot] = temp;
						player->buf.id = 0;
						player->buf.num = 0;
					}
				}
			}
			else
			{
				if (chosenslot != 2)
				{
					if (furnace->slots[chosenslot].id == 0)
					{
						furnace->slots[chosenslot] = player->buf;
						player->buf.id = 0;
						player->buf.num = 0;
					}
					else
					{
						if (furnace->slots[chosenslot].id == player->buf.id && furnace->slots[chosenslot].num + player->buf.num <= 64)
						{
							furnace->slots[chosenslot].num += player->buf.num;
							player->buf.id = 0;
							player->buf.num = 0;
						}
						else
						{
							slot temp = furnace->slots[chosenslot];
							furnace->slots[chosenslot] = player->buf;
							if (!player->isCraft)
								player->slots[player->bufslot] = temp;
							else
								furnace->slots[player->bufslot] = temp;
							player->buf.id = 0;
							player->buf.num = 0;
						}
					}
				}
				else
				{
					player->addToInventory(player->buf.num, player->buf.id);
					player->buf.id = 0;
					player->buf.num = 0;
				}
			}
		}
		else
		{
			if (!isFurnace)
			{
				player->slots[player->bufslot] = player->buf;
				player->buf.id = 0;
				player->buf.num = 0;
			}
			else
			{
				player->addToInventory(player->buf.num, player->buf.id);
				player->buf.id = 0;
				player->buf.num = 0;
			}
		}
	}
}

void ControlFurnace::processRightMouse(Player *player, Furnace *furnace, float x, float y)
{
	bool isFurnace;
	int chosenslot = defSlot(x, y, &isFurnace);
	if (player->buf.id != 0)
	{
		if (chosenslot >= 0)
		{
			if (!isFurnace)
			{
				if (player->slots[chosenslot].id == 0 || player->slots[chosenslot].id == player->buf.id && player->slots[chosenslot].num < 64)
				{
					player->bufslot = chosenslot;
					player->buf.num--;
					player->slots[chosenslot].id = player->buf.id;
					player->slots[chosenslot].num++;
					if (player->buf.num == 0)
						player->buf.id = 0;
				}
			}
			else
			{
				if (chosenslot != 2 && furnace->slots[chosenslot].id == 0 || furnace->slots[chosenslot].id == player->buf.id && furnace->slots[chosenslot].num < 64)
				{
					player->buf.num--;
					furnace->slots[chosenslot].id = player->buf.id;
					furnace->slots[chosenslot].num++;
					if (player->buf.num == 0)
						player->buf.id = 0;
				}
			}
		}
	}
}

int ControlFurnace::defSlot(float x, float y, bool* furnace)
{
	int res = -1;
	if (x > 0.271875f && x < 0.31198f)
		res = 0;
	if (x > 0.325f && x < 0.3651f)
		res = 1;
	if (x > 0.378125f && x < 0.418229f)
		res = 2;
	if (x > 0.43125f && x < 0.471354f)
		res = 3;
	if (x > 0.484375f && x < 0.524479f)
		res = 4;
	if (x > 0.5375f && x < 0.5776f)
		res = 5;
	if (x > 0.590625f && x < 0.630729f)
		res = 6;
	if (x > 0.64375f && x < 0.683854f)
		res = 7;

	if (y > 0.477777f && y < 0.549074f)
		res += 0;
	else
		if (y > 0.572222f && y < 0.643518f)
			res += 8;
		else
			if (y > 0.666667f && y < 0.737963f)
				res += 16;
			else res = -1;
			if (res != -1)
			{
				*furnace = false;
				return res;
			}

			res = -1;
			if (x > 0.378125f && x < 0.415625f && y > 0.1333333f && y < 0.2f)
				res = 0;
			if (x > 0.378125f && x < 0.415625f && y > 0.322222f && y < 0.388889f)
				res = 1;
			if (x > 0.5375f && x < 0.575f && y > 0.2277777f && y < 0.2944444f)
				res = 2;
			if (res != -1)
				*furnace = true;
			return res;


}