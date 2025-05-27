NAME = vne
EXE = $(NAME)
TARGET = ./$(EXE)

CFILES = $(wildcard src/*.c)
OBJECTS = $(CFILES:.c=.o)

DEBUG = on

CC = gcc
CFLAGS = -Wall -std=c99
LDLIBS =

ifeq ($(DEBUG),on)
	CFLAGS += -g3 -O0
else
	CFLAGS += -O2
endif

all: $(OBJECTS)
	$(CC) $(CFLAGS) $^ -o $(TARGET) $(LDLIBS)

src/%.o: src/%.c src/%.h
	$(CC) $(CFLAGS) -c $< -o $@

src/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm src/*.o

run:
	$(TARGET)

test:
	echo 1 | $(TARGET)

debug:
	gdb -q $(TARGET)

watch:
	fd '\.c|\.h|Makefile' | entr -cs 'make -s && make -s run'

.PHONY:
	clean run test debug watch
