#include <omp.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

//Setting the size for our matrix.
int max = 100;

//Set up variables to track performance through runtime.
double start_time;
double run_time;
int i, j, k;

int main(int argc, char *argv[])
{
	//Making our matrices
	//matrices are 100x100, same number of columns and rows so no reshaping required.
	int m1[max][max], m2[max][max], results[max][max];
	{
		for (int ii = 0; ii < max; ++ii)
		{
			for (int jj = 0; jj < max; ++jj)
			{
				//Filling matrices with random numbers
				m1[ii][jj] = (double)rand();
				m2[ii][jj]  = (double)rand();
				//Filling results matrix with zeros so its empty before beginning
				results[ii][jj] = 0.0;
			}
		}
	}


	//Begin time tracker
	start_time = omp_get_wtime();
		//Parallelizing x and y threads.
		//These threads loop through the matrices
		//Each thread gets a pair of x and y to work on
		//#pragma omp parallel for collapse(2)
		#pragma omp parallel shared(m1, m2, results) private(i,j,k)
  	// {
		//#pragma omp for  schedule(static)
		for (int i = 0; i < max; i++)
				{
					//loop interchanged applied
					for(k = 0; k < max; k++)
					{ //For each pair of ik make sure it is sempty
							results[i][j] = 0;
							//For each pair of ik carry out the calculation
							for (int j = 0; j < max; j++)
								{
									//Carry out our calculation
									//For the same pair of ij fill results with multiplication result
									results[i][j] += m1[i][k] * m2[k][j];
								}
					}
				}
		//	}

	//End performance tracker
	run_time = omp_get_wtime() - start_time;
	//Print out all reuslts and details of this test
	printf("Method : Non-Parallel Scalar Expansion \nRuntime : %f\n", run_time );
	printf("Deimensions: %dx%d\n", max, max);
	return 0;
}
