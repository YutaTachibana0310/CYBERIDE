//=====================================
//
//�p�[�e�B�N���}�l�[�W���w�b�_[particleManager.h]
//Author:GP11A341 21 ���ԗY��
//
//=====================================
#ifndef _PARTICLEMANAGER_H_
#define _PARTICLEMANAGER_H_

#include "main.h"

/**************************************
�}�N����`
***************************************/
#define FVF_PARTICLE	(D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1)

/**************************************
�\���̒�`
***************************************/
typedef struct
{
	D3DXVECTOR3 vtx;		// ���_���W
	D3DCOLOR diffuse;		// ���ˌ�
	D3DXVECTOR2 tex;		// �e�N�X�`�����W
} VERTEX_PRATICLE;


/**************************************
�v���g�^�C�v�錾
***************************************/
void InitParticleManager(int num);
void UninitParticleManager(void);
void UpdateParticleManager(void);
void DrawParticleManager(void);

#endif