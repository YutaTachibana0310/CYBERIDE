//==================================
//
//�G�l�~�[�~�T�C�����ˏ���[enemyMissileHoming.cpp]
//Author:GP11A341 21 ���ԗY��
//
//==================================
#include "enemyMissileHoming.h"

/***********************************
�J�n����
************************************/
void EnemyMissileHomingEnter(ENEMYMISSILE *ptr)
{
	ptr->flgHoming = true;

}

/***********************************
�X�V����
************************************/
void EnemyMissileHomingUpdate(ENEMYMISSILE *ptr)
{

}

/***********************************
�I������
************************************/
void EnemyMissileHomingExit(ENEMYMISSILE *ptr)
{
	ptr->flgHoming = false;
}