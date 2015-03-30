#include <gtest/gtest.h>
#include "calc.h"

// TEST(TestCaseName, TestName)
TEST(CalcTest, AddSubtractTest)
{
    // EXPECT_* 失败时，继续向下运行
    EXPECT_EQ(3, Calculator::add(1, 2));
}

int main(int argc, char *argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
