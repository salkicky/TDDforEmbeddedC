/*************************************************
 *
 * CirculerBufferTest.c
 *
 *
 **************************************************/

#include "unity_fixture.h"
#include <stdlib.h>
#include "CirculerBuffer.h"

#define BUF_MAX_SIZE  2
int buffer[BUF_MAX_SIZE];

TEST_GROUP(CirculerBuffer);

/* set up */
TEST_SETUP(CirculerBuffer)
{
	CirculerBuffer_create(buffer, BUF_MAX_SIZE);
}

/* tear down */
TEST_TEAR_DOWN(CirculerBuffer)
{
}


////// TEST //////////////////////////////////////

TEST(CirculerBuffer, PutOneData)
{
	CirculerBuffer_put(1);
	TEST_ASSERT_EQUAL_INT(1, buffer[0]);
}

TEST(CirculerBuffer, PutOneData2)
{
	CirculerBuffer_put(2);
	TEST_ASSERT_EQUAL_INT(2, buffer[0]);
}

TEST(CirculerBuffer, GetOneData)
{
	CirculerBuffer_put(1);
	TEST_ASSERT_EQUAL_INT(1, CirculerBuffer_get());
}

TEST(CirculerBuffer, PutTwoData)
{
	CirculerBuffer_put(1);
	CirculerBuffer_put(2);
	TEST_ASSERT_EQUAL_INT(1, buffer[0]);
	TEST_ASSERT_EQUAL_INT(2, buffer[1]);
}

TEST(CirculerBuffer, GetTwoData)
{
	CirculerBuffer_put(1);
	CirculerBuffer_put(2);
	TEST_ASSERT_EQUAL_INT(1, CirculerBuffer_get());
	TEST_ASSERT_EQUAL_INT(2, CirculerBuffer_get());
}

// 空であるかどうかを確認する
TEST(CirculerBuffer, BufferIsEmpty)
{
	TEST_ASSERT_TRUE(CirculerBuffer_isEmpty());
}

// 空でないことを確認する
TEST(CirculerBuffer, BufferIsNotEmpty) 
{
	CirculerBuffer_put(1);
	TEST_ASSERT_FALSE(CirculerBuffer_isEmpty());
}
