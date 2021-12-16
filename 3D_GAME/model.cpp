//================================================
//
//3D�A�N�V����(model.cpp)
//Author:��e�E�l
//
//================================================
#include"main.h"
#include"model.h"
#include"camera.h"
#include"input.h"
#include"shadow.h"

//================================================
//�O���[�o���ϐ�
//================================================
LPD3DXMESH g_pMeshModel = NULL;					//���b�V�����ւ̃|�C���^
LPD3DXBUFFER g_pBuffMatModel = NULL;			//�}�e���A�����ւ̃|�C���^
DWORD g_nNumMatModel = 0;						//�}�e���A�����
D3DXVECTOR3 g_posModel;							//�ʒu
D3DXVECTOR3 g_rotModel;							//����
D3DXVECTOR3	g_rotDestModel;						//�ړI�̊p�x
D3DXMATRIX g_mtxWorldModel;						//���[���h�}�g���b�N�X�i�s��j
int g_nIdxShadow;								//�e�̔ԍ�

//================================================
//�|���S���̏������ݒ�
//================================================
void InitModel(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX("data//MODEL//tank100.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_pBuffMatModel,
		NULL,
		&g_nNumMatModel,
		&g_pMeshModel);

	g_posModel = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�ʒu�̏����ݒ�
	g_rotModel = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�����̏����ݒ�
	g_nIdxShadow = SetShadow(D3DXVECTOR3(g_posModel.x, 0.1f, g_posModel.z), g_rotModel);
}

//================================================
//�|���S���̏I������
//================================================
void UninitModel(void)
{
	//���b�V���̔j��
	if (g_pMeshModel != NULL)
	{
		g_pMeshModel->Release();
		g_pMeshModel = NULL;
	}

	//�}�e���A���̔j��
	if (g_pBuffMatModel != NULL)
	{
		g_pBuffMatModel->Release();
		g_pBuffMatModel = NULL;
	}
}

//================================================
//�|���S���̍X�V����
//================================================
void UpdateModel(void)
{
	//�J�����̏����|�C���^�[�ɓ����
	Camera *pCamera = GetCamera();

	if (GetKeyboardPress(DIK_UP) == true)
	{//�O�ړ�
		g_posModel.x += sinf(pCamera->rot.y) * 1.0f;
		g_posModel.z += cosf(pCamera->rot.y) * 1.0f;
		g_rotDestModel.y = D3DX_PI + pCamera->rot.y;
	}
	if (GetKeyboardPress(DIK_DOWN) == true)
	{//��ړ�
		g_posModel.x -= sinf(pCamera->rot.y) * 1.0f;
		g_posModel.z -= cosf(pCamera->rot.y) * 1.0f;
		g_rotDestModel.y = 0.0f + pCamera->rot.y;
	}
	if (GetKeyboardPress(DIK_LEFT) == true)
	{//���ړ�
		g_posModel.x += sinf(pCamera->rot.y - (D3DX_PI / 2)) * 1.0f;
		g_posModel.z += cosf(pCamera->rot.y - (D3DX_PI / 2)) * 1.0f;
		g_rotDestModel.y = (D3DX_PI / 2) + pCamera->rot.y;
	}
	if (GetKeyboardPress(DIK_RIGHT) == true)
	{//�E�ړ�
		g_posModel.x -= sinf(pCamera->rot.y - (D3DX_PI / 2)) * 1.0f;
		g_posModel.z -= cosf(pCamera->rot.y - (D3DX_PI / 2)) * 1.0f;
		g_rotDestModel.y = (-D3DX_PI / 2) + pCamera->rot.y;
	}


	float frot = g_rotDestModel.y - g_rotModel.y;


	//�ړ��ʂ̍X�V
	if (frot > D3DX_PI)
	{
		frot -= D3DX_PI * 2;
	}
	if (frot < -D3DX_PI)
	{
		frot += D3DX_PI * 2;
	}
	g_rotModel.y += frot * 0.1f;

	//�p�x�̐��K��
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
//�|���S���̕`�揈��
//================================================
void DrawModel(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans;

	//���݂̃}�e���A���ۑ��p
	D3DMATERIAL9 matDef;

	//�}�e���A���f�[�^�ւ̃|�C���^
	D3DXMATERIAL *pMat;

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_mtxWorldModel);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_rotModel.y, g_rotModel.x, g_rotModel.z);
	D3DXMatrixMultiply(&g_mtxWorldModel, &g_mtxWorldModel, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, g_posModel.x, g_posModel.y, g_posModel.z);
	D3DXMatrixMultiply(&g_mtxWorldModel, &g_mtxWorldModel, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldModel);

	//���݂̃}�e���A���ێ�
	pDevice->GetMaterial(&matDef);

	//�}�e���A���f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)g_pBuffMatModel->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)g_nNumMatModel; nCntMat++)
	{
		//�}�e���A���ݒ�
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		//���f���p�[�c�̕`��
		g_pMeshModel->DrawSubset(nCntMat);
	}

	//�ێ����Ă����}�e���A����߂�
	pDevice->SetMaterial(&matDef);
}