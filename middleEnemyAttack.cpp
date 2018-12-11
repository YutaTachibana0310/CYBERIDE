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
#define MIDDLEENEMY_ATTACK_INETBAL		(120)					//�U���Ԋu
#define MIDDLEENEMY_ATTACK_LOOPMAX		(8)						//1��̍U���̃��[�v��
#define MIDDLEENEMY_ATTACK_MAX			(5)						//�U���I����
#define MIDDLEENEMY_ATTACK_ANGLE		(0.765f)				//���ˊp�x
#define MIDDLEENEMY_ATTACK_INITVELOCITY	(200.0f)				//�z�[�~���O�e�������x
#define MIDDLEENEMY_ATTACK_REACH_MAX	(90)					//�z�[�~���O���B�����ő�l
#define MIDDLEENEMY_ATTACK_REACH_MIN	(80)					//�z�[�~���O���B�����ŏ��l
#define MIDDLEENEMY_ATTACK_SHOTPOS		(D3DXVECTOR3(0, 0, 50))	//�z�[�~���O�e���ˈʒu

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
void EnterMiddleEnemyAttack(MIDDLEENEMY *enemy)
{
	enemy->cntFrame = 0;
	enemy->atkNum = 0;
}

/**************************************
�X�V����
***************************************/
void UpdateMiddleEnemyAttack(MIDDLEENEMY *enemy)
{
	if (enemy->cntFrame % MIDDLEENEMY_ATTACK_INETBAL == 0)
	{
		float baseAngle = D3DXToRadian(360.0f / MIDDLEENEMY_ATTACK_LOOPMAX);

		for (int i = 0; i < MIDDLEENEMY_ATTACK_LOOPMAX; i++)
		{
			D3DXVECTOR3 dir = D3DXVECTOR3(sinf(i * MIDDLEENEMY_ATTACK_ANGLE), cosf(i * MIDDLEENEMY_ATTACK_ANGLE), 0.0f);
			dir *= MIDDLEENEMY_ATTACK_INITVELOCITY;
			SetEnemyHomingBullet(enemy->pos + MIDDLEENEMY_ATTACK_SHOTPOS, dir, RandomRange(MIDDLEENEMY_ATTACK_REACH_MIN, MIDDLEENEMY_ATTACK_REACH_MAX));
		}

		enemy->cntFrame = 0;
		enemy->atkNum++;
	}

	if (enemy->atkNum == MIDDLEENEMY_ATTACK_MAX)
	{
		ChangeStateMiddleEnemy(enemy, MiddleEnemyWait);
	}

	enemy->cntFrame++;
}

/**************************************
�ޏꏈ��
***************************************/
void ExitMiddleEnemyAttack(MIDDLEENEMY *enemy)
{

}