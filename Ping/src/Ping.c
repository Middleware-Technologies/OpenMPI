#include "mpi.h"
#include <stdio.h>

int main(int argc, char *argv[])
{
	  int numtasks, rank, dest, source, rc, count, tag=1;
	  char inmsg[10];
	  MPI_Status stat;

	  MPI_Init(&argc,&argv);
	  MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
	  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	  if(rank == 0)
	  {
			dest = 1; source = 1;
			char *outmsg="ciao sono 0";
			//INVIO A 1
			rc = MPI_Send(outmsg, 12, MPI_CHAR, dest, tag, MPI_COMM_WORLD);
			//RICEVO DA 1
			rc = MPI_Recv(inmsg, 15, MPI_CHAR, source, tag, MPI_COMM_WORLD, &stat);
	  }
	  else if(rank == 1)
	  {
			dest = 0; source = 0;
			char *outmsg="ciao sono 1";
			//RICEVO DA 0
			rc = MPI_Recv(inmsg, 15, MPI_CHAR, source, tag, MPI_COMM_WORLD, &stat);
			//INVIO A ZERO
			rc = MPI_Send(outmsg, 12, MPI_CHAR, dest, tag, MPI_COMM_WORLD);
	  }
	  rc = MPI_Get_count(&stat, MPI_CHAR, &count);

	  printf("Task %d: received %d char(s) - %s -  from task %d with tag %d\n",
		 rank, count, inmsg, stat.MPI_SOURCE, stat.MPI_TAG);
	  MPI_Finalize();
}
