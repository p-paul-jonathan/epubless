#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#include "constants.h"
#include "dynamic_array_string.h"
#include "os_helpers.h"
#include "string_helpers.h"
// -----------------------------------------------------------------------------
// Helpers
// -----------------------------------------------------------------------------

// Create directory if it does not exist
int create_dir_if_missing(const char *path) {
  struct stat st = {0};
  if (stat(path, &st) == -1) {
    if (mkdir(path, 0755) != 0) {
      perror("mkdir");
      return 1;
    }
  }
  return 0;
}

// Portable parent dir extractor (no dirname)
int create_parent_dirs(const char *filepath) {
  char *copy = strdup(filepath);
  if (!copy)
    return -1;

  char *last_slash = strrchr(copy, '/');
#ifdef _WIN32
  char *last_backslash = strrchr(copy, '\\');
  if (!last_slash || (last_backslash && last_backslash > last_slash))
    last_slash = last_backslash;
#endif

  if (last_slash) {
    *last_slash = '\0';
    create_dir_if_missing(copy);
  }

  free(copy);
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
  const char *home = getenv("HOME");
  static char cache_dir_abs_path[PATH_MAX_LEN];
  snprintf(cache_dir_abs_path, sizeof(cache_dir_abs_path), "%s/%s", home,
           CACHE_DIR_SUBPATH);

  if (create_dir_if_missing(cache_dir_abs_path) ||
      create_dir_if_missing(get_base_dir(BOOKS_SUBPATH)) ||
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

char *extract_filename(char *path) {
  if (!path || *path == '\0')
    return strdup("");

  // Remove any trailing path separators
  size_t len = strlen(path);
  while (len > 0 && (path[len - 1] == '/' || path[len - 1] == '\\')) {
    path[len - 1] = '\0';
    len--;
  }

  if (len == 0)
    return strdup("");

  // Split path and take the last component
  struct DynamicArrayString filename_arr = split_string(path, PATH_SEPARATOR);
  char *filename_with_extension = NULL;

  if (filename_arr.len > 0) {
    char *last = dynamic_array_string_get_index(&filename_arr, -1);
    filename_with_extension = strdup(last ? last : "");
  } else {
    filename_with_extension = strdup("");
  }

  dynamic_array_string_free(&filename_arr);
  return filename_with_extension;
}

char *extract_filename_without_extension(char *path) {
  char *filename_with_extension = extract_filename(path);
  if (!filename_with_extension)
    return NULL;

  // Split by '.' to separate extension parts
  struct DynamicArrayString dot_split_arr =
      split_string(filename_with_extension, ".");
  free(filename_with_extension);

  if (dot_split_arr.len == 0) {
    dynamic_array_string_free(&dot_split_arr);
    return strdup("");
  }

  // Handle hidden files correctly (.hidden should remain)
  if (dot_split_arr.len > 1 && filename_with_extension[0] != '.') {
    dynamic_array_string_pop(&dot_split_arr);
  }

  char *filename = join_string(&dot_split_arr, ".");
  dynamic_array_string_free(&dot_split_arr);

  return filename;
}
