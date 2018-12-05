//=====================================
//
//�v���C���[�~�T�C���A�N�Z������[playerMissileAccel.cpp]
//Author:GP11A341 21 ���ԗY��
//
//=====================================
#include "playerMissile.h"
#include "Easing.h"

/**************************************
�}�N����`
***************************************/
#define PLAYERMISSILE_SPEED_MAX			(60.0f)
#define PLAYERMISSILE_ACCEL_VALUE		(0.5f)
#define PLAYERMISSILE_ACCEL_ROTANGLE	(0.08f)
#define PLAYERMISSILE_ACCEL_END			(30)
#define PLAYERMISSILE_ACCEL_GOALSPEED	(10.0f)

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
void EnterPlayerMissileAccel(PLAYERMISSILE *missile)
{
	missile->cntFrame = 0;
	missile->startSpeed = missile->speed;
}

/**************************************
�X�V����
***************************************/
void UpdatePlayerMissileAccel(PLAYERMISSILE *missile)
{
	//���x�x�N�g������]
	D3DXVECTOR3 axis;
	D3DXVECTOR3 diff = *missile->target - missile->pos;
	D3DXVec3Cross(&axis, &missile->velocity, &diff);
	RotateByQuaternion(&missile->velocity, &axis, PLAYERMISSILE_ACCEL_ROTANGLE, &missile->velocity);

	//���f������]
	D3DXVec3Cross(&axis, &PLAYERMISSILE_DEFAULT_ANGLE, &missile->velocity);
	D3DXQuaternionRotationAxis(&missile->rot, &axis, acosf(D3DXVec3Dot(&missile->velocity, &PLAYERMISSILE_DEFAULT_ANGLE)));

	//����
	float t = (float)missile->cntFrame / PLAYERMISSILE_ACCEL_END;
	missile->speed = EaseOutCubic(t, missile->startSpeed, PLAYERMISSILE_ACCEL_GOALSPEED);

	//���W�X�V
	missile->pos += missile->velocity * missile->speed;

	if (!*missile->targetActive)
	{
		ChangeStatePlayerMissile(missile, PLAYERMISSILE_STRAIGHT);
	}

	missile->cntFrame++;
	if (missile->cntFrame == PLAYERMISSILE_ACCEL_END)
	{
		ChangeStatePlayerMissile(missile, PLAYERMISSILE_HOMING);
	}
}