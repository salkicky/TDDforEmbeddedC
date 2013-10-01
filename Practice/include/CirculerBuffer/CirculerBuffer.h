/*******************************************************
 * 
 * CirculerBuffer.h
 *
 *******************************************************/
#ifndef CIRCULER_BUFFER_H
#define CIRCULER_BUFFER_H

#define EMPTY       1
#define NOT_EMPTY   0

#define OK          0
#define NG         -1

/************************************************
 * FIFO�𐶐�����
 *
 * [in] buf : int�^�z��̃o�b�t�@�ւ̃|�C���^
 * [in] buf_size : �o�b�t�@�T�C�Y
 * 
 * ��������
 *      buf���w���o�b�t�@�̈�́AFIFO�o�b�t�@�𗘗p���͉�����Ȃ����ƁB
 *      buf_size ��1�ȏ���w�肷�邱�ƁB
 ************************************************/
void CirculerBuffer_create(int *buf, unsigned int buf_size);

/************************************************
 * FIFO�փf�[�^��o�^����
 *
 * [in] data : FIFO�֓o�^����f�[�^
 * [out] �o�^���ʁiOK:�o�^�����ANG:�o�^���s�j
 ************************************************/
int CirculerBuffer_put(int data);

/************************************************
 * FIFO����f�[�^�����o��
 *
 * [out] data : FIFO������o�����f�[�^
 *
 * ��������
 *      FIFO����f�[�^�����o���ꍇ�ɂ́A�K��
 *      ��łȂ����Ƃ��m�F���邱�ƁB
 ************************************************/
int CirculerBuffer_get(void);

/************************************************
 * FIFO���󂩂ǂ�����Ԃ�
 *
 * [out] : �o�b�t�@��ԁiEMPTY:��ANOT_EMPTY:�f�[�^����j
 ************************************************/
int CirculerBuffer_isEmpty(void);


#endif  /* CIRCULER_BUFFER_H */
