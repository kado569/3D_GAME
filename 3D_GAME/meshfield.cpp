//================================================
//
//3Dアクション(meshfield.cpp)
//Author:門脇勇斗
//
//================================================
#include "main.h"
#include "meshfield.h"

//================================================
//グローバル変数
//================================================
LPDIRECT3DTEXTURE9 g_pTextureMeshfield = NULL;			//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMeshfield = NULL;		//頂点バッファへのポインタ
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffMeshfield = NULL;		//インデックスへのポインタ
Meshfield g_Meshfield;

//================================================
//メッシュの初期化設定
//================================================
void InitMeshfield(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//テクスチャ読み込み 
	D3DXCreateTextureFromFile(pDevice,
		"data/cave001.jpg",
		&g_pTextureMeshfield);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * MESHFIELD_VERTEX_NUM,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffMeshfield,
		NULL);

	//インデックスバッファの作成
	pDevice->CreateIndexBuffer(sizeof(WORD) * 1000,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,							//頂点フォーマット
		D3DPOOL_MANAGED,
		&g_pIdxBuffMeshfield,
		NULL);

	VERTEX_3D * pVtx ;							//頂点情報のポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffMeshfield->Lock(0, 0, (void**)&pVtx, 0);

	//インデックスバッファロック
	WORD *pIdx;
	g_pIdxBuffMeshfield->Lock(0, 0, (void**)&pIdx, 0);

	for (int nCntZ = 0; nCntZ < MESHFIELD_Z_BLOCK + 1; nCntZ++)
	{
		for (int nCntX = 0; nCntX < MESHFIELD_X_BLOCK + 1; nCntX++)
		{
			//頂点座標設定
			pVtx[0].pos = D3DXVECTOR3(-100.0f + 70.0f * nCntX, 0.0f, 100.0f - 70.0f * nCntZ);

			//各頂点の法線設定（ベクトルの大きさは1にする）
			pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

			//頂点カラーの設定
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);

			pVtx++;
		}
	}

	for (int nCntZ = 0; nCntZ < MESHFIELD_Z_BLOCK + 1; nCntZ++)
	{
		for (int nCntX = 0; nCntX < MESHFIELD_X_BLOCK + 1; nCntX++)
		{
			//インデックスの設定
			pIdx[0] = (nCntX + MESHFIELD_X_BLOCK + 1) *(nCntZ + 1);			//下段の頂点
			pIdx[1] = (nCntX + MESHFIELD_X_BLOCK + 1) * nCntZ;				//上段の頂点
			pIdx += 2;
		}

		if (nCntZ < MESHFIELD_Z_BLOCK - 1)
		{//縮退ポリゴンの作成
			pIdx[0] = pIdx[-1];		//ひとつ前のpIdxの値を入れる
			pIdx[1] = (MESHFIELD_X_BLOCK + 1)*(nCntZ + 2);
			pIdx += 2;
		}

	}

	//インデックスバッファアンロック
	g_pIdxBuffMeshfield->Unlock();

	//頂点バッファをアンロックする
	g_pVtxBuffMeshfield->Unlock();
}

//================================================
//ポリゴンの終了処理
//================================================
void UninitMeshfield(void)
{
	//バッファ破棄
	if (g_pVtxBuffMeshfield != NULL)
	{
		g_pVtxBuffMeshfield->Release();
		g_pVtxBuffMeshfield = NULL;
	}

	//テクスチャ破棄
	if (g_pTextureMeshfield != NULL)
	{
		g_pTextureMeshfield->Release();
		g_pTextureMeshfield = NULL;
	}

	//インデックス破棄
	if (g_pIdxBuffMeshfield != NULL)
	{
		g_pIdxBuffMeshfield->Release();
		g_pIdxBuffMeshfield = NULL;
	}

}

//================================================
//ポリゴンの更新処理
//================================================
void UpdateMeshfield(void)
{

}

//================================================
//ポリゴンの描画処理
//================================================
void DrawMeshfield(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//計算用マトリックス
	D3DXMATRIX mtxRot, mtxTrans;

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&g_Meshfield.mtxWorld);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Meshfield.rot.y, g_Meshfield.rot.x, g_Meshfield.rot.z);
	D3DXMatrixMultiply(&g_Meshfield.mtxWorld, &g_Meshfield.mtxWorld, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, g_Meshfield.pos.x, g_Meshfield.pos.y, g_Meshfield.pos.z);
	D3DXMatrixMultiply(&g_Meshfield.mtxWorld, &g_Meshfield.mtxWorld, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &g_Meshfield.mtxWorld);

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffMeshfield, 0, sizeof(VERTEX_3D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	//テクスチャ設定
	pDevice->SetTexture(0, g_pTextureMeshfield);

	//ポリゴン描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);		//プリミティブの種類
}