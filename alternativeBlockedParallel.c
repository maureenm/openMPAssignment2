#include <omp.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

//Setting the size for our matrix.
int max = 100;
double start_time;
double run_time;
//Initializing number of threads.
int NUM_THREADS;

int main(int argc, char *argv[])
{
	//Making our matrices
	//matrices are 100x100, same number of columns and rows so no reshaping required.
	int m1[max][max], m2[max][max], results[max][max];
	int acc, i, j, x, y;
	//Defining number of threads to be used for calculations
	NUM_THREADS = 4;
	//Setting a fixed block size which will be 10x10 squares
	int block  = 10;

	{
		for (int ii = 0; ii < max; ++ii)
		{
			for (int jj = 0; jj < max; ++jj)
			{
				//Filling the two matrices with random values
				m1[ii][jj] = (double)rand();
				m2[ii][jj]  = (double)rand();
				//Filling results matrix with zeros so its empty before beginning
				results[ii][jj] = 0.0;
			}
		}
	}

		//Begin time tracker
		start_time = omp_get_wtime();
		//Parallelizing the outer two for loops and defining the number of threads.
		#pragma omp parallel for collapse(2), num_threads(NUM_THREADS)
		//This for loop will jump in block sizes(10) for each row of
		//The blockes are being created with these two collapsed loops.
		for (int i = 0; i < max; i += block)
		{
			for (int j = 0; j < max; j += block)
			{
				//Iterating through the block rows
				for (int y = 0; y < block; y++)
				{
					//iterating through the block columns
					for (int k = i; k < i + block; k ++)
						{
							//Using a temporary variable to store
							acc = m1[i][k];
							for(x = j; x < j + block; x++)
							{
								//Creating our critical section
									#pragma omp critical
							results[i][j] += acc * m2[k][j];

						}
					}
				}
			}
		}

		//End performance tracker
		run_time = omp_get_wtime() - start_time;
		//Print out all reuslts and details of this test
		printf("Method : Alternative Matrix Multiplication Parallelised \nRuntime : %f\n", run_time );
		printf("Deimensions: %dx%d\n", max, max);
		printf("Number of blocks: %d \nNumber of Threads: %d", block, NUM_THREADS);
		return 0;
}
