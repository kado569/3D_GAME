//================================================
//
//3D�A�N�V����(meshfield.h)
//Author:��e�E�l
//
//================================================
#ifndef _MESHFILD_H_
#define _MESHFILD_H_

#include "main.h"

//================================================
//���b�V���̍\����
//================================================
typedef struct
{
	D3DXVECTOR3 pos;			//���_���W
	D3DXVECTOR3 rot;			//����
	D3DXMATRIX mtxWorld;		//���[���h�}�g���b�N�X
}Meshfield;

//================================================
//�}�N����`
//================================================
#define MESHFIELD_X_BLOCK	(2)	//X�����̃u���b�N��
#define MESHFIELD_Z_BLOCK	(2)	//Z�����̃u���b�N��
#define MESHFIELD_VERTEX_NUM	((MESHFIELD_X_BLOCK + 1) * (MESHFIELD_Z_BLOCK + 1))
#define MESHFIELD_INDEX_NUM		(((MESHFIELD_X_BLOCK + 1) * 2 * MESHFIELD_Z_BLOCK)  + ( MESHFIELD_Z_BLOCK - 1) * 2)
#define MESHFIELD_PRIMITIVE_NUM	(MESHFIELD_X_BLOCK * MESHFIELD_Z_BLOCK * 2 + (MESHFIELD_Z_BLOCK - 1) * ((MESHFIELD_X_BLOCK * MESHFIELD_X_BLOCK) -2))

//================================================
//�v���g�^�C�v�錾
//================================================
void InitMeshfield(void);
void UninitMeshfield(void);
void UpdateMeshfield(void);
void DrawMeshfield(void);

#endif