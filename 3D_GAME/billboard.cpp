//================================================
//
//3Dアクション(billboard.cpp)
//Author:門脇勇斗
//
//================================================

#include"main.h"
#include"billboard.h"
#include"shadow.h"

//================================================
//グローバル変数
//================================================
LPDIRECT3DTEXTURE9 g_pTextureBillboard = NULL;		//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBillboard = NULL;	//頂点バッファへのポインタ
D3DXVECTOR3 g_posBillboard;							//位置
D3DXVECTOR3 g_rotBillboard;							//向き
D3DXMATRIX g_mtxWorldBillboard;						//ワールドマトリックス（行列）
Billboard g_aBillboard[MAX_BILLBOARD];				//ビルボードの最大数

//================================================
//ビルボードの初期化設定
//================================================
void InitBillboard(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//テクスチャ読み込み 
	D3DXCreateTextureFromFile(pDevice,
		"data//bullet000.png",
		&g_pTextureBillboard);

	//頂点バッファの設定
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_BILLBOARD,	//確保するバッファのサイズ 
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,	//頂点フォーマット
		D3DPOOL_MANAGED,
		&g_pVtxBuffBillboard,
		NULL);

	VERTEX_3D*pVtx;	//頂点情報のポインタ

					//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffBillboard->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntBillboard = 0; nCntBillboard < MAX_BILLBOARD; nCntBillboard++)
	{
		//方向設定
		g_rotBillboard = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//頂点座標設定
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//各頂点の法線設定（ベクトルの大きさは1にする）
		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

		//頂点カラーの設定
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;
	}
	//頂点バッファをアンロックする
	g_pVtxBuffBillboard->Unlock();

	SetBillboard(D3DXVECTOR3(0.0f, 20.0f, 20.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	for (int nCntBillboard = 0; nCntBillboard < MAX_BILLBOARD; nCntBillboard++)
	{
		g_aBillboard[nCntBillboard].IdxShadow = SetShadow(D3DXVECTOR3(g_aBillboard[nCntBillboard].pos.x, 0.1f, g_aBillboard[nCntBillboard].pos.z)
			, g_aBillboard[nCntBillboard].rot);
		break;
	}
}

//================================================
//ビルボードの終了処理
//================================================
void UninitBillboard(void)
{
	//バッファ破棄
	if (g_pVtxBuffBillboard != NULL)
	{
		g_pVtxBuffBillboard->Release();
		g_pVtxBuffBillboard = NULL;
	}

	//テクスチャ破棄
	if (g_pTextureBillboard != NULL)
	{
		g_pTextureBillboard->Release();
		g_pTextureBillboard = NULL;
	}
}

//================================================
//ビルボードの更新処理
//================================================
void UpdateBillboard(void)
{

}

//================================================
//ビルボードの描画処理
//================================================
void DrawBillboard(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//計算用マトリックス
	D3DXMATRIX mtxRot, mtxTrans;

	//テクスチャ設定
	pDevice->SetTexture(0, g_pTextureBillboard);

	for (int nCntBillboard = 0; nCntBillboard < MAX_BILLBOARD; nCntBillboard++)
	{
		if (g_aBillboard[nCntBillboard].bUse == true)
		{
			//ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_aBillboard[nCntBillboard].mtxWorld);
			D3DXMATRIX mtxView;
			pDevice->GetTransform(D3DTS_VIEW, &mtxView);

			//カメラの逆行列を設定
			g_aBillboard[nCntBillboard].mtxWorld._11 = mtxView._11;
			g_aBillboard[nCntBillboard].mtxWorld._12 = mtxView._21;
			g_aBillboard[nCntBillboard].mtxWorld._13 = mtxView._31;
			g_aBillboard[nCntBillboard].mtxWorld._21 = mtxView._12;
			g_aBillboard[nCntBillboard].mtxWorld._22 = mtxView._22;
			g_aBillboard[nCntBillboard].mtxWorld._23 = mtxView._32;
			g_aBillboard[nCntBillboard].mtxWorld._31 = mtxView._13;
			g_aBillboard[nCntBillboard].mtxWorld._32 = mtxView._23;
			g_aBillboard[nCntBillboard].mtxWorld._33 = mtxView._33;

			//位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_aBillboard[nCntBillboard].pos.x, g_aBillboard[nCntBillboard].pos.y, g_aBillboard[nCntBillboard].pos.z);
			D3DXMatrixMultiply(&g_aBillboard[nCntBillboard].mtxWorld, &g_aBillboard[nCntBillboard].mtxWorld, &mtxTrans);

			//ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_aBillboard[nCntBillboard].mtxWorld);

			//頂点バッファをデータストリームに設定
			pDevice->SetStreamSource(0, g_pVtxBuffBillboard, 0, sizeof(VERTEX_3D));

			//頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);

			//ライト無効
			pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

			//ビルボード描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntBillboard * 4, 2);	//プリミティブの種類

																				//ライト有効に戻す
			pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
		}
	}
}

//================================================
//ビルボードの設置処理
//================================================
void SetBillboard(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	VERTEX_3D*pVtx;	//頂点情報のポインタ
	int nCntBillboard;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffBillboard->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBillboard = 0; nCntBillboard < MAX_BILLBOARD; nCntBillboard++)
	{

		if (g_aBillboard[nCntBillboard].bUse == false)
		{
			g_aBillboard[nCntBillboard].pos = pos;
			g_aBillboard[nCntBillboard].rot = rot;

			pVtx[0].pos = D3DXVECTOR3(-10.0f, 20.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(10.0f, 20.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(-10.0f, 0.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(10.0f, 0.0f, 0.0f);

			g_aBillboard[nCntBillboard].bUse = true;

			break;
		}
		pVtx += 4;	//ポインタを4つ進める
	}
	//頂点バッファをアンロックする
	g_pVtxBuffBillboard->Unlock();
}