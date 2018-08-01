CC = g++
OUT = lowg

SRC = $(shell find src -name '*.cpp')
SRC += $(shell find src -name '*.c')
SRC += $(shell find deps/glad -name '*.c')
OBJ = $(patsubst %.cpp, %.o, $(SRC))

CFLAGS = -Wall
CFLAGS += -Ideps
CFLAGS += -Ldeps
CFLAGS += `pkg-config --static --libs glfw3`
CFLAGS += -lfreeimage

all: $(OUT)

$(OUT): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

%.o: %.cpp
	$(CC) $< -c -o $@ $(CFLAGS)

clean:
	-rm $(OUT)
	-find src -type f -name '*.o' -delete
