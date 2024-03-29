#include <stdio.h>
#include <math.h>
#include "sound.h"

int main(int argc, char *argv[])
{
	int sample_rate = 48000;
	//double freq = 261.63;
	double freq = 277.183;
	double amp = 1;
	int depth = atoi(argv[1]);
	double duration = 3;
	double time = 0;
	double val = 0;
	short temp = 0;
	int i = 0;

	FILE *fp = fopen("sine.bin", "wb");
	FILE *sq = fopen("square.bin", "wb");
	FILE *sm = fopen("triangle.bin", "wb");
	FILE *saw = fopen("sawtooth.bin", "wb");
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
 		fwrite( &temp,sizeof(short),1,fp);
		time = i/(1.0*sample_rate);
		i++;
	}
	time = 0; 
	i = 0;
	while (i <= sample_rate*duration)
	{
		temp = (short) 10000.0*square(depth, freq, time);
		fwrite(&temp,sizeof(short),1,sq);
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
	time = 0; 
	i = 0;
	while (i <= sample_rate*duration)
	{
		temp = (short) 10000.0*sawtooth(freq, time);
		fwrite((const void*) &temp,sizeof(short),1,saw);
		time = i/(1.0*sample_rate);
		i++;
	}
	fprintf(gp, "e\n");
	fflush(gp);
	fclose(fp);
	fclose(sq);
	fclose(gp);
}
