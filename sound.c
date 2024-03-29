#include <stdio.h>
#include <math.h>
#include "sound.h"

double sine(double amp, double freq, double time)
{
		return amp*sin(2.0*M_PI*freq*time);
}

double square(int n, double freq, double time)
{
	double sq = 0;
	int k = 1;
	while (k <= 2*n + 1)
	{
		sq += sin(2.0*k*freq*M_PI*time)/(1.0*k);
		k += 2;
	}
	sq = (4/M_PI)*sq;
	return sq;

}

double triangle(int n, double freq, double time)
{
	double triangle;
	int k = 1;
	int sign = -1;
	while (k <= 2*n)
	{
		triangle += (1/(k*k*1.0))*sign*sine(1.0, k*freq, time);
		sign *= -1;
		k += 2;
	}
	return triangle;
}
double sawtooth(double freq, double time)
{
    double saw;
    double p = 1/freq;
    return 2*((time/p) - floor((1/2) + (time/p)));
}
