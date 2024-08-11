#include <string.h>

#include "odbc_infer.h"

enum OdbcInferences {
  POSTGRESQL,
  UNKNOWN
};

enum OdbcInferences OdbcInferences_from_str(const char *s) {
  if (strcmp(s, "PostgreSQL") == 0) return POSTGRESQL;
  else return UNKNOWN;
}

const char * OdbcInferences(enum OdbcInferences odbcInferences) {
  switch (odbcInferences) {
  case POSTGRESQL:
    return "PostgreSQL";
  case UNKNOWN:
  default:
    return "UNKNOWN";
  }
}
