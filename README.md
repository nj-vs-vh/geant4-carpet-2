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

2. Modify `configure.sh` for your system, place correct `COAST_DIR` and `G4INSTALL` in there. Then run it with

```bash
. configure.sh
```

# TODO:

* интегрировать `corsika2geant` в приложение и организовать чтение напрямую из DAT файла CORSIKA
* ...
