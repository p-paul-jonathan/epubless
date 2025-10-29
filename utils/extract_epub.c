#include <errno.h>
#include <minizip/unzip.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <zlib.h>

#include "constants.h"
#include "dirs.h"
#include "extract_epub.h"

// ---- Static Helpers ----

// Extract a single file safely from the current ZIP entry
static int extract_current_file(unzFile zip, const char *dest_dir) {
  if (!zip || !dest_dir) {
    fprintf(stderr, "extract_current_file: invalid arguments\n");
    return -1;
  }

  char filename_inzip[ZIP_FILENAME_MAX_LEN];
  unz_file_info file_info;

  if (unzGetCurrentFileInfo(zip, &file_info, filename_inzip,
                            sizeof(filename_inzip), NULL, 0, NULL,
                            0) != UNZ_OK) {
    fprintf(stderr, "extract_current_file: failed to get file info\n");
    return -1;
  }

  size_t len = strlen(dest_dir) + strlen(filename_inzip) + 2;
  char *full_path = malloc(len);
  if (!full_path) {
    fprintf(stderr, "extract_current_file: malloc error\n");
    return -1;
  }

  snprintf(full_path, len, "%s/%s", dest_dir, filename_inzip);

  // If directory, ensure it exists
  if (filename_inzip[strlen(filename_inzip) - 1] == '/') {
    create_dir_if_missing(full_path);
    free(full_path);
    return 0;
  }

  // Ensure parent directories exist
  if (create_parent_dirs(full_path) != 0) {
    fprintf(stderr,
            "extract_current_file: failed to create parent dirs for %s\n",
            full_path);
    free(full_path);
    return -1;
  }

  if (unzOpenCurrentFile(zip) != UNZ_OK) {
    fprintf(stderr, "extract_current_file: cannot open zip entry\n");
    free(full_path);
    return -1;
  }

  FILE *out = fopen(full_path, "wb");
  if (!out) {
    perror("fopen");
    unzCloseCurrentFile(zip);
    free(full_path);
    return -1;
  }

  char *buffer = malloc(ZIP_BUFFER_SIZE);
  if (!buffer) {
    fprintf(stderr, "extract_current_file: malloc error (buffer)\n");
    fclose(out);
    unzCloseCurrentFile(zip);
    free(full_path);
    return -1;
  }

  int bytes;
  while ((bytes = unzReadCurrentFile(zip, buffer, ZIP_BUFFER_SIZE)) > 0) {
    if (fwrite(buffer, 1, bytes, out) != (size_t)bytes) {
      perror("fwrite");
      bytes = -1;
      break;
    }
  }

  free(buffer);
  fclose(out);
  unzCloseCurrentFile(zip);
  free(full_path);

  if (bytes < 0) {
    fprintf(stderr, "extract_current_file: error reading from zip\n");
    return -1;
  }

  return 0;
}

// ---- Public Functions ----

int extract_zip(const char *zip_path, const char *dest_dir) {
  if (!zip_path || !dest_dir) {
    fprintf(stderr, "extract_zip: invalid arguments\n");
    return -1;
  }

  if (create_dir_if_missing(dest_dir) != 0) {
    fprintf(stderr, "extract_zip: cannot create output dir: %s\n", dest_dir);
    return -1;
  }

  unzFile zip = unzOpen(zip_path);
  if (!zip) {
    fprintf(stderr, "extract_zip: cannot open zip: %s\n", zip_path);
    return -1;
  }

  if (unzGoToFirstFile(zip) != UNZ_OK) {
    fprintf(stderr, "extract_zip: zip appears empty: %s\n", zip_path);
    unzClose(zip);
    return -1;
  }

  do {
    if (extract_current_file(zip, dest_dir) != 0)
      fprintf(stderr, "extract_zip: warning — failed to extract a file.\n");
  } while (unzGoToNextFile(zip) == UNZ_OK);

  unzClose(zip);
  return 0;
}
