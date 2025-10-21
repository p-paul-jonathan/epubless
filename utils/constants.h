#ifndef CONSTANTS_H
#define CONSTANTS_H

// Path & buffer sizes
#define PATH_MAX_LEN 512
#define CMD_MAX_LEN 1024

// Cache subdirectories
#define CACHE_DIR_SUBPATH ".cache/epubless"
#define BOOKS_SUBPATH "books"
#define TMP_SUBPATH "tmp"
#define BOOKMARKS_SUBPATH "bookmarks"

#ifdef _WIN32
  #define PATH_SEPARATOR "\\"
#else
  #define PATH_SEPARATOR "/"
#endif

#endif // CONSTANTS_H
