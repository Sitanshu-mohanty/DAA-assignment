CC = gcc
CFLAGS = -std=c11 -O2 -Wall -Wextra -pedantic -Iinclude
TARGET = bin/benchmark

SOURCES = src/merge_arrays.c benchmark/benchmark.c

all: $(TARGET)

$(TARGET): $(SOURCES) include/merge_arrays.h
	mkdir -p bin
	$(CC) $(CFLAGS) $(SOURCES) -o $(TARGET)

clean:
	rm -rf bin

.PHONY: all clean
