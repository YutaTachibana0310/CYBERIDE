//=====================================
//
//�~�h���G�l�~�[�ړ���ԏ���[middleEnemyMove.cpp]
//Author:GP11A341 21 ���ԗY��
//
//=====================================
#include "middleEnemyModel.h"
#include "EasingVector.h"

/**************************************
�}�N����`
***************************************/
#define MIDDLEENEMY_MOVE_END		(180)

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
�X�V����
***************************************/
void UpdateMiddleEnemyMove(MIDDLEENEMYMODEL *enemy)
{
	if (enemy->cntFrame > MIDDLEENEMY_MOVE_END)
	{
		return;
	}

	enemy->cntFrame++;
	float t = (float)enemy->cntFrame / MIDDLEENEMY_MOVE_END;
	enemy->pos = EaseOutCubicVector(t, enemy->startPos, enemy->goalPos);
	enemy->rot = EaseOutCubicVector(t, enemy->startRot, enemy->goalRot);
}

/**************************************
���ꏈ��
***************************************/
void EnterMiddleEnemyMove(MIDDLEENEMYMODEL *enemy)
{
	enemy->cntFrame = 0;
	enemy->startPos = enemy->pos;
	enemy->startRot = enemy->rot;
}

/**************************************
�ޏꏈ��
***************************************/
void ExitMiddleEnemyMove(MIDDLEENEMYMODEL *enemy)
{

}

