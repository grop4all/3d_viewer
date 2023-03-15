
all:
	gcc -std=c11 -g parser.c -o out
	./out

leaks: all
	valgrind --leak-check=full  --track-origins=yes ./out