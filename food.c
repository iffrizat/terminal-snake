#include <stdlib.h>

#include "food.h"

static int rand_between(int x, int y)
{
		return x + (rand() % (y - x + 1));
}

void place_food(struct Food *f, int x, int y)
{
		f->x = x;
		f->y = y;
}

void random_place_food(struct Food *f, int w, int h)
{
		place_food(f, rand_between(10, w-1), rand_between(10, h-1));
}
