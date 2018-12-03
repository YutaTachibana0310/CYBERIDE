//=====================================
//
//�G�l�~�[�z�[�~���O�o���b�g�g���C���w�b�_[EnemyBulletTrail.h]
//Author:GP11A341 21 ���ԗY��
//
//=====================================
#ifndef _ENEMYBULLETTRAIL_H_
#define _ENEMYBULLETTRAIL_H_

#include "main.h"

/**************************************
�}�N����`
***************************************/
#define ENEMYBULLETTRAIL_MAX		(4096)
/**************************************
�\���̒�`
***************************************/
typedef struct
{
	bool active;

	D3DXVECTOR3 pos;
	int cntFrame;
}ENEMYBULLET_TRAIL;
/**************************************
�v���g�^�C�v�錾
***************************************/
void InitEnemyBulletTrail(int num);
void UninitEnemyBulletTrail(int num);
void UpdateEnemyBulletTrail(void);
void DrawEnemyBulletTrail(void);
void SetEnemyHomingBulletTrail(D3DXVECTOR3 pos);
#endif