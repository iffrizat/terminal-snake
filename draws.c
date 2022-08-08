#include <ncurses.h>

#include "snake.h"
#include "food.h"
#include "draws.h"

void draw_snake(struct Node *s, int len)
{
		attron(COLOR_PAIR(2));
		struct Node cur;
		for (int i = 0; i < len; i++) {
				cur = s[i];
				mvaddch(cur.y, cur.x, '#');
		}
		attroff(COLOR_PAIR(2));
}


void draw_boundaries(int w, int h)
{
		for (int y = 0; y < h; y++) {
				for (int x = 0; x < w; x++) {
						move(y, x);

						if (x == 0 || x == w-1 || y == 0 || y == -1) {
								addch('*');
						}
				}
		}
}

void draw_food(struct Food *f)
{
		attron(COLOR_PAIR(1));
		mvaddch(f->y, f->x, 'O');
		attroff(COLOR_PAIR(1));
}

void draw_score(int score)
{
		mvprintw(1, 1, "Your score is: %d", score);
}
