#include "base_struct.hpp"
#include "mpi_example.hpp"

#include "source.hpp"
#include "worker.hpp"
#include "run.hpp"
#include <iostream>

int main ( int argc, char *argv[] ){

    MPIIO 	hIO(argc, argv);
	int 	workerNum = hIO.getSzProc()-1;

	Option::parse(argc, argv);

	if(hIO.isMaster()){
		Option::print();
	}
	
	run_exp(Option::inFileName, Option::outPath, hIO, workerNum, Option::method, Option::budget, Option::trial);
	
	hIO.cleanup();

}
