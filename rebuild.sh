mkdir -p build
cmake -DCMAKE_PREFIX_PATH=$G4INSTALL -B build/
cd build
make
cd ..
