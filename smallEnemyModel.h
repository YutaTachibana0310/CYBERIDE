//=====================================
//
//�X���[���G�l�~�[�w�b�_[smallEnemyModel.h]
//Author:GP11A341 21 ���ԗY��
//
//=====================================
#ifndef _SMALLENEMY_H_
#define _SMALLENEMY_H_

#include "main.h"
#include "collider.h"

/**************************************
�}�N����`
***************************************/
#define SMALLENEMY_MAX			(128)

/**************************************
�\���̒�`
***************************************/
//�X���[���G�l�~�[��Ԓ�`
enum SMALLENEMY_STATE
{
	SmallEnemyMove,			//�ړ����
	SmallEnemyAttack,		//�U�����
	SmallEnemyEscape,		//�������
	SmallEnemyWait,			//�ҋ@���
	SmallEnemyStateMax		
};

//�X���[���G�l�~�[�\����
typedef struct
{
	bool active;

	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
	int cntFrame;
	int state;

	D3DXVECTOR3 startPos, goalPos;
	D3DXVECTOR3 startRot, goalRot;

	float hp;
	int atkNum;

	SPHERE collider;
}SMALLENEMY;
/**************************************
�v���g�^�C�v�錾
***************************************/
void InitSmallEnemy(int num);
void UninitSmallEnemy(int num);
void UpdateSmallEnemy(void);
void DrawSmallEnemy(void);
void ChangeStateSmallEnemy(SMALLENEMY *ptr, int next);
SMALLENEMY *GetSmallEnemyAdr(int id);
void LockonSmallEnemy(void);
void CollisionSmallEnemyAndBullet(void);

//�e��ԍX�V����
void UpdateSmallEnemyMove(SMALLENEMY *enemy);
void UpdateSmallEnemyAttack(SMALLENEMY *enemy);
void UpdateSmallEnemyEscape(SMALLENEMY *enemy);
void UpdateSmallEnemyWait(SMALLENEMY *enemy);

//�e��ԓ��ꏈ��
void EnterSmallEnemyMove(SMALLENEMY *enemy);
void EnterSmallEnemyAttack(SMALLENEMY *enemy);
void EnterSmallEnemyEscape(SMALLENEMY *enemy);
void EnterSmallEnemyWait(SMALLENEMY *enemy);

//�e��ԑޏꏈ��
void ExitSmallEnemyMove(SMALLENEMY *enemy);
void ExitSmallEnemyAttack(SMALLENEMY *enemy);
void ExitSmallEnemyEscape(SMALLENEMY *enemy);
void ExitSmallEnemyWait(SMALLENEMY *enemy);

#endif