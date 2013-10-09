extern "C"
{
#include "Sample.h"
}

#include "CppUTest/TestHarness.h"

TEST_GROUP(Sample)
{
    void setup()
    {
      Sample_Create();
    }

    void teardown()
    {
       Sample_Destroy();
    }
};

TEST(Sample, Create)
{
  CHECK_TRUE(1);
  //FAIL("Start here");
}

