//==================================
//
//�G�l�~�[�~�T�C�����ˏ���[enemyMissileLaunch.cpp]
//Author:GP11A341 21 ���ԗY��
//
//==================================
#include "enemyMissileLaunch.h"
#include "Easing.h"

#define ENEMYMISSILE_INITSPEED		(5.0f)		//�����X�s�[�h
#define ENEMYMISSILE_TARGETSPEED	(20.0f)		//�ڕW�X�s�[�h
#define ENEMYMISSILE_LAUNCHDURATION	(30)			//���˂���z�[�~���O�ɑJ�ڂ���t���[��
/***********************************
�J�n����
************************************/
void EnemyMissileLaunchEnter(ENEMYMISSILE *ptr)
{
	ptr->active = true;
	ptr->cntFrame = 0;
	ptr->speed = 0.0f;
}

/***********************************
�X�V����
************************************/
void EnemyMissileLaunchUpdate(ENEMYMISSILE *ptr)
{
	//���x�X�V
	ptr->cntFrame++;
	//ptr->speed = EaseInOutCubic((float)ptr->cntFrame/ ENEMYMISSILE_LAUNCHDURATION, ENEMYMISSILE_INITSPEED, ENEMYMISSILE_TARGETSPEED);
	ptr->speed = 5.0f;

	//���W�X�V
	ptr->pos += ptr->speed * ptr->velocity;

	//�ڕW�X�s�[�h�ɓ��B���Ă�����J��
	if (ptr->cntFrame >= ENEMYMISSILE_LAUNCHDURATION)
	{
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                          
		ChangeStateEnemyMissile(ptr, ENEMYMISSILE_HOMING);
	}
}

/***********************************
�I������
************************************/
void EnemyMissileLaunchExit(ENEMYMISSILE *ptr)
{

}