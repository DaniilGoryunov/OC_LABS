#include <gtest/gtest.h>
extern "C" {
    #include "../lab4/include/pi-sin.h"
}
#include <iostream>

TEST(Pi, test_01){
    int res = Pi(11);
    EXPECT_EQ(res, 3.232316);
}

TEST(Integral, test_01){
    float res = sin_integral(2, 10, 0.1);
    EXPECT_EQ(res, -2.235324);
}