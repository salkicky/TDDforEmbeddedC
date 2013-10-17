extern "C"
{
#include "LightController.h"
}

#include "CppUTest/TestHarness.h"

TEST_GROUP(LightController)
{
    void setup()
    {
      LightController_Create();
    }

    void teardown()
    {
       LightController_Destroy();
    }
};

TEST(LightController, Create)
{
  //FAIL("Start here");
  CHECK_TRUE(1);
}

