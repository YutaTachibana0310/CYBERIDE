//=====================================
//
//�f�o�b�O�E�B���h�E�w�b�_[debugWindow.h]
//Author:GP11A341 21 ���ԗY��
//
//=====================================
#ifndef _DEBUGWINDOW_H_
#define _DEBUGWINDOW_H_

#include "main.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_win32.h"
#include "imgui/imgui_impl_dx9.h"

/**************************************
�}�N����`
***************************************/
#define USE_DEBUGWINDOW
#define STR(var) #var		//var�𕶎���ɒu������}�N��
/**************************************
�\���̒�`
***************************************/

/**************************************
�v���g�^�C�v�錾
***************************************/
void InitDebugWindow(HWND hWnd, LPDIRECT3DDEVICE9 pDevice);
void UninitDebugWindow(int num);
void UpdateDebugWindow(void);
void DrawDebugWindow(void);

void BeginTimerCount(void);				//���𑜓x�^�C�}�[�v���J�n
double GetProgressTimerCount(void);		//�^�C�}�[�o�ߎ��Ԏ擾����
void GetTimerCount(LARGE_INTEGER *ptr);	//�^�C�}�[�J�E���g�擾(20�t���[���Ԋu)
double CalcProgressTime(LARGE_INTEGER start, LARGE_INTEGER end);	//�o�ߎ��Ԏ擾	
#endif