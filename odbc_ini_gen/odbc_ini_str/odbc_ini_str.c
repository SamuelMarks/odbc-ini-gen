#include "odbc_ini_str.h"
#include <string.h>

bool ends_with(const char *const s, const char *const suffix) {
  /* https://stackoverflow.com/a/63921254
   * could go extreme like http://0x80.pl/articles/simd-strfind.html
   * */
  const size_t str_len = strlen(s);
  const size_t suffix_len = strlen(suffix);

  return (str_len >= suffix_len) &&
         (!memcmp(s + str_len - suffix_len, suffix, suffix_len));
}
