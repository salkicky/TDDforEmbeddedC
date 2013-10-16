extern "C"
{
#include "TimeServiceSpy.h"
}

#include "CppUTest/TestHarness.h"

TEST_GROUP(TimeServiceSpy)
{
    void setup()
    {
      TimeService_Create();
    }

    void teardown()
    {
       TimeService_Destroy();
    }
};

TEST(TimeServiceSpy, Create)
{
  FAIL("Start here");
}

