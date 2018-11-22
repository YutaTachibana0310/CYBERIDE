//=====================================
//
//�v���C���[�~�T�C���w�b�_[playerMissile.h]
//Author:GP11A341 21 ���ԗY��
//
//=====================================
#ifndef _PLAYERMISSILE_H_
#define _PLAYERMISSILE_H_

#include "main.h"
#include "collider.h"

/**************************************
�}�N����`
***************************************/
#define PLAYERMISSILE_MAX	(64)

/**************************************
�\���̒�`
***************************************/
typedef struct
{
	bool active;
	D3DXVECTOR3 pos, rot;
	D3DXVECTOR3 *target;
	float *targetHP;

	int cntFrame;			//�J�E���g�t���[��
	int reachFrame;			//���e�^�C�~���O
	D3DXVECTOR3 velocity;	//�i�s���x

}PLAYERMISSILE;

/**************************************
�v���g�^�C�v�錾
***************************************/
void InitPlayerMissile(int num);
void UninitPlayerMissile(int num);
void UpdatePlayerMissile(void);
void DrawPlayerMissile(void);
void SetPlayerMissile(D3DXVECTOR3 *target, float *pTargetHP, D3DXVECTOR3 pos);
void ColliisonPlayerMissileAndEnemyMissile(void);
#endif