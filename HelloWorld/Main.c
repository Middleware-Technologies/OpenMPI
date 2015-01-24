/*
* Compiling:
*  mpicc -o OUT FILE
* Running in multithreading
*  mpirun -np NUM_THREAD OUT
* Running in cluster-mode
*  mpirun -host LIST_HOSTS OUT
*/
#include "mpi.h"
#include <stdio.h>

int main(int argc,char *argv[])
{
	int numTot, myNum;
	char processorName[10];
	int size;
	
	MPI_Init(&argc, &argv);  //START PARALLEL
	
	//GET NUMBER OF THREADS
	MPI_Comm_size(MPI_COMM_WORLD, &numTot);
	//GET MY NUM
	MPI_Comm_rank(MPI_COMM_WORLD, &myNum);
	//GET PROCESS' NAME
	MPI_Get_processor_name(processorName,&size);

	//DO STUFF
	printf("I'M %d OF %d ON %s\n",myNum,numTot,processorName);

	MPI_Finalize();		//END PARALLEL

	return 0;
}
