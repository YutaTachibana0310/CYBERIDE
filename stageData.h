//=====================================
//
//�X�e�[�W�f�[�^�w�b�_[stageData.h]
//Author:GP11A341 21 ���ԗY��
//
//=====================================
#ifndef _STAGEDATA_H_
#define _STAGEDATA_H_

#include "main.h"

/**************************************
�}�N����`
***************************************/

/**************************************
�\���̒�`
***************************************/
typedef struct
{
	int emmittFrame;
	int type;
	D3DXVECTOR3 initPos;
	D3DXVECTOR3 targetPos;
}STAGE_DATA;
/**************************************
�v���g�^�C�v�錾
***************************************/
void InitStageData(int num);
void UninitStageData(int num);
int UpdateStageData(STAGE_DATA *out, DWORD currentFrame);

#endif