#include <iostream>
#include <gtest/gtest.h>
#include "nn.h"


using namespace gherkin;

TEST(TestSuiteSample, TestSample){
    double a[2] = {1,2};
    double b[2] = {1,2};

    Vector tink(2);
    Vector tank(2);

    tink<<a;
    tank<<a;

    double pred_value = weighted_sum(tink, tank);
    ASSERT_EQ(4, pred_value);
}

// int main(int argc, char **argv)
// {
//     testing::InitGoogleTest(&argc, argv);
//     return RUN_ALL_TESTS();
// }