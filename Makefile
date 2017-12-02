CC := gcc
CFLAGS := -std=c11 -Wall -Wextra -Wformat=2 -Wshadow -Wpedantic \
	-Wno-unused-parameter -Wno-missing-field-initializers -Ofast -flto
DCFLAGS := -Wall -std=c99 -pedantic -O2

sources = $(wildcard src/*.c)
deps = build/sds.o

all: solver

solver: $(sources) $(deps)
	$(CC) $(CFLAGS) -isystemlib/ $^ -o $@

build/sds.o: lib/sds/sds.c
	$(CC) $(DCFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -f build/*
	rm -f solver
