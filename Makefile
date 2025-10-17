CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -g

OBJ_DIR = build
TARGET = epubless
TEST_FILE = test/narnia.epub

SRC_FILES = epubless.c utils/dirs.c
OBJ_FILES = $(SRC_FILES:%.c=$(OBJ_DIR)/%.o)

all: $(TARGET)

$(TARGET): $(OBJ_FILES)
	@echo "Linking $@ ..."
	$(CC) $(CFLAGS) -o $@ $^

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@echo "Compiling $< ..."
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR) $(TARGET)

test:
	@echo "Running $(TARGET) with EPUB: $(TEST_FILE)"
	./$(TARGET) $(TEST_FILE)

.PHONY: all clean test
