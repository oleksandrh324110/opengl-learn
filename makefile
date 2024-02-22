.PHONY: default-target all
default-target: all

ifndef target
$(error target is NOT defined)
endif

CFLAGS := -std=c11 -O3 -g -Wall -Wextra -Wpedantic
CFLAGS += -Ilib/cglm/include -Ilib/glad/include -Ilib/glfw/include/ -Ilib/stb
LDFLAGS := lib/cglm/libcglm.a lib/glad/src/gl.o lib/glfw/src/libglfw3.a

CMAKEFLAGS :=

ifeq ($(target), linux)
	CC := gcc
	CFLAGS +=
	LDFLAGS +=
	CMAKEFLAGS +=
else ifeq ($(target), windows)
	CC := gcc
	CFLAGS +=
	LDFLAGS += -lgdi32
	CMAKEFLAGS += -G "MinGW Makefiles"
else ifeq ($(target), darwin)
	CC := clang
	CFLAGS +=
	LDFLAGS += -framework OpenGL -framework IOKit -framework Cocoa -framework CoreVideo -framework CoreAudio
else ifeq ($(target), wsl)
	CC := x86_64-w64-mingw32-gcc
	CFLAGS +=
	LDFLAGS += -lgdi32 -mwindows
	CMAKEFLAGS += -DCMAKE_TOOLCHAIN_FILE=./CMake/x86_64-w64-mingw32.cmake
endif

SRC = $(wildcard src/*.c) $(wildcard src/**/*.c) $(wildcard src/**/**/*.c) $(wildcard src/**/**/**/*.c)
OBJ = $(SRC:.c=.o)

.PHONY: all clean

all: compile link run

lib:
	cd lib/glfw && cmake . $(CMAKEFLAGS) && make
	cd lib/cglm && cmake . -DCGLM_STATIC=ON $(CMAKEFLAGS) && make
	cd lib/glad && $(CC) -c src/gl.c -o src/gl.o -Iinclude

compile: $(OBJ)

%.o: %.c
	$(CC) -c $< -o $@ $(CFLAGS)

link:
	$(CC) $(OBJ) -o bin/main.exe $(LDFLAGS)

run:
	./bin/main.exe