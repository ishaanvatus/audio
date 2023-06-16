# How Does a Computer store sound?

## Introduction and terminologies explained
Sound is an analog signal, computers are particularly bad at storing these kinds of signal since an analog signal would require infinite amount of storage.


But for an audio signal of known frequencies, the [Nyquist-Shannon sampling theorem](https://en.wikipedia.org/wiki/Nyquist%E2%80%93Shannon_sampling_theorem) guarantees lossless digitization if the sampling rate is atleast twice the maximum frequency of the signal.

### Terminologies:

1. [Sampling rate](https://en.wikipedia.org/wiki/Sampling_(signal_processing)#Sampling_rate): defines the number of samples/second, how many readings of the signal will be taken in one second. Common values are 44.1 kHz and 48 kHz.
2. [Bit depth](https://en.wikipedia.org/wiki/Audio_bit_depth): computers can't store infinite precision decimals, bit depth refers to the number of possible states that can be stored for the signal, for example a bit depth of 4 means each sample can have one of 16 values, 7 above 0 and 8 below 0 (7 above because of 0). Common values are 16 bit for listening to music and 24 bit or even 32 bit for music production.


