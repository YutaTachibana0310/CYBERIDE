//=====================================
//
//�G�N�X�v���[�W�����t���A[explosionFire.h]
//Author:GP11A341 21 ���ԗY��
//
//=====================================
#ifndef _EXPLOSIONFLARE_H_
#define _EXPLOSIONFLARE_H_

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
	float initScale;

}EXPLOSIONFLARE;
/**************************************
�v���g�^�C�v�錾
***************************************/
void InitExplosionFlare(int num);
void UninitExplosionFlare(void);
void UpdateExplosionFlare(void);
void DrawExplosionFlare(LPDIRECT3DVERTEXDECLARATION9 declare, LPD3DXEFFECT effect);
void SetExplosionFlare(const D3DXVECTOR3 *pos);

#endif