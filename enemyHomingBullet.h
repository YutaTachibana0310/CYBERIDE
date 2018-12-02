//=====================================
//
//�G�l�~�[�z�[�~���O�o���b�g�w�b�_[EnemyHomingBullet.h]
//Author:GP11A341 21 ���ԗY��
//
//=====================================
#ifndef _ENEMYHOMINGBULLET_H_
#define _ENEMYHOMINGBULLET_H_

#include "main.h"

/**************************************
�}�N����`
***************************************/
#define ENEMYHOMINGBULLET_MAX		(4096)

/**************************************
�\���̒�`
***************************************/
typedef struct
{
	bool active = false;

	D3DXVECTOR3 pos;

	int targetPlayerID;
	int cntFrame;
	D3DXVECTOR3 velocity;

}ENEMYHOMINGBULLET;
/**************************************
�v���g�^�C�v�錾
***************************************/
void InitEnemyHomingBullet(int num);
void UninitEnemyHomingBullet(int num);
void UpdateEnemyHomingBullet(void);
void DrawEnemyHomingBullet(void);
void SetEnemyHomingBullet(D3DXVECTOR3 pos, D3DXVECTOR3 moveDir, float speed);
#endif