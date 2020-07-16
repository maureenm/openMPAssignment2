#include <omp.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

//Setting the size for our matrix.
int max = 100;
//Set up variables to track performance through runtime.
double start_time;
double run_time;


int main(int argc, char *argv[])
{
	//Making our matrices
	//matrices are 100x100, same number of columns and rows so no reshaping required.
	int m1[max][max], m2[max][max], results[max][max];
	int sum, i, j, k;
	{
		for (int ii = 0; ii < max; ++ii)
		{
			for (int jj = 0; jj < max; ++jj)
			{
				//Filling matrices with random numbers

				m1[ii][jj] = (double)rand();
				m2[ii][jj]  = (double)rand();
				//Filling results matrix with zeros so its empty before beginning
				//results[ii][jj] = 0.0;
			}
		}

		for (int x = 0; x < max; x++)
		{
			for (int y = 0; y < max; y++)
			{
				m2[x][y] = m2[x][y];
			}
		}
	}




	//Begin time tracker
	start_time = omp_get_wtime();
	//Loop through rows of matrix
	#pragma parallel for collapse(2) private(i, j, k) num_threads(4)
		for (int i = 0; i < max; i++)
			{
				//Loop through columns of matrix
				for (int j = 0; j < max; j++)
					{
						//Actual calculation carried out here for each iteration of k
						for(k = 0; k < max; k++)
							{
								results[i][j] += m1[i][k] * m2[j][k];
							}

					}
				}

	//End performance tracker
	run_time = omp_get_wtime() - start_time;
	//Print out all reuslts and details of this test
	printf("Method : Parallel Transpose \nRuntime : %f\n", run_time );
	printf("Deimensions: %dx%d\n", max, max);
	return 0;
}
