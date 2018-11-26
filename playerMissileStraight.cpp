//=====================================
//
//�v���C���[�~�T�C���X�g���[�g����[playerMissileStraight.cpp]
//Author:GP11A341 21 ���ԗY��
//
//=====================================
#include "playerMissile.h"

/**************************************
�}�N����`
***************************************/
#define PLAYERMISSILE_BORDER_Z		(0.0f)
#define PLAYERMISSILE_STRAIGHT_END	(120)

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
void EnterPlayerMissileStraight(PLAYERMISSILE *missile)
{
	missile->cntFrame = 0;
	missile->speed = 40.0f;
}

/**************************************
�X�V����
***************************************/
void UpdatePlayerMissileStraight(PLAYERMISSILE *missile)
{
	//���W�X�V
	missile->pos += missile->velocity * missile->speed;

	if (missile->pos.z < PLAYERMISSILE_BORDER_Z)
	{
		missile->active = false;
	}

	//�J�E���g�X�V
	missile->cntFrame++;
	if (missile->cntFrame > PLAYERMISSILE_STRAIGHT_END)
	{
		missile->active = false;
	}
}