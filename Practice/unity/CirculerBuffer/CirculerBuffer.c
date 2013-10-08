/*******************************************************
 * 
 * CirculerBuffer.c
 *
 *******************************************************/
#include "CirculerBuffer.h"

struct CirculerBuffer_ContextTag {
    int *buf;                       // �o�b�t�@�L���p�|�C���^ 
    unsigned int buf_size;          // �o�b�t�@�T�C�Y
    unsigned int wp;                // �f�[�^�������ݗp�C���f�b�N�X
    unsigned int rp;                // �f�[�^�ǂݏo���p�C���f�b�N�X
    int size;
};

static  struct CirculerBuffer_ContextTag context;

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
void CirculerBuffer_create(int *buf, unsigned int buf_size)
{
    context.buf = buf;
    context.buf_size = buf_size;
    context.wp = 0;
    context.rp = 0;
    context.size = 0;
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
    if (context.size == context.buf_size) {
        if (context.wp == context.rp) {
            return NG;
        }
    }

    // �f�[�^�̓o�^
	context.buf[context.wp] = data;

    // �f�[�^�o�^�p�C���f�b�N�X�̍X�V
    context.size++;
    if (context.wp == (context.buf_size - 1)) {
        context.wp = 0;
    } else {
        context.wp++;
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
	if (context.size == 0) {
		return NG;
	}

    // �f�[�^���o��
	*data = context.buf[context.rp];

    // �f�[�^���o���p�C���f�b�N�X�̍X�V
	context.size--;
    if (context.rp == (context.buf_size - 1)) {
        context.rp = 0;
    } else {
        context.rp++;
    }

	return OK;
}

/************************************************
 * FIFO���󂩂ǂ�����Ԃ�
 *
 * [out] : �o�b�t�@��ԁiEMPTY:��ANOT_EMPTY:�f�[�^����j
 ************************************************/
int CirculerBuffer_isEmpty(void)
{
	return context.size ? NOT_EMPTY : EMPTY;
}
