//================================================
//
//3D�A�N�V����(camera.cpp)
//Author:��e�E�l
//
//================================================
#include "input.h"
#include "main.h"
#include "camera.h"

//================================================
//�O���[�o���ϐ�
//================================================
Camera g_camera;

//================================================
//����������
//================================================
void InitCamera(void)
{
	//���_�E�����_�E��������w��
	g_camera.posV = D3DXVECTOR3(0.0f, 200.0f, -200.0f);
	g_camera.posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_camera.vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//�����E���_���璍���_�܂ł̋���������������
	g_camera.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_camera.fDistance = sqrtf((g_camera.posR.x - g_camera.posV.x) * (g_camera.posR.x - g_camera.posV.x) + (g_camera.posR.z - g_camera.posV.z) * (g_camera.posR.z - g_camera.posV.z));
}

//================================================
//�I������
//================================================
void UninitCamera(void)
{

}

//================================================
//�X�V����
//================================================
void UpdateCamera(void)
{
	//�����_�̈ړ�
	if (GetKeyboardPress(DIK_Q) == true)
	{//����]
		g_camera.rot.y += 0.1f;
		g_camera.posR.x = g_camera.posV.x + sinf(g_camera.rot.y) * g_camera.fDistance;
		g_camera.posR.z = g_camera.posV.z + cosf(g_camera.rot.y) * g_camera.fDistance;
	}

	if (GetKeyboardPress(DIK_E) == true)
	{//�E��]
		g_camera.rot.y -= 0.1f;
		g_camera.posR.x = g_camera.posV.x + sinf(g_camera.rot.y) * g_camera.fDistance;
		g_camera.posR.z = g_camera.posV.z + cosf(g_camera.rot.y) * g_camera.fDistance;
	}

	//���_�̉�]
	if (GetKeyboardPress(DIK_Z) == true)
	{//����]
		g_camera.rot.y -= 0.1f;
		g_camera.posV.x = g_camera.posR.x - sinf(g_camera.rot.y) * g_camera.fDistance;
		g_camera.posV.z = g_camera.posR.z - cosf(g_camera.rot.y) * g_camera.fDistance;
	}

	if (GetKeyboardPress(DIK_C) == true)
	{//�E��]
		g_camera.rot.y += 0.1f;
		g_camera.posV.x = g_camera.posR.x - sinf(g_camera.rot.y) * g_camera.fDistance;
		g_camera.posV.z = g_camera.posR.z - cosf(g_camera.rot.y) * g_camera.fDistance;
	}

	//���_�̈ړ�
	if (GetKeyboardPress(DIK_W) == true)
	{//�O�ړ�
		g_camera.posV.x += sinf(g_camera.rot.y) * 1.0f;
		g_camera.posV.z += cosf(g_camera.rot.y) * 1.0f;

		g_camera.posR.x = g_camera.posV.x + sinf(g_camera.rot.y) * g_camera.fDistance;
		g_camera.posR.z = g_camera.posV.z + cosf(g_camera.rot.y) * g_camera.fDistance;
	}
	if (GetKeyboardPress(DIK_S) == true)
	{//��ړ�
		g_camera.posV.x -= sinf(g_camera.rot.y) * 1.0f;
		g_camera.posV.z -= cosf(g_camera.rot.y) * 1.0f;

		g_camera.posR.x = g_camera.posV.x + sinf(g_camera.rot.y) * g_camera.fDistance;
		g_camera.posR.z = g_camera.posV.z + cosf(g_camera.rot.y) * g_camera.fDistance;
	}
	if (GetKeyboardPress(DIK_D) == true)
	{//�E�ړ�
		g_camera.posV.x += sinf(g_camera.rot.y + (D3DX_PI / 2)) * 1.0f;
		g_camera.posV.z += cosf(g_camera.rot.y + (D3DX_PI / 2)) * 1.0f;

		g_camera.posR.x = g_camera.posV.x + sinf(g_camera.rot.y) * g_camera.fDistance;
		g_camera.posR.z = g_camera.posV.z + cosf(g_camera.rot.y) * g_camera.fDistance;
	}
	if (GetKeyboardPress(DIK_A) == true)
	{//���ړ�
		g_camera.posV.x -= sinf(g_camera.rot.y + (D3DX_PI / 2)) * 1.0f;
		g_camera.posV.z -= cosf(g_camera.rot.y + (D3DX_PI / 2)) * 1.0f;

		g_camera.posR.x = g_camera.posV.x + sinf(g_camera.rot.y) * g_camera.fDistance;
		g_camera.posR.z = g_camera.posV.z + cosf(g_camera.rot.y) * g_camera.fDistance;
	}

	//�J�����̐��K��
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
//�J�����̐ݒ菈��
//================================================
void SetCamera(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�r���[�}�g���b�N�X������
	D3DXMatrixIdentity(&g_camera.mtxView);

	//�r���[�}�g���b�N�X�̍쐬
	D3DXMatrixLookAtLH(&g_camera.mtxView,
						&g_camera.posV,
						&g_camera.posR,
						&g_camera.vecU);

	//�r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &g_camera.mtxView);

	//�v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_camera.mtxProjection);

	//�v���W�F�N�V�����}�g���b�N�X�̍쐬
	D3DXMatrixPerspectiveFovLH(&g_camera.mtxProjection,
		D3DXToRadian(45.0f),
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,
		10.0f,
		1000.0f);

	//�v���W�F�N�V�����}�g���b�N�X�̏�����
	pDevice->SetTransform(D3DTS_PROJECTION, &g_camera.mtxProjection);
}

//================================================
//�J�������̎擾
//================================================
Camera *GetCamera(void)
{
	return &g_camera;
}