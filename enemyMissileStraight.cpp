//==================================
//
//�G�l�~�[�~�T�C�����ˏ���[enemyMissileStraight.cpp]
//Author:GP11A341 21 ���ԗY��
//
//==================================
#include "enemyMissileStraight.h"

/***********************************
�}�N����`
************************************/
#define ENEMYMISSILE_BORDER_Z		(-200.0f)		//�~�T�C����Z���W���E�l

/***********************************
�J�n����
************************************/
void EnemyMissileStraightEnter(ENEMYMISSILE *ptr)
{
	
}

/***********************************
�X�V����
************************************/
void EnemyMissileStraightUpdate(ENEMYMISSILE *ptr)
{
	//���W�̍X�V
	ptr->pos += ptr->speed * ptr->moveDir;

	//��A�N�e�B�u��
	if (ptr->pos.z < ENEMYMISSILE_BORDER_Z)
	{
		ptr->active = false;
	}
}

/***********************************
�I������
************************************/
void EnemyMissileStraightExit(ENEMYMISSILE *ptr)
{

}