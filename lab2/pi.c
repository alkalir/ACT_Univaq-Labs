/*

This program will numerically compute the integral of

                  4/(1+x*x) 
				  
from 0 to 1.  The value of this integral is pi.

It uses the timer from the OpenMP runtime library although it would be possible to use
other functions to get time (and do not involve Openmp)

History: Written by Tim Mattson, 11/99.

*/
#include <stdio.h>
#include <omp.h>
static long num_steps = 100000000; // number of sub-intervals used in the numerical integration
double step; 

int main ()
{
	  int i;
	  double x, pi, sum = 0.0;
	  double start_time, run_time;

	  step = 1.0/(double) num_steps; //width of each sub-interval

        	 
	  start_time = omp_get_wtime(); // take a timestamp

	  for (i=1;i<= num_steps; i++){
		  x = (i-0.5)*step; // compute mid-point at base
		  sum = sum + 4.0/(1.0+x*x); // compute height
	  }

	  pi = step * sum; // multiply all rectangles
	  run_time = omp_get_wtime() - start_time;
	  printf("\n pi with %ld steps is %lf in %lf seconds\n ",num_steps,pi,run_time);
}	  




