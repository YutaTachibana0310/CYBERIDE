//==================================
//
//�G�l�~�[�~�T�C�����ˏ���[enemyMissileHoming.cpp]
//Author:GP11A341 21 ���ԗY��
//
//==================================
#include "enemyMissileHoming.h"
#include "playerModel.h"

/***********************************
�}�N����`
***********************************/
#define ENEMYMISSILE_HOMINGANGLE	(0.05f)			//�z�[�~���O�̉�]�p�x
#define ENEMYMISSILE_FORWORD		(D3DXVECTOR3(0.0f, 0.0f, -1.0f))	//��ƂȂ�i�s����
#define ENEMYMISSILE_HOMINGFRAME	(240)

/***********************************
�J�n����
************************************/
void EnemyMissileHomingEnter(ENEMYMISSILE *ptr)
{
	ptr->period = 300;
	ptr->cntFrame = 0;
	ptr->speed = 2.0f;
}

/***********************************
�X�V����
************************************/
void EnemyMissileHomingUpdate(ENEMYMISSILE *ptr)
{
	//�ړ������̃z�[�~���O a = 2(d - vt) / t^2
	//D3DXVECTOR3 diff = GetPlayerAdr(0)->pos - ptr->pos;
	//D3DXVECTOR3 accel = 2.0f * (diff - ptr->velocity * ptr->period) / (ptr->period * ptr->period);
	//ptr->period--;

	//ptr->velocity += accel;
	//ptr->pos += ptr->velocity * ptr->speed;

	D3DXVECTOR3 axis;
	D3DXVECTOR3 targetDir = GetPlayerAdr(0)->pos - ptr->pos;
	D3DXVec3Cross(&axis, &ptr->velocity, &targetDir);
	RotateByQuaternion(&ptr->velocity, &axis, ENEMYMISSILE_HOMINGANGLE , &ptr->velocity);

	//��]�N�H�[�^�j�I����ݒ�
	D3DXVec3Cross(&axis, &ENEMYMISSILE_FORWORD, &ptr->velocity);
	D3DXQuaternionRotationAxis(&ptr->rot, &axis, acosf(D3DXVec3Dot(&ptr->velocity, &ENEMYMISSILE_FORWORD)));

	//���W�̍X�V
	ptr->pos += ptr->velocity * ptr->speed;

	ptr->cntFrame++;

	//�J��
	if (ptr->cntFrame >= ENEMYMISSILE_HOMINGFRAME)
	{
		ChangeStateEnemyMissile(ptr, ENEMYMISSILE_STRAIGHT);
	}
	if (ptr->pos.z < -10.0f)
	{
		ptr->active = false;
	}
}

/***********************************
�I������
************************************/
void EnemyMissileHomingExit(ENEMYMISSILE *ptr)
{

}
