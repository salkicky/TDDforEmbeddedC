/*******************************************************
 * 
 * CirculerBuffer.c
 *
 *******************************************************/
#include "CirculerBuffer.h"

static int *g_buf;
static int g_buf_size;
static unsigned int g_put_index;
static unsigned int g_get_index;


void CirculerBuffer_create(int *buf, unsigned int buf_size)
{
	g_buf = buf;
	g_buf_size = buf_size;
	g_put_index = 0;
	g_get_index = 0;
}


int CirculerBuffer_put(int data)
{
	g_buf[g_put_index] = data;
	
	g_put_index++;
	if (g_buf_size <= g_put_index) {
		g_put_index = 0;
	}

	return 0;
}


int CirculerBuffer_get(void)
{
	int data;

	data = g_buf[g_get_index];

	g_get_index++;
	if (g_buf_size <= g_get_index) {
		g_get_index = 0;
	}

	return data;
}


int CirculerBuffer_isEmpty(void)
{
	return (g_put_index == g_get_index);
}
