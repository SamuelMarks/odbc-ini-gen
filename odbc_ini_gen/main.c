#include <stdio.h>
#include <stdlib.h>

#if defined(HAS_STDBOOL) && !defined(bool)
#include <stdbool.h>
#else
#include "odbc_ini_gen_stdbool.h"
#endif /* defined(HAS_STDBOOL) && !defined(bool) */

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)

#include <Fileapi.h>
#include <io.h>
#include <wchar.h>

#ifndef strtok_r
#define strtok_r strtok_s
#endif /* ! strtok_r */

#else

#include <sys/stat.h>
#include <unistd.h>

#endif /* defined(WIN32) || defined(_WIN32) || defined(__WIN32__) ||           \
          defined(__NT__) */

bool is_directory(const char *);
bool is_file(const char *);

int main(int argc, char *argv[]) {
  unsigned drivers_added = 0;
  const char *search_paths[] =
#if defined(__APPLE__) && defined(__MACH__) && __APPLE__ && __MACH__
      {
          "/usr/local/lib"
      }
#else
      {
          "/usr/lib/x86_64-linux-gnu/odbc",
          "/usr/lib/x86_64-linux-gnu/odbc",
          "/usr/lib/aarch64-linux-gnu/odbc",
          "/usr/lib/arm-linux-gnueabi/odbc",
          "/usr/lib/arm-linux-gnueabihf/odbc",
          "/usr/lib/i386-linux-gnu/odbc",
          "/usr/lib/mips64el-linux-gnuabi64/odbc",
          "/usr/lib/mipsel-linux-gnu/odbc",
          "/usr/lib/powerpc64le-linux-gnu/odbc",
          "/usr/lib/s390x-linux-gnu/odbc",
          "/usr/lib/x86_64-linux-gnu/odbc"
      }
#endif
      ;
  switch (argc) {
  case 0:
  case 1:

  }
  if ((sizeof search_paths / sizeof search_paths[0]) == 0)
    fputs("Nowhere to search for ODBC drivers", stderr);

  puts("Hello");
  return drivers_added > 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}

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
