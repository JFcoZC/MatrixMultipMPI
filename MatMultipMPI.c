/*
*Matrix Multiplication algorithm implementatio using MPI
*
*154678
*José Francisco Zerón Cabrera
*/

//Libraries
#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>

//Global variables
int N = 10;
int MASTERID = 0;

//------- FUNCTIONS --------

//----- END FUCNTIONS ------

//Start main function/program
int main(int argc, char *argv[])
{
	//+++ Declaration of variables +++
	int matrixA[10][10];
	int matrixB[10][10];
	int matrixR[10][10];
	int filaActualMatriz;

	//MPI
	int totalProcessorsInComm;
	int resourceProcessId;
	int procesIdDestination; //#Process to which the Master sends the data
	int numRowTag;

	//+++ Variables initialization +++

	//+++ Input data +++
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			matrixA[i][j] = (j*i) + 1;
			matrixB[i][j] = 0;
			matrixR[i][j] = 0;

		}//End for 2

	}//End for 1

	for (int i = 0; i < N; i++)
	{
		matrixB[i][i] = 2;
	}//End for 3

	filaActualMatriz = 0;
	//Initialize proces ID with because the destination processor
	//can not be the MASTER process
	procesIdDestination = 1;

	//+++ Proces +++

	/*
	*Initialize the structure of communication between Processors(Indispenable for communication)
	*/
	MPI_Init(&argc, &argv);

	/*
	*Save the rank/Id actual process in variable resourceProcesId
	*
	*Input: desired communicator that we want to know it is ID->MPI_COMM_WORLD
	*Output: int ID communicator -> save in resourceProcessId
	*/
	MPI_Comm_rank(MPI_COMM_WORLD, &resourceProcessId);

	/*
	*Determine the current number of processors associated with specific communicator
	*
	*Input: desired communicator that we want to know its size ->MPI_COMM_WORLD
	*Output: int #Processors in current communicator -> save in totalProcessorsInComm
	*/
	MPI_Comm_size(MPI_COMM_WORLD, &totalProcessorsInComm);

	//------------ MASTER WORK ----------
	if (resourceProcessId == MASTERID)
	{
		printf("Master Splitting the work!\n");

		//While there are rows in the matrix
		while (filaActualMatriz < N)
		{
			//Send equal number of Rows to each process
			if ( procesIdDestination < totalProcessorsInComm )
			{
				procesIdDestination++;

			}//End if
			else
			{
				procesIdDestination = 1;
			}//End else

			numRowTag = filaActualMatriz;
			/*
			* Send data from actual processor to other processor.
			* data = data buffer -> matrixA[#Row] [ponter* memory]
			* count = # of elements that will be send ->N [int]
			* dataType -> MPI_INT [MPI DATA TYPE]
			* source = # of processor from which data is sent -> (in this case used to specify the destination) [int]
			* tag = # used to add some information about the data as you want -> numRowTag [int]
			* comm = Communicator throught wich the communication is performed -> MPI_COMM_WORLD [MPI CONSTANT]
			*/

			//Send actual row from matrixA
			//MPI_Send(&N, 1, MPI_INT, procesIdDestination, 0, MPI_COMM_WORLD);

			filaActualMatriz++;

		}//Fin while

		printf("Master reciving the work of their workers!\n");

	}//End if Master work*/
	//----------- END MASTER WORK -------

	//------------ WORKERS WORK ----------
	if (resourceProcessId != MASTERID)
	{
		//Recieve actual row from matrixA
		//MPI_Recv(matrixA[filaActualMatriz], N, MPI_INT, procesIdDestination, numRowTag, MPI_COMM_WORLD);

	}//End if workers work
	//----------- END WORKERS WORK -------

	//+++ Output data +++

	//Ends the prallel communication between processors(After this processors
	//can not continue sending messages)
	MPI_Finalize();

	//+++ End of program +++
	printf("End of program V2");

	//Indicates to the OS that all ends ok
	return 0;

}//End main function

