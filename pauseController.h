//=====================================
//
//�|�[�Y�R���g���[���[�w�b�_[pauseController.h]
//Author:GP11A341 21 ���ԗY��
//
//=====================================
#ifndef _PAUSECONTROLLER_H_
#define _PAUSECONTROLLER_H_

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
void InitPauseController(int num);
void UninitPauseController(int num);
void UpdatePauseController(void);
void DrawPauseController(void);
bool GetPauseState(void);

#endif