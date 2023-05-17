# compiler and flags
CC = gcc
CFLAGS =	-Ofast -flto -Wall -Wextra -Wpedantic -Wshadow -Werror -Wbad-function-cast \
			-Wno-unused-result -Wcast-align -Wundef -Wpointer-arith -funroll-loops

# linker flags
LDFLAGS = -s

# linker libraries
LDLIBS = -lm

# directories
BIN = bin
SRC = src
OBJ = obj
INC = -I include

# automatically create directories as needed
MKDIR = @mkdir -p $(@D)

# set different flags and libraries depending on the operating system
ifeq ($(OS), Windows_NT)
	EXECUTABLE += windows-$(PROCESSOR_ARCHITECTURE)
	LDFLAGS += -static -Wl,--subsystem,windows
	LDLIBS += -D FREEGLUT_STATIC -lfreeglut_static -lopengl32 -lwinmm -lgdi32
else
	EXECUTABLE += $(shell uname -s)-$(shell uname -p)
	LDFLAGS += -fuse-ld=gold
	LDLIBS += -lglut -lGL
endif

.PHONY: build run clean

# find all C source files in the source directory
SRCS := $(wildcard $(SRC)/*.c)

# generate object file names by replacing the source directory with the object directory
OBJS := $(patsubst $(SRC)/%.c, $(OBJ)/%.o, $(SRCS))

# final executable
EXECUTABLE := $(BIN)/Carrom2D-$(shell echo $(EXECUTABLE) | tr 'A-Z' 'a-z' | tr -d " ")

# default target
build: $(EXECUTABLE)

# rule to generate object files
$(OBJ)/%.o: $(SRC)/%.c
	$(MKDIR)
	$(CC) $(INC) $(CFLAGS) $(LDLIBS) -c $< -o $@

# rule to link object files into the final build
$(EXECUTABLE): $(OBJS)
	$(MKDIR)
	$(CC) $(INC) $(CFLAGS) $(LDFLAGS) $^ -o $@ $(LDLIBS)

# run target
run:
	$(EXECUTABLE)

# clean target
clean:
	rm -rf $(OBJ)/*.o $(EXECUTABLE)
