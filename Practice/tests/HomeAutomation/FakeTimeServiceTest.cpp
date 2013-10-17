extern "C"
{
#include "FakeTimeService.h"
}

#include "CppUTest/TestHarness.h"

TEST_GROUP(FakeTimeService)
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

TEST(FakeTimeService, Create)
{
  FAIL("Start here");
}

