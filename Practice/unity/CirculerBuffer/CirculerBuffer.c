/*******************************************************
 * 
 * CirculerBuffer.c
 *
 *******************************************************/
#include "CirculerBuffer.h"

static int *g_buf;                  // バッファ記憶用ポインタ
static unsigned int i_max;          // バッファインデックス最大値
static unsigned int put_i;          // データ登録用インデックス
static unsigned int get_i;          // データ取り出し用インデックス
static int is_empty_flg;            // データ空フラグ

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
	g_buf = buf;
	i_max = buf_size - 1;

	put_i = 0;
	get_i = 0;
    is_empty_flg = EMPTY;
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
    if (is_empty_flg == NOT_EMPTY) {
        if (put_i == get_i) {
            return NG;
        }
    }

    // データの登録
	g_buf[put_i] = data;
    is_empty_flg = NOT_EMPTY;

    // データ登録用インデックスの更新
    if (put_i == i_max) {
        put_i = 0;
    } else {
        put_i++;
    }

	return OK;
}

/************************************************
 * FIFOからデータを取り出す
 *
 * [out] data : FIFOから取り出したデータ
 *
 * 制限事項
 *      FIFOからデータを取り出す場合には、必ず
 *      空でないことを確認すること。
 ************************************************/
int CirculerBuffer_get(void)
{
	int data;

    // データ取り出し
	data = g_buf[get_i];

    // データ取り出し用インデックスの更新
    if (get_i == i_max) {
        get_i = 0;
    } else {
        get_i++;
    }

    if (get_i == put_i) {
        // 取り出すデータが無くなったので空フラグを更新
        is_empty_flg = EMPTY;
    }

	return data;
}

/************************************************
 * FIFOが空かどうかを返す
 *
 * [out] : バッファ状態（EMPTY:空、NOT_EMPTY:データあり）
 ************************************************/
int CirculerBuffer_isEmpty(void)
{
	return is_empty_flg;
}
