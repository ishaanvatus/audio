#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char *argv[])
{
	int sample_rate = 48000;
	double freq = 220;
	double amp = 1;
	int duration = 12;
	int sample[sample_rate*duration];
	sample[0] = (int) 32767;
	sample[1] = (int) (-32768);
	FILE *fp = fopen("sine.raw", "wb");
	FILE *log = fopen("sine.log", "w");
	if (fp == NULL)
	{
		return -1;
	}
	double val = 0;
	int counter = 0;

	for (int j = 1; j <= duration; j++)
	{
		for (int i = (j-1)*sample_rate; i < sample_rate*j; i++)
		{
			val = (int) amp*32767.0*sin(1.0*2.0*M_PI*freq*((i*2.0)/(sample_rate*1.0)));
			sample[1] = val;
			fwrite(&sample[1], sizeof(*sample), 1, fp);
		}
		freq *= 1.0594630943592953; 
	}
}
