INCLUDE = -I${COAST_DIR}/include/ -I..
LIBS = -L ${COAST_DIR}/lib/ -lCorsikaFileIO -lCorsikaIntern -L .. -lcorsika2geant

build_dump_to_text:
	g++ ${INCLUDE} dump_to_text.cpp ${LIBS} -o dump_to_text

build_n_e_mu_stats:
	g++ ${INCLUDE} Ne_Nmu_counts.cpp ${LIBS} -o Ne_Nmu_counts
