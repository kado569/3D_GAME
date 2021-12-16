//================================================
//
//3D�A�N�V����(main.cpp)
//Author:��e�E�l
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
//�O���[�o���ϐ�
//================================================
LPDIRECT3D9		g_pD3D = NULL;					//Direct3D�I�u�W�F�N�g�ւ̃|�C���^
LPDIRECT3DDEVICE9 g_pD3DDevice = NULL;			//Direct3D�f�o�C�X�ւ̃|�C���^

//================================================
//���C���֐�
//================================================
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hInstancePrev, LPSTR lCmdLine, int nCmdShow)
{
	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };		//��ʃT�C�Y�̍\����

	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),				//WNDCLASSEX�̃������T�C�Y
		CS_CLASSDC,						//�E�B���h�E�̃X�^�C��
		WindowProc,						//�E�B���h�E�v���V�[�W��
		0,
		0,
		hInstance,						//�C���X�^���X�n���h��
		LoadIcon(NULL,IDI_APPLICATION),	//�^�X�N�o�[�A�C�R��
		LoadCursor(NULL,IDC_ARROW),		//�}�E�X�J�[�\��
		(HBRUSH)(COLOR_WINDOW + 1),		//�N���C�A���g�̈�̔w�i�F
		NULL,							//���j���[�o�[
		CLASS_NAME,						//�E�B���h�E�N���X�̖��O
		LoadIcon(NULL,IDI_APPLICATION)	//�t�@�C���A�C�R��

	};
	HWND hWnd;							//�E�B���h�E�n���h��
	MSG msg;							//���b�Z�[�W���i�[����ϐ�

	//�E�B���h�E�N���X�̓o�^
	RegisterClassEx(&wcex);

	//�N���C�A���g�̈���w��̃T�C�Y�ɒ���
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

	//�E�B���h�E����
	hWnd = CreateWindowEx(
		0,								//�g���E�B���h�E�X�^�C��
		CLASS_NAME,						//�E�B���h�E�N���X�̖��O
		WINDOW_NAME,					//�E�B���h�E�̖��O
		WS_OVERLAPPEDWINDOW,			//�E�B���h�E�X�^�C��
		CW_USEDEFAULT,					//�E�B���h�E�̍���x���W
		CW_USEDEFAULT,					//�E�B���h�E�̍���y���W
		(rect.right - rect.left),		//�E�B���h�E�̕�
		(rect.bottom - rect.top),		//�E�B���h�E�̍���		
		NULL,							//�e�E�B���h�E�̃n���h��
		NULL,							//���j���[�n���h��or�q�E�B���h�EID
		hInstance,						//�C���X�^���X�n���h��
		NULL);							//�E�B���h�E�����f�[�^

	//����������(�_�����������̏���)
	if (FAILED(Init(hInstance, hWnd, TRUE)))
	{//���������s
		return -1;
	}

	//�E�B���h�E�\��
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	//���b�Z�[�W���[�v
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)
		{//windows�̏���
			if (msg.message == WM_QUIT)
			{//WM_QUIT���b�Z�[�W���󂯎�����烁�b�Z�[�W���[�v�𔲂���
				break;
			}

			else
			{
				//���b�Z�[�W�̐ݒ�
				TranslateMessage(&msg);		//���z�L�[���b�Z�[�W�𕶎����b�Z�[�W�֕ϊ�
				DispatchMessage(&msg);		//�E�B���h�E�v���V�[�W���[�փ��b�Z�[�W�𑗏o
			}
		}

		else
		{//DirectX�̏���
		 //�X�V����
			Update();
			//�`�揈��
			Draw();
		}
	}

	//�I������
	Uninit();

	//�E�B���h�E�N���X�̓o�^������
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	return (int)msg.wParam;


}
//================================================
//�E�B���h�E�v���V�[�W���[
//================================================
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_DESTROY:
		//WM_QUIT���b�Z�[�W�𑗂�
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:								//�L�[�~���̃��b�Z�[�W
		switch (wParam)
		{
		case VK_ESCAPE:								//esc�L�[�������ꂽ

			DestroyWindow(hWnd);					//�E�B���h�E��j������([WM_DESTROY]���b�Z�[�W�𑗂�)

			break;
		}
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

//================================================
//����������
//================================================
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	D3DDISPLAYMODE d3ddm;							//�f�B�X�v���C���[�h
	D3DPRESENT_PARAMETERS d3dpp;					//�v���[���e�[�V�����p�����[�^

	//irect3D�I�u�W�F�N�g�̐���
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (g_pD3D == NULL)
	{
		return E_FAIL;
	}

	//���݂̃f�B�X�v���C���[�h���擾
	if (FAILED(g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	//�f�o�C�X�̃v���[���e�[�V�����p�����[�^�̐ݒ�
	ZeroMemory(&d3dpp, sizeof(d3dpp));				//�p�����[�^�[���N���A

	d3dpp.BackBufferWidth = SCREEN_WIDTH;			//�Q�[����ʃT�C�Y�i���j

	d3dpp.BackBufferHeight = SCREEN_HEIGHT;			//�Q�[����ʃT�C�Y�i�����j

	d3dpp.BackBufferFormat = d3ddm.Format;			//�o�b�N�o�b�t�@�̌`��

	d3dpp.BackBufferCount = 1;						//�o�b�N�o�b�t�@�̐�

	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;		//�_�u���o�b�t�@�̐؂�ւ��i�f���M���ɓ����j

	d3dpp.EnableAutoDepthStencil = TRUE;			//�f�v�X�o�b�t�@�ƃX�e���V���o�b�t�@���쐬

	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;		//�f�v�X�o�b�t�@�Ƃ���16bit���g��

	d3dpp.Windowed = bWindow;						//�E�C���h�E���[�h

	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;		//���t���b�V�����[�g

	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;		//�C���^�[�o��

	//Direct3D�f�o�C�X�̐����i�`�揈���ƒ��_�������n�[�h�E�F�A�ōs���j
	if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp,
		&g_pD3DDevice)))

	{
		//Direct3D�f�o�C�X�̐����i�`�揈���̓n�[�h�E�F�A�A���_������CPU�ōs���j
		if (FAILED((g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp,
			&g_pD3DDevice))))

		{
			//Direct3D�f�o�C�X�̐����i�`�揈���ƒ��_������CPU�ōs���j
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

	//�����_�[�X�e�[�g�̐ݒ�
	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//�e�N�X�`���X�e�[�W�X�e�[�g�p�����[�^�̐ݒ�
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);

	//�L�[�{�[�h�̏�����
	if (FAILED(InitKeyboard(hInstance, hWnd)))
	{
		return E_FAIL;
	}

	//�e��I�u�W�F�N�g�̏���������
	//�J�����̏������ݒ�
	InitCamera();

	//
	InitMeshfield();

	////�|���S���̏������ݒ�
	//InitPolygon();

	//���C�g�̏������ݒ�
	InitLight();

	//�e�̏���������
	InitShadow();

	//���f���̏������ݒ�
	InitModel();

	//�ǂ̏���������
	InitWall();
	
	//�r���{�[�h�̏���������
	InitBillboard();

	return S_OK;
}

//================================================
//�I������
//================================================
void Uninit(void)
{
	//�e��I�u�W�F�N�g�̏I������
	//
	UninitMeshfield();

	////�|���S���̏I���ݒ�
	//UninitPolygon();

	//���C�g�̏I���ݒ�
	UninitLight();

	//�e�̏I������
	UninitShadow();

	//���f���̏I���ݒ�
	UninitModel();

	//�ǂ̏I������
	UninitWall();

	//�J�����̏I���ݒ�
	UninitCamera();

	//�r���{�[�h�̏I������
	UninitBillboard();

	//Direct3D�f�o�C�X�̔j��
	if (g_pD3DDevice != NULL)
	{
		g_pD3DDevice->Release();
		g_pD3DDevice = NULL;
	}

	//Direct3D�I�u�W�F�N�g�̔j��
	if (g_pD3D != NULL)
	{
		g_pD3D->Release();
		g_pD3D = NULL;
	}
}

//================================================
//�X�V����
//================================================
void Update(void)
{
	//�L�[�{�[�h�̍X�V
	UpdateKeyboard();

	//�J�����̍X�V�ݒ�
	UpdateCamera();

	//
	UpdateMeshfield();

	//���C�g�̍X�V�ݒ�
	UpdateLight();

	////�|���S���̍X�V�ݒ�
	//UpdatePolygon();

	//�e�̍X�V����
	UpdateShadow();

	//���f���̍X�V�ݒ�
	UpdateModel();

	//�ǂ̍X�V����
	UpdataWall();

	//�r���{�[�h�̍X�V����
	UpdateBillboard();

	if(GetKeyboardTrigger(DIK_1) == true)
	{//1�L�[�������ꂽ
	 //���C���[�t���[�����[�h�����ɖ߂�
		g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	}
	if (GetKeyboardTrigger(DIK_2) == true)
	{//2�L�[�������ꂽ
	 //���C���[�t���[�����[�h�̐ݒ�
		g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	}

}

//================================================
//�`�揈��
//================================================
void Draw(void)
{
	//��ʃN���A�i�o�b�t�@�N���A�AZ�o�b�t�@�̃N���A�j
	g_pD3DDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);


	//�`��J�n
	if (SUCCEEDED(g_pD3DDevice->BeginScene()))
	{//�`��J�n������
		//�J�����̐ݒ�
		SetCamera();

		////
		DrawMeshfield();

		////�|���S���`�揈��
		//DrawPolygon();

		//�e�̕`�揈��
		DrawShadow();

		//���f���̕`�揈��
		DrawModel();

		//�ǂ̕`�揈��
		DrawWall();

		//�r���{�[�h�̕`�揈��
		DrawBillboard();

		//�`��I��
		g_pD3DDevice->EndScene();
	}

	//�o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�̓���ւ�
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

//================================================
//�f�o�C�X�̎擾
//================================================
LPDIRECT3DDEVICE9 GetDevice(void)
{
	return g_pD3DDevice;
}
