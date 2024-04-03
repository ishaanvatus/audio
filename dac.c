//sawtooth
#include <lpc17xx.h>

void delayMS(unsigned int milliseconds);
int main(void) {
  unsigned int value = 0;
  LPC_PINCON -> PINSEL1 |= (1 << 21); //Select AOUT function for P0.26 , bits[21:20] = [10]
  while (1) {
    if (value > 1023) value = 0; //For 10-bit DAC max-value is 2^10 - 1 = 1023
    LPC_DAC -> DACR = (value << 6);
    delayMS(9999); //for 10 millisecond delay
    value++;
  }
}
void delayMS(unsigned int count) {
  LPC_TIM0 -> CTCR = 0x0;
  LPC_TIM0 -> PR = 2;
  LPC_TIM0 -> TCR = 0x02;
  LPC_TIM0 -> TCR = 0x01;
  while (LPC_TIM0 -> TC < count);
  LPC_TIM0 -> TCR = 0x00;
}

//triangular
#include <lpc17xx.h>

int main(void) {
  unsigned int temp, i;
  LPC_PINCON -> PINSEL1 |= (1 << 21); //Select AOUT function for P0.26 , bits[21:20] = [10]
  while (1) {
    for (i = 0; i != 1023; i++) {
      temp = i;
      LPC_DAC -> DACR = (temp << 6);
    }
    for (i = 1023; i != 0; i--) {
      temp = i;
      LPC_DAC -> DACR = (temp << 6);
    }
  }
}

//square wave
#include <lpc17xx.h>

void delayMS(unsigned int milliseconds);
int main(void) {
  LPC_PINCON -> PINSEL1 |= (1 << 21); //Select AOUT function for P0.26 , bits[21:20] = [10]
  while (1) {
    LPC_DAC -> DACR = (1023 << 6);
    delayMS(9999); //for 10 millisecond delay
    LPC_DAC -> DACR = (0 << 6);
    delayMS(9999); //for 10 millisecond delay
  }
}
void delayMS(unsigned int count) {
  LPC_TIM0 -> CTCR = 0x0;
  LPC_TIM0 -> PR = 2;
  LPC_TIM0 -> TCR = 0x02;
  LPC_TIM0 -> TCR = 0x01;
  while (LPC_TIM0 -> TC < count);
  LPC_TIM0 -> TCR = 0x00;
}

//sine wave
#include <lpc17xx.h>

#include <math.h>

#define pi 3.14
int main(void) {
  unsigned int i, temp;
  float rad, value;
  LPC_PINCON -> PINSEL1 |= (1 << 21); //Select AOUT function for P0.26, bits[21:20] = [10]
  while (1) {
    for (i = 0; i <= 360; i = i + 9) //keep on incrementing value from 00 till 360 in step of 9. 40
    //samples for one cycle
    {
      rad = sin(i * (pi / 180));
      value = 1.65 + 1.65 * rad;
      temp = (value * 1023) / 3.3;
      LPC_DAC -> DACR = (temp << 6);
    }
  }
}
