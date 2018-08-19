CC = g++
OUT = lowg

SRC = $(shell find src -name '*.cpp')
SRCC = $(shell find deps/glad -name '*.c')
OBJ = $(patsubst src/%.cpp, objs/%.o, $(SRC))
OBJC = $(patsubst deps/glad/%.c, objs/%.o, $(SRCC))

CFLAGS = -Wall
CFLAGS += -Ideps
CFLAGS += -Ldeps
CFLAGS += `pkg-config --static --libs glfw3`
CFLAGS += -lfreeimage

all: $(OBJ) $(OBJC)

$(OBJ): objs/%.o: src/%.cpp
	$(CC) $< -c -o $@ $(CFLAGS)

$(OBJC): objs/%.o: deps/glad/%.c
	$(CC) $< -c -o $@ $(CFLAGS)

OBJS = $(OBJ)
OBJS += $(OBJC)

lib:
	@echo "making lib"
	@$(foreach obj,$(OBJS),ar -cvq liblowg.a $(obj);)

.PHONY: lib

clean:
	-find . -type f -name '*.o' -delete
