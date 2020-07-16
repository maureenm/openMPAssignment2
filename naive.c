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
	}


	//Begin time tracker
	start_time = omp_get_wtime();
	//Loop through rows of matrix
		for (int i = 0; i < max; i++)
			{
				//Loop through columns of matrix
				for (int j = 0; j < max; j++)
					{
						//Set sum = 1 for each iteration of j
						sum = 0;
						//Actual calculation carried out here for each iteration of k
						for(k = 0; k < max; k++)
							{
								sum += m1[i][k] * m2[k][j];
								//results[i][j] += m1[i][k] * m2[k][j];
							}
						//Saving results into results matrix
						results[i][j] = sum;
					}
				}

	//End performance tracker
	run_time = omp_get_wtime() - start_time;
	//Print out all reuslts and details of this test
	printf("Method : Naive \nRuntime : %f\n", run_time );
	printf("Deimensions: %dx%d\n", max, max);
	return 0;
}
