CFLAGS := -Wall
CFILES := snake.o draws.o food.o 
LIBS := -lncurses

main: $(CFILES)
		gcc $(CFLAGS) $^ -o main $(LIBS) 

%.o: %.c
		gcc $(CFLAGS) -c $^ 2> temp

clean:
		rm *.o main

