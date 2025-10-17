#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "utils/dirs.h"

void print_help(const char *prog_name) {
  printf("epubless — a terminal EPUB reader\n\n");
  printf("Usage:\n");
  printf("  %s <file.epub>      Open an EPUB file\n", prog_name);
  printf("  %s -h | --help      Show this help message\n\n", prog_name);
  printf("Directories:\n");
  printf("  ~/.cache/epubless/books/       Extracted EPUB content\n");
  printf("  ~/.cache/epubless/tmp/         Temporary files\n");
  printf("  ~/.cache/epubless/bookmarks/   User bookmarks\n\n");
  printf("Example:\n");
  printf("  %s ~/Documents/book.epub\n", prog_name);
}

char* extract_filename(char* path) {
    // Find the last occurrence of '/' or '\'
    char* last_slash = strrchr(path, '/');
    char* last_backslash = strrchr(path, '\\');

    // Determine which separator is the last one
    char* separator = NULL;
    if (last_slash > last_backslash) { // Handles cases where both exist, like "C:/folder\file.txt"
        separator = last_slash;
    } else {
        separator = last_backslash;
    }

    // If no separator is found, the entire path is the filename
    if (separator == NULL) {
        return path;
    } else {
        // Return the substring after the last separator
        return separator + 1;
    }
}

int main(int argc, char **argv) {
  if (argc != 2) {
    fprintf(stderr, "Usage: %s <file.epub> or %s --help\n", argv[0], argv[0]);
    return EXIT_FAILURE;
  }

  if (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0) {
    print_help(argv[0]);
    return EXIT_SUCCESS;
  }

  char *book_name = extract_filename(argv[1]);

  if (create_cache_structure() != 0) {
    fprintf(stderr, "Failed to initialize cache structure.\n");
    return EXIT_FAILURE;
  }

  if (create_cache_for_book(book_name) != 0) {
    fprintf(stderr, "Failed to initialize cache structure for book: %s\n", book_name);
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
