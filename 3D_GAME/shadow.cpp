//================================================
//
//3Dアクション(shadow.cpp)
//Author:門脇勇斗
//
//================================================
#include "shadow.h"
#include "main.h"

//================================================
//グローバル変数
//================================================
LPDIRECT3DTEXTURE9 g_pTextureShadow = NULL;				//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffShadow = NULL;		//頂点バッファへのポインタ
Shadow g_Shadow[MAX_SHADOW];

//================================================
//影の初期化設定
//================================================
void InitShadow(void)
{
	//デバイスの取得 
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//テクスチャ読み込み 
	D3DXCreateTextureFromFile(pDevice,
		"data/shadow000.jpg",
		&g_pTextureShadow);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * 10,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffShadow,
		NULL);

	VERTEX_3D * pVtx;							//頂点情報のポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffShadow->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(-20.0f, 0.2f, 20.0f);
	pVtx[1].pos = D3DXVECTOR3(20.0f, 0.2f, 20.0f);
	pVtx[2].pos = D3DXVECTOR3(-20.0f, 0.2f, -20.0f);
	pVtx[3].pos = D3DXVECTOR3(20.0f, 0.2f, -20.0f);

	//各頂点の法線の設定
	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//頂点カラーの設定
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//バッファアンロック
	g_pVtxBuffShadow->Unlock();
}

//================================================
//影の終了処理
//================================================
void UninitShadow(void)
{
	//バッファ破棄
	if (g_pVtxBuffShadow != NULL)
	{
		g_pVtxBuffShadow->Release();
		g_pVtxBuffShadow = NULL;
	}

	//テクスチャ破棄
	if (g_pTextureShadow != NULL)
	{
		g_pTextureShadow->Release();
		g_pTextureShadow = NULL;
	}
}

//================================================
//影の更新処理
//================================================
void UpdateShadow(void)
{

}

//================================================
//影の描画処理
//================================================
void DrawShadow(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//計算用マトリックス
	D3DXMATRIX mtxRot, mtxTrans;

	//減算合成の設定
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	//テクスチャ設定
	pDevice->SetTexture(0, g_pTextureShadow);

	for (int nCntShadow = 0; nCntShadow <MAX_SHADOW; nCntShadow++)
	{
		if (g_Shadow[nCntShadow].bUse == true)
		{
			//ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_Shadow[nCntShadow].mtxWorld);

			//向きを反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot,g_Shadow[nCntShadow].rot.y,g_Shadow[nCntShadow].rot.x, g_Shadow[nCntShadow].rot.z);
			D3DXMatrixMultiply(&g_Shadow[nCntShadow].mtxWorld, &g_Shadow[nCntShadow].mtxWorld, &mtxRot);

			//位置を反転
			D3DXMatrixTranslation(&mtxTrans, g_Shadow[nCntShadow].pos.x, g_Shadow[nCntShadow].pos.y, g_Shadow[nCntShadow].pos.z);
			D3DXMatrixMultiply(&g_Shadow[nCntShadow].mtxWorld, &g_Shadow[nCntShadow].mtxWorld, &mtxTrans);

			//ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_Shadow[nCntShadow].mtxWorld);

			//頂点バッファをデータストリームに設定
			pDevice->SetStreamSource(0, g_pVtxBuffShadow, 0, sizeof(VERTEX_3D));

			//頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);

			//テクスチャ設定
			pDevice->SetTexture(0, g_pTextureShadow);

			//ポリゴン描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);		//プリミティブの種類
		}
	}
	//設定を元に戻す
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//テクスチャをもとに戻す
	pDevice->SetTexture(0, NULL);
}

//================================================
//影の設定
//================================================
int SetShadow(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	int nCntShadow;

	for (nCntShadow = 0; nCntShadow < 10; nCntShadow++)
	{
		if (g_Shadow[nCntShadow].bUse == false)
		{
			g_Shadow[nCntShadow].pos = pos;
			g_Shadow[nCntShadow].rot = rot;
			g_Shadow[nCntShadow].bUse = true;

			break;
		}
	}

	return nCntShadow;	//影の番号(index)を返す
}

//================================================
//影の位置の更新処理
//================================================
void SetPositionShadow(int nIdxShadow, D3DXVECTOR3 pos)
{
	g_Shadow[nIdxShadow].pos = pos;
}
