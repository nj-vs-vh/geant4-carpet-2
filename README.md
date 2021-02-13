## Installation

1. Install COAST
   1. [Download](https://web.ikp.kit.edu/rulrich/coast-files/coast-v4r5.tar.gz) and unpack tar archive
  
   2. Create directory for COAST libraries and headers, store its path in `COAST_DIR`, 

   ```bash
   mkdir /my/coast/build
   export COAST_DIR=/my/coast/build
   ```

   3. Run following commands from COAST dir
   ```bash
   ./configure
   make
   make check
   make install
   ```

2. Create `configure.sh` from example, make sure to place correct `COAST_DIR` and `G4INSTALL` in there. Then run it

```bash
cp configure.sh.example configure.sh
# modify configure.sh here, it will not show in git
. configure.sh
```

3. Run CMake and build with

```bash
. rebuild.sh
```

4. Run application from build directory

```bash
cd build
./Carpet2 /path/to/corsika/file
```
