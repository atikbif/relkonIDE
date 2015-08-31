#include <gtest/gtest.h>
#include "display.h"

class LCDTest: public ::testing::Test
{
protected:
    LCDTest() {}
    virtual ~LCDTest() {}
    virtual void SetUp() {}
    virtual void TearDown() {}
};

TEST_F(LCDTest,initLCD) {
    ASSERT_TRUE(true);
}

TEST_F(LCDTest,addRemoveStrings) {
    ASSERT_TRUE(true);
}

TEST_F(LCDTest,addRemoveVars) {
    ASSERT_TRUE(true);
}

TEST_F(LCDTest,addRemoveSymbols) {
    ASSERT_TRUE(true);
}

int main(int argc, char *argv[]) {
    ::testing::InitGoogleTest(&argc,argv);
    return RUN_ALL_TESTS();
}
