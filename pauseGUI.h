//=====================================
//
//�|�[�YGUI�w�b�_[pauseGUI.h]
//Author:GP11A341 21 ���ԗY��
//
//=====================================
#ifndef _PAUSEGUI_H_
#define _PAUSEGUI_H_

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
void InitPauseGUI(int num);
void UninitPauseGUI(int num);
void UpdatePauseGUI(void);
void DrawPauseGUI(int index, bool selected);
void DrawPauseMenuState(int index, bool selected, bool state);

#endif