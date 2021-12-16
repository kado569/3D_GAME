//================================================
//
//3Dアクション(light.cpp)
//Author:門脇勇斗
//
//================================================
#include "main.h"
#include "light.h"

//================================================
//グローバル変数
//================================================
D3DLIGHT9 g_light[MAX_LIGHT];		//ライト情報

//================================================
//ライト初期化
//================================================
void InitLight(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DXVECTOR3 vecDir[MAX_LIGHT];						//ライトの方向へベクトル

	//ライトをクリアする
	ZeroMemory(&g_light[0], sizeof(g_light));			//構造体変数をクリアできる便利関数

	//============================================
	//ライト1つ目
	//============================================
	//ライトの種類を設定
	g_light[0].Type = D3DLIGHT_DIRECTIONAL;		//平行光源

	//ライトの拡散光を設定
	g_light[0].Diffuse = D3DXCOLOR(1.0f, 0.8f, 0.7f, 1.0f);

	//ライトの方向指定
	vecDir[0] = D3DXVECTOR3(1.57f, -0.6f, -0.9f);

	//正規化する
	D3DXVec3Normalize(&vecDir[0], &vecDir[0]);
	g_light[0].Direction = vecDir[0];

	//ライトを設定する
	pDevice->SetLight(0, &g_light[0]);

	//ライトを有効にする
	pDevice->LightEnable(0, TRUE);

	//============================================
	//ライト2つ目
	//============================================
	//ライトの種類を設定
	g_light[1].Type = D3DLIGHT_DIRECTIONAL;		//平行光源

												//ライトの拡散光を設定
	g_light[1].Diffuse = D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f);

	//ライトの方向指定
	vecDir[1] = D3DXVECTOR3(0.6f, 1.0f, -1.57f);

	//正規化する
	D3DXVec3Normalize(&vecDir[1], &vecDir[1]);
	g_light[1].Direction = vecDir[1];

	//ライトを設定する
	pDevice->SetLight(0, &g_light[1]);

	//ライトを有効にする
	pDevice->LightEnable(0, TRUE);

	//============================================
	//ライト3つ目
	//============================================
	//ライトの種類を設定
	g_light[2].Type = D3DLIGHT_DIRECTIONAL;		//平行光源

	//ライトの拡散光を設定
	g_light[2].Diffuse = D3DXCOLOR(0.6f, 0.4f, 0.3f, 1.0f);

	//ライトの方向指定
	vecDir[2] = D3DXVECTOR3(-1.57f, -0.2f, 0.9f);

	//正規化する
	D3DXVec3Normalize(&vecDir[2], &vecDir[2]);
	g_light[2].Direction = vecDir[2];

	//ライトを設定する
	pDevice->SetLight(0, &g_light[2]);

	//ライトを有効にする
	pDevice->LightEnable(0, TRUE);
}

//================================================
//ライトの終了処理
//================================================
void UninitLight(void)
{

}

//================================================
//ライトの更新処理
//================================================
void UpdateLight(void)
{

}
