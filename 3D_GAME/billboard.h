//================================================
//
//3Dアクション(billboard.cpp)
//Author:門脇勇斗
//
//================================================
#ifndef _BILLBOARD_H_
#define _BILLBOARD_H_

#include "main.h"

//================================================
//マクロ定義
//================================================
#define MAX_BILLBOARD	(256)	//ビルボードの最大数

//================================================
//ビルボードの構造体
//================================================
typedef struct
{
	D3DXVECTOR3 pos;		//位置
	D3DXVECTOR3 rot;		//方向
	D3DXMATRIX mtxWorld;	//ワールドマトリックス
	bool bUse;				//使用しているか
	int IdxShadow;			//影の設置
}Billboard;

//================================================
//プロトタイプ宣言
//================================================
void InitBillboard(void);
void UninitBillboard(void);
void UpdateBillboard(void);
void DrawBillboard(void);
void SetBillboard(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
#endif