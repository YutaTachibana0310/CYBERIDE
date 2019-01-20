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
#include "stageData.h"

/**************************************
�}�N����`
***************************************/

/**************************************
�\���̒�`
***************************************/
typedef struct {
	bool active;				//�A�N�e�B�u����
	WORD id;					//�ŗLID
	float moveSpeed;			//�ړ��X�s�[�h
	D3DXVECTOR3 moveDir;		//�ړ�����
	D3DXVECTOR3 rotValue;		//��]��

	COLLIDER_CUBE collider;		//�����蔻��
	float hp;					//HP

	D3DXVECTOR3 pos;			//���W
	D3DXVECTOR3 rot;			//��]��
	float scale;				//�X�P�[��

	int cntFrame;				//�t���[���J�E���g
	int currentState;			//���

	D3DXVECTOR3 startPos;
	D3DXVECTOR3 goalPos;
	int moveDurtaion;

	int type;

	D3DXVECTOR3 controller1;
	D3DXVECTOR3 controller2;

}HARD_CUBE_OBJECT;

enum HARDCUBE_STATE
{
	HardCubeInit,
	HardCubeMove,
	HardCubeNormalAttack,
	HardCubeHomingAttack,
	HardCubeCharge,
	HardCubeEscape,
	HardCubeBezier,
	HardCubeStateMax
};

enum HARDCUBE_TYPE
{
	HardCubeNormalType,
	HardCubeHomingType,
	HardCubeChargeType,
	HardCubeBezierType,
	HardCubeTypeMax
};

/**************************************
�v���g�^�C�v�錾
***************************************/
void InitHardCubeObject(int num);
void UninitHardCubeObject(int num);
void UpdateHardCubeObject(void);
void DrawHardCubeObject(void);

void LockonHardCubeObject(void);
bool SetHardCubeObject(D3DXVECTOR3 *setPos);
void DisableHardCube(HARD_CUBE_OBJECT *ptr);	//��A�N�e�B�u����
void ChangeStateHardCube(HARD_CUBE_OBJECT *ptr, int nextState);
bool SetHardCubeObjectFromData(STAGE_DATA *data);

//�e��ԓ��ꏈ���֐�
void OnEnterHardCubeInit(HARD_CUBE_OBJECT *ptr);
void OnEnterHardCubeMove(HARD_CUBE_OBJECT *ptr);
void OnEnterHardCubeNormalAttack(HARD_CUBE_OBJECT *ptr);
void OnEnterHardCubeHomingAttack(HARD_CUBE_OBJECT *ptr);
void OnEnterHardCubeEscape(HARD_CUBE_OBJECT *ptr);
void OnEnterHardCubeCharge(HARD_CUBE_OBJECT *ptr);
void OnEnterHardCubeBezier(HARD_CUBE_OBJECT *ptr);

//�e��ԍX�V�����֐�
void OnUpdateHardCubeInit(HARD_CUBE_OBJECT *ptr);
void OnUpdateHardCubeMove(HARD_CUBE_OBJECT *ptr);
void OnUpdateHardCubeNormalAttack(HARD_CUBE_OBJECT *ptr);
void OnUpdateHardCubeHomingAttack(HARD_CUBE_OBJECT *ptr);
void OnUpdateHardCubeEscape(HARD_CUBE_OBJECT *ptr);
void OnUpdateHardCubeCharge(HARD_CUBE_OBJECT *ptr);
void OnUpdateHardCubeBezier(HARD_CUBE_OBJECT *ptr);

#endif