//=====================================
//
//�G�l�~�[�~�T�C���X���b�O�w�b�_[enemyMissileSmog.h]
//Author:GP11A341 21 ���ԗY��
//
//=====================================
#ifndef _ENEMYMISSILESMOG_H_
#define _ENEMYMISSILESMOG_H_

#include "main.h"

/**************************************
�}�N����`
***************************************/

/**************************************
�\���̒�`
***************************************/
typedef struct
{
	D3DXVECTOR3 pos;
	int cntFrame;
	bool active;
}EnemyMissileSmog;
/**************************************
�v���g�^�C�v�錾
***************************************/
void InitEnemyMissileSmog(int num);
void UninitEnemyMissileSmog(void);
void UpdateEnemyMissileSmog(void);
void DrawEnemyMissileSmog(void);
void SetEnemyMissileSmog(D3DXVECTOR3 pos);

#endif