//=====================================
//
//�{�[�i�X�|�W�V�����w�b�_[bonusPositionTelop.h]
//Author:GP11A341 21 ���ԗY��
//
//=====================================
#ifndef _BONUSPOSITIONTELOP_H_
#define _BONUSPOSITIONTELOP_H_

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
void InitBonusPositionTelop(int num);
void UninitBonusPositionTelop(int num);
void UpdateBonusPositionTelop(void);
void DrawBonusPositionTelop(void);
void SetStateBonusPositionTelop(bool state);
void SetPositionBonusPositionTelop(D3DXVECTOR3 setPos);
#endif