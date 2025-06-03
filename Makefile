TARGET = vne

CFILES = $(wildcard src/*.c)
HEADERS = $(wildcard src/*.h)
OBJECTS = $(CFILES:.c=.o)

DEBUG = on

CC = gcc
CFLAGS = -Wall -std=c99
LDLIBS = -lncurses

ifeq ($(OS), Windows_NT)
	CFLAGS += -Iexternal/pdcurses -Lexternal/pdcurses
	LDLIBS = -lpdcurses
endif

ifeq ($(DEBUG),on)
	CFLAGS += -g3 -O0
else
	CFLAGS += -O2
endif

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $^ -o $(TARGET) $(LDLIBS)

src/%.o: src/%.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm src/*.o

run:
	./$(TARGET)

test:
	./$(TARGET) sample-scripts/test

debug:
	gdb -q $(TARGET)

watch:
	fd '\.c|\.h|Makefile' | entr -cs 'make -s && make -s run'

.PHONY:
	clean run test debug watch
