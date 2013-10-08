/*******************************************************
 * 
 * CirculerBuffer.c
 *
 *******************************************************/
#include "CirculerBuffer.h"

static  struct CirculerBuffer_ContextTag *contextp;

/************************************************
 * FIFO�𐶐�����
 *
 * [in] context : �Ǘ��p�G���A�ւ̃|�C���^
 * [in] buf : int�^�z��̃o�b�t�@�ւ̃|�C���^
 * [in] buf_size : �o�b�t�@�T�C�Y
 * 
 * ��������
 *      buf���w���o�b�t�@�̈�́AFIFO�o�b�t�@�𗘗p���͉�����Ȃ����ƁB
 *      buf_size ��1�ȏ���w�肷�邱�ƁB
 ************************************************/
void CirculerBuffer_create(struct CirculerBuffer_ContextTag *context, int *buf, unsigned int buf_size)
{
	contextp = context;

    contextp->buf = buf;
    contextp->buf_size = buf_size;
    contextp->wp = 0;
    contextp->rp = 0;
    contextp->size = 0;
}

/************************************************
 * FIFO�փf�[�^��o�^����
 *
 * [in] data : FIFO�֓o�^����f�[�^
 * [out] �o�^���ʁiOK:�o�^�����ANG:�o�^���s�j
 ************************************************/
int CirculerBuffer_put(int data)
{
    // �o�b�t�@�I�[�o�[�t���[�̊m�F
    if (contextp->size == contextp->buf_size) {
		return NG;
    }

    // �f�[�^�̓o�^
	contextp->buf[contextp->wp] = data;

    // �f�[�^�o�^�p�C���f�b�N�X�̍X�V
    contextp->size++;
    if (contextp->wp == (contextp->buf_size - 1)) {
        contextp->wp = 0;
    } else {
        contextp->wp++;
    }

	return OK;
}

/************************************************
 * FIFO����f�[�^�����o��
 *
 * [in] *data : FIFO������o�����f�[�^
 * [out] ���o�����ʁiOK:�����ANG:���s�j
 *
 * ��������
 *      FIFO����f�[�^�����o���ꍇ�ɂ́A�K��
 *      ��łȂ����Ƃ��m�F���邱�ƁB
 ************************************************/
int CirculerBuffer_get(int *data)
{
	if (contextp->size == 0) {
		return NG;
	}

    // �f�[�^���o��
	*data = contextp->buf[contextp->rp];

    // �f�[�^���o���p�C���f�b�N�X�̍X�V
	contextp->size--;
    if (contextp->rp == (contextp->buf_size - 1)) {
        contextp->rp = 0;
    } else {
        contextp->rp++;
    }

	return OK;
}

/************************************************
 * FIFO�̓o�^�\�f�[�^�T�C�Y��Ԃ�
 *
 * [out] : �o�^�\�f�[�^�T�C�Y
 ************************************************/
int CirculerBuffer_getCapacity(void)
{
	return (contextp->buf_size - contextp->size);
}
