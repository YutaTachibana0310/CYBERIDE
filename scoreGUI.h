//=============================================================================
//
// �X�R�AGUI�w�b�_ [ScoreGUI.h]
// Author : GP11A341 21 ���ԗY��
//
//=============================================================================
#ifndef _SCOREGUI_H_
#define _SCOREGUI_H_

#include "main.h"
#include <stdio.h>
// �}�N����`


//*****************************************************************************
// �\���̒�`
//*****************************************************************************
typedef struct {
	float					radius;						// �|���S���̔��a
	float					angle;						// �|���S���̊p�x
}SCOREGUI;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitScoreGUI(int num);							//�X�R�AGUI����������
void UninitScoreGUI(int num);							//�X�R�AGUI�I������
void UpdateScoreGUI(void);								//�X�R�AGUI�X�V����
void DrawScoreGUI(void);								//�X�R�AGUI�`�揈��
void DrawScoreGUIDebug(void);
void SaveSettingScoreGUI(FILE *fp);
void LoadSettingsScoreGUI(FILE *fp);
#endif
