#include <gtest/gtest.h>
#include <iostream>
#include <fstream>
#include "parent.hpp"

void TestParent(const std::string &src, const std::string &check) {
    std::stringstream srcStream;
    const char* filename = "test.txt";

    srcStream << filename << " " << src;

    Parent(getenv("PATH_TO_CHILD"), srcStream);

    std::ifstream in(filename);
    std::string res;
    std::getline(in, res);
    EXPECT_EQ(res, check);
    std::remove(filename);

}

TEST(test01, sum1) {
    std::string s = "1 2 3 4 5";
    std::string check = "15";
    TestParent(s, check);
}

TEST(test01, sum2) {
    std::string s = "1 2 3";
    std::string check = "6";
    TestParent(s, check);
}

TEST(test02, sum2) {
    std::string s = "";
    std::string check = "0";
    TestParent(s, check);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
