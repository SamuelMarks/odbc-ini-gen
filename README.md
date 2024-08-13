odbc-ini-gen
============
[![License](https://img.shields.io/badge/license-Apache--2.0%20OR%20MIT-blue.svg)](https://opensource.org/licenses/Apache-2.0)
[![CI for Linux, Windows, macOS](https://github.com/SamuelMarks/odbc-ini-gen/workflows/CI%20for%20Linux,%20Windows,%20macOS/badge.svg)](https://github.com/SamuelMarks/odbc-ini-gen/actions)
[![CI for FreeBSD](https://api.cirrus-ci.com/github/SamuelMarks/odbc-ini-gen.svg)](https://cirrus-ci.com/github/SamuelMarks/odbc-ini-gen)
[![C89](https://img.shields.io/badge/C-89-blue)](https://en.wikipedia.org/wiki/C89_(C_version))

ODBC dynamic ini builder, like GRUB update-triggers os-probe but for your database drivers.

## Current inferences

| Name       | Detected from                  |
|------------|--------------------------------|
| PostgreSQL | `psqlodbca.so`; `psqlodbcw.so` |
| SQLite     | `libsqliteodbc.so`             |

## `--help`

    odbc-ini-gen: ODBC dynamic ini builder, like GRUB update-triggers os-probe but for your database drivers.
    (by default does `--infer-all` with output to stdout)
    
    Usage:
    odbc-ini-gen...
    odbc-ini-gen --output=<f>...
    odbc-ini-gen --infer-all...
    odbc-ini-gen --infer-all --output=<f>...
    odbc-ini-gen --infer-all --search=<folder>...
    odbc-ini-gen --infer-all --search=<folder> --output=<f>...
    odbc-ini-gen --name=<name> --driver=<lib>...
    odbc-ini-gen --name=<name> --driver=<lib> --output=<f>...
    odbc-ini-gen --name=<name> --driver=<lib> --desc=<desc>...
    odbc-ini-gen --name=<name> --driver=<lib> --desc=<desc> --output=<f>...
    odbc-ini-gen --help
    odbc-ini-gen --version
    
    Options:
    -h --help               Show this screen.
    --version               Show version.
    --infer-all             Find ODBC shared libraries and infer their database names. This is the default.
    --no-infer-all          Doesn't infer anything automatically. This is default when `--name` or `--driver` is provided.
    --name=<name>           Explicitly provided library name
    --desc=<lib>            Explicitly provided description
    --props=<s>             Explicitly additional properties (doesn't validate)
    --driver=<lib>          Explicitly provided shared library||object location (doesn't check existence)
    --search=<folder>       Folder to (non-recursively) search for shared objects within
    -o=<f>, --output=<f>    Output file. If not specified: will use `stdout`. If specified: will overwrite file.


## Build dependencies

- [CMake](https://cmake.org) (3.19 or later)
- C compiler (any that work with CMake, and were released within the last 30 years)

### Build

```bash
mkdir build && cd build
cmake ..
cmake --build .
```

### Docker
```bash
docker build . -t odbc-ini-gen:latest
```

### CLI interface

Generated with `docopt`, use `python -m pip install https://api.github.com/repos/offscale/docopt.c/zipball/pyth
on-3-13#egg=docopt_c` then:
```bash
$ python -m docopt_c '.docopt' -o 'odbc_ini_gen/'
```

## OS/distribution specific notes

### Cygwin
[iODBC](https://www.iodbc.org) is used.

---

## License

Licensed under either of

- Apache License, Version 2.0 ([LICENSE-APACHE](LICENSE-APACHE) or <https://www.apache.org/licenses/LICENSE-2.0>)
- MIT license ([LICENSE-MIT](LICENSE-MIT) or <https://opensource.org/licenses/MIT>)

at your option.

### Contribution

Unless you explicitly state otherwise, any contribution intentionally submitted
for inclusion in the work by you, as defined in the Apache-2.0 license, shall be
dual licensed as above, without any additional terms or conditions.
