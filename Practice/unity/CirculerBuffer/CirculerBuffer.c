/*******************************************************
 * 
 * CirculerBuffer.c
 *
 *******************************************************/
#include "CirculerBuffer.h"

struct CirculerBuffer_ContextTag {
    int *buf;                       // バッファ記憶用ポインタ 
    unsigned int buf_size;          // バッファサイズ
    unsigned int wp;                // データ書き込み用インデックス
    unsigned int rp;                // データ読み出し用インデックス
    int size;
};

static  struct CirculerBuffer_ContextTag context;

/************************************************
 * FIFOを生成する
 *
 * [in] buf : int型配列のバッファへのポインタ
 * [in] buf_size : バッファサイズ
 * 
 * 制限事項
 *      bufが指すバッファ領域は、FIFOバッファを利用中は解放しないこと。
 *      buf_size は1以上を指定すること。
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
 * FIFOへデータを登録する
 *
 * [in] data : FIFOへ登録するデータ
 * [out] 登録結果（OK:登録成功、NG:登録失敗）
 ************************************************/
int CirculerBuffer_put(int data)
{
    // バッファオーバーフローの確認
    if (context.size == context.buf_size) {
        if (context.wp == context.rp) {
            return NG;
        }
    }

    // データの登録
	context.buf[context.wp] = data;

    // データ登録用インデックスの更新
    context.size++;
    if (context.wp == (context.buf_size - 1)) {
        context.wp = 0;
    } else {
        context.wp++;
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
	if (context.size == 0) {
		return NG;
	}

    // データ取り出し
	*data = context.buf[context.rp];

    // データ取り出し用インデックスの更新
	context.size--;
    if (context.rp == (context.buf_size - 1)) {
        context.rp = 0;
    } else {
        context.rp++;
    }

	return OK;
}

/************************************************
 * FIFOが空かどうかを返す
 *
 * [out] : バッファ状態（EMPTY:空、NOT_EMPTY:データあり）
 ************************************************/
int CirculerBuffer_isEmpty(void)
{
	return context.size ? NOT_EMPTY : EMPTY;
}
