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
struct CirculerBuffer_ContextTag context;

void get_data_expected_as(int expected_data)
{
	int data;

	TEST_ASSERT_EQUAL_INT(OK, CirculerBuffer_get(&data));
	TEST_ASSERT_EQUAL_INT(expected_data, data);
}

//////////////////////////////////////////////////
TEST_GROUP(CirculerBuffer);

/* set up */
TEST_SETUP(CirculerBuffer)
{
	CirculerBuffer_create(&context, buffer, BUF_MAX_SIZE);
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
	CirculerBuffer_put(1);
	get_data_expected_as(1);
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
	CirculerBuffer_put(1);
	CirculerBuffer_put(2);
	get_data_expected_as(1);
	get_data_expected_as(2);
}

// 空であるかどうかを確認する
TEST(CirculerBuffer, BufferIsEmpty)
{
	TEST_ASSERT_EQUAL_INT(BUF_MAX_SIZE, CirculerBuffer_getCapacity());
}

// 空でないことを確認する
TEST(CirculerBuffer, BufferIsNotEmpty) 
{
	CirculerBuffer_put(1);
	TEST_ASSERT_EQUAL_INT(BUF_MAX_SIZE - 1, CirculerBuffer_getCapacity());
}

// バッファサイズよりも大きい回数分、putを行った場合の動作（バッファ溢れ無し） 
TEST(CirculerBuffer, NotDestroyMemoryArea)
{
	int buf[3] = {-1, -1, -1};
	CirculerBuffer_create(&context, buf, 2);

	CirculerBuffer_put(1);
	CirculerBuffer_put(2);
	get_data_expected_as(1);
	CirculerBuffer_put(3);
	get_data_expected_as(2);
	get_data_expected_as(3);
	TEST_ASSERT_EQUAL_INT(-1, buf[2]);
}

// バッファサイズ以上にデータを登録した場合の動作
TEST(CirculerBuffer, BufferOverRun)
{
	int buf[3] = {-1, -1 -1};
	CirculerBuffer_create(&context, buf, 2);

	TEST_ASSERT_EQUAL_INT(OK, CirculerBuffer_put(1));
	TEST_ASSERT_EQUAL_INT(OK, CirculerBuffer_put(2));
	TEST_ASSERT_EQUAL_INT(NG, CirculerBuffer_put(3));
}

// 登録データ数以上にデータを取り出そうとした場合の動作
TEST(CirculerBuffer, GetFromEmptyBuffer)
{
	int data;

	TEST_ASSERT_EQUAL_INT(OK, CirculerBuffer_put(1));
	get_data_expected_as(1);

	TEST_ASSERT_EQUAL_INT(NG, CirculerBuffer_get(&data));
}

TEST(CirculerBuffer, UsualTest)
{
	TEST_ASSERT_EQUAL_INT(OK, CirculerBuffer_put(1));
	TEST_ASSERT_EQUAL_INT(OK, CirculerBuffer_put(2));
	TEST_ASSERT_EQUAL_INT(OK, CirculerBuffer_put(3));
	get_data_expected_as(1);
	TEST_ASSERT_EQUAL_INT(OK, CirculerBuffer_put(4));
	TEST_ASSERT_EQUAL_INT(OK, CirculerBuffer_put(-2));
	get_data_expected_as(2);
	TEST_ASSERT_EQUAL_INT(OK, CirculerBuffer_put(6));
	TEST_ASSERT_EQUAL_INT(OK, CirculerBuffer_put(-1));
	get_data_expected_as(3);
	get_data_expected_as(4);
	get_data_expected_as(-2);
}
