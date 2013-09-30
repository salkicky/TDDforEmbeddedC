/*******************************************************
 * 
 * CirculerBuffer.c
 *
 *******************************************************/
#include "CirculerBuffer.h"

static int *g_bufp;


void CirculerBuffer_create(int *bufp)
{
	g_bufp = bufp;
}


void CirculerBuffer_put(int data)
{
	*g_bufp = data;
}


int CirculerBuffer_get(void)
{
	return 1;
}
