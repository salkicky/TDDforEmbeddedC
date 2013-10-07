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
    int is_empty_flg;               // �f�[�^��t���O
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
    context.is_empty_flg = EMPTY;
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
    if (context.is_empty_flg == NOT_EMPTY) {
        if (context.wp == context.rp) {
            return NG;
        }
    }

    // �f�[�^�̓o�^
	context.buf[context.wp] = data;
    context.is_empty_flg = NOT_EMPTY;

    // �f�[�^�o�^�p�C���f�b�N�X�̍X�V
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
 * [out] data : FIFO������o�����f�[�^
 *
 * ��������
 *      FIFO����f�[�^�����o���ꍇ�ɂ́A�K��
 *      ��łȂ����Ƃ��m�F���邱�ƁB
 ************************************************/
int CirculerBuffer_get(void)
{
	int data;

    // �f�[�^���o��
	data = context.buf[context.rp];

    // �f�[�^���o���p�C���f�b�N�X�̍X�V
    if (context.rp == (context.buf_size - 1)) {
        context.rp = 0;
    } else {
        context.rp++;
    }

    if (context.rp == context.wp) {
        // ���o���f�[�^�������Ȃ����̂ŋ�t���O���X�V
        context.is_empty_flg = EMPTY;
    }

	return data;
}

/************************************************
 * FIFO���󂩂ǂ�����Ԃ�
 *
 * [out] : �o�b�t�@��ԁiEMPTY:��ANOT_EMPTY:�f�[�^����j
 ************************************************/
int CirculerBuffer_isEmpty(void)
{
	return context.is_empty_flg;
}
