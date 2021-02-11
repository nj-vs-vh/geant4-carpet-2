# corsika2geant

Simple wrapper around COAST tool to extract particle data from CORSIKA DAT files

## Prerequisites

Install COAST:

1. [Download](https://web.ikp.kit.edu/rulrich/coast-files/coast-v4r5.tar.gz) and unpack tar archive
  
2. Create directory for COAST libraries and headers, store its path in `COAST_DIR`, 

```bash
mkdir /my/coast/build
export COAST_DIR=/my/coast/build
```

3. Run following commands from inside unpacked archive
```bash
./configure
make
make check
make install
```

`COAST_DIR` environment variable must be set during all later buildings, it makes sense to place its definition somwhere in an activation script.

To run `corsika2geant` you would also need to modify `LD_LIBRARY_PATH` as follows (otherwise, dynamic linker doesn't know where to find COAST libs) :

```bash
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$COAST_DIR/lib
```

There are two modes of operation: standalone and as a library used from other code

## Stadalone

`corsika2geant` may be used just to read data and print formatted output to stdout

### build

```bash
make standalone
```

### run

```bash
# print only shower metadata
./corsika2geant <file path>
# print every particle params
./corsika2geant -v <file path>
```

## Shared library

### build

```bash
make lib
```

In addition to previous `LD_LIBRARY_PATH` modification, to use `corsika2geant` in your code you should also set

```bash
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$(pwd)
```

### usage

See example in `lib_usage`
