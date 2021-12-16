//================================================
//
//3D�A�N�V����(light.cpp)
//Author:��e�E�l
//
//================================================
#include "main.h"
#include "light.h"

//================================================
//�O���[�o���ϐ�
//================================================
D3DLIGHT9 g_light[MAX_LIGHT];		//���C�g���

//================================================
//���C�g������
//================================================
void InitLight(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DXVECTOR3 vecDir[MAX_LIGHT];						//���C�g�̕����փx�N�g��

	//���C�g���N���A����
	ZeroMemory(&g_light[0], sizeof(g_light));			//�\���̕ϐ����N���A�ł���֗��֐�

	//============================================
	//���C�g1��
	//============================================
	//���C�g�̎�ނ�ݒ�
	g_light[0].Type = D3DLIGHT_DIRECTIONAL;		//���s����

	//���C�g�̊g�U����ݒ�
	g_light[0].Diffuse = D3DXCOLOR(1.0f, 0.8f, 0.7f, 1.0f);

	//���C�g�̕����w��
	vecDir[0] = D3DXVECTOR3(1.57f, -0.6f, -0.9f);

	//���K������
	D3DXVec3Normalize(&vecDir[0], &vecDir[0]);
	g_light[0].Direction = vecDir[0];

	//���C�g��ݒ肷��
	pDevice->SetLight(0, &g_light[0]);

	//���C�g��L���ɂ���
	pDevice->LightEnable(0, TRUE);

	//============================================
	//���C�g2��
	//============================================
	//���C�g�̎�ނ�ݒ�
	g_light[1].Type = D3DLIGHT_DIRECTIONAL;		//���s����

												//���C�g�̊g�U����ݒ�
	g_light[1].Diffuse = D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f);

	//���C�g�̕����w��
	vecDir[1] = D3DXVECTOR3(0.6f, 1.0f, -1.57f);

	//���K������
	D3DXVec3Normalize(&vecDir[1], &vecDir[1]);
	g_light[1].Direction = vecDir[1];

	//���C�g��ݒ肷��
	pDevice->SetLight(0, &g_light[1]);

	//���C�g��L���ɂ���
	pDevice->LightEnable(0, TRUE);

	//============================================
	//���C�g3��
	//============================================
	//���C�g�̎�ނ�ݒ�
	g_light[2].Type = D3DLIGHT_DIRECTIONAL;		//���s����

	//���C�g�̊g�U����ݒ�
	g_light[2].Diffuse = D3DXCOLOR(0.6f, 0.4f, 0.3f, 1.0f);

	//���C�g�̕����w��
	vecDir[2] = D3DXVECTOR3(-1.57f, -0.2f, 0.9f);

	//���K������
	D3DXVec3Normalize(&vecDir[2], &vecDir[2]);
	g_light[2].Direction = vecDir[2];

	//���C�g��ݒ肷��
	pDevice->SetLight(0, &g_light[2]);

	//���C�g��L���ɂ���
	pDevice->LightEnable(0, TRUE);
}

//================================================
//���C�g�̏I������
//================================================
void UninitLight(void)
{

}

//================================================
//���C�g�̍X�V����
//================================================
void UpdateLight(void)
{

}
