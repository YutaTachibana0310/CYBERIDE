//=====================================
//
//�^�[�Q�b�g�T�C�g�w�b�_[targetSite.h]
//Author:GP11A341 21 ���ԗY��
//
//=====================================
#ifndef _TARGETSITE_H_
#define _TARGETSITE_H_

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

}TARGETSITE;
/**************************************
�v���g�^�C�v�錾
***************************************/
void InitTargetSite(int num);
void UninitTargetSite(int num);
void UpdateTargetSite(void);
void DrawTargetSite(void);
void SetTargetSitePosition(D3DXVECTOR3 pos, int id);
TARGETSITE *GetTargetSiteADr(int id);
#endif