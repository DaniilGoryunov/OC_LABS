#include "../include/pi-sin.h"
#include <math.h>

float Pi(int k){
    float res = 1;
    for (int n = 1; n <= k; n++) {
        res *= ((4 * pow(n, 2)) / (4 * pow(n, 2) - 1));
    }
    return 2 * res;
}

float sin_integral(float A, float B, float e){
    float dx = (B - A) / e;
    int steps = (B - A) / dx;
    float current = A;
    float result = 0;
    for (int i = 0; i < steps; ++i){
        result += dx * (sin(current) + sin(current + dx)) / 2;
        current += dx;
    }
    result += (B - current) * (sin(B) + sin(current)) / 2;
    return result;
}