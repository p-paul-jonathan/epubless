#include "dirs.h"
#include "constants.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

// -----------------------------------------------------------------------------
// Helpers
// -----------------------------------------------------------------------------

// Create directory if it does not exist
static int create_dir_if_missing(const char *path) {
  struct stat st = {0};
  if (stat(path, &st) == -1) {
    if (mkdir(path, 0755) != 0) {
      perror("mkdir");
      return 1;
    }
  }
  return 0;
}

// Generic: get path to a base subdirectory (books, tmp, bookmarks)
static char *get_base_dir(const char *subdir) {
  const char *home = getenv("HOME");
  if (!home)
    return NULL;

  static char path[PATH_MAX_LEN];
  snprintf(path, sizeof(path), "%s/%s/%s", home, CACHE_DIR_SUBPATH, subdir);
  return path;
}

// Generic: get path to a specific book inside a base subdirectory
static char *get_dir_for_book(const char *subdir, const char *book_name) {
  const char *base = get_base_dir(subdir);
  if (!base)
    return NULL;

  static char path[PATH_MAX_LEN];
  snprintf(path, sizeof(path), "%s/%s", base, book_name);
  return path;
}

// -----------------------------------------------------------------------------
// Public functions
// -----------------------------------------------------------------------------

// Create base cache directories: books/, tmp/, bookmarks/
int create_cache_structure(void) {
  if (create_dir_if_missing(get_base_dir(BOOKS_SUBPATH)) ||
      create_dir_if_missing(get_base_dir(TMP_SUBPATH)) ||
      create_dir_if_missing(get_base_dir(BOOKMARKS_SUBPATH))) {
    return 1;
  }
  return 0;
}

// Create directories for a specific book
int create_cache_for_book(const char *book_name) {
  if (!book_name)
    return 1;

  if (create_dir_if_missing(get_dir_for_book(BOOKS_SUBPATH, book_name)) ||
      create_dir_if_missing(get_dir_for_book(TMP_SUBPATH, book_name)) ||
      create_dir_if_missing(get_dir_for_book(BOOKMARKS_SUBPATH, book_name))) {
    return 1;
  }
  return 0;
}

// Get base directories
char *get_books_dir(void) { return get_base_dir(BOOKS_SUBPATH); }
char *get_tmp_dir(void) { return get_base_dir(TMP_SUBPATH); }
char *get_bookmarks_dir(void) { return get_base_dir(BOOKMARKS_SUBPATH); }

// Get per-book directories
char *get_books_dir_for_book(const char *book_name) {
  return get_dir_for_book(BOOKS_SUBPATH, book_name);
}
char *get_tmp_dir_for_book(const char *book_name) {
  return get_dir_for_book(TMP_SUBPATH, book_name);
}
char *get_bookmarks_dir_for_book(const char *book_name) {
  return get_dir_for_book(BOOKMARKS_SUBPATH, book_name);
}
