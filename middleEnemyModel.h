//=====================================
//
//�~�h���G�l�~�[���f���w�b�_[middleEnemyModel.h]
//Author:GP11A341 21 ���ԗY��
//
//=====================================
#ifndef _MIDDLEENMYMODEL_H_
#define _MIDDLEENMYMODEL_H_

#include "main.h"

/**************************************
�}�N����`
***************************************/
#define MIDDLEENEMY_MAX			(36)
/**************************************
�\���̒�`
***************************************/
typedef struct
{
	bool active;

	D3DXVECTOR3 pos;
	
}MIDDLEENMYMODEL;
/**************************************
�v���g�^�C�v�錾
***************************************/
void InitMiddleEnemyModel(int num);
void UninitMiddleEnemyModel(int num);
void UpdateMiddleEnemyModel(void);
void DrawMiddleEnemyModel(void);

#endif