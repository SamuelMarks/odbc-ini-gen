#ifndef ODBC_INI_GEN_ODBC_INI_TYPES_H
#define ODBC_INI_GEN_ODBC_INI_TYPES_H

struct OdbcIniBasicRecord {
  char * filepath;
  const char * name;
  const char *const description;
};

struct PairOfc_str {
  const char *first;
  const char *second;
};

#endif /* ODBC_INI_GEN_ODBC_INI_TYPES_H */
