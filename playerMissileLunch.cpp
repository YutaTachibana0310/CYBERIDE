//=====================================
//
//�v���C���[�~�T�C�������`����[playerMissileLaunch.cpp]
//Author:GP11A341 21 ���ԗY��
//
//=====================================
#include "playerMissile.h"
#include "Easing.h"

/**************************************
�}�N����`
***************************************/
#define PLAYERMISSILE_LAUNCH_END		(20)
#define PLAYERMISSILE_LAUNCH_GOALSPEED	(2.0f)

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
void EnterPlayerMissileLaunch(PLAYERMISSILE *missile)
{
	missile->cntFrame = 0;
}

/**************************************
�X�V����
***************************************/
void UpdatePlayerMissileLaunch(PLAYERMISSILE *missile)
{
	//���x�x�N�g������]
	D3DXVECTOR3 axis;
	D3DXVECTOR3 diff = *missile->target - missile->pos;
	D3DXVec3Cross(&axis, &missile->velocity, &D3DXVECTOR3(0.0f, 0.0f, 1.0f));
	RotateByQuaternion(&missile->velocity, &axis, 0.1f, &missile->velocity);

	//���f������]
	D3DXVec3Cross(&axis, &PLAYERMISSILE_DEFAULT_ANGLE, &missile->velocity);
	D3DXQuaternionRotationAxis(&missile->rot, &axis, acosf(D3DXVec3Dot(&missile->velocity, &PLAYERMISSILE_DEFAULT_ANGLE)));

	//�X�s�[�h�X�V
	float t = (float)missile->cntFrame / PLAYERMISSILE_LAUNCH_END;
	missile->speed = EaseOutCubic(t, missile->startSpeed, PLAYERMISSILE_LAUNCH_GOALSPEED);

	//���W�X�V
	missile->pos += missile->velocity * missile->speed;

	missile->cntFrame++;
	if (missile->cntFrame == PLAYERMISSILE_LAUNCH_END)
	{
		ChangeStatePlayerMissile(missile, PLAYERMISSILE_ACCEL);
	}

}