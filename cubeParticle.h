//=====================================
//
//�L���[�u�p�[�e�B�N���w�b�_[cubeParticle.h]
//Author:GP11A341 21 ���ԗY��
//
//=====================================
#ifndef _CUBEOBJECT_H_
#define _CUBEOBJECT_H_

#include "main.h"
#include "collider.h"

/**************************************
�}�N����`
***************************************/

/**************************************
�\���̒�`
***************************************/
typedef struct
{
	bool active;
	
	D3DXVECTOR3 moveDir;
	int cntFrame;
	

}CUBE_PARTICLE;

/**************************************
�v���g�^�C�v�錾
***************************************/
void InitCubeParticle(int num);
void UninitCubeParticle(int num);
void UpdateCubeParticle(void);
void DrawCubeParticle(void);

void SetCubeParticle(D3DXVECTOR3 setPos, D3DXCOLOR col);
#endif