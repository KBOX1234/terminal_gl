# Compiler
CC = gcc

# Detect platform
UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S),Linux)
    BACKEND_SRC = impl/backend_linux.c
endif
ifeq ($(UNAME_S),Darwin)
    BACKEND_SRC = impl/backend_mac.c
endif
ifeq ($(OS),Windows_NT)
    BACKEND_SRC = impl/backend_windows.c
endif

# Directories
SRC_DIR = src
INC_DIR = include
BUILD_DIR = build
LIB_DIR = lib

# Flags
CFLAGS = -I$(INC_DIR) -Wall -Wextra -O2 -fsanitize=address

# Find all source files except backend ones
SRC_FILES = $(shell find $(SRC_DIR) -name "*.c" ! -path "*/backend/*")

# Add platform backend
SRC_FILES += $(BACKEND_SRC)

# Object files
OBJ_FILES = $(patsubst %.c,$(BUILD_DIR)/%.o,$(SRC_FILES))

# Static library name
LIB_NAME = $(LIB_DIR)/libterminal_gl.a

# Default target
all: $(LIB_NAME)

# Build static library
$(LIB_NAME): $(OBJ_FILES)
	@mkdir -p $(LIB_DIR)
	ar rcs $@ $^

# Compile .c to .o
$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean
clean:
	rm -rf $(BUILD_DIR) $(LIB_DIR)

.PHONY: all clean
