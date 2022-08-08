#include <stdio.h>
#include <ncurses.h>
#include <time.h>
#include <stdlib.h>

#include "food.h"
#include "snake.h"
#include "draws.h"

void advance_snake(struct Node *s, int len, enum Dir d)
{
		struct Node *head = &s[0];

		for (int i = len-1; i > 0; i--) {
				s[i] = s[i-1]; /* We shift the snake towards its head */
		};

		/* Depending on the direction, we make a new head node
		   at the needed coordinates 
		*/

		switch (d) {
				case UP:
						*head = (struct Node){ head->x, head->y - 1 };
						break;
				case RIGHT:
						*head = (struct Node){ head->x + 1, head->y };
						break;
				case DOWN:
						*head = (struct Node){ head->x, head->y + 1 };
						break;
				case LEFT:
						*head = (struct Node){ head->x - 1, head->y };
		};
}

enum Dir get_new_dir(enum Dir prev_d)
{
		int key = getch();

		if (key == ERR) {
				return prev_d;
		}

		if (key == KEY_UP && prev_d != DOWN) {
				return UP;
		}

		if (key == KEY_RIGHT && prev_d != LEFT) {
				return RIGHT;
		}

		if (key == KEY_DOWN && prev_d != UP) {
				return DOWN;
		}

		if (key == KEY_LEFT && prev_d != RIGHT) {
				return LEFT;
		}
		
		return prev_d;
}

int does_snake_eat(struct Node *s, struct Food *f)
{
		struct Node *head = &s[0];

		if (head->x == f->x && head->y == f->y) {
				return 1;
		}

		return 0;
}

int does_snake_collide(struct Node *s, int len, int w, int h)
{
		struct Node *head = &s[0];

		/* First, check for possible collision with boundaries */
		
		if (head->x == 0 || head->x == w-1 || 
		    head->y == 0 || head->y == h-1) {
				return 1;
		}

		/* Second, check for possible collison with itself */

		for (int i = 1; i < len; i++) {
				if (head->x == s[i].x && head->y == s[i].y) {
						return 1;
				}
		}

		/* By this point we know that the snake hasn't collided with anything */

		return 0;
}

int main(void)
{
		srand(time(NULL));

		initscr();
		cbreak();
		start_color();
		
		init_pair(1, COLOR_RED, COLOR_WHITE);
		init_pair(2, COLOR_GREEN, COLOR_BLACK);

		noecho();
		curs_set(0);
		keypad(stdscr, TRUE);
		timeout(500); /* Set the timeout to be half a second */

		int w, h;

		getmaxyx(stdscr, h, w);

		struct Node snake[128] = { { w/2, h/2 } };
		struct Food f;
		random_place_food(&f, w, h);

		int len = 1;
		enum Dir dir = RIGHT;

		/* Main game loop */
		while (1) {
				clear();
				
				draw_food(&f);
				draw_score(len - 1);
				advance_snake(snake, len, dir);
				draw_snake(snake, len);
				draw_boundaries(w-1, h-1);
				
				if (does_snake_collide(snake, len, w, h)) {
						break;
				}

				if (does_snake_eat(snake, &f)) {
						len++;
						random_place_food(&f, w, h);
				}

				refresh();
				dir = get_new_dir(dir);
		};

		endwin();
		
		return 0;
}
