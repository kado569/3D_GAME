//================================================
//
//3Dアクション(model.cpp)
//Author:門脇勇斗
//
//================================================
#include"main.h"
#include"model.h"
#include"camera.h"
#include"input.h"
#include"shadow.h"

//================================================
//グローバル変数
//================================================
LPD3DXMESH g_pMeshModel = NULL;					//メッシュ情報へのポインタ
LPD3DXBUFFER g_pBuffMatModel = NULL;			//マテリアル情報へのポインタ
DWORD g_nNumMatModel = 0;						//マテリアル情報数
D3DXVECTOR3 g_posModel;							//位置
D3DXVECTOR3 g_rotModel;							//向き
D3DXVECTOR3	g_rotDestModel;						//目的の角度
D3DXMATRIX g_mtxWorldModel;						//ワールドマトリックス（行列）
int g_nIdxShadow;								//影の番号

//================================================
//ポリゴンの初期化設定
//================================================
void InitModel(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//Xファイルの読み込み
	D3DXLoadMeshFromX("data//MODEL//tank100.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_pBuffMatModel,
		NULL,
		&g_nNumMatModel,
		&g_pMeshModel);

	g_posModel = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//位置の初期設定
	g_rotModel = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//向きの初期設定
	g_nIdxShadow = SetShadow(D3DXVECTOR3(g_posModel.x, 0.1f, g_posModel.z), g_rotModel);
}

//================================================
//ポリゴンの終了処理
//================================================
void UninitModel(void)
{
	//メッシュの破棄
	if (g_pMeshModel != NULL)
	{
		g_pMeshModel->Release();
		g_pMeshModel = NULL;
	}

	//マテリアルの破棄
	if (g_pBuffMatModel != NULL)
	{
		g_pBuffMatModel->Release();
		g_pBuffMatModel = NULL;
	}
}

//================================================
//ポリゴンの更新処理
//================================================
void UpdateModel(void)
{
	//カメラの情報をポインターに入れる
	Camera *pCamera = GetCamera();

	if (GetKeyboardPress(DIK_UP) == true)
	{//前移動
		g_posModel.x += sinf(pCamera->rot.y) * 1.0f;
		g_posModel.z += cosf(pCamera->rot.y) * 1.0f;
		g_rotDestModel.y = D3DX_PI + pCamera->rot.y;
	}
	if (GetKeyboardPress(DIK_DOWN) == true)
	{//後移動
		g_posModel.x -= sinf(pCamera->rot.y) * 1.0f;
		g_posModel.z -= cosf(pCamera->rot.y) * 1.0f;
		g_rotDestModel.y = 0.0f + pCamera->rot.y;
	}
	if (GetKeyboardPress(DIK_LEFT) == true)
	{//左移動
		g_posModel.x += sinf(pCamera->rot.y - (D3DX_PI / 2)) * 1.0f;
		g_posModel.z += cosf(pCamera->rot.y - (D3DX_PI / 2)) * 1.0f;
		g_rotDestModel.y = (D3DX_PI / 2) + pCamera->rot.y;
	}
	if (GetKeyboardPress(DIK_RIGHT) == true)
	{//右移動
		g_posModel.x -= sinf(pCamera->rot.y - (D3DX_PI / 2)) * 1.0f;
		g_posModel.z -= cosf(pCamera->rot.y - (D3DX_PI / 2)) * 1.0f;
		g_rotDestModel.y = (-D3DX_PI / 2) + pCamera->rot.y;
	}


	float frot = g_rotDestModel.y - g_rotModel.y;


	//移動量の更新
	if (frot > D3DX_PI)
	{
		frot -= D3DX_PI * 2;
	}
	if (frot < -D3DX_PI)
	{
		frot += D3DX_PI * 2;
	}
	g_rotModel.y += frot * 0.1f;

	//角度の正規化
	if (g_rotModel.y > D3DX_PI)
	{
		g_rotModel.y -= D3DX_PI * 2;
	}
	if (g_rotModel.y < -D3DX_PI)
	{
		g_rotModel.y += D3DX_PI * 2;
	}

	SetPositionShadow(g_nIdxShadow,(D3DXVECTOR3(g_posModel.x, 0.1f, g_posModel.z)));
}

//================================================
//ポリゴンの描画処理
//================================================
void DrawModel(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//計算用マトリックス
	D3DXMATRIX mtxRot, mtxTrans;

	//現在のマテリアル保存用
	D3DMATERIAL9 matDef;

	//マテリアルデータへのポインタ
	D3DXMATERIAL *pMat;

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&g_mtxWorldModel);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_rotModel.y, g_rotModel.x, g_rotModel.z);
	D3DXMatrixMultiply(&g_mtxWorldModel, &g_mtxWorldModel, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, g_posModel.x, g_posModel.y, g_posModel.z);
	D3DXMatrixMultiply(&g_mtxWorldModel, &g_mtxWorldModel, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldModel);

	//現在のマテリアル保持
	pDevice->GetMaterial(&matDef);

	//マテリアルデータへのポインタを取得
	pMat = (D3DXMATERIAL*)g_pBuffMatModel->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)g_nNumMatModel; nCntMat++)
	{
		//マテリアル設定
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		//モデルパーツの描画
		g_pMeshModel->DrawSubset(nCntMat);
	}

	//保持していたマテリアルを戻す
	pDevice->SetMaterial(&matDef);
}