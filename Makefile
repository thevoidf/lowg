CC = gcc
OUT = main

CFLAGS = -Wall

SRC = $(wildcard src/*.c)
SRC += $(wildcard lib/*.c)
# SRC += $(wildcard lib/SOIL/*.c)
OBJS = $(SRC:.c=.o)

CFLAGS = -Ilib
CFLAGS += -Isrc
CFLAGS += `pkg-config --cflags glfw3`

LDFLAGS = -Llib
LDFLAGS += -lSOIL
LDFLAGS += `pkg-config --static --libs glfw3`

all: $(OUT)

$(OUT): $(OBJS)
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) $< -c -o $@ $(CFLAGS)

clean:
	rm $(OUT) $(OBJS)

.PHONY: clean
