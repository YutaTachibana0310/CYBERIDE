//=====================================
//
//�e���v���[�g�w�b�_[EnemyManager.h]
//Author:GP11A341 21 ���ԗY��
//
//=====================================
#ifndef _ENEMYMANAGER_H_
#define _ENEMYMANAGER_H_

#include "main.h"

/**************************************
�}�N����`
***************************************/

/**************************************
�\���̒�`
***************************************/

/**************************************
�v���g�^�C�v�錾
***************************************/
void InitEnemyManager(int num);
void UninitEnemyManager(int num);
void UpdateEnemyManager(void);
void DrawEnemyManager(void);
void CheckEnemyCollision(void);
void EmmittCubeObject(int num, D3DXVECTOR3 *setPos, float setSpeed);
void EmmittBonusCube(D3DXVECTOR3 *setPos);
void EmittHardCubeObject(int num, D3DXVECTOR3 *setPos);

#endif