//================================================
//
//3Dアクション(effect.h)
//Author:門脇勇斗
//
//================================================
#ifndef _EFFECT_H_
#define _EFFECT_H_

#include "main.h"

//================================================
//マクロ定義
//================================================
#define MAX_EFFECT		(10)	//影の最大数

//================================================
//エフェクトの構造体
//================================================
typedef struct
{
	D3DXVECTOR3 pos;			//頂点座標
	D3DXMATRIX mtxWorld;		//ワールドマトリックス
	bool bUse;
}Effect;

//================================================
//プロトタイプ宣言
//================================================
void InitEffect(void);
void UninitEffect(void);
void UpdateEffect(void);
void DrawEffect(void);
int SetEffect(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 move, D3DXCOLOR col);

#endif