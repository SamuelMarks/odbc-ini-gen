#include "odbc_ini_fs.h"

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
