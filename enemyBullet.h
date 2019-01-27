//=====================================
//
//�G�l�~�[�o���b�g�w�b�_[EnemyBullet.h]
//Author:GP11A341 21 ���ԗY��
//
//=====================================
#ifndef _ENEMYBULLET_H_
#define _ENEMYBULLET_H_

#include "main.h"
#include "collider.h"

/**************************************
�}�N����`
***************************************/
#define ENEMYBULLET_MAX		(4096)

/**************************************
�\���̒�`
***************************************/
typedef struct
{
	bool active = false;

	D3DXVECTOR3 pos;

	D3DXVECTOR3 moveDir;
	float speed;
	COLLIDER_CUBE collider;
}ENEMYBULLET;
/**************************************
�v���g�^�C�v�錾
***************************************/
void InitEnemyBullet(int num);
void UninitEnemyBullet(int num);
void UpdateEnemyBullet(void);
void DrawEnemyBullet(void);
void SetEnemyBullet(D3DXVECTOR3 pos, D3DXVECTOR3 moveDir, float speed);
#endif