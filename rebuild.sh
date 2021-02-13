mkdir -p build
cd build
cmake -DCMAKE_PREFIX_PATH=$G4INSTALL ..
make
cd ..
