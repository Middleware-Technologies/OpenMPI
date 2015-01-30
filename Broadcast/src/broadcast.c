#include "mpi.h"
#include <stdio.h>

//EXAMPLE 1: Thread 0 Send A Message In Broadcast
int main(int argc, char *argv[])
{
	int numtasks, rank;
	int msg=0;

	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	if(rank == 0)
	{
		msg=10;
	}
	printf("Thread %d: msg= %d\n", rank, msg);

	//BCAST(VALUE, COUNT, SENDER, WORLD)
	MPI_Bcast(&msg, 1, MPI_INT, 0, MPI_COMM_WORLD);

	printf("Thread %d: msg= %d\n", rank, msg);

	MPI_Finalize();

	return 0;
}



