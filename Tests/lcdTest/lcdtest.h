#ifndef LCDTEST_H
#define LCDTEST_H

#include <gtest/gtest.h>

class LCDTest: public ::testing::Test
{
public:
    LCDTest();
    ~LCDTest();
    virtual void SetUp();
    virtual void TearDown();
};

#endif // LCDTEST_H
