//================================================
//
//3Dアクション(effect.cpp)
//Author:門脇勇斗
//
//================================================
#include "effect.h"
#include "main.h"

//================================================
//グローバル変数
//================================================
LPDIRECT3DTEXTURE9 g_pTextureEffect = NULL;				//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEffect = NULL;		//頂点バッファへのポインタ
Effect g_Effect[MAX_EFFECT];

//================================================
//エフェクトの初期化設定
//================================================
void InitEffect(void)
{
	//デバイスの取得 
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	////テクスチャ読み込み 
	//D3DXCreateTextureFromFile(pDevice,
	//	"data/shadow000.jpg",
	//	&g_pTextureEffect);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * 10,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffEffect,
		NULL);

	VERTEX_3D * pVtx;							//頂点情報のポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

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
	g_pVtxBuffEffect->Unlock();
}

//================================================
//エフェクトの終了処理
//================================================
void UninitEffect(void)
{
	//バッファ破棄
	if (g_pVtxBuffEffect != NULL)
	{
		g_pVtxBuffEffect->Release();
		g_pVtxBuffEffect = NULL;
	}

	//テクスチャ破棄
	if (g_pTextureEffect != NULL)
	{
		g_pTextureEffect->Release();
		g_pTextureEffect = NULL;
	}
}

//================================================
//エフェクトの更新処理
//================================================
void UpdateEffect(void)
{

}

//================================================
//エフェクトの描画処理
//================================================
void DrawEffect(void)
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
	pDevice->SetTexture(0, g_pTextureEffect);

	for (int nCntEffect = 0; nCntEffect <MAX_EFFECT; nCntEffect++)
	{
		if (g_Effect[nCntEffect].bUse == true)
		{
			//ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_Effect[nCntEffect].mtxWorld);

			//位置を反転
			D3DXMatrixTranslation(&mtxTrans, g_Effect[nCntEffect].pos.x, g_Effect[nCntEffect].pos.y, g_Effect[nCntEffect].pos.z);
			D3DXMatrixMultiply(&g_Effect[nCntEffect].mtxWorld, &g_Effect[nCntEffect].mtxWorld, &mtxTrans);

			//ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_Effect[nCntEffect].mtxWorld);

			//頂点バッファをデータストリームに設定
			pDevice->SetStreamSource(0, g_pVtxBuffEffect, 0, sizeof(VERTEX_3D));

			//頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);

			//テクスチャ設定
			pDevice->SetTexture(0, g_pTextureEffect);

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
//エフェクトの設定
//================================================
//void SetEffect(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 move, D3DXCOLOR col)
//{
//	for (int nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
//	{
//		if (g_Effect[nCntEffect].bUse == false)
//		{
//			
//			g_Effect[nCntEffect].bUse = true;
//			break;
//		}
//	}
//}
