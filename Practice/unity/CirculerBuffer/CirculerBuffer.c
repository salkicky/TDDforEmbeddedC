/*******************************************************
 * 
 * CirculerBuffer.c
 *
 *******************************************************/
#include "CirculerBuffer.h"

static  struct CirculerBuffer_ContextTag *cp;

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
	cp = context;

    cp->buf = buf;
    cp->buf_size = buf_size;
    cp->wp = 0;
    cp->rp = 0;
    cp->size = 0;
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
    if (cp->size == cp->buf_size) {
		return NG;
    }

    // �f�[�^�̓o�^
	cp->buf[cp->wp] = data;

    // �f�[�^�o�^�p�C���f�b�N�X�̍X�V
    cp->size++;
    if (cp->wp == (cp->buf_size - 1)) {
        cp->wp = 0;
    } else {
        cp->wp++;
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
	if (cp->size == 0) {
		return NG;
	}

    // �f�[�^���o��
	*data = cp->buf[cp->rp];

    // �f�[�^���o���p�C���f�b�N�X�̍X�V
	cp->size--;
    if (cp->rp == (cp->buf_size - 1)) {
        cp->rp = 0;
    } else {
        cp->rp++;
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
	return (cp->buf_size - cp->size);
}
