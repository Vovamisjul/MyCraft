#include "math.h"

float myfloor(float x)
{
	if (x - floorf(x) < 0.5f) return floorf(x);
	return ceilf(x);
}
