#ifndef FOOD_H
#define FOOD_H

struct Food {
		int x;
		int y;
};

void place_food(struct Food *f, int x, int y);
void random_place_food(struct Food *f, int w, int h);

#endif
