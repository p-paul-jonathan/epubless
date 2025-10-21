# Compiler settings
CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -g -D_POSIX_C_SOURCE=200809L -I./utils

# Directories and targets
OBJ_DIR = build
UTILS_DIR = utils
TARGET = epubless
TEST_FILE = test/narnia.epub

# Automatically find all .c files
SRC_FILES = $(wildcard *.c) $(wildcard $(UTILS_DIR)/*.c)
OBJ_FILES = $(patsubst %.c,$(OBJ_DIR)/%.o,$(SRC_FILES))

# Default rule
all: $(TARGET)

# Linking step
$(TARGET): $(OBJ_FILES)
	@echo "Linking $@ ..."
	$(CC) $(CFLAGS) -o $@ $^

# Compilation rule (auto creates subdirs)
$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@echo "Compiling $< ..."
	$(CC) $(CFLAGS) -c $< -o $@

# Clean build artifacts
clean:
	rm -rf $(OBJ_DIR) $(TARGET)

# Run test
test: $(TARGET)
	@echo "Running $(TARGET) with EPUB: $(TEST_FILE)"
	./$(TARGET) $(TEST_FILE)

.PHONY: all clean test
