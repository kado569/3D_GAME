//================================================
//
//3D�A�N�V����(main.h)
//Author:��e�E�l
//
//================================================
#ifndef _MAIN_H_
#define _MAIN_H_
#include<windows.h>
#include "d3dx9.h"							//�`�揈���ɕK�v
#define DIRECTINPUT_VERSION (0x0800)		//�r���h���̌x���Ώ��p
#include "dinput.h"							//���͏����K�v
#include "xaudio2.h"						//�T�E���h�����ɕK�v

//================================================
//���C�u�����̃����N
//================================================
#pragma comment(lib, "d3d9.lib")	//�`�揈���ɕK�v
#pragma comment(lib, "d3dx9.lib")	//[d3d9.lib]�̊g�����C�u����
#pragma comment(lib, "dxguid.lib")	//DirectX�R���|�[�l���g(���i)�g�p�ɕK�v
#pragma comment(lib, "winmm.lib")	//�V�X�e�������擾�ɕK�{
#pragma comment(lib, "dinput8.lib")	//���͏����ɕK�v

//================================================
//�}�N����`
//================================================
#define CLASS_NAME		"WindowClass"			//�E�B���h�E�N���X�̖��O
#define WINDOW_NAME		"3D_GAME"				//�E�B���h�E�̖��O�i�L���v�V�����ɕ\���j
#define SCREEN_WIDTH (1280)						//�E�B���h�E�̕�
#define SCREEN_HEIGHT (720)						//�E�B���h�E�̍���
#define FVF_VERTEX_2D (D3DFVF_XYZRHW |D3DFVF_DIFFUSE |D3DFVF_TEX1)
#define FVF_VERTEX_3D (D3DFVF_XYZ |D3DFVF_NORMAL |D3DFVF_DIFFUSE |D3DFVF_TEX1)	

//================================================
//�v���g�^�C�v�錾
//================================================
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM IParam);
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
void Uninit(void);
void Update(void);
void Draw(void);

//================================================
//���_���u3D�v�̍\���̂��`
//================================================
typedef struct
{
	D3DXVECTOR3 pos;		//���_���W
	D3DXVECTOR3 nor;		//�@���x�N�g��
	D3DCOLOR col;			//���_�J���[
	D3DXVECTOR2 tex;		//�e�N�X�`�����W
} VERTEX_3D;

//================================================
//�v���g�^�C�v�錾
//================================================
LPDIRECT3DDEVICE9 GetDevice(void);

#endif