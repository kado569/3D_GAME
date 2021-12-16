//================================================
//
//3D�A�N�V����(effect.h)
//Author:��e�E�l
//
//================================================
#ifndef _EFFECT_H_
#define _EFFECT_H_

#include "main.h"

//================================================
//�}�N����`
//================================================
#define MAX_EFFECT		(10)	//�e�̍ő吔

//================================================
//�G�t�F�N�g�̍\����
//================================================
typedef struct
{
	D3DXVECTOR3 pos;			//���_���W
	D3DXMATRIX mtxWorld;		//���[���h�}�g���b�N�X
	bool bUse;
}Effect;

//================================================
//�v���g�^�C�v�錾
//================================================
void InitEffect(void);
void UninitEffect(void);
void UpdateEffect(void);
void DrawEffect(void);
int SetEffect(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 move, D3DXCOLOR col);

#endif