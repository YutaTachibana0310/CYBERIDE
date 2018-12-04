//=====================================
//
//�~�h���G�l�~�[�ҋ@����[middleEnemyWait.cpp]
//Author:GP11A341 21 ���ԗY��
//
//=====================================
#include "middleEnemyModel.h"
#include "EasingVector.h"

/**************************************
�}�N����`
***************************************/
#define MIDDLEENEMY_WAIT_END		(120)

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
void EnterMiddleEnemyWait(MIDDLEENEMYMODEL *enemy)
{
	enemy->cntFrame = 0;
}

/**************************************
�X�V����
***************************************/
void UpdateMiddleEnemyWait(MIDDLEENEMYMODEL *enemy)
{
	enemy->cntFrame++;
	if (enemy->cntFrame == MIDDLEENEMY_WAIT_END)
	{
		ChangeStateMiddleEnemy(enemy, MiddleEnemyEscape);
	}

}

/**************************************
�ޏꏈ��
***************************************/
void ExitMiddleEnemyWait(MIDDLEENEMYMODEL *enemy)
{

}