//=====================================
//
//���b�N�I��GUI�w�b�_[lockonGUI.h]
//Author:GP11A341 21 ���ԗY��
//
//=====================================
#ifndef _LOCKONGUI_H_
#define _LOCKONGUI_H_

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
	int state;
}LOCKONGUI;
/**************************************
�v���g�^�C�v�錾
***************************************/
void InitLockonGUI(int num);
void UninitLockonGUI(int num);
void UpdateLockonGUI(void);
void DrawLockonGUI(void);
void SetLockonGUIPos(int id, D3DXVECTOR3 pos);
LOCKONGUI *GetLockonGUIAdr(int id);
#endif