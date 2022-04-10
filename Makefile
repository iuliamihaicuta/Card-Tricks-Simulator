# Copyright Mihaicuta Iulia-Andreea-Naomi 314CAb 2021-2022
# compiler setup
CC=gcc
CFLAGS=-Wall -Wextra -std=c99 -g

# define targets
TARGETS=main

all: main

build: $(TARGETS)

main: main.c add_del.c doubly_linked_list.c operation.c show.c
	$(CC) $(CFLAGS) main.c add_del.c doubly_linked_list.c operation.c show.c -o tema1

clean:
	rm -f $(TARGETS)

