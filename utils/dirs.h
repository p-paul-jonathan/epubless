#ifndef DIRS_H
#define DIRS_H

#ifdef __cplusplus
extern "C" {
#endif

// Create base cache directories: ~/.cache/epubless/{books,tmp,bookmarks}
int create_cache_structure(void);

// Create per-book directories inside the cache
int create_cache_for_book(const char *book_name);

// Get base cache directories
char *get_books_dir(void);
char *get_tmp_dir(void);
char *get_bookmarks_dir(void);

// Get per-book directories
char *get_books_dir_for_book(const char *book_name);
char *get_tmp_dir_for_book(const char *book_name);
char *get_bookmarks_dir_for_book(const char *book_name);

#ifdef __cplusplus
}
#endif

#endif // DIRS_H
