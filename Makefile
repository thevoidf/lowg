CC = g++
OUT = lowg

SRC = $(shell find src -name '*.cpp')
SRCC = $(shell find deps/glad -name '*.c')
OBJ = $(patsubst src/%.cpp, objs/%.o, $(SRC))
OBJC = $(patsubst deps/glad/%.c, objs/%.o, $(SRCC))

#g++ -I../deps -I/usr/include/FTGL -I/usr/include/freetype2 ../objs/*.o fonts.cpp -o fonts -lglfw -lrt -lm -ldl -lfreeimage -lfreetype -lftgl -lz -lpng 16 -lm -lz -lm

CFLAGS = -Wall
CFLAGS += -Ideps
CFLAGS += -Ldeps
CFLAGS += -Llib
CFLAGS += -I/usr/include/freetype2
CFLAGS += `pkg-config --static --libs glfw3`
CFLAGS += -lfreeimage
CFLAGS += -lfreetype
CFLAGS += -lfreetype-gl

all: $(OBJ) $(OBJC)

$(OBJ): objs/%.o: src/%.cpp
	$(CC) $< -c -o $@ $(CFLAGS)

$(OBJC): objs/%.o: deps/glad/%.c
	$(CC) $< -c -o $@ $(CFLAGS)

OBJS = $(OBJ)
OBJS += $(OBJC)

lib:
	@$(foreach obj,$(OBJS),ar -cvq liblowg.a $(obj);)

clean:
	-find . -type f -name '*.o' -delete
