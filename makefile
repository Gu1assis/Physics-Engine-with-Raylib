# Raylib Location
RAYLIB = ./raylib

# Name of final Executable
TARGET = PhysicsWithRaylib

# Compiler
CC = gcc

# Source code location
SRC = src/main.c

# Compilation flags
CFLAGS = -Wall -Wextra -std=c99 -Iinclude -I$(RAYLIB)/include

# Linking flags
# -lraylib does the principal linking
LDFLAGS = -L$(RAYLIB)/lib -lraylib -lopengl32 -lgdi32 -lwinmm -lm -lpthread

# Compile 
$(TARGET): $(SRC)
	$(CC) $(SRC) $(CFLAGS) $(LDFLAGS) -o $(TARGET)

clean:
	rm -f $(TARGET)