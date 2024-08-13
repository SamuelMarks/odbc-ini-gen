#include <string.h>

#include "odbc_infer.h"
#include "odbc_ini_fs.h"
#include "odbc_ini_types.h"

enum OdbcInferences OdbcInferences_from_str(const char *s) {
  if (strcmp(s, "libsqlite3odbc.so") == 0)
      return SQLITE;
  else if (strcmp(s, "psqlodbca.so") == 0)
    return POSTGRESQL_ANSI;
  else if (strcmp(s, "psqlodbcw.so") == 0)
    return POSTGRESQL_UNICODE;
  /* TODO: libsqlite3odbc-0.9998.so? */
  else
    return UNKNOWN;
}

const char *OdbcInferences_to_str(enum OdbcInferences odbcInferences) {
  switch (odbcInferences) {
  case SQLITE:
    return "libsqlite3odbc.so";
  case POSTGRESQL_ANSI:
    return "psqlodbca.so";
  case POSTGRESQL_UNICODE:
    return "psqlodbcw.so";
  case UNKNOWN:
  default:
    return "UNKNOWN";
  }
}

struct PairOfc_str
OdbcInferences_to_name_description(enum OdbcInferences odbcInferences) {
  switch (odbcInferences) {
  case SQLITE:
    return (struct PairOfc_str){
        "SQLite",
        "SQLite ODBC Driver"};
  case POSTGRESQL_ANSI:
    return (struct PairOfc_str){
        "PostgreSQL UNICODE",
        "Unicode enabled driver that will work well with modern versions of "
        "applications such as Microsoft Access, with character from a huge "
        "range of languages. You should use this driver with PostgreSQL "
        "databases encoded as 'UNICODE' (more precisely known as 'UTF-8' in "
        "PostgreSQL)."};
  case POSTGRESQL_UNICODE:
    return (struct PairOfc_str){
        "PostgreSQL ANSI",
        "ANSI driver which is also able to handle some multibyte character "
        "sets such as EUC_JP, BIG5 and Shift-JIS. This driver should also be "
        "used with databases encoded using any of the LATIN charactersets"};
  case UNKNOWN:
  default:
    return (struct PairOfc_str){NULL, NULL};
  }
}
