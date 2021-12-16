//================================================
//
//3D�A�N�V����(billboard.cpp)
//Author:��e�E�l
//
//================================================
#ifndef _BILLBOARD_H_
#define _BILLBOARD_H_

#include "main.h"

//================================================
//�}�N����`
//================================================
#define MAX_BILLBOARD	(256)	//�r���{�[�h�̍ő吔

//================================================
//�r���{�[�h�̍\����
//================================================
typedef struct
{
	D3DXVECTOR3 pos;		//�ʒu
	D3DXVECTOR3 rot;		//����
	D3DXMATRIX mtxWorld;	//���[���h�}�g���b�N�X
	bool bUse;				//�g�p���Ă��邩
	int IdxShadow;			//�e�̐ݒu
}Billboard;

//================================================
//�v���g�^�C�v�錾
//================================================
void InitBillboard(void);
void UninitBillboard(void);
void UpdateBillboard(void);
void DrawBillboard(void);
void SetBillboard(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
#endif