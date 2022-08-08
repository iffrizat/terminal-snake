#ifndef DRAWS_H
#define DRAWS_H

void draw_snake(struct Node *s, int len);
void draw_boundaries(int w, int h);
void draw_food(struct Food *f);
void draw_score(int score);

#endif
