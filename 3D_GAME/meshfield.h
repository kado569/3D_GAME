//================================================
//
//3Dアクション(meshfield.h)
//Author:門脇勇斗
//
//================================================
#ifndef _MESHFILD_H_
#define _MESHFILD_H_

#include "main.h"

//================================================
//メッシュの構造体
//================================================
typedef struct
{
	D3DXVECTOR3 pos;			//頂点座標
	D3DXVECTOR3 rot;			//向き
	D3DXMATRIX mtxWorld;		//ワールドマトリックス
}Meshfield;

//================================================
//マクロ定義
//================================================
#define MESHFIELD_X_BLOCK	(2)	//X方向のブロック数
#define MESHFIELD_Z_BLOCK	(2)	//Z方向のブロック数
#define MESHFIELD_VERTEX_NUM	((MESHFIELD_X_BLOCK + 1) * (MESHFIELD_Z_BLOCK + 1))
#define MESHFIELD_INDEX_NUM		(((MESHFIELD_X_BLOCK + 1) * 2 * MESHFIELD_Z_BLOCK)  + ( MESHFIELD_Z_BLOCK - 1) * 2)
#define MESHFIELD_PRIMITIVE_NUM	(MESHFIELD_X_BLOCK * MESHFIELD_Z_BLOCK * 2 + (MESHFIELD_Z_BLOCK - 1) * ((MESHFIELD_X_BLOCK * MESHFIELD_X_BLOCK) -2))

//================================================
//プロトタイプ宣言
//================================================
void InitMeshfield(void);
void UninitMeshfield(void);
void UpdateMeshfield(void);
void DrawMeshfield(void);

#endif