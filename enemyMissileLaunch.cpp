//==================================
//
//�G�l�~�[�~�T�C�����ˏ���[enemyMissileLaunch.cpp]
//Author:GP11A341 21 ���ԗY��
//
//==================================
#include "enemyMissileLaunch.h"

#define ENEMYMISSILE_INITSPEED		(50.0f)		//�����X�s�[�h
#define ENEMYMISSILE_TARGETSPEED	(200.0f)	//�ڕW�X�s�[�h
/***********************************
�J�n����
************************************/
void EnemyMissileLaunchEnter(ENEMYMISSILE *ptr)
{
	ptr->active = true;
	ptr->cntFrame = 0;
	ptr->flgHoming = false;

}

/***********************************
�X�V����
************************************/
void EnemyMissileLaunchUpdate(ENEMYMISSILE *ptr)
{

}

/***********************************
�I������
************************************/
void EnemyMissileLaunchExit(ENEMYMISSILE *ptr)
{

}