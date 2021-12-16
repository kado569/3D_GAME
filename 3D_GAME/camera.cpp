//================================================
//
//3Dアクション(camera.cpp)
//Author:門脇勇斗
//
//================================================
#include "input.h"
#include "main.h"
#include "camera.h"

//================================================
//グローバル変数
//================================================
Camera g_camera;

//================================================
//初期化処理
//================================================
void InitCamera(void)
{
	//視点・注視点・上方向を指定
	g_camera.posV = D3DXVECTOR3(0.0f, 200.0f, -200.0f);
	g_camera.posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_camera.vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//向き・視点から注視点までの距離を初期化する
	g_camera.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_camera.fDistance = sqrtf((g_camera.posR.x - g_camera.posV.x) * (g_camera.posR.x - g_camera.posV.x) + (g_camera.posR.z - g_camera.posV.z) * (g_camera.posR.z - g_camera.posV.z));
}

//================================================
//終了処理
//================================================
void UninitCamera(void)
{

}

//================================================
//更新処理
//================================================
void UpdateCamera(void)
{
	//注視点の移動
	if (GetKeyboardPress(DIK_Q) == true)
	{//左回転
		g_camera.rot.y += 0.1f;
		g_camera.posR.x = g_camera.posV.x + sinf(g_camera.rot.y) * g_camera.fDistance;
		g_camera.posR.z = g_camera.posV.z + cosf(g_camera.rot.y) * g_camera.fDistance;
	}

	if (GetKeyboardPress(DIK_E) == true)
	{//右回転
		g_camera.rot.y -= 0.1f;
		g_camera.posR.x = g_camera.posV.x + sinf(g_camera.rot.y) * g_camera.fDistance;
		g_camera.posR.z = g_camera.posV.z + cosf(g_camera.rot.y) * g_camera.fDistance;
	}

	//視点の回転
	if (GetKeyboardPress(DIK_Z) == true)
	{//左回転
		g_camera.rot.y -= 0.1f;
		g_camera.posV.x = g_camera.posR.x - sinf(g_camera.rot.y) * g_camera.fDistance;
		g_camera.posV.z = g_camera.posR.z - cosf(g_camera.rot.y) * g_camera.fDistance;
	}

	if (GetKeyboardPress(DIK_C) == true)
	{//右回転
		g_camera.rot.y += 0.1f;
		g_camera.posV.x = g_camera.posR.x - sinf(g_camera.rot.y) * g_camera.fDistance;
		g_camera.posV.z = g_camera.posR.z - cosf(g_camera.rot.y) * g_camera.fDistance;
	}

	//視点の移動
	if (GetKeyboardPress(DIK_W) == true)
	{//前移動
		g_camera.posV.x += sinf(g_camera.rot.y) * 1.0f;
		g_camera.posV.z += cosf(g_camera.rot.y) * 1.0f;

		g_camera.posR.x = g_camera.posV.x + sinf(g_camera.rot.y) * g_camera.fDistance;
		g_camera.posR.z = g_camera.posV.z + cosf(g_camera.rot.y) * g_camera.fDistance;
	}
	if (GetKeyboardPress(DIK_S) == true)
	{//後移動
		g_camera.posV.x -= sinf(g_camera.rot.y) * 1.0f;
		g_camera.posV.z -= cosf(g_camera.rot.y) * 1.0f;

		g_camera.posR.x = g_camera.posV.x + sinf(g_camera.rot.y) * g_camera.fDistance;
		g_camera.posR.z = g_camera.posV.z + cosf(g_camera.rot.y) * g_camera.fDistance;
	}
	if (GetKeyboardPress(DIK_D) == true)
	{//右移動
		g_camera.posV.x += sinf(g_camera.rot.y + (D3DX_PI / 2)) * 1.0f;
		g_camera.posV.z += cosf(g_camera.rot.y + (D3DX_PI / 2)) * 1.0f;

		g_camera.posR.x = g_camera.posV.x + sinf(g_camera.rot.y) * g_camera.fDistance;
		g_camera.posR.z = g_camera.posV.z + cosf(g_camera.rot.y) * g_camera.fDistance;
	}
	if (GetKeyboardPress(DIK_A) == true)
	{//左移動
		g_camera.posV.x -= sinf(g_camera.rot.y + (D3DX_PI / 2)) * 1.0f;
		g_camera.posV.z -= cosf(g_camera.rot.y + (D3DX_PI / 2)) * 1.0f;

		g_camera.posR.x = g_camera.posV.x + sinf(g_camera.rot.y) * g_camera.fDistance;
		g_camera.posR.z = g_camera.posV.z + cosf(g_camera.rot.y) * g_camera.fDistance;
	}

	//カメラの正規化
	if (g_camera.rot.y > D3DX_PI)
	{
		g_camera.rot.y -= D3DX_PI * 2;
	}
	else if (g_camera.rot.y < -D3DX_PI)
	{
		g_camera.rot.y += D3DX_PI * 2;
	}
}

//================================================
//カメラの設定処理
//================================================
void SetCamera(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//ビューマトリックス初期化
	D3DXMatrixIdentity(&g_camera.mtxView);

	//ビューマトリックスの作成
	D3DXMatrixLookAtLH(&g_camera.mtxView,
						&g_camera.posV,
						&g_camera.posR,
						&g_camera.vecU);

	//ビューマトリックスの設定
	pDevice->SetTransform(D3DTS_VIEW, &g_camera.mtxView);

	//プロジェクションマトリックスの初期化
	D3DXMatrixIdentity(&g_camera.mtxProjection);

	//プロジェクションマトリックスの作成
	D3DXMatrixPerspectiveFovLH(&g_camera.mtxProjection,
		D3DXToRadian(45.0f),
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,
		10.0f,
		1000.0f);

	//プロジェクションマトリックスの初期化
	pDevice->SetTransform(D3DTS_PROJECTION, &g_camera.mtxProjection);
}

//================================================
//カメラ情報の取得
//================================================
Camera *GetCamera(void)
{
	return &g_camera;
}