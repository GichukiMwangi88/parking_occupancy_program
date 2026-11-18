# C compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -Wextra -std=c11 -Iincludes -Iconfig

# Application source files
SRCS = $(wildcard src/*.c)

# Object files generated from source files
OBJS = $(SRCS:.c=.o)

# Name of the executable
TARGET = parking_occupancy

# Default target: build the application
all: $(TARGET)

# Link object files into the executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# Compile each C source file into an object file
src/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

