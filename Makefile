CC = g++
OUT = lowg

SRC = $(wildcard src/*.c)
SRC += $(wildcard src/*.cpp)
SRC += $(wildcard lib/*.c)
SRC += $(wildcard lib/*.cpp)

OBJ = ${SRC:.cpp=.o}

CFLAGS = -Wall
CFLAGS += -Ilib
CFLAGS += -Llib
CFLAGS += `pkg-config --static --libs glfw3`
CFLAGS += -lfreeimage
CFLAGS += -lSOIL

LDFLAGS = -Wall
LDFLAGS += -lSOIL
LDFLAGS += -lfreeimage
LDFLAGS += -Ilib
LDFLAGS += `pkg-config --static --libs glfw3`

all: $(OUT)

$(OUT): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

%.o: %.cpp
	$(CC) $< -c -o $@ $(LDFLAGS)

clean:
	-rm $(OUT)
	-rm src/*.o
