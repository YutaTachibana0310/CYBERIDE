//=====================================
//
//�~�h���G�l�~�[���f���w�b�_[middleEnemyModel.h]
//Author:GP11A341 21 ���ԗY��
//
//=====================================
#ifndef _MIDDLEENMYMODEL_H_
#define _MIDDLEENMYMODEL_H_

#include "main.h"
#include "collider.h"

/**************************************
�}�N����`
***************************************/
#define MIDDLEENEMY_MAX				(36)
#define MIDDLEENEMY_COLLIDER_RADIUS	(20.0f)

/**************************************
�\���̒�`
***************************************/
//�~�h���G�l�~�[��Ԓ�`
enum MIDDLEENEMY_STATE
{
	MiddleEnemyMove,		//�ړI���W�Ɉړ�������
	MiddleEnemyAttack,		//�U�����
	MiddleEnemyEscape,		//�������
	MiddleEnemyWait,		//�ҋ@���
	MiddleEnemyStateMax		
};

//�~�h���G�l�~�[�\����
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

}MIDDLEENEMYMODEL;
/**************************************
�v���g�^�C�v�錾
***************************************/
void InitMiddleEnemyModel(int num);
void UninitMiddleEnemyModel(int num);
void UpdateMiddleEnemyModel(void);
void DrawMiddleEnemyModel(void);
void ChangeStateMiddleEnemy(MIDDLEENEMYMODEL *ptr, int next);
MIDDLEENEMYMODEL *GetMiddleEnemyAdr(int num);
void LockonMiddleEnemy(void);
void CollisionMiddleEnemyAndBullet(void);

//�e��ԍX�V����
void UpdateMiddleEnemyMove(MIDDLEENEMYMODEL *enemy);
void UpdateMiddleEnemyAttack(MIDDLEENEMYMODEL *enemy);
void UpdateMiddleEnemyEscape(MIDDLEENEMYMODEL *enemy);
void UpdateMiddleEnemyWait(MIDDLEENEMYMODEL *enemy);

//�e��ԓ��ꏈ��
void EnterMiddleEnemyMove(MIDDLEENEMYMODEL *enemy);
void EnterMiddleEnemyAttack(MIDDLEENEMYMODEL *enemy);
void EnterMiddleEnemyEscape(MIDDLEENEMYMODEL *enemy);
void EnterMiddleEnemyWait(MIDDLEENEMYMODEL *enemy);

//�e��ԑޏꏈ��
void ExitMiddleEnemyMove(MIDDLEENEMYMODEL *enemy);
void ExitMiddleEnemyAttack(MIDDLEENEMYMODEL *enemy);
void ExitMiddleEnemyEscape(MIDDLEENEMYMODEL *enemy);
void ExitMiddleEnemyWait(MIDDLEENEMYMODEL *enemy);

#endif