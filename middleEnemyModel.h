//=====================================
//
//�~�h���G�l�~�[���f���w�b�_[middleEnemyModel.h]
//Author:GP11A341 21 ���ԗY��
//
//=====================================
#ifndef _MIDDLEENMYMODEL_H_
#define _MIDDLEENMYMODEL_H_

#include "main.h"

/**************************************
�}�N����`
***************************************/
#define MIDDLEENEMY_MAX			(36)
/**************************************
�\���̒�`
***************************************/
//�~�h���G�l�~�[��Ԓ�`
enum MIDDLEENEMY_STATE
{
	MiddleEnemyMove,
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

void UpdateMiddleEnemyMove(MIDDLEENEMYMODEL *enemy);

void EnterMiddleEnemyMove(MIDDLEENEMYMODEL *enemy);

void ExitMiddleEnemyMove(MIDDLEENEMYMODEL *enemy);


#endif