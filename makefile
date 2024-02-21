OS := $(or $(OS), $(shell uname))

CFLAGS := -std=c11 -O3 -g -Wall -Wextra -Wpedantic
CFLAGS += -Ilib/cglm/include -Ilib/glad/include -Ilib/glfw/include/ -Ilib/stb
LDFLAGS := lib/cglm/libcglm.a lib/glad/src/gl.o lib/glfw/src/libglfw3.a

CMAKEFLAGS :=

ifeq ($(OS), Windows_NT)
	CC := gcc
	CFLAGS +=
	LDFLAGS += -lgdi32
	CMAKEFLAGS += -G "MinGW Makefiles"
else ifeq ($(OS), Darwin)
	CC := clang
	CFLAGS +=
	LDFLAGS += -framework OpenGL -framework IOKit -framework Cocoa -framework CoreVideo -framework CoreAudio
endif

SRC = $(wildcard src/*.c) $(wildcard src/**/*.c) $(wildcard src/**/**/*.c) $(wildcard src/**/**/**/*.c)
OBJ = $(SRC:.c=.o)

.PHONY: all clean

all: compile link run

libs:
	cd lib/cglm && cmake . -DCGLM_STATIC=ON $(CMAKEFLAGS) && make
	cd lib/glad && $(CC) -c src/gl.c -o src/gl.o -Iinclude
	cd lib/glfw && cmake . $(CMAKEFLAGS) && make

compile: $(OBJ)

%.o: %.c
	$(CC) -c $< -o $@ $(CFLAGS)

link:
	$(CC) $(OBJ) -o bin/main.exe $(LDFLAGS)

run:
	bin/main.exe