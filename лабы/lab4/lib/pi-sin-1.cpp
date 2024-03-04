#include "../include/pi-sin.h"
#include <math.h>

float Pi(int k){
    float res = -1;
    for (int n = 0; n <= k; n++) {
        res = res + (-pow(-1, n) / (2 * n - 1));
    }
    return 4 * res;
}

float sin_integral(float A, float B, float e){
    float dx = (B - A) / e;
    int steps = (B - A) / dx;
    float current = A;
    float result = 0;
    for (int i = 0; i < steps; i++){
        result += dx * sin(current + dx / 2);
        current += dx;
    }
    result += (B - current) * sin((B + current) / 2);
    return result;
}
