//=====================================
//
//�X���[���G�l�~�[��������[smallEnemyEscape.cpp]
//Author:GP11A341 21 ���ԗY��
//
//=====================================
#include "smallEnemyModel.h"
#include "EasingVector.h"

/**************************************
�}�N����`
***************************************/
#define SMALLENEMY_ESCAPE_END		(300)
#define SMALLENEMY_ESCAPE_GOALPOS_Z	(3000.0f)
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
void EnterSmallEnemyEscape(SMALLENEMY *enemy)
{
	enemy->cntFrame = 0;
	enemy->startPos = enemy->pos;
	enemy->goalPos = enemy->startPos;
	enemy->goalPos.z = SMALLENEMY_ESCAPE_GOALPOS_Z;
}

/**************************************
�X�V����
***************************************/
void UpdateSmallEnemyEscape(SMALLENEMY *enemy)
{
	enemy->cntFrame++;

	float t = (float)enemy->cntFrame / SMALLENEMY_ESCAPE_END;
	enemy->pos = EaseInCubicVector(t, enemy->startPos, enemy->goalPos);

	if (enemy->cntFrame == SMALLENEMY_ESCAPE_END)
	{
		enemy->active = false;
	}
}

/**************************************
�ޏꏈ��
***************************************/
void ExitSmallEnemyEscape(SMALLENEMY *enemy)
{

}