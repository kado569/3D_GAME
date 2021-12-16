//================================================
//
//3D�A�N�V����(meshfield.cpp)
//Author:��e�E�l
//
//================================================
#include "main.h"
#include "meshfield.h"

//================================================
//�O���[�o���ϐ�
//================================================
LPDIRECT3DTEXTURE9 g_pTextureMeshfield = NULL;			//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMeshfield = NULL;		//���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffMeshfield = NULL;		//�C���f�b�N�X�ւ̃|�C���^
Meshfield g_Meshfield;

//================================================
//���b�V���̏������ݒ�
//================================================
void InitMeshfield(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�e�N�X�`���ǂݍ��� 
	D3DXCreateTextureFromFile(pDevice,
		"data/cave001.jpg",
		&g_pTextureMeshfield);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * MESHFIELD_VERTEX_NUM,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffMeshfield,
		NULL);

	//�C���f�b�N�X�o�b�t�@�̍쐬
	pDevice->CreateIndexBuffer(sizeof(WORD) * 1000,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,							//���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,
		&g_pIdxBuffMeshfield,
		NULL);

	VERTEX_3D * pVtx ;							//���_���̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffMeshfield->Lock(0, 0, (void**)&pVtx, 0);

	//�C���f�b�N�X�o�b�t�@���b�N
	WORD *pIdx;
	g_pIdxBuffMeshfield->Lock(0, 0, (void**)&pIdx, 0);

	for (int nCntZ = 0; nCntZ < MESHFIELD_Z_BLOCK + 1; nCntZ++)
	{
		for (int nCntX = 0; nCntX < MESHFIELD_X_BLOCK + 1; nCntX++)
		{
			//���_���W�ݒ�
			pVtx[0].pos = D3DXVECTOR3(-100.0f + 70.0f * nCntX, 0.0f, 100.0f - 70.0f * nCntZ);

			//�e���_�̖@���ݒ�i�x�N�g���̑傫����1�ɂ���j
			pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

			//���_�J���[�̐ݒ�
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);

			pVtx++;
		}
	}

	for (int nCntZ = 0; nCntZ < MESHFIELD_Z_BLOCK + 1; nCntZ++)
	{
		for (int nCntX = 0; nCntX < MESHFIELD_X_BLOCK + 1; nCntX++)
		{
			//�C���f�b�N�X�̐ݒ�
			pIdx[0] = (nCntX + MESHFIELD_X_BLOCK + 1) *(nCntZ + 1);			//���i�̒��_
			pIdx[1] = (nCntX + MESHFIELD_X_BLOCK + 1) * nCntZ;				//��i�̒��_
			pIdx += 2;
		}

		if (nCntZ < MESHFIELD_Z_BLOCK - 1)
		{//�k�ރ|���S���̍쐬
			pIdx[0] = pIdx[-1];		//�ЂƂO��pIdx�̒l������
			pIdx[1] = (MESHFIELD_X_BLOCK + 1)*(nCntZ + 2);
			pIdx += 2;
		}

	}

	//�C���f�b�N�X�o�b�t�@�A�����b�N
	g_pIdxBuffMeshfield->Unlock();

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffMeshfield->Unlock();
}

//================================================
//�|���S���̏I������
//================================================
void UninitMeshfield(void)
{
	//�o�b�t�@�j��
	if (g_pVtxBuffMeshfield != NULL)
	{
		g_pVtxBuffMeshfield->Release();
		g_pVtxBuffMeshfield = NULL;
	}

	//�e�N�X�`���j��
	if (g_pTextureMeshfield != NULL)
	{
		g_pTextureMeshfield->Release();
		g_pTextureMeshfield = NULL;
	}

	//�C���f�b�N�X�j��
	if (g_pIdxBuffMeshfield != NULL)
	{
		g_pIdxBuffMeshfield->Release();
		g_pIdxBuffMeshfield = NULL;
	}

}

//================================================
//�|���S���̍X�V����
//================================================
void UpdateMeshfield(void)
{

}

//================================================
//�|���S���̕`�揈��
//================================================
void DrawMeshfield(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans;

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_Meshfield.mtxWorld);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Meshfield.rot.y, g_Meshfield.rot.x, g_Meshfield.rot.z);
	D3DXMatrixMultiply(&g_Meshfield.mtxWorld, &g_Meshfield.mtxWorld, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, g_Meshfield.pos.x, g_Meshfield.pos.y, g_Meshfield.pos.z);
	D3DXMatrixMultiply(&g_Meshfield.mtxWorld, &g_Meshfield.mtxWorld, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_Meshfield.mtxWorld);

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffMeshfield, 0, sizeof(VERTEX_3D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	//�e�N�X�`���ݒ�
	pDevice->SetTexture(0, g_pTextureMeshfield);

	//�|���S���`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);		//�v���~�e�B�u�̎��
}