#include <stdio.h>
#include <stdlib.h>

#if defined(HAS_STDBOOL) && !defined(bool)
#include <stdbool.h>
#else
#include "odbc_ini_gen_stdbool.h"
#endif /* defined(HAS_STDBOOL) && !defined(bool) */

#include "odbc_ini_gen_config.h"
#include "odbc_ini_gen_cli.h"

int main(int argc, char *argv[]) {
  unsigned drivers_added = 0;
  const char *search_paths[] = {
#if defined(__APPLE__) && defined(__MACH__) && __APPLE__ && __MACH__
      "/usr/local/lib"
#elif defined(__CYGWIN__)
    "/lib"
#else
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
#endif
  };
  size_t n_search_paths = sizeof search_paths / sizeof search_paths[0];
  struct DocoptArgs _stack_args; // allocate to stack
  struct DocoptArgs *args = &_stack_args;
  int return_code = docopt(args, argc, argv, /* help */ true, /* version */ ODBC_INI_GEN_VERSION);
  // assert(args != NULL);
  if (return_code != EXIT_SUCCESS) return return_code;

  if ((sizeof search_paths / sizeof search_paths[0]) == 0)
    fputs("Nowhere to search for ODBC drivers", stderr);
  else if (args->infer_all) {
    size_t i;
    for(i=0; i<n_search_paths; i++) {
      printf("search_paths[%02ld] = \"%s\"\n", i, search_paths[i]);
    }
    puts("TODO: implement --infer-all");
  }

  puts("Hello");
  return drivers_added > 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}
