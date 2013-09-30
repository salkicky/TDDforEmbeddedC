#include "unity_fixture.h"
#include <stdio.h>

static void RunAllTests(void)
{
    RUN_TEST_GROUP(sprintf);
    RUN_TEST_GROUP(LedDriver);
    RUN_TEST_GROUP(CirculerBuffer);
}


int main(int argc, char *argv[])
{
    return UnityMain(argc, argv, RunAllTests);
}
