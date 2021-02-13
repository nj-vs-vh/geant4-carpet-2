mkdir -p build
cd build
cmake -DCMAKE_PREFIX_PATH=$G4INSTALL ..
# for a debug build use
# cmake -DCMAKE_PREFIX_PATH=$G4INSTALL -DCMAKE_BUILD_TYPE=Debug .. 
make
cd ..
