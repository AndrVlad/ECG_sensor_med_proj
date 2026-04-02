/**************************************************************
WinFilter version 0.8
http://www.winfilter.20m.com
akundert@hotmail.com

Filter type: Low Pass
Filter model: Butterworth
Filter order: 3
Sampling Frequency: 853 Hz
Cut Frequency: 100.000000 Hz
Coefficents Quantization: 16-bit

Z domain Zeros
z = -1.000000 + j 0.000000
z = -1.000000 + j 0.000000
z = -1.000000 + j 0.000000

Z domain Poles
z = 0.443058 + j -0.000000
z = 0.554503 + j -0.435544
z = 0.554503 + j 0.435544
***************************************************************/
#define NCoef 3
#define DCgain 16

__int16 iir(__int16 NewSample) {
    __int16 ACoef[NCoef+1] = {
         7082,
        21248,
        21248,
         7082
    };

    __int16 BCoef[NCoef+1] = {
        16384,
        -25429,
        16196,
        -3609
    };

    static __int32 y[NCoef+1]; //output samples
    //Warning!!!!!! This variable should be signed (input sample width + Coefs width + 3 )-bit width to avoid saturation.

    static __int16 x[NCoef+1]; //input samples
    int n;

    //shift the old samples
    for(n=NCoef; n>0; n--) {
       x[n] = x[n-1];
       y[n] = y[n-1];
    }

    //Calculate the new output
    x[0] = NewSample;
    y[0] = ACoef[0] * x[0];
    for(n=1; n<=NCoef; n++)
        y[0] += ACoef[n] * x[n] - BCoef[n] * y[n];

    y[0] /= BCoef[0];

    return y[0] / DCgain;
}
