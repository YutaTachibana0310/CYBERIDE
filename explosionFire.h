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
	D3DXVECTOR3 rot;
	bool active;

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