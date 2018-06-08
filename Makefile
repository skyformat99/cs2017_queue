compile:
	clang -g -O0 -Wall -std=gnu11 -Wno-int-to-void-pointer-cast -lpthread main.c queue.c -o queue.out

test1-1: compile
	./query.out
