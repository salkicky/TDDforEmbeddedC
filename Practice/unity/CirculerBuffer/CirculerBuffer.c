/*******************************************************
 * 
 * CirculerBuffer.c
 *
 *******************************************************/
#include "CirculerBuffer.h"

static int *g_buf;
static unsigned int g_i_max;
static unsigned int g_put_i;
static unsigned int g_get_i;
static unsigned int g_is_empty_flg;


void CirculerBuffer_create(int *buf, unsigned int buf_size)
{
	g_buf = buf;
	g_i_max = buf_size - 1;
	g_put_i = 0;
	g_get_i = 0;
    g_is_empty_flg = 1;
}


int CirculerBuffer_put(int data)
{
    if (g_is_empty_flg == 0) {
        if (g_put_i == g_get_i) {
            return -1;
        }
    }

	g_buf[g_put_i] = data;
    g_is_empty_flg = 0;

    if (g_put_i == g_i_max) {
        g_put_i = 0;
    } else {
        g_put_i++;
    }

	return 0;
}


int CirculerBuffer_get(void)
{
	int data;

	data = g_buf[g_get_i];

    if (g_get_i == g_i_max) {
        g_get_i = 0;
    } else {
        g_get_i++;
    }

    if (g_get_i == g_put_i) {
        g_is_empty_flg = 1;
    }

	return data;
}


int CirculerBuffer_isEmpty(void)
{
	return (g_put_i == g_get_i);
}
