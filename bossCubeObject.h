//=====================================
//
//�{�X�L���[�u�I�u�W�F�N�g�w�b�_[bossCubeObject.h]
//Author:GP11A341 21 ���ԗY��
//
//=====================================
#ifndef _BOSSCUBEOBJECT_H_
#define _BOSSCUBEOBJECT_H_

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
	int id;
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
	D3DXVECTOR3 scale;

}BOSS_CUBE_OBJECT;
/**************************************
�v���g�^�C�v�錾
***************************************/
void InitBossCubeObject(int num);
void UninitBossCubeObject(int num);
void UpdateBossCubeObject(void);
void DrawBossCubeObject(void);

#endif