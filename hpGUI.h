//=====================================
//
//HPGUI�w�b�_[hpGUI.h]
//Author:GP11A341 21 ���ԗY��
//
//=====================================
#ifndef _HPGUI_H_
#define _HPGUI_H_

#include "main.h"
#include <stdio.h>
/**************************************
�}�N����`
***************************************/

/**************************************
�\���̒�`
***************************************/
typedef struct {
	float radius, angle;
}HPGUI;
/**************************************
�v���g�^�C�v�錾
***************************************/
void InitHpGUI(int num);
void UninitHpGUI(int num);
void UpdateHpGUI(void);
void DrawHpGUI(void);
void DrawHPGUIDebug(void);
void SaveSettinghpGUIGUI(FILE *fp);
void LoadSettingshpGUIGUI(FILE *fp);
#endif