//================================================
//
//3Dアクション(wall.h)
//Author:門脇勇斗
//
//================================================
#ifndef _WALL_H_
#define _WALL_H_

#include "main.h"

//================================================
//マクロ定義
//================================================
#define MAX_WALL (4)				//壁の最大数

//================================================
//壁の構造体
//================================================
typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
	D3DXMATRIX  mtxWorld;
	bool bUse;
} Wall;

//================================================
//プロトタイプ宣言
//================================================
void InitWall(void);								//壁の初期化処理
void UninitWall(void);								//壁の終了処理
void UpdataWall(void);								//壁の更新処理
void DrawWall(void);								//壁の描画処理
void SetWall(D3DXVECTOR3 pos, D3DXVECTOR3 rot);		//壁の設定処理

#endif