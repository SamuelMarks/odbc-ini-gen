#include <stdio.h>
#include <stdlib.h>

#if defined(HAS_STDBOOL) && !defined(bool)
#include <stdbool.h>
#else
#include "odbc_ini_gen_stdbool.h"
#endif /* defined(HAS_STDBOOL) && !defined(bool) */

#include <errno.h>
#include <c89stringutils_string_extras.h>

#include "odbc_infer.h"
#include "odbc_ini_fs.h"
#include "odbc_ini_gen_cli.h"
#include "odbc_ini_gen_config.h"

void run_on_each_file(char **buf,
                      const char *name, const char *filepath) {
  enum OdbcInferences odbc_inference = OdbcInferences_from_str(name);
  struct PairOfc_str name_description = OdbcInferences_to_name_description(odbc_inference);

  jasprintf(buf,
            "[%s]\n"
            "Description     = %s\n"
            "Driver          = %s\n"
            "FileUsage       = 1\n\n",
            name_description.first, name_description.second,
            filepath);
}

int main(int argc, char *argv[]) {
  const char *search_paths[] = {
#if defined(__APPLE__) && defined(__MACH__) && __APPLE__ && __MACH__
      "/usr/local/lib"
#elif defined(__CYGWIN__)
      "/lib"
#else
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
  int return_code = docopt(args, argc, argv, /* help */ true,
                           /* version */ ODBC_INI_GEN_VERSION);
  char *buf = NULL;
  // assert(args != NULL);
  if (return_code != EXIT_SUCCESS)
    return return_code;

  struct closure_store_char_ptr_on_cstr_cstr_to_void func_with_data = {
      run_on_each_file, buf
  };

  if ((sizeof search_paths / sizeof search_paths[0]) == 0 &&
      args->search == NULL)
    fputs("Nowhere to search for ODBC drivers", stderr);
  else if (args->infer_all) {
    size_t i;
    for (i = 0; i < n_search_paths; i++)
      foreach_regular_file_entry(search_paths[i], &func_with_data);
  }
  if (func_with_data.buf == NULL) {
    fputs("Nothing found", stderr);
    return EXIT_FAILURE;
  }

  if (args->output == NULL)
    puts(func_with_data.buf);
  else {
    FILE *fd = fopen(args->output, "wt");
    ssize_t bytes_written;
    if (fd == NULL) {
      fprintf(stderr, "error using output file \"%s\"", args->output);
      return ENOENT;
    }
    bytes_written = fputs(func_with_data.buf, fd);
    fclose(fd);
    if (bytes_written < 1) {
      fputs("Did not write anything to file", stderr);
      return EXIT_FAILURE;
    }
  }

  free(func_with_data.buf);

  return EXIT_SUCCESS;
}
