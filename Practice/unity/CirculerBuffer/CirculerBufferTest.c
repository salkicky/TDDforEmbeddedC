/*************************************************
 *
 * CirculerBufferTest.c
 *
 *
 **************************************************/

#include "unity_fixture.h"
#include <stdlib.h>
#include "CirculerBuffer.h"

#define BUF_MAX_SIZE  100
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

// データを１つ登録する。
TEST(CirculerBuffer, PutOneData)
{
	CirculerBuffer_put(1);
	TEST_ASSERT_EQUAL_INT(1, buffer[0]);
}

// 別のデータを１つ登録する。
TEST(CirculerBuffer, PutOneData2)
{
	CirculerBuffer_put(2);
	TEST_ASSERT_EQUAL_INT(2, buffer[0]);
}

// FIFOからデータを１つ取り出す
TEST(CirculerBuffer, GetOneData)
{
	int data;

	CirculerBuffer_put(1);
	CirculerBuffer_get(&data);
	TEST_ASSERT_EQUAL_INT(1, data);
}

// FIFOへデータを２つ登録する。
TEST(CirculerBuffer, PutTwoData)
{
	CirculerBuffer_put(1);
	CirculerBuffer_put(2);
	TEST_ASSERT_EQUAL_INT(1, buffer[0]);
	TEST_ASSERT_EQUAL_INT(2, buffer[1]);
}

// FIFOへデータを２つ登録し、２つ取り出す
TEST(CirculerBuffer, GetTwoData)
{
	int data;

	CirculerBuffer_put(1);
	CirculerBuffer_put(2);

	CirculerBuffer_get(&data);
	TEST_ASSERT_EQUAL_INT(1, data);
	
	CirculerBuffer_get(&data);
	TEST_ASSERT_EQUAL_INT(2, data);
}

// 空であるかどうかを確認する
TEST(CirculerBuffer, BufferIsEmpty)
{
	TEST_ASSERT_TRUE(EMPTY == CirculerBuffer_isEmpty());
}

// 空でないことを確認する
TEST(CirculerBuffer, BufferIsNotEmpty) 
{
	CirculerBuffer_put(1);
	TEST_ASSERT_FALSE(CirculerBuffer_isEmpty());
}

// バッファサイズよりも大きい回数分、putを行った場合の動作（バッファ溢れ無し） 
TEST(CirculerBuffer, NotDestroyMemoryArea)
{
	int buf[3] = {-1, -1, -1};
	int data;

	CirculerBuffer_create(buf, 2);

	CirculerBuffer_put(1);
	CirculerBuffer_put(2);
	CirculerBuffer_get(&data);
	TEST_ASSERT_EQUAL_INT(1, data);
	CirculerBuffer_put(3);
	CirculerBuffer_get(&data);
	TEST_ASSERT_EQUAL_INT(2, data);
	CirculerBuffer_get(&data);
	TEST_ASSERT_EQUAL_INT(3, data);
	TEST_ASSERT_EQUAL_INT(-1, buf[2]);
}

// バッファサイズ以上にデータを登録した場合の動作
TEST(CirculerBuffer, BufferOverRun)
{
	int buf[3] = {-1, -1 -1};
	CirculerBuffer_create(buf, 2);

	TEST_ASSERT_EQUAL_INT(OK, CirculerBuffer_put(1));
	TEST_ASSERT_EQUAL_INT(OK, CirculerBuffer_put(2));
	TEST_ASSERT_EQUAL_INT(NG, CirculerBuffer_put(3));
}

TEST(CirculerBuffer, UsualTest)
{
	int data;

	TEST_ASSERT_EQUAL_INT(OK, CirculerBuffer_put(1));
	TEST_ASSERT_EQUAL_INT(OK, CirculerBuffer_put(2));
	TEST_ASSERT_EQUAL_INT(OK, CirculerBuffer_put(3));
	CirculerBuffer_get(&data);
	TEST_ASSERT_EQUAL_INT(1, data);
	TEST_ASSERT_EQUAL_INT(OK, CirculerBuffer_put(4));
	TEST_ASSERT_EQUAL_INT(OK, CirculerBuffer_put(-2));
	CirculerBuffer_get(&data);
	TEST_ASSERT_EQUAL_INT(2, data);
	TEST_ASSERT_EQUAL_INT(OK, CirculerBuffer_put(6));
	TEST_ASSERT_EQUAL_INT(OK, CirculerBuffer_put(-1));
	CirculerBuffer_get(&data);
	TEST_ASSERT_EQUAL_INT(3, data);
	CirculerBuffer_get(&data);
	TEST_ASSERT_EQUAL_INT(4, data);
	CirculerBuffer_get(&data);
	TEST_ASSERT_EQUAL_INT(-2, data);
}
