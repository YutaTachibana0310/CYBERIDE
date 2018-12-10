//=====================================
//
//�e���v���[�g�w�b�_[playerBullet.h]
//Author:GP11A341 21 ���ԗY��
//
//=====================================
#ifndef _PLAYERBULLET_H_
#define _PLAYERBULLET_H_

#include "main.h"
#include "collider.h"
/**************************************
�}�N����`
***************************************/
#define PLAYERBULLET_MAX				(128)
#define PLAYERBULLET_COLLIDER_RAIDUS	(5.0f)
/**************************************
�\���̒�`
***************************************/
typedef struct
{
	bool active;

	D3DXVECTOR3 pos, rot, scale;
	D3DXVECTOR3 moveDir;
	float rotation;
	float speed;
	int cntFrame;

	SPHERE collider;
}PLAYERBULLET;
/**************************************
�v���g�^�C�v�錾
***************************************/
void InitPlayerBullet(int num);
void UninitPlayerBullet(int num);
void UpdatePlayerBullet(void);
void DrawPlayerBullet(void);
void SetPlayerBullet(D3DXVECTOR3 pos, float speed);
PLAYERBULLET *GetPlayerBulletAdr(int id);
void SetPlayerBulletState(int state);

#endif