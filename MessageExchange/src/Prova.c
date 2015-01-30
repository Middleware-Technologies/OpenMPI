/*
 ============================================================================
 Name        : Prova.c
 Author      : Luca
 Version     :
 Description : Exchange a message between thread
 Instruction:
 	 - Install PTP plugin for eclipse
 	 - ImportProject
 	 - Right Click on Project >Properties>Paths AND Symbols
 	     In includes tab add the Include Folder of your MPI'INSTALLATION FOLDER
 	       (.openmpi/include)

 ============================================================================
 */
#include <mpi.h>
#include <stdio.h>
#include <string.h>


int main(int argc, char *argv[])
{
	int			my_rank;		/* rank of process */
	int			num_procs;		/* number of processes */
	int			source;			/* rank of sender */
	int			dest = 0;		/* rank of receiver */
	int			tag = 0;		/* tag for messages */
	char		message[100];	/* storage for message */
	MPI_Status	status ;		/* return status for receive */

	/* start up MPI */
	MPI_Init(&argc, &argv);

	/* find out process rank */
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank); 

	/* find out number of processes */
	MPI_Comm_size(MPI_COMM_WORLD, &num_procs); 

	if (my_rank != 0)   //IF I'M ANOTHER THREAD
	{
		/* create message */
		snprintf(message,26, "Greetings from process %d!", my_rank);
		/* send message to thread 0 */
		MPI_Send(message, strlen(message)+1, MPI_CHAR,dest, tag, MPI_COMM_WORLD);
	}
	else  //IF I'M THREAD 0
	{
		printf("Number of processes in system: %d\n",num_procs);
		for (source = 1; source < num_procs; source++)
		{
			MPI_Recv(message, 100, MPI_CHAR, source, tag,MPI_COMM_WORLD, &status);
			printf("Process 0 received %s from %d\n",message,source);
		}
	}

	/* shut down MPI */
	MPI_Finalize(); 

	return 0;
}
