CC = gcc

OUT = main

CFLAGS = -Wall

SRC =$(wildcard src/*.c)
SRC += $(wildcard lib/*.c)
OBJS = $(SRC:.c=.o)

CFLAGS = -I lib
CFLAGS += -I src
CFLAGS += `pkg-config --cflags glfw3`

LDFLAGS = -L lib
LDFLAGS += `pkg-config --static --libs glfw3`

all: $(OUT)

$(OUT): $(OBJS)
	$(CC) -o $@ $^ $(LDFLAGS)

.PHONY: clean

clean:
	rm $(OUT) $(OBJS)

#gcc -I include `pkg-config --cflags glfw3` -o main src/main.c lib/glad.c `pkg-config --static --libs glfw3`
