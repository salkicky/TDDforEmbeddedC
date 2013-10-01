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
 * FIFOを生成する
 *
 * [in] buf : int型配列のバッファへのポインタ
 * [in] buf_size : バッファサイズ
 * 
 * 制限事項
 *      bufが指すバッファ領域は、FIFOバッファを利用中は解放しないこと。
 *      buf_size は1以上を指定すること。
 ************************************************/
void CirculerBuffer_create(int *buf, unsigned int buf_size);

/************************************************
 * FIFOへデータを登録する
 *
 * [in] data : FIFOへ登録するデータ
 * [out] 登録結果（OK:登録成功、NG:登録失敗）
 ************************************************/
int CirculerBuffer_put(int data);

/************************************************
 * FIFOからデータを取り出す
 *
 * [out] data : FIFOから取り出したデータ
 *
 * 制限事項
 *      FIFOからデータを取り出す場合には、必ず
 *      空でないことを確認すること。
 ************************************************/
int CirculerBuffer_get(void);

/************************************************
 * FIFOが空かどうかを返す
 *
 * [out] : バッファ状態（EMPTY:空、NOT_EMPTY:データあり）
 ************************************************/
int CirculerBuffer_isEmpty(void);


#endif  /* CIRCULER_BUFFER_H */
