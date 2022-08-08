#ifndef SNAKE_H
#define SNAKE_H

enum Dir {UP, RIGHT, DOWN, LEFT};

struct Node {
		int x;
		int y;
};

void fill_snake(struct Node *s);
void advance_snake(struct Node *s, int len, enum Dir d);
enum Dir get_new_dir(enum Dir prev_d);
int does_snake_collide(struct Node *s, int len, int w, int h);
int does_snake_eat(struct Node *s, struct Food *f);

#endif
