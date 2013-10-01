/*******************************************************
 * 
 * CirculerBuffer.c
 *
 *******************************************************/
#include "CirculerBuffer.h"

static int *g_buf;                  // �o�b�t�@�L���p�|�C���^
static unsigned int i_max;          // �o�b�t�@�C���f�b�N�X�ő�l
static unsigned int put_i;          // �f�[�^�o�^�p�C���f�b�N�X
static unsigned int get_i;          // �f�[�^���o���p�C���f�b�N�X
static int is_empty_flg;            // �f�[�^��t���O

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
	g_buf = buf;
	i_max = buf_size - 1;

	put_i = 0;
	get_i = 0;
    is_empty_flg = EMPTY;
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
    if (is_empty_flg == NOT_EMPTY) {
        if (put_i == get_i) {
            return NG;
        }
    }

    // �f�[�^�̓o�^
	g_buf[put_i] = data;
    is_empty_flg = NOT_EMPTY;

    // �f�[�^�o�^�p�C���f�b�N�X�̍X�V
    if (put_i == i_max) {
        put_i = 0;
    } else {
        put_i++;
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
	data = g_buf[get_i];

    // �f�[�^���o���p�C���f�b�N�X�̍X�V
    if (get_i == i_max) {
        get_i = 0;
    } else {
        get_i++;
    }

    if (get_i == put_i) {
        // ���o���f�[�^�������Ȃ����̂ŋ�t���O���X�V
        is_empty_flg = EMPTY;
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
	return is_empty_flg;
}
