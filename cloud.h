//==========================================
//
//�_�w�b�_[cloud.h]
//Author:GP11A341 21 ���ԗY��
//
//==========================================
#ifndef _CLOUD_H_
#define _CLOUD_H_

#include "main.h"

/******************************************
�}�N����`
*******************************************/

/******************************************
�\���̒�`
*******************************************/
typedef struct _CLOUD
{
	bool active;			//�g�p�t���O
	D3DXVECTOR3 pos;		//���W
	float rot;				//��]��
	_CLOUD* next;			//���X�g�\���̎��̉_�ւ̃|�C���^
}CLOUD;

/******************************************
�v���g�^�C�v�錾
*******************************************/
void InitCloud(int num);
void UninitCloud(void);
void UpdateCloud(void);
void DrawCloud(void);
void SetCloud(D3DXVECTOR3 pos);
#endif