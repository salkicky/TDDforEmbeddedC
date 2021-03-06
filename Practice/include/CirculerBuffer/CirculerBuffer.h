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
    int *buf;           // バッファ記憶用ポインタ 
    int buf_size;       // バッファサイズ
    int wp;             // データ書き込み用インデックス
    int rp;             // データ読み出し用インデックス
    int size;
};

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
void CirculerBuffer_create(struct CirculerBuffer_ContextTag *context, int *buf, unsigned int buf_size);

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
 * [in] *data : FIFOから取り出したデータ
 * [out] 取り出し結果（OK:成功、NG:失敗）
 *
 * 制限事項
 *      FIFOからデータを取り出す場合には、必ず
 *      空でないことを確認すること。
 ************************************************/
int CirculerBuffer_get(int *data);

/************************************************
 * FIFOの登録可能データサイズを返す
 *
 * [out] : 登録可能データサイズ
 ************************************************/
int CirculerBuffer_getCapacity(void);


#endif  /* CIRCULER_BUFFER_H */
