# -----------------------------------------------------------------------------
# Compiler and base settings
# -----------------------------------------------------------------------------
CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -g -D_POSIX_C_SOURCE=200809L -I./utils

OBJ_DIR = build
UTILS_DIR = utils
TARGET = epubless
TEST_FILE = test/narnia.epub

SRC_FILES = $(wildcard *.c) $(wildcard $(UTILS_DIR)/*.c)
OBJ_FILES = $(patsubst %.c,$(OBJ_DIR)/%.o,$(SRC_FILES))

# -----------------------------------------------------------------------------
# Platform detection
# -----------------------------------------------------------------------------
UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S),Darwin) # macOS
  CFLAGS += -I/opt/homebrew/include -I/opt/homebrew/include/minizip
  LDFLAGS += -L/opt/homebrew/lib -lminizip -lz
else ifeq ($(UNAME_S),Linux)
  CFLAGS += -I/usr/include -I/usr/include/minizip
  LDFLAGS += -L/usr/lib -lminizip -lz
else ifeq ($(OS),Windows_NT)
  CFLAGS += -I"C:/msys64/mingw64/include" -I"C:/msys64/mingw64/include/minizip"
  LDFLAGS += -L"C:/msys64/mingw64/lib" -lminizip -lz
endif

# -----------------------------------------------------------------------------
# Build rules
# -----------------------------------------------------------------------------
all: $(TARGET)

$(TARGET): $(OBJ_FILES)
	@echo "Linking $@ ..."
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@echo "Compiling $< ..."
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR) $(TARGET)

test: $(TARGET)
	@echo "Running $(TARGET) with EPUB: $(TEST_FILE)"
	./$(TARGET) $(TEST_FILE)

.PHONY: all clean test
