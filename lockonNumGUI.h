//=====================================
//
//���b�N�I����GUI�w�b�_[lockonNumGUI.h]
//Author:GP11A341 21 ���ԗY��
//
//=====================================
#ifndef _LOCKONNUMGUI_H_
#define _LOCKONNUMGUI_H_

#include "main.h"
#include <stdio.h>
/**************************************
�}�N����`
***************************************/

/**************************************
�\���̒�`
***************************************/

/**************************************
�v���g�^�C�v�錾
***************************************/
void InitLockonNumGUI(int num);
void UninitLockonNumGUI(int num);
void UpdateLockonNumGUI(void);
void DrawLockonNumGUI(void);
void DrawLockNumlevelGUIDebug(void);
void SaveSettingLockonLevelGUI(FILE *fp);
void LoadSettingsLockonNumGUI(FILE *fp);
#endif