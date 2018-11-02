//=====================================
//
//�p�[�e�B�N���}�l�[�W���w�b�_[particleManager.h]
//Author:GP11A341 21 ���ԗY��
//
//=====================================
#ifndef _PARTICLEMANAGER_H_
#define _PARTICLEMANAGER_H_

#include "main.h"
#include "Easing.h"

/**************************************
�}�N����`
***************************************/
#define PARTICLE_INITPOS (D3DXVECTOR3(-9999.9f, -9999.9f, -9999.9f))	//�����ʒu

/**************************************
�\���̒�`
***************************************/
typedef struct
{
	float x, y, z;
	float u, v;
} VERTEX_PARTICLE;		//�p�[�e�B�N�����_�\����

typedef struct
{
	float u, v;
} VERTEX_UV;			//�p�[�e�B�N��UV�\����

typedef struct
{
	float r, g, b, a;
} VERTEX_COLOR;			//�p�[�e�B�N���J���[�\����

typedef struct
{
	bool active;
	int cntFrame, lifeFrame;

	//�X�s�[�h
	float initSpeed, endSpeed;
	EASING_TYPE speedType;

	//�X�P�[��
	float initScale, endScale;
	EASING_TYPE scaleType;

	//�J���[
	float initRed, initGreen, initBlue, initAlpha;
	float endRed, endGreen, endBlue, endAlpha;
	EASING_TYPE colorType;

	D3DXVECTOR3 pos;
	D3DXVECTOR3 moveDir;	
}PARTICLE;				//�p�[�e�B�N���\����

/**************************************
�v���g�^�C�v�錾
***************************************/
void InitParticleManager(int num);
void UninitParticleManager(void);
void UpdateParticleManager(void);
void DrawParticleManager(void);

#endif