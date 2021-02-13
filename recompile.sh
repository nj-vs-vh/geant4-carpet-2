mkdir -p build
cmake -DCMAKE_PREFIX_PATH=$G4INSTALL -S . -B build/
cd build
make
