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
	D3DXVECTOR3 *target;
}ROCKONSITE;

/**************************************
�v���g�^�C�v�錾
***************************************/
void InitRockonSite(int num);
void UninitRockonSite(int num);
void UpdateRockonSite(void);
void DrawRockonSite(void);
void SetRockonSite(int id, D3DXVECTOR3 *target);

#endif