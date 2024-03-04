#include <gtest/gtest.h>
extern "C" {
    #include "../lab4/lib/pi-sin-1.c"
}
#include <iostream>

TEST(Pi, test_01){
    int res = Pi(11);
    EXPECT_EQ(res, 5);
}

TEST(Square, test_01){
    float res = sin_integral(2, 10, 1);
    EXPECT_EQ(res, 20);
}

