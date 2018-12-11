//=====================================
//
//�X���[���G�l�~�[�ړ�����[smallEnemyMove.cpp]
//Author:GP11A341 21 ���ԗY��
//
//=====================================
#include "smallEnemyModel.h"
#include "EasingVector.h"

/**************************************
�}�N����`
***************************************/
#define SMALLENEMY_MOVE_END		(120)


/**************************************
�\���̒�`
***************************************/

/**************************************
�O���[�o���ϐ�
***************************************/

/**************************************
�v���g�^�C�v�錾
***************************************/

/**************************************
���ꏈ��
***************************************/
void EnterSmallEnemyMove(SMALLENEMY *enemy)
{
	enemy->cntFrame = 0;
	enemy->startPos = enemy->pos;
}

/**************************************
�X�V����
***************************************/
void UpdateSmallEnemyMove(SMALLENEMY *enemy)
{
	enemy->cntFrame++;

	float t = (float)enemy->cntFrame / SMALLENEMY_MOVE_END;
	enemy->pos = EaseOutCubicVector(t, enemy->startPos, enemy->goalPos);

	if (enemy->cntFrame == SMALLENEMY_MOVE_END)
	{
		ChangeStateSmallEnemy(enemy, SmallEnemyWait);
	}
}

/**************************************
�ޏꏈ��
***************************************/
void ExitSmallEnemyMove(SMALLENEMY *enemy)
{

}