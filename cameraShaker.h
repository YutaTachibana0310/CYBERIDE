//=====================================
//
//�J�����V�F�C�J�[�w�b�_[cameraShaker.h]
//Author:GP11A341 21 ���ԗY��
//
//=====================================
#ifndef _CAMERASHAKER_H_
#define _CAMERASHAKER_H_

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
void InitCameraShaker(int num);
void UninitCameraShaker(int num);
void UpdateCameraShaker(void);

void SetCameraShaker(float length);
D3DXVECTOR3 GetCameraOffsetValue(void);

#endif