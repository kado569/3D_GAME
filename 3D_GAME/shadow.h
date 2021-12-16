//================================================
//
//3D�A�N�V����(shadow.h)
//Author:��e�E�l
//
//================================================
#ifndef _SHADOW_H_
#define _SHADOW_H_

#include "main.h"

//================================================
//�}�N����`
//================================================
#define MAX_SHADOW		(10)	//�e�̍ő吔

//================================================
//�e�̍\����
//================================================
typedef struct
{
	D3DXVECTOR3 pos;			//���_���W
	D3DXVECTOR3 rot;			//����
	D3DXMATRIX mtxWorld;		//���[���h�}�g���b�N�X
	bool bUse;
}Shadow;

//================================================
//�v���g�^�C�v�錾
//================================================
void InitShadow(void);
void UninitShadow(void);
void UpdateShadow(void);
void DrawShadow(void);
int SetShadow(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
void SetPositionShadow(int nIbxShadow, D3DXVECTOR3 pos);

#endif