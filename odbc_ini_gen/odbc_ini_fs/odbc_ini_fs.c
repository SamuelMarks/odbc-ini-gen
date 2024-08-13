#include <c89stringutils_string_extras.h>
#include <dirent.h>

#include "odbc_ini_fs.h"

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
#define PATH_SEP "\\"
#else
#define PATH_SEP "/"
#endif

bool is_directory(const char *const path) {
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
  const DWORD dwAttrib = GetFileAttributes(path);

  return (dwAttrib != INVALID_FILE_ATTRIBUTES &&
          (dwAttrib & FILE_ATTRIBUTE_DIRECTORY));
#else
  struct stat statbuf;
  if (stat(path, &statbuf) != 0)
    return false;
  return S_ISDIR(statbuf.st_mode);
#endif /* defined(WIN32) || defined(_WIN32) || defined(__WIN32__) ||           \
          defined(__NT__) */
}

bool is_file(const char *const path) {
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
  const DWORD dwAttrib = GetFileAttributes(path);

  return dwAttrib != INVALID_FILE_ATTRIBUTES && !is_directory(path);
#else
  struct stat statbuf;
  if (stat(path, &statbuf) != 0)
    return false;
  return S_ISREG(statbuf.st_mode);
#endif /* defined(WIN32) || defined(_WIN32) || defined(__WIN32__) ||           \
          defined(__NT__) */
}

int foreach_regular_file_entry(
    const char *const directory,
    struct closure_store_char_ptr_on_cstr_cstr_to_void *f
    /*void (*f)(const char *const)*/) {
  struct dirent *dir;
  DIR *d = opendir(directory);
  if (d) {
    while ((dir = readdir(d)) != NULL) {
      if (dir->d_type == DT_REG) {
        char *filepath;
        asprintf(&filepath, "%s" PATH_SEP "%s", directory, dir->d_name);
        f->func(&f->buf, dir->d_name, filepath);
        free(filepath);
      }
    }
    closedir(d);
  } else {
    return 1; /* check errno */
  }
  return 0;
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
#error                                                                         \
    "TODO: learn.microsoft.com/en-us/windows/win32/fileio/listing-the-files-in-a-directory"
  return 1;
#endif
}
