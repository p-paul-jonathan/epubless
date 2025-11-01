#ifndef OS_HELPERS_H
#define OS_HELPERS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>

#ifdef _WIN32
  #include <direct.h>    // _mkdir, _rmdir
  #include <io.h>        // _access, _unlink
  #include <windows.h>   // Sleep
  #define PATH_SEPARATOR "\\"

  // Windows mkdir only takes one argument (ignore mode)
  #define MKDIR(path, mode) _mkdir(path)
  #define RMDIR(path) _rmdir(path)
  #define UNLINK(path) _unlink(path)
  #define ACCESS(path, mode) _access(path, mode)

  // access() mode flags compatibility
  #ifndef F_OK
    #define F_OK 0  // existence check
  #endif
  #ifndef R_OK
    #define R_OK 4  // read permission
  #endif
  #ifndef W_OK
    #define W_OK 2  // write permission
  #endif

  // Sleep milliseconds
  static inline void sleep_ms(unsigned int ms) {
    Sleep(ms);
  }

  // Get home directory
  static inline const char *get_home_dir(void) {
    const char *home = getenv("USERPROFILE");
    if (!home) home = getenv("HOMEDRIVE");  // fallback
    return home;
  }

  // Join two paths safely
  static inline void join_path(char *dest, size_t size, const char *base, const char *append) {
    snprintf(dest, size, "%s\\%s", base, append);
  }

#else // ---------------------- POSIX / Linux / macOS ----------------------

  #include <unistd.h>
  #define PATH_SEPARATOR "/"

  #define MKDIR(path, mode) mkdir(path, mode)
  #define RMDIR(path) rmdir(path)
  #define UNLINK(path) unlink(path)
  #define ACCESS(path, mode) access(path, mode)

  static inline void sleep_ms(unsigned int ms) {
    nanosleep((const struct timespec[]){{ms / 1000, (ms % 1000) * 1000000L}}, NULL);
  }

  static inline const char *get_home_dir(void) {
    return getenv("HOME");
  }

  static inline void join_path(char *dest, size_t size, const char *base, const char *append) {
    snprintf(dest, size, "%s/%s", base, append);
  }

#endif // _WIN32

// Cross-platform check if a path exists
static inline int path_exists(const char *path) {
  return ACCESS(path, F_OK) == 0;
}

// Cross-platform check if file is readable
static inline int path_readable(const char *path) {
  return ACCESS(path, R_OK) == 0;
}

// Cross-platform check if file is writable
static inline int path_writable(const char *path) {
  return ACCESS(path, W_OK) == 0;
}

#endif // OS_HELPERS_H
