//=====================================
//
//�v���C���[�~�T�C���A�N�Z������[playerMissileHoming.cpp]
//Author:GP11A341 21 ���ԗY��
//
//=====================================
#include "playerMissile.h"

/**************************************
�}�N����`
***************************************/

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
void EnterPlayerMissileHoming(PLAYERMISSILE *missile)
{
	missile->cntFrame = 0;
	missile->speed = 20.0f;
}

/**************************************
�X�V����
***************************************/
void UpdatePlayerMissileHoming(PLAYERMISSILE *missile)
{
	//���x�x�N�g�����v�Z
	D3DXVECTOR3 axis;
	D3DXVECTOR3 diff = *missile->target - missile->pos;
	D3DXVec3Normalize(&missile->velocity, &diff);

	//���f������]
	D3DXVec3Cross(&axis, &PLAYERMISSILE_DEFAULT_ANGLE, &missile->velocity);
	D3DXQuaternionRotationAxis(&missile->rot, &axis, acosf(D3DXVec3Dot(&missile->velocity, &PLAYERMISSILE_DEFAULT_ANGLE)));

	//���W�X�V
	missile->pos += missile->velocity * missile->speed;

	if (!*missile->targetActive)
	{
		ChangeStatePlayerMissile(missile, PLAYERMISSILE_STRAIGHT);
	}

}