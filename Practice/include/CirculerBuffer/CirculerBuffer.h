/*******************************************************
 * 
 * CirculerBuffer.h
 *
 *******************************************************/
#ifndef CIRCULER_BUFFER_H
#define CIRCULER_BUFFER_H

void CirculerBuffer_create(int *buf, unsigned int buf_size);
int CirculerBuffer_put(int data);
int CirculerBuffer_get(void);

int CirculerBuffer_isEmpty(void);


#endif  /* CIRCULER_BUFFER_H */
