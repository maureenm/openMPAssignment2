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

		for (int i = 0; i < max; i++)
				{
					for (int j = 0; j < max; j++)
						{
							//For each pair of ij make sure it is empty
							results[i][j] = 0;
							//For each pair of ij carry out the calculation
							for(k = 0; k < max; k++)
							{
								//For the same pair of ij fill results with multiplication result
								results[i][j] += m1[i][k] * m2[k][j];
							}
						}
				}

	//End performance tracker
	run_time = omp_get_wtime() - start_time;
	//Print out all reuslts and details of this test
	printf("Method : Non-Parallel Scalar Expansion \nRuntime : %f\n", run_time );
	printf("Deimensions: %dx%d\n", max, max);
	return 0;
}
