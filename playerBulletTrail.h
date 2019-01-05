//=====================================
//
//�v���C���[�o���b�g�w�b�_[PlayerBulletTrail.h]
//Author:GP11A341 21 ���ԗY��
//
//=====================================
#ifndef _PLAYERBULLETTRAIL_H_
#define _PLAYERBULLETTRAIL_H_

#include "main.h"

/**************************************
�}�N����`
***************************************/
#define PLAYERBULLETTRAIL_MAX		(2048)
/**************************************
�\���̒�`
***************************************/
typedef struct
{
	bool active;

	D3DXVECTOR3 pos;
	int cntFrame;
}PLAYERBULLET_TRAIL;
/**************************************
�v���g�^�C�v�錾
***************************************/
void InitPlayerBulletTrail(int num);
void UninitPlayerBulletTrail(int num);
void UpdatePlayerBulletTrail(void);
void DrawPlayerBulletTrail(void);
void SetPlayerBulletTrail(D3DXVECTOR3 pos, float alpha);

#endif