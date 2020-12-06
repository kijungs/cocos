#ifndef _MPI_EXAMPLE_HPP_
#define _MPI_EXAMPLE_HPP_

#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <ctime>
#include <mpi.h>

void timestamp ()
{
# define TIME_SIZE 40

  static char time_buffer[TIME_SIZE];
  const struct std::tm *tm_ptr;
  size_t len;
  std::time_t now;

  now = std::time ( NULL );
  tm_ptr = std::localtime ( &now );

  len = std::strftime ( time_buffer, TIME_SIZE, "%d %B %Y %I:%M:%S %p", tm_ptr );

  std::cout << time_buffer << "\n";

  return;
# undef TIME_SIZE
}


void printMessage(int szProc){

    timestamp ();
    cout << "\n";
    cout << "SUM - Master process:\n";
    cout << "  C++ version\n";
    cout << "\n";
    cout << "  An MPI example program.\n";
    cout << "  The master process computes some coefficients,\n";
    cout << "  sends them to each worker process, which sums them.\n";
    cout << "\n";
    cout << "  Compiled on " << __DATE__ << " at " << __TIME__ << ".\n";
    cout << "\n";
    cout << "  The number of processes available is " << szProc << "\n";

}

void printMessage2(){
    cout << "\n";         
    cout << "SUM - Master process:\n";       
    cout << "  Normal end of execution.\n";
    cout << "\n";
    timestamp ( );   
}   

int mpi_sum_example(int argc, char **argv)
{

# define N 100

  double array[N];
  int i, rank, szProc;
  const int MASTER_NODE = 0;
  const double PI = 3.141592653589793238462643;
  double seed, sum, sum_all;
  int tag;
  MPI_Status status;
  
  const int master = 0;

//
//  Initialize MPI.
//
  MPI_Init ( &argc, &argv );
  MPI_Comm_size ( MPI_COMM_WORLD, &szProc );
  MPI_Comm_rank ( MPI_COMM_WORLD, &rank );

  if ( rank == MASTER_NODE)
  {
	printMessage(szProc);

	// Init array
    seed = 1.2345;
    for ( i = 0; i < N; i++ )
    {
      array[i] = ( double ) i * seed * PI;
    }
    MPI_Bcast ( array, N, MPI_DOUBLE, master, MPI_COMM_WORLD );
  }


//  Each process adds up its entries.
  sum = 0.0;
  for ( i = 0; i < N; i++ )
  {
    sum = sum + array[i] * ( double ) (rank + 1);
  }

  cout << "\n";
  cout << "SUM - Process " << rank << ":\n";
  cout << "  My contribution to the sum is " << sum << "\n";
// 
//  Each worker process sends its sum back to the master process.
//
  if ( rank != 0 ) 
  {
    MPI_Send ( &sum, 1, MPI_DOUBLE, master, 1, MPI_COMM_WORLD );
  }
  else 
  {
    sum_all = sum;
    for ( i = 1; i < szProc; i++ ) 
    {
      tag = 1;
      MPI_Recv ( &sum, 1, MPI_DOUBLE, MPI_ANY_SOURCE, 1, 
        MPI_COMM_WORLD, &status );

      sum_all = sum_all + sum;
    }
  }


  if ( rank == MASTER_NODE )
  {
    cout << "\n";         
    cout << "SUM - Master process:\n";         
    cout << "  The total sum is " << sum_all << "\n";
  }
//
//  Terminate MPI.

  MPI_Finalize ( );


  if ( rank == MASTER_NODE )
  {
	printMessage2();
  }

  return 0;

# undef N
}

#endif // #ifndef _MPI_EXAMPLE_HPP_
