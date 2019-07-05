#include "ControlBench.h"

void ControlBench::processLeftMouse(Player *player, float x, float y)
{
	bool isCraft;
	int chosenslot = defSlot(x, y, &isCraft);
	if (player->buf.id == 0)																	//take
	{
		if (chosenslot >= 0)
		{
			player->isCraft = isCraft;
			if (!isCraft)
			{

				player->bufslot = chosenslot;
				player->buf = player->slots[chosenslot];
				player->slots[chosenslot].id = 0;
				player->slots[chosenslot].num = 0;
			}
			else
			{
				if (chosenslot != 9)
				{
					player->bufslot = chosenslot;
					player->buf = player->benchCraftSlots[chosenslot];
					player->benchCraftSlots[chosenslot].id = 0;
					player->benchCraftSlots[chosenslot].num = 0;
				}
				else
				{
					player->bufslot = chosenslot;
					player->buf = player->benchCraftSlots[chosenslot];
					player->benchCraftSlots[chosenslot].id = 0;
					player->benchCraftSlots[chosenslot].num = 0;
					for (int i = 0; i < 9; i++)
					{
						if (player->benchCraftSlots[i].id)
						{
							player->benchCraftSlots[i].num--;
							if (player->benchCraftSlots[i].num <= 0)
							{
								player->benchCraftSlots[i].num = 0;
								player->benchCraftSlots[i].id = 0;
							}
						}
					}
				}
			}
		}
	}
	else																						//put
	{
		if (chosenslot >= 0)
		{
			if (!isCraft)
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
				if (chosenslot != 9)
				{
					if (player->benchCraftSlots[chosenslot].id == 0)
					{
						player->benchCraftSlots[chosenslot] = player->buf;
						player->buf.id = 0;
						player->buf.num = 0;
					}
					else
					{
						if (player->benchCraftSlots[chosenslot].id == player->buf.id && player->benchCraftSlots[chosenslot].num + player->buf.num <= 64)
						{
							player->benchCraftSlots[chosenslot].num += player->buf.num;
							player->buf.id = 0;
							player->buf.num = 0;
						}
						else
						{
							slot temp = player->benchCraftSlots[chosenslot];
							player->benchCraftSlots[chosenslot] = player->buf;
							if (!player->isCraft)
								player->slots[player->bufslot] = temp;
							else
								player->benchCraftSlots[player->bufslot] = temp;
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
			if (!isCraft)
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


void ControlBench::processRightMouse(Player *player, float x, float y)
{
	bool isCraft;
	int chosenslot = defSlot(x, y, &isCraft);
	if (player->buf.id != 0)
	{
		if (chosenslot >= 0)
		{
			if (!isCraft)
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
				if (chosenslot != 9 && player->benchCraftSlots[chosenslot].id == 0 || player->benchCraftSlots[chosenslot].id == player->buf.id && player->benchCraftSlots[chosenslot].num < 64)
				{
					player->buf.num--;
					player->benchCraftSlots[chosenslot].id = player->buf.id;
					player->benchCraftSlots[chosenslot].num++;
					if (player->buf.num == 0)
						player->buf.id = 0;
				}
			}
		}
	}
}

int ControlBench::defSlot(float x, float y, bool* isCraft)
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
				*isCraft = false;
				return res;
			}
			res = -1;
			if (x > 0.271875f && x < 0.31198f)
				res = 0;
			if (x > 0.325f && x < 0.3651f)
				res = 1;
			if (x > 0.378125f && x < 0.418229f)
				res = 2;

			if (y > 0.12777778f && y < 0.1944444f)
				res += 0;
			else
				if (y > 0.2222222f && y < 0.2888888f)
					res += 3;
				else
				{
					if (y > 0.31666667f && y < 0.3833333f)
						res += 6;
					else
						res = -1;
				}
			if (x > 0.4875f && x < 0.525f && y > 0.2222222f && y < 0.2888888f)
				res = 9;
			if (res != -1)
				*isCraft = true;
			return res;
}
