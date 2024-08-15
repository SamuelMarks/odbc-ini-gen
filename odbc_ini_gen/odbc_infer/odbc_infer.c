#include <string.h>

#include "odbc_infer.h"
#include "odbc_ini_types.h"

enum OdbcInferences OdbcInferences_from_str(const char *s) {
  if (strcmp(s, "libsqlite3odbc.so") == 0)
    /* TODO: libsqlite3odbc-0.9998.so? */
    return SQLITE;
  else if (strcmp(s, "libtdsodbc.so") == 0)
    return TDS;
  else if (strcmp(s, "libw1odbc.so") == 0)
    return W1RETAP;
  else if (strcmp(s, "psqlodbca.so") == 0)
    return POSTGRESQL_ANSI;
  else if (strcmp(s, "psqlodbcw.so") == 0)
    return POSTGRESQL_UNICODE;
  else
    return UNKNOWN;
}

const char *OdbcInferences_to_str(enum OdbcInferences odbcInferences) {
  switch (odbcInferences) {
  case POSTGRESQL_ANSI:
    return "psqlodbca.so";
  case POSTGRESQL_UNICODE:
    return "psqlodbcw.so";
  case SQLITE:
    return "libsqlite3odbc.so";
  case TDS:
    return "libtdsodbc.so";
  case UNKNOWN:
  default:
    return "UNKNOWN";
  }
}

struct PairOfc_str
OdbcInferences_to_name_description(enum OdbcInferences odbcInferences) {
  switch (odbcInferences) {
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
  case SQLITE:
    return (struct PairOfc_str){"SQLite", "SQLite ODBC Driver"};
  case TDS:
    return (struct PairOfc_str){
        "FreeTDS", "Driver for connecting to MS SQL and Sybase SQL servers"};
  case W1RETAP:
    return (struct PairOfc_str){"1-Wire",
                                "Data logger for 1-Wire weather sensors"};
  case UNKNOWN:
  default:
    return (struct PairOfc_str){NULL, NULL};
  }
}
