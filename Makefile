CC = gcc
OUT = main

CFLAGS = -Wall

SRC = $(wildcard src/*.c)
SRC += $(wildcard lib/*.c)
OBJS = $(SRC:.c=.o)

CFLAGS = -Ilib
CFLAGS += -Isrc
CFLAGS += `pkg-config --cflags glfw3`

LDFLAGS = -L lib
LDFLAGS += `pkg-config --static --libs glfw3`

all: $(OUT)

$(OUT): $(OBJS)
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) $< -c -o $@ $(CFLAGS)

clean:
	rm $(OUT) $(OBJS)

.PHONY: clean
