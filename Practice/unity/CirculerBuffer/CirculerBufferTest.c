/*************************************************
 *
 * CirculerBufferTest.c
 *
 *
 **************************************************/

#include "unity_fixture.h"
#include <stdlib.h>
#include "CirculerBuffer.h"

int buffer;

TEST_GROUP(CirculerBuffer);

/* set up */
TEST_SETUP(CirculerBuffer)
{
	CirculerBuffer_create(&buffer);
}

/* tear down */
TEST_TEAR_DOWN(CirculerBuffer)
{
}


////// TEST //////////////////////////////////////

TEST(CirculerBuffer, PutOneData)
{
	CirculerBuffer_put(1);
	TEST_ASSERT_EQUAL_INT(1, buffer);
}

TEST(CirculerBuffer, PutOneData2)
{
	CirculerBuffer_put(2);
	TEST_ASSERT_EQUAL_INT(2, buffer);
}

TEST(CirculerBuffer, GetOneData)
{
	CirculerBuffer_put(1);
	TEST_ASSERT_EQUAL_INT(1, CirculerBuffer_get());
}

