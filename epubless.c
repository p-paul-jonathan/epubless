#include "utils/extract_epub.h"
#include "utils/dirs.h"

static void print_help(const char *prog_name) {
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
  // TODO: Make no args open previously opened books
  if (argc != 2) {
    fprintf(stderr, "Usage: %s <file.epub> or %s --help\n", argv[0], argv[0]);
    return EXIT_FAILURE;
  }

  if (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0) {
    print_help(argv[0]);
    return EXIT_SUCCESS;
  }

  if (create_cache_structure() != 0) {
    fprintf(stderr, "Failed to create cache for program: %s\n", argv[0]);
    return EXIT_FAILURE;
  }

  char *book_name = extract_filename_without_extension(argv[1]);
  if (!book_name) {
    fprintf(stderr, "Failed to extract book name from: %s\n", argv[1]);
    return EXIT_FAILURE;
  }

  if (create_cache_for_book(book_name) != 0) {
    fprintf(stderr, "Failed to create cache for book: %s\n", book_name);
    free(book_name);
    return EXIT_FAILURE;
  }

  if (extract_zip(argv[1], get_books_dir_for_book(book_name)) != 0) {
    fprintf(stderr, "Failed to extract EPUB: %s\n", argv[1]);
    free(book_name);
    return EXIT_FAILURE;
  }

  printf("Successfully extracted '%s' into cache.\n", book_name);
  free(book_name);
  return EXIT_SUCCESS;
}
