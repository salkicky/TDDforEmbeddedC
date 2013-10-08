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

// �f�[�^���P�o�^����B
TEST(CirculerBuffer, PutOneData)
{
	CirculerBuffer_put(1);
	TEST_ASSERT_EQUAL_INT(1, buffer[0]);
}

// �ʂ̃f�[�^���P�o�^����B
TEST(CirculerBuffer, PutOneData2)
{
	CirculerBuffer_put(2);
	TEST_ASSERT_EQUAL_INT(2, buffer[0]);
}

// FIFO����f�[�^���P���o��
TEST(CirculerBuffer, GetOneData)
{
	CirculerBuffer_put(1);
	get_data_expected_as(1);
}

// FIFO�փf�[�^���Q�o�^����B
TEST(CirculerBuffer, PutTwoData)
{
	CirculerBuffer_put(1);
	CirculerBuffer_put(2);
	TEST_ASSERT_EQUAL_INT(1, buffer[0]);
	TEST_ASSERT_EQUAL_INT(2, buffer[1]);
}

// FIFO�փf�[�^���Q�o�^���A�Q���o��
TEST(CirculerBuffer, GetTwoData)
{
	CirculerBuffer_put(1);
	CirculerBuffer_put(2);
	get_data_expected_as(1);
	get_data_expected_as(2);
}

// ��ł��邩�ǂ������m�F����
TEST(CirculerBuffer, BufferIsEmpty)
{
	TEST_ASSERT_EQUAL_INT(BUF_MAX_SIZE, CirculerBuffer_getCapacity());
}

// ��łȂ����Ƃ��m�F����
TEST(CirculerBuffer, BufferIsNotEmpty) 
{
	CirculerBuffer_put(1);
	TEST_ASSERT_EQUAL_INT(BUF_MAX_SIZE - 1, CirculerBuffer_getCapacity());
}

// �o�b�t�@�T�C�Y�����傫���񐔕��Aput���s�����ꍇ�̓���i�o�b�t�@��ꖳ���j 
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

// �o�b�t�@�T�C�Y�ȏ�Ƀf�[�^��o�^�����ꍇ�̓���
TEST(CirculerBuffer, BufferOverRun)
{
	int buf[3] = {-1, -1 -1};
	CirculerBuffer_create(&context, buf, 2);

	TEST_ASSERT_EQUAL_INT(OK, CirculerBuffer_put(1));
	TEST_ASSERT_EQUAL_INT(OK, CirculerBuffer_put(2));
	TEST_ASSERT_EQUAL_INT(NG, CirculerBuffer_put(3));
}

// �o�^�f�[�^���ȏ�Ƀf�[�^�����o�����Ƃ����ꍇ�̓���
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
