//=====================================
//
//�v���C���[�~�T�C���X���b�O�w�b�_[PlayerMissileSmog.h]
//Author:GP11A341 21 ���ԗY��
//
//=====================================
#ifndef _PLAYERMISSILESMOG_H_
#define _PLAYERMISSILESMOG_H_

#include "main.h"

/**************************************
�}�N����`
***************************************/

/**************************************
�\���̒�`
***************************************/
typedef struct
{
	bool active;
	D3DXVECTOR3 pos;

	int cntFrame;
	int patternAnim;
}PLAYERMISSILESMOG;

/**************************************
�v���g�^�C�v�錾
***************************************/
void InitPlayerMissileSmog(int num);
void UninitPlayerMissileSmog(int num);
void UpdatePlayerMissileSmog(void);
void DrawPlayerMissileSmog(void);
void SetPlayerMissileSmog(D3DXVECTOR3 pos);
#endif