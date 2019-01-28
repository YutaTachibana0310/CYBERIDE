//=====================================
//
//�{�[�i�X�L���[�u�w�b�_[bonusCube.h]
//Author:GP11A341 21 ���ԗY��
//
//=====================================
#ifndef _BONUSCUBE_H_
#define _BONUSCUBE_H_

#include "main.h"
#include "collider.h"

/**************************************
�}�N����`
***************************************/

/**************************************
�\���̒�`
***************************************/
typedef struct {
	bool active;						//�A�N�e�B�u����
	WORD id;							//�ŗLID
	float moveSpeed;					//�ړ��X�s�[�h
	D3DXVECTOR3 rotValue;				//��]��
	COLLIDER_CUBE collider;				//�����蔻��
	float hp;							//HP
	D3DXVECTOR3 pos;					//���W
	D3DXVECTOR3 rot;					//��]��
	float scale;						//�X�P�[��

	int cntFrame;						//�J�E���g�t���[��
	D3DXVECTOR3 startPos, goalPos;		//�X�^�[�g���W�A�G���h���W
	int cntMove;						//�ړ���
}BONUS_CUBE_OBJECT;

/**************************************
�v���g�^�C�v�錾
***************************************/
void InitBonusCube(int num);
void UninitBonusCube(int num);
void UpdateBonusCube(void);
void DrawBonusCube(void);

void LockonBonusCube(void);
bool SetBonusCube(D3DXVECTOR3 *setPos);
bool IsAllBonusCubeDisable(void);

#endif