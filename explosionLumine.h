//=====================================
//
//�������~�l�w�b�_[explosionLumine.h]
//Author:GP11A341 21 ���ԗY��
//
//=====================================
#ifndef _EXPLOSIONLUMINE_H_
#define _EXPLOSIONLUMINE_H_

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
	int cntFrame;
	int lifeFrame;
	D3DXVECTOR3 moveDir;
}EXPLOSION_LUMINE;

/**************************************
�v���g�^�C�v�錾
***************************************/
void InitExplosionLumine(int num);
void UninitExplosionLumine(int num);
void UpdateExplosionLumine(void);
void DrawExplosionLumine(LPD3DXEFFECT effect);
void SetExplosionLumine(D3DXVECTOR3 *setPos);

#endif