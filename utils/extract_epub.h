#ifndef EXTRACT_EPUB_H
#define EXTRACT_EPUB_H

// Extracts all files from a ZIP archive into the given destination directory.
// Returns 0 on success, -1 on failure.
int extract_zip(const char *zip_path, const char *dest_dir);

#endif // EXTRACT_EPUB_H
