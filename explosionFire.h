//=====================================
//
//�G�N�X�v���[�W�����t�@�C�A�w�b�_[explosionFire.h]
//Author:GP11A341 21 ���ԗY��
//
//=====================================
#ifndef _EXPLOSIONFIRE_H_
#define _EXPLOSIONFIRE_H_

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
	float rot;
	bool active;
	float initSpeed;
	float endSpeed;
	D3DXVECTOR3 moveDir;
	int lifeFrame;
	int cntFrame;
	float scale;
	float alpha;

}EXPLOSIONFIRE;
/**************************************
�v���g�^�C�v�錾
***************************************/
void InitExplosionFire(int num);
void UninitExplosionFire(void);
void UpdateExplosionFire(void);
void DrawExplosionFire(void);
void SetExplosionFire(const D3DXVECTOR3 *pos);

#endif