//================================================
//
//3Dアクション(main.cpp)
//Author:門脇勇斗
//
//================================================
#include "main.h"
#include "polygon.h"
#include "light.h"
#include "camera.h"
#include "model.h"
#include "input.h"
#include "shadow.h"
#include "wall.h"
#include "billboard.h"
#include "meshfield.h"

//================================================
//グローバル変数
//================================================
LPDIRECT3D9		g_pD3D = NULL;					//Direct3Dオブジェクトへのポインタ
LPDIRECT3DDEVICE9 g_pD3DDevice = NULL;			//Direct3Dデバイスへのポインタ

//================================================
//メイン関数
//================================================
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hInstancePrev, LPSTR lCmdLine, int nCmdShow)
{
	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };		//画面サイズの構造体

	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),				//WNDCLASSEXのメモリサイズ
		CS_CLASSDC,						//ウィンドウのスタイル
		WindowProc,						//ウィンドウプロシージャ
		0,
		0,
		hInstance,						//インスタンスハンドル
		LoadIcon(NULL,IDI_APPLICATION),	//タスクバーアイコン
		LoadCursor(NULL,IDC_ARROW),		//マウスカーソル
		(HBRUSH)(COLOR_WINDOW + 1),		//クライアント領域の背景色
		NULL,							//メニューバー
		CLASS_NAME,						//ウィンドウクラスの名前
		LoadIcon(NULL,IDI_APPLICATION)	//ファイルアイコン

	};
	HWND hWnd;							//ウィンドウハンドル
	MSG msg;							//メッセージを格納する変数

	//ウィンドウクラスの登録
	RegisterClassEx(&wcex);

	//クライアント領域を指定のサイズに調整
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

	//ウィンドウ生成
	hWnd = CreateWindowEx(
		0,								//拡張ウィンドウスタイル
		CLASS_NAME,						//ウィンドウクラスの名前
		WINDOW_NAME,					//ウィンドウの名前
		WS_OVERLAPPEDWINDOW,			//ウィンドウスタイル
		CW_USEDEFAULT,					//ウィンドウの左上x座標
		CW_USEDEFAULT,					//ウィンドウの左上y座標
		(rect.right - rect.left),		//ウィンドウの幅
		(rect.bottom - rect.top),		//ウィンドウの高さ		
		NULL,							//親ウィンドウのハンドル
		NULL,							//メニューハンドルor子ウィンドウID
		hInstance,						//インスタンスハンドル
		NULL);							//ウィンドウ生成データ

	//初期化処理(ダメだった時の処理)
	if (FAILED(Init(hInstance, hWnd, TRUE)))
	{//初期化失敗
		return -1;
	}

	//ウィンドウ表示
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	//メッセージループ
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)
		{//windowsの処理
			if (msg.message == WM_QUIT)
			{//WM_QUITメッセージを受け取ったらメッセージループを抜ける
				break;
			}

			else
			{
				//メッセージの設定
				TranslateMessage(&msg);		//仮想キーメッセージを文字メッセージへ変換
				DispatchMessage(&msg);		//ウィンドウプロシージャーへメッセージを送出
			}
		}

		else
		{//DirectXの処理
		 //更新処理
			Update();
			//描画処理
			Draw();
		}
	}

	//終了処理
	Uninit();

	//ウィンドウクラスの登録を解除
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	return (int)msg.wParam;


}
//================================================
//ウィンドウプロシージャー
//================================================
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_DESTROY:
		//WM_QUITメッセージを送る
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:								//キー降下のメッセージ
		switch (wParam)
		{
		case VK_ESCAPE:								//escキーが押された

			DestroyWindow(hWnd);					//ウィンドウを破棄する([WM_DESTROY]メッセージを送る)

			break;
		}
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

//================================================
//初期化処理
//================================================
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	D3DDISPLAYMODE d3ddm;							//ディスプレイモード
	D3DPRESENT_PARAMETERS d3dpp;					//プレゼンテーションパラメータ

	//irect3Dオブジェクトの生成
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (g_pD3D == NULL)
	{
		return E_FAIL;
	}

	//現在のディスプレイモードを取得
	if (FAILED(g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	//デバイスのプレゼンテーションパラメータの設定
	ZeroMemory(&d3dpp, sizeof(d3dpp));				//パラメータゼロクリア

	d3dpp.BackBufferWidth = SCREEN_WIDTH;			//ゲーム画面サイズ（横）

	d3dpp.BackBufferHeight = SCREEN_HEIGHT;			//ゲーム画面サイズ（高さ）

	d3dpp.BackBufferFormat = d3ddm.Format;			//バックバッファの形式

	d3dpp.BackBufferCount = 1;						//バックバッファの数

	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;		//ダブルバッファの切り替え（映像信号に同期）

	d3dpp.EnableAutoDepthStencil = TRUE;			//デプスバッファとステンシルバッファを作成

	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;		//デプスバッファとして16bitを使う

	d3dpp.Windowed = bWindow;						//ウインドウモード

	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;		//リフレッシュレート

	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;		//インターバル

	//Direct3Dデバイスの生成（描画処理と頂点処理をハードウェアで行う）
	if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp,
		&g_pD3DDevice)))

	{
		//Direct3Dデバイスの生成（描画処理はハードウェア、頂点処理はCPUで行う）
		if (FAILED((g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp,
			&g_pD3DDevice))))

		{
			//Direct3Dデバイスの生成（描画処理と頂点処理をCPUで行う）
			if (FAILED((g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
				D3DDEVTYPE_REF,
				hWnd,
				D3DCREATE_SOFTWARE_VERTEXPROCESSING,
				&d3dpp,
				&g_pD3DDevice))))

			{
				return E_FAIL;
			}
		}
	}

	//レンダーステートの設定
	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//テクスチャステージステートパラメータの設定
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);

	//キーボードの初期化
	if (FAILED(InitKeyboard(hInstance, hWnd)))
	{
		return E_FAIL;
	}

	//各種オブジェクトの初期化処理
	//カメラの初期化設定
	InitCamera();

	//
	InitMeshfield();

	////ポリゴンの初期化設定
	//InitPolygon();

	//ライトの初期化設定
	InitLight();

	//影の初期化処理
	InitShadow();

	//モデルの初期化設定
	InitModel();

	//壁の初期化処理
	InitWall();
	
	//ビルボードの初期化処理
	InitBillboard();

	return S_OK;
}

//================================================
//終了処理
//================================================
void Uninit(void)
{
	//各種オブジェクトの終了処理
	//
	UninitMeshfield();

	////ポリゴンの終了設定
	//UninitPolygon();

	//ライトの終了設定
	UninitLight();

	//影の終了処理
	UninitShadow();

	//モデルの終了設定
	UninitModel();

	//壁の終了処理
	UninitWall();

	//カメラの終了設定
	UninitCamera();

	//ビルボードの終了処理
	UninitBillboard();

	//Direct3Dデバイスの破棄
	if (g_pD3DDevice != NULL)
	{
		g_pD3DDevice->Release();
		g_pD3DDevice = NULL;
	}

	//Direct3Dオブジェクトの破棄
	if (g_pD3D != NULL)
	{
		g_pD3D->Release();
		g_pD3D = NULL;
	}
}

//================================================
//更新処理
//================================================
void Update(void)
{
	//キーボードの更新
	UpdateKeyboard();

	//カメラの更新設定
	UpdateCamera();

	//
	UpdateMeshfield();

	//ライトの更新設定
	UpdateLight();

	////ポリゴンの更新設定
	//UpdatePolygon();

	//影の更新処理
	UpdateShadow();

	//モデルの更新設定
	UpdateModel();

	//壁の更新処理
	UpdataWall();

	//ビルボードの更新処理
	UpdateBillboard();

	if(GetKeyboardTrigger(DIK_1) == true)
	{//1キーが押された
	 //ワイヤーフレームモードを元に戻す
		g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	}
	if (GetKeyboardTrigger(DIK_2) == true)
	{//2キーが押された
	 //ワイヤーフレームモードの設定
		g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	}

}

//================================================
//描画処理
//================================================
void Draw(void)
{
	//画面クリア（バッファクリア、Zバッファのクリア）
	g_pD3DDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);


	//描画開始
	if (SUCCEEDED(g_pD3DDevice->BeginScene()))
	{//描画開始が成功
		//カメラの設定
		SetCamera();

		////
		DrawMeshfield();

		////ポリゴン描画処理
		//DrawPolygon();

		//影の描画処理
		DrawShadow();

		//モデルの描画処理
		DrawModel();

		//壁の描画処理
		DrawWall();

		//ビルボードの描画処理
		DrawBillboard();

		//描画終了
		g_pD3DDevice->EndScene();
	}

	//バックバッファとフロントバッファの入れ替え
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

//================================================
//デバイスの取得
//================================================
LPDIRECT3DDEVICE9 GetDevice(void)
{
	return g_pD3DDevice;
}
