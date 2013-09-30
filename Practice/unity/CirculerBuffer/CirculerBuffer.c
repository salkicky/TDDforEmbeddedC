/*******************************************************
 * 
 * CirculerBuffer.c
 *
 *******************************************************/
#include "CirculerBuffer.h"

static int *g_bufp;
static unsigned int g_put_index;
static unsigned int g_get_index;


void CirculerBuffer_create(int *bufp, unsigned int buf_size)
{
	g_bufp = bufp;
	g_put_index = 0;
	g_get_index = 0;
}


void CirculerBuffer_put(int data)
{
	g_bufp[g_put_index] = data;
	g_put_index++;
}


int CirculerBuffer_get(void)
{
	int data;

	data = g_bufp[g_get_index];
	g_get_index++;

	return data;
}

int CirculerBuffer_isEmpty(void)
{
	return (g_put_index == g_get_index);
}
