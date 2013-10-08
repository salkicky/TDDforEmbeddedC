/*******************************************************
 * 
 * CirculerBuffer.h
 *
 *******************************************************/
#ifndef CIRCULER_BUFFER_H
#define CIRCULER_BUFFER_H

#define OK          0
#define NG         -1

struct CirculerBuffer_ContextTag {
    int *buf;           // �o�b�t�@�L���p�|�C���^ 
    int buf_size;       // �o�b�t�@�T�C�Y
    int wp;             // �f�[�^�������ݗp�C���f�b�N�X
    int rp;             // �f�[�^�ǂݏo���p�C���f�b�N�X
    int size;
};

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
void CirculerBuffer_create(struct CirculerBuffer_ContextTag *context, int *buf, unsigned int buf_size);

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
 * [in] *data : FIFO������o�����f�[�^
 * [out] ���o�����ʁiOK:�����ANG:���s�j
 *
 * ��������
 *      FIFO����f�[�^�����o���ꍇ�ɂ́A�K��
 *      ��łȂ����Ƃ��m�F���邱�ƁB
 ************************************************/
int CirculerBuffer_get(int *data);

/************************************************
 * FIFO�̓o�^�\�f�[�^�T�C�Y��Ԃ�
 *
 * [out] : �o�^�\�f�[�^�T�C�Y
 ************************************************/
int CirculerBuffer_getCapacity(void);


#endif  /* CIRCULER_BUFFER_H */
