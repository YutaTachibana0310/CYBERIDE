//=====================================
//
//�L���[�u�I�u�W�F�N�g�w�b�_[cubeObject.h]
//Author:GP11A341 21 ���ԗY��
//
//=====================================
#ifndef _CUBEOBJECT_H_
#define _CUBEOBJECT_H_

#include "main.h"
#include "collider.h"

/**************************************
�}�N����`
***************************************/

/**************************************
�\���̒�`
***************************************/
typedef struct
{
	bool active;				//�A�N�e�B�u����
	WORD id;					//�ŗLID
	D3DXVECTOR3 rotValue;		//1�t���[��������̉�]��
	float moveSpeed;			//1�t���[��������̈ړ���
	COLLIDER_CUBE collider;		//�����蔻��
	float hp;					//HP
	D3DXVECTOR3 pos;			//���W
	D3DXVECTOR3 rot;			//��]
	float scale;				//�X�P�[��
}CUBE_OBJECT;

/**************************************
�v���g�^�C�v�錾
***************************************/
void InitCubeObject(int num);
void UninitCubeObject(int num);
void UpdateCubeObject(void);
void DrawCubeObject(void);

void LockonCubeObject(void);
void DamageAllCubeObject(void);
bool SetCubeObject(D3DXVECTOR3 *setPos, float speed);
#endif