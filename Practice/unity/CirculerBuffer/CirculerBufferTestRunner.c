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
	RUN_TEST_CASE(CirculerBuffer, PutTwoData);
	RUN_TEST_CASE(CirculerBuffer, GetTwoData);
	RUN_TEST_CASE(CirculerBuffer, BufferIsEmpty);
	RUN_TEST_CASE(CirculerBuffer, BufferIsNotEmpty);
}
