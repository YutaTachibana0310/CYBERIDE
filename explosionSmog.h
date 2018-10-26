//=====================================
//
//�G�N�X�v���[�W�����X���b�O�w�b�_[explosionSmog.h]
//Author:GP11A341 21 ���ԗY��
//
//=====================================
#ifndef _EXPLOSIONSMOG_H_
#define _EXPLOSIONSMOG_H_

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

}EXPLOSIONSMOG;
/**************************************
�v���g�^�C�v�錾
***************************************/
void InitExplosionSmog(int num);
void UninitExplosionSmog(void);
void UpdateExplosionSmog(void);
void DrawExplosionSmog(void);
void SetExplosionSmog(const D3DXVECTOR3 *pos);

#endif