/*************************************************
 *
 * CirculerBufferTestRunner.c
 *
 *
 **************************************************/

#include "unity_fixture.h"

TEST_GROUP_RUNNER(CirculerBuffer)
{
	RUN_TEST_CASE(CirculerBuffer, PutOneData);
	RUN_TEST_CASE(CirculerBuffer, PutOneData2);
	RUN_TEST_CASE(CirculerBuffer, GetOneData);
}
