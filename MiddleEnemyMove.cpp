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
void UpdateMiddleEnemyMove(MIDDLEENEMYMODEL *enemy)
{
	enemy->cntFrame++;

	if (enemy->cntFrame > MIDDLEENEMY_MOVE_END)
	{
		if (enemy->cntFrame % 120 == 0)
		{
			for (int i = 0; i < 8; i++)
			{
				D3DXVECTOR3 dir = D3DXVECTOR3(sinf(i * 45 * 0.017f), cosf(i * 45 * 0.017f),  .0f) * 200;
				SetEnemyHomingBullet(enemy->pos, dir, rand() % 30 + 60);
			}
		}
		return;
	}


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

