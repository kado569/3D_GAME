//================================================
//
//3D�A�N�V����(effect.cpp)
//Author:��e�E�l
//
//================================================
#include "effect.h"
#include "main.h"

//================================================
//�O���[�o���ϐ�
//================================================
LPDIRECT3DTEXTURE9 g_pTextureEffect = NULL;				//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEffect = NULL;		//���_�o�b�t�@�ւ̃|�C���^
Effect g_Effect[MAX_EFFECT];

//================================================
//�G�t�F�N�g�̏������ݒ�
//================================================
void InitEffect(void)
{
	//�f�o�C�X�̎擾 
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	////�e�N�X�`���ǂݍ��� 
	//D3DXCreateTextureFromFile(pDevice,
	//	"data/shadow000.jpg",
	//	&g_pTextureEffect);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * 10,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffEffect,
		NULL);

	VERTEX_3D * pVtx;							//���_���̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(-20.0f, 0.2f, 20.0f);
	pVtx[1].pos = D3DXVECTOR3(20.0f, 0.2f, 20.0f);
	pVtx[2].pos = D3DXVECTOR3(-20.0f, 0.2f, -20.0f);
	pVtx[3].pos = D3DXVECTOR3(20.0f, 0.2f, -20.0f);

	//�e���_�̖@���̐ݒ�
	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//�o�b�t�@�A�����b�N
	g_pVtxBuffEffect->Unlock();
}

//================================================
//�G�t�F�N�g�̏I������
//================================================
void UninitEffect(void)
{
	//�o�b�t�@�j��
	if (g_pVtxBuffEffect != NULL)
	{
		g_pVtxBuffEffect->Release();
		g_pVtxBuffEffect = NULL;
	}

	//�e�N�X�`���j��
	if (g_pTextureEffect != NULL)
	{
		g_pTextureEffect->Release();
		g_pTextureEffect = NULL;
	}
}

//================================================
//�G�t�F�N�g�̍X�V����
//================================================
void UpdateEffect(void)
{

}

//================================================
//�G�t�F�N�g�̕`�揈��
//================================================
void DrawEffect(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans;

	//���Z�����̐ݒ�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	//�e�N�X�`���ݒ�
	pDevice->SetTexture(0, g_pTextureEffect);

	for (int nCntEffect = 0; nCntEffect <MAX_EFFECT; nCntEffect++)
	{
		if (g_Effect[nCntEffect].bUse == true)
		{
			//���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_Effect[nCntEffect].mtxWorld);

			//�ʒu�𔽓]
			D3DXMatrixTranslation(&mtxTrans, g_Effect[nCntEffect].pos.x, g_Effect[nCntEffect].pos.y, g_Effect[nCntEffect].pos.z);
			D3DXMatrixMultiply(&g_Effect[nCntEffect].mtxWorld, &g_Effect[nCntEffect].mtxWorld, &mtxTrans);

			//���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_Effect[nCntEffect].mtxWorld);

			//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffEffect, 0, sizeof(VERTEX_3D));

			//���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			//�e�N�X�`���ݒ�
			pDevice->SetTexture(0, g_pTextureEffect);

			//�|���S���`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);		//�v���~�e�B�u�̎��
		}
	}
	//�ݒ�����ɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//�e�N�X�`�������Ƃɖ߂�
	pDevice->SetTexture(0, NULL);
}

//================================================
//�G�t�F�N�g�̐ݒ�
//================================================
//void SetEffect(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 move, D3DXCOLOR col)
//{
//	for (int nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
//	{
//		if (g_Effect[nCntEffect].bUse == false)
//		{
//			
//			g_Effect[nCntEffect].bUse = true;
//			break;
//		}
//	}
//}
