//=====================================
//
//�X�R�A�{��GUI�w�b�_[scoreMagniGUI.h]
//Author:GP11A341 21 ���ԗY��
//
//=====================================
#ifndef _SCOREMAGNIGUI_H_
#define _SCOREMAGNIGUI_H_

#include "main.h"

/**************************************
�}�N����`
***************************************/

/**************************************
�\���̒�`
***************************************/
typedef struct {
	bool active;
	int cntFrame;
	D3DXVECTOR3 pos;
}SCOREMAGNI_GUI;
/**************************************
�v���g�^�C�v�錾
***************************************/
void InitScoreMagniGUI(int num);
void UninitScoreMagniGUI(int num);
void UpdateScoreMagniGUI(void);
void DrawScoreMagniGUI(LPD3DXEFFECT effect);
void SetScoreMagniGUI(D3DXVECTOR3 pos);
#endif