//================================================
//
//3D�A�N�V����(wall.h)
//Author:��e�E�l
//
//================================================
#ifndef _WALL_H_
#define _WALL_H_

#include "main.h"

//================================================
//�}�N����`
//================================================
#define MAX_WALL (4)				//�ǂ̍ő吔

//================================================
//�ǂ̍\����
//================================================
typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
	D3DXMATRIX  mtxWorld;
	bool bUse;
} Wall;

//================================================
//�v���g�^�C�v�錾
//================================================
void InitWall(void);								//�ǂ̏���������
void UninitWall(void);								//�ǂ̏I������
void UpdataWall(void);								//�ǂ̍X�V����
void DrawWall(void);								//�ǂ̕`�揈��
void SetWall(D3DXVECTOR3 pos, D3DXVECTOR3 rot);		//�ǂ̐ݒ菈��

#endif