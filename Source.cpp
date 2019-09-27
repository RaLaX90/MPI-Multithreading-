#include <iostream> 
#include <iomanip> 
#include <fstream> 
#include <cstdlib> 
#include <ctime> 
#include <cassert> 
#include <math.h> 
#include <windows.h>  
#include <mpi.h> 

//#include <omp.h>

#define n 10
void smod5(int *in, int *inout, int *l, MPI_Datatype *type) {
	int i;
	for (i = 0; i < *l; i++) ((int*)inout)[i] = (((int*)in)[i] + ((int*)inout)[i]) % 5;
}
int main(int argc, char **argv)
{
	int rank, size, i;
	int a[10];
	int b[10];
	MPI_Op op;
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	for (i = 0; i < 10; i++) a[i] = i + rank + 1;
	printf("process %d a[0] = %d\n", rank, a[0]);
	MPI_Op_create((MPI_User_function *)smod5, 1, &op);
	MPI_Reduce(&a, &b, n, MPI_INT, op, 0, MPI_COMM_WORLD);
	MPI_Op_free(&op);
	if (rank == 0) printf("b[0] = %d\n", b[0]);
	MPI_Finalize();
	return 0;
}