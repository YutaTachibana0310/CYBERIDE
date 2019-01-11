//=====================================
//
//�n�[�h�L���[�u�I�u�W�F�N�g�w�b�_[hardCubeObject.h]
//Author:GP11A341 21 ���ԗY��
//
//=====================================
#ifndef _HARDCUBEOBJECT_H_
#define _HARDCUBEOBJECT_H_

#include "main.h"
#include "collider.h"

/**************************************
�}�N����`
***************************************/

/**************************************
�\���̒�`
***************************************/
typedef struct {
	bool active;				//�A�N�e�B�u����
	float moveSpeed;			//�ړ��X�s�[�h
	D3DXVECTOR3 rotValue;		//��]��
	COLLIDER_CUBE collider;		//�����蔻��
	float hp;					//HP
	D3DXVECTOR3 pos;			//���W
	D3DXVECTOR3 rot;			//��]��

}HARD_CUBE_OBJECT;
/**************************************
�v���g�^�C�v�錾
***************************************/
void InitHardCubeObject(int num);
void UninitHardCubeObject(int num);
void UpdateHardCubeObject(void);
void DrawHardCubeObject(void);

void LockonHardCubeObject(void);

#endif