# Compiler and flags
CC = gcc
CFLAGS = 

# Source files
SRC = spinning_cube.c quaternion.c

# Object files
OBJ = $(SRC:.c=.o)

# Output executable
TARGET = spinning_cube

# Default target
.PHONY: all
all: $(TARGET)

# Rule to build the final executable
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ) -lm  # Link the math library

# Rule to compile object files from source
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Test executable
TEST_TARGET = test
TEST_SRC = test.c quaternion.c
TEST_OBJ = $(TEST_SRC:.c=.o)

# Rule to build and run tests
.PHONY: test
test: $(TEST_OBJ)
	$(CC) $(CFLAGS) -o $(TEST_TARGET) $(TEST_OBJ) -lm  # Link the math library
	./$(TEST_TARGET)

# Clean up generated files
.PHONY: clean
clean:
	rm -f $(OBJ) $(TEST_OBJ) $(TARGET) $(TEST_TARGET)

