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
	D3DXVECTOR3 rotValue;		//1�t���[��������̉�]��
	float moveSpeed;			//1�t���[��������̈ړ���
	COLLIDER_CUBE collider;		//�����蔻��
	bool active;
	float hp;

}CUBE_OBJECT;

/**************************************
�v���g�^�C�v�錾
***************************************/
void InitCubeObject(int num);
void UninitCubeObject(int num);
void UpdateCubeObject(void);
void DrawCubeObject(void);

void CollisionCubeObjectAndBullet(void);
void LockonCubeObject(void);

#endif