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

}MIDDLEENEMY;
/**************************************
�v���g�^�C�v�錾
***************************************/
void InitMiddleEnemy(int num);
void UninitMiddleEnemy(int num);
void UpdateMiddleEnemy(void);
void DrawMiddleEnemy(void);
void ChangeStateMiddleEnemy(MIDDLEENEMY *ptr, int next);
MIDDLEENEMY *GetMiddleEnemyAdr(int num);
void LockonMiddleEnemy(void);
void CollisionMiddleEnemyAndBullet(void);

//�e��ԍX�V����
void UpdateMiddleEnemyMove(MIDDLEENEMY *enemy);
void UpdateMiddleEnemyAttack(MIDDLEENEMY *enemy);
void UpdateMiddleEnemyEscape(MIDDLEENEMY *enemy);
void UpdateMiddleEnemyWait(MIDDLEENEMY *enemy);

//�e��ԓ��ꏈ��
void EnterMiddleEnemyMove(MIDDLEENEMY *enemy);
void EnterMiddleEnemyAttack(MIDDLEENEMY *enemy);
void EnterMiddleEnemyEscape(MIDDLEENEMY *enemy);
void EnterMiddleEnemyWait(MIDDLEENEMY *enemy);

//�e��ԑޏꏈ��
void ExitMiddleEnemyMove(MIDDLEENEMY *enemy);
void ExitMiddleEnemyAttack(MIDDLEENEMY *enemy);
void ExitMiddleEnemyEscape(MIDDLEENEMY *enemy);
void ExitMiddleEnemyWait(MIDDLEENEMY *enemy);

#endif