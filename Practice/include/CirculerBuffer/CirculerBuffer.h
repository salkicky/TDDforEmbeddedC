/*******************************************************
 * 
 * CirculerBuffer.h
 *
 *******************************************************/
#ifndef CIRCULER_BUFFER_H
#define CIRCULER_BUFFER_H

void CirculerBuffer_create(int *buf);
void CirculerBuffer_put(int data);
int  CirculerBuffer_get(void);


#endif  /* CIRCULER_BUFFER_H */
