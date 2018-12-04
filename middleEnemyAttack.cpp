//=====================================
//
//�~�h���G�l�~�[�A�^�b�N����[middleEnemyAttack.cpp]
//Author:GP11A341 21 ���ԗY��
//
//=====================================
#include "middleEnemyModel.h"
#include "enemyHomingBullet.h"

/**************************************
�}�N����`
***************************************/
#define MIDDLEENEMY_ATTACK_INETBAL		(120)
#define MIDDLEENEMY_ATTACK_LOOPMAX		(8)
#define MIDDLEENEMY_ATTACK_MAX			(5)
#define MIDDLEENEMY_ATTACK_ANGLE		(0.765f)
#define MIDDLEENEMY_ATTACK_INITVELOCITY	(200.0f)
#define MIDDLEENEMY_ATTACK_REACH_MAX	(90)
#define MIDDLEENEMY_ATTACK_REACH_MIN	(60)

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
void EnterMiddleEnemyAttack(MIDDLEENEMYMODEL *enemy)
{
	enemy->cntFrame = 0;
	enemy->atkNum = 0;
}

/**************************************
�X�V����
***************************************/
void UpdateMiddleEnemyAttack(MIDDLEENEMYMODEL *enemy)
{
	if (enemy->cntFrame % MIDDLEENEMY_ATTACK_INETBAL == 0)
	{
		float baseAngle = D3DXToRadian(360.0f / MIDDLEENEMY_ATTACK_LOOPMAX);

		for (int i = 0; i < MIDDLEENEMY_ATTACK_LOOPMAX; i++)
		{
			D3DXVECTOR3 dir = D3DXVECTOR3(sinf(i * MIDDLEENEMY_ATTACK_ANGLE), cosf(i * MIDDLEENEMY_ATTACK_ANGLE), 0.0f);
			dir *= MIDDLEENEMY_ATTACK_INITVELOCITY;
			SetEnemyHomingBullet(enemy->pos, dir, RandomRange(MIDDLEENEMY_ATTACK_REACH_MIN, MIDDLEENEMY_ATTACK_REACH_MAX));
		}

		enemy->cntFrame = 0;
		enemy->atkNum++;
	}

	enemy->cntFrame++;
}

/**************************************
�ޏꏈ��
***************************************/
void ExitMiddleEnemyAttack(MIDDLEENEMYMODEL *enemy)
{

}