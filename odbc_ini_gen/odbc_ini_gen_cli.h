#ifndef DOCOPT_ODBC_INI_GEN_CLI_H
#define DOCOPT_ODBC_INI_GEN_CLI_H

#include "odbc_ini_gen_config.h"

#include <stddef.h>

#if defined(__STDC__) && defined(__STDC_VERSION__) &&                          \
    __STDC_VERSION__ >= 199901L

#include <stdbool.h>

#elif !defined(_STDBOOL_H)
#define _STDBOOL_H

#include <stdlib.h>

#ifdef true
#undef true
#endif
#ifdef false
#undef false
#endif
#ifdef bool
#undef bool
#endif

#define true 1
#define false (!true)
typedef size_t bool;

#endif

#if defined(_AIX)

#include <sys/limits.h>

#elif defined(__FreeBSD__) || defined(__NetBSD__)
|| defined(__OpenBSD__) || defined(__bsdi__) || defined(__DragonFly__) ||
    defined(macintosh) || defined(__APPLE__) ||
    defined(__APPLE_CC__)

#include <sys/syslimits.h>

#elif defined(__HAIKU__)

#include <system/user_runtime.h>

#elif defined(__linux__) || defined(linux) || defined(__linux)

#include <linux/version.h>

#if LINUX_VERSION_CODE <= KERNEL_VERSION(2, 6, 22)

#include <linux/limits.h>

#else

#define ARG_MAX 131072 /* # bytes of args + environ for exec() */
/* it's no longer defined, see this example and more at
 * https://unix.stackexchange.com/q/120642 */

#endif

#elif (defined(__FreeBSD__) || defined(__NetBSD__) || defined(__OpenBSD__) ||  \
       defined(__bsdi__) || defined(__DragonFly__) || defined(macintosh) ||    \
       defined(__APPLE__) || defined(__APPLE_CC__))

#include <sys/param.h>

#if defined(__APPLE__) || defined(__APPLE_CC__)
/* ARG_MAX gives a segfault on macOS when used for array size below */
#undef ARG_MAX
#undef NCARGS
#endif

#else

#include <limits.h>

#endif

#ifndef ARG_MAX
#ifdef NCARGS
#define ARG_MAX NCARGS
#else
#define ARG_MAX 131072
#endif
#endif

struct DocoptArgs {

  /* commands */
  size_t odbc_ini_gen;
  /* options without arguments */
  size_t help;
  size_t infer_all;
  size_t version;
  /* options with arguments */
  char *desc;
  char *driver;
  char *name;
  char *output;
  char *search;
  /* special */
  const char *usage_pattern;
  const char *help_message[28];
};

int docopt(struct DocoptArgs *, int, char *[], bool, const char *);

#endif
