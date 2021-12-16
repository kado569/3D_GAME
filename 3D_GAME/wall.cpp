//================================================
//
//3D�A�N�V����(main.cpp)
//Author:��e�E�l
//
//================================================
#include "main.h"
#include "wall.h"
#include "meshfield.h"

//�O���[�o���ϐ�
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffWall = NULL;
LPDIRECT3DTEXTURE9 g_pTextureWall = NULL;
Wall g_Wall[MAX_WALL];

//================================================
//�ǂ̏�����
//================================================
void InitWall(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	////�e�N�X�`���̓ǂݍ���
	//D3DXCreateTextureFromFile(pDevice,
	//	"./data/TEXTURE/block000.jpg",
	//	&g_pTextureWall);

	for (int nCntWall = 0; nCntWall < MAX_WALL; nCntWall++)
	{
		g_Wall[nCntWall].bUse = false;
		g_Wall[nCntWall].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Wall[nCntWall].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(
		sizeof(VERTEX_3D) * 4 * MAX_WALL,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D, D3DPOOL_MANAGED,
		&g_pVtxBuffWall, NULL);

	VERTEX_3D *pVtx = NULL;

	//���_�o�b�t�@�����b�N
	g_pVtxBuffWall->Lock(0, 0, (void**)&pVtx, 0);

	//���_���̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(-100.0f, 100.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(100.0f, 100.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(-100.0f, 0.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(100.0f, 0.0f, 0.0f);

	//�e���_�̖@���̐ݒ�
	pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//�e�N�X�`��
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffWall->Unlock();

	//�ǂ̐ݒ�
	SetWall(D3DXVECTOR3(100.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, -1.57f, 0.0f));
	SetWall(D3DXVECTOR3(0.0f, 0.0f, -100.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f));
	SetWall(D3DXVECTOR3(-100.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 1.57f, 0.0f));
	SetWall(D3DXVECTOR3(0.0f, 0.0f, 100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
}

//================================================
//�ǂ̏I������
//================================================
void UninitWall(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureWall != NULL)
	{
		g_pTextureWall->Release();
		g_pTextureWall = NULL;
	}

	//���_�o�b�t�@�̉��
	if (g_pVtxBuffWall != NULL)
	{
		g_pVtxBuffWall->Release();
		g_pVtxBuffWall = NULL;
	}
}

//================================================
//�ǂ̍X�V����
//================================================
void UpdataWall(void)
{

}

//================================================
//�ǂ̕`�揈��
//================================================
void DrawWall(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureWall);

	for (int nCntWall = 0; nCntWall < MAX_WALL; nCntWall++)
	{
		//���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_Wall[nCntWall].mtxWorld);

		//�����𔽓]
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Wall[nCntWall].rot.y, g_Wall[nCntWall].rot.x, g_Wall[nCntWall].rot.z);
		D3DXMatrixMultiply(&g_Wall[nCntWall].mtxWorld, &g_Wall[nCntWall].mtxWorld, &mtxRot);

		//�ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTrans, g_Wall[nCntWall].pos.x, g_Wall[nCntWall].pos.y, g_Wall[nCntWall].pos.z);
		D3DXMatrixMultiply(&g_Wall[nCntWall].mtxWorld, &g_Wall[nCntWall].mtxWorld, &mtxTrans);

		//���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_Wall[nCntWall].mtxWorld);

		//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
		pDevice->SetStreamSource(0, g_pVtxBuffWall, 0, sizeof(VERTEX_3D));

		//���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_3D);

		//�ǂ̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	}

	pDevice->SetTexture(0, NULL);

}

//================================================
//�ǂ̐ݒ菈��
//================================================
void SetWall(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	for (int nCntWall = 0; nCntWall < MAX_WALL; nCntWall++)
	{
		if (g_Wall[nCntWall].bUse == false)
		{
			g_Wall[nCntWall].pos = pos;
			g_Wall[nCntWall].rot = rot;
			g_Wall[nCntWall].bUse = true;
			break;
		}
	}
}