//=====================================
//
//�~�h���G�l�~�[�ړ���ԏ���[middleEnemyMove.cpp]
//Author:GP11A341 21 ���ԗY��
//
//=====================================
#include "middleEnemyModel.h"
#include "EasingVector.h"
#include "playerModel.h"
#include "enemyHomingBullet.h"
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
void UpdateMiddleEnemyMove(MIDDLEENEMY *enemy)
{
	enemy->cntFrame++;

	float t = (float)enemy->cntFrame / MIDDLEENEMY_MOVE_END;
	enemy->pos = EaseOutCubicVector(t, enemy->startPos, enemy->goalPos);
	enemy->rot = EaseOutCubicVector(t, enemy->startRot, enemy->goalRot);

	if (enemy->cntFrame == MIDDLEENEMY_MOVE_END)
	{
		ChangeStateMiddleEnemy(enemy, MiddleEnemyAttack);
	}
}

/**************************************
���ꏈ��
***************************************/
void EnterMiddleEnemyMove(MIDDLEENEMY *enemy)
{
	enemy->cntFrame = 0;
	enemy->startPos = enemy->pos;
	enemy->startRot = enemy->rot;
}

/**************************************
�ޏꏈ��
***************************************/
void ExitMiddleEnemyMove(MIDDLEENEMY *enemy)
{

}

