INCLUDE = -I${COAST_DIR}/include/
LIBS = -L ${COAST_DIR}/lib/ -lCorsikaFileIO -lCorsikaIntern

standalone:
	g++ ${INCLUDE} corsika2geant.cpp ${LIBS} -o corsika2geant

lib:
	g++ -fPIC -shared ${INCLUDE} corsika2geant.cpp ${LIBS} -o libcorsika2geant.so
