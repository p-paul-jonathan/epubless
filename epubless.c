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

int main(int argc, char **argv) {
  if (argc != 2) {
    fprintf(stderr, "Usage: %s <file.epub> or %s --help\n", argv[0], argv[0]);
    return EXIT_FAILURE;
  }

  if (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0) {
    print_help(argv[0]);
    return EXIT_SUCCESS;
  }

  if (create_cache_structure() != 0) {
    fprintf(stderr, "Failed to create cache for program: %s", argv[0]);
    return EXIT_FAILURE;
  }

  char *book_name = extract_filename_without_extenstion(argv[1]);
  if (create_cache_for_book(book_name) != 0) {
    fprintf(stderr, "Failed to create cache for book: %s", book_name);
    return EXIT_FAILURE;
  }
  free(book_name);

  return EXIT_SUCCESS;
}
