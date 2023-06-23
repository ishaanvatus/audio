#include <stdio.h>
#include <math.h>

double triangle(int n, double freq, double time);
double sine(double amp, double freq, double time);
double square(int n, double freq, double time);

int main(int argc, char *argv[])
{
	int sample_rate = 48000;
	double freq = 1;
	double amp = 1;
	int depth = atoi(argv[1]);
	double duration = 1;
	double time = 0;
	double val = 0;
	short temp = 0;
	int i = 0;

	FILE *fp = fopen("sine.bin", "wb");
	FILE *sq = fopen("square.bin", "wb");
	FILE *sm = fopen("triangle.bin", "wb");
	FILE *gp = fopen("plot", "w");
	fprintf(gp, "plot '-'\n");
	if (fp == NULL)
	{
		return -1;
	}
	while (i <= sample_rate*duration)
	{
		val = 10000.0*sine(amp, freq, time);
		temp = (short) val;
 		fwrite((const void*) &temp,sizeof(short),1,fp);
		time = i/(1.0*sample_rate);
		i++;
	}
	time = 0; 
	i = 0;
	while (i <= sample_rate*duration)
	{
		temp = (short) 1000.0*square(depth, freq, time);
		fwrite((const void*) &temp,sizeof(short),1,sq);
		fprintf(gp, "%lf, %d\n", time, temp);
		time = i/(1.0*sample_rate);
		i++;
	}
	time = 0; 
	i = 0;
	while (i <= sample_rate*duration)
	{
		temp = (short) 10000.0*triangle(depth, freq, time);
		fwrite((const void*) &temp,sizeof(short),1,sm);
		time = i/(1.0*sample_rate);
		i++;
	}
	fprintf(gp, "e\n");
	fflush(gp);
	fclose(fp);
	fclose(sq);
	fclose(gp);
}
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
