//=====================================
//
//�V���h�E�w�b�_[shadow.h]
//Author:GP11A341 21 ���ԗY��
//
//=====================================
#ifndef _SHADOW_H_
#define _SHADOW_H_

#include "main.h"

/**************************************
�}�N����`
***************************************/

/**************************************
�\���̒�`
***************************************/

/**************************************
�v���g�^�C�v�錾
***************************************/
void InitShadow(int num);
void UninitShadow(int num);
void UpdateShadow(void);
void DrawShadow(LPD3DXEFFECT effect);
void SetShadow(D3DVECTOR pos);
#endif