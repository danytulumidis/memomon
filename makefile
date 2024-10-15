# Compiler and flags
CC = clang

# Targets
TARGET = memomon
OBJ = memomon.c

# Default rule
all: $(TARGET)

# Link object files to create the executable
$(TARGET): $(OBJ)
	$(CC) -o $(TARGET) $(OBJ)

run: all
	./${TARGET}

# Clean up generated files
clean:
	rm -f $(TARGET) 

