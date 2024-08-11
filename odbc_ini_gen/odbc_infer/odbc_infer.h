#ifndef ODBC_INI_GEN_ODBC_INFER_H
#define ODBC_INI_GEN_ODBC_INFER_H

#if defined(HAS_STDBOOL) && !defined(bool)
#include <stdbool.h>
#else
#include "odbc_ini_gen_stdbool.h"
#endif /* defined(HAS_STDBOOL) && !defined(bool) */

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)

#include <Fileapi.h>
#include <assert.h>
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

#include "odbc_ini_gen_config.h"

enum OdbcInferences;

const char* OdbcInferences_to_str(enum OdbcInferences);
enum OdbcInferences OdbcInferences_from_str(const char*);

#endif /* !ODBC_INI_GEN_ODBC_INFER_H */
