//=====================================
//
//���b�N�I���T�C�g�w�b�_[rockonSite.h]
//Author:GP11A341 21 ���ԗY��
//
//=====================================
#ifndef _ROCKONSITE_H_
#define _ROCKONSITE_H_

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
	int id;

	D3DXVECTOR3 pos;
	D3DXVECTOR3 screenPos;
	float scale;
	int cntFrame;
	float alpha;
	float rot;
}ROCKONSITE;

/**************************************
�v���g�^�C�v�錾
***************************************/
void InitRockonSite(int num);
void UninitRockonSite(int num);
void UpdateRockonSite(void);
void DrawRockonSite(void);
ROCKONSITE *SetRockonSite(int id, D3DXVECTOR3 *target, bool *targetActive);
void ReleaseRockonSite(ROCKONSITE *ptr);
void SetRockonSitePos(int id, D3DXVECTOR3 pos);
void ActivateRockonSite(int id);
#endif