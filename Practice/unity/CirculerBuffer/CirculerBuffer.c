/*******************************************************
 * 
 * CirculerBuffer.c
 *
 *******************************************************/
#include "CirculerBuffer.h"

static  struct CirculerBuffer_ContextTag *contextp;

/************************************************
 * FIFOを生成する
 *
 * [in] context : 管理用エリアへのポインタ
 * [in] buf : int型配列のバッファへのポインタ
 * [in] buf_size : バッファサイズ
 * 
 * 制限事項
 *      bufが指すバッファ領域は、FIFOバッファを利用中は解放しないこと。
 *      buf_size は1以上を指定すること。
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
 * FIFOへデータを登録する
 *
 * [in] data : FIFOへ登録するデータ
 * [out] 登録結果（OK:登録成功、NG:登録失敗）
 ************************************************/
int CirculerBuffer_put(int data)
{
    // バッファオーバーフローの確認
    if (contextp->size == contextp->buf_size) {
		return NG;
    }

    // データの登録
	contextp->buf[contextp->wp] = data;

    // データ登録用インデックスの更新
    contextp->size++;
    if (contextp->wp == (contextp->buf_size - 1)) {
        contextp->wp = 0;
    } else {
        contextp->wp++;
    }

	return OK;
}

/************************************************
 * FIFOからデータを取り出す
 *
 * [in] *data : FIFOから取り出したデータ
 * [out] 取り出し結果（OK:成功、NG:失敗）
 *
 * 制限事項
 *      FIFOからデータを取り出す場合には、必ず
 *      空でないことを確認すること。
 ************************************************/
int CirculerBuffer_get(int *data)
{
	if (contextp->size == 0) {
		return NG;
	}

    // データ取り出し
	*data = contextp->buf[contextp->rp];

    // データ取り出し用インデックスの更新
	contextp->size--;
    if (contextp->rp == (contextp->buf_size - 1)) {
        contextp->rp = 0;
    } else {
        contextp->rp++;
    }

	return OK;
}

/************************************************
 * FIFOの登録可能データサイズを返す
 *
 * [out] : 登録可能データサイズ
 ************************************************/
int CirculerBuffer_getCapacity(void)
{
	return (contextp->buf_size - contextp->size);
}
