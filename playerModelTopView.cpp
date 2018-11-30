//=====================================
//
//�v���C���[���f����l�̏���[playerModelTopView.cpp]
//Author:GP11A341 21 ���ԗY��
//
//=====================================
#include "playerModelTopView.h"
#include "playerBullet.h"
#include "input.h"

/**************************************
�}�N����`
***************************************/
#define PLAYERTOP_BULLETSPEED	(5.0f)
#define PLAYERTOP_RANGE_X		(80.0f)
#define PLAYERTOP_RANGE_Z		(70.0f)

/**************************************
�\���̒�`
***************************************

/**************************************
�O���[�o���ϐ�
***************************************/

/**************************************
�v���g�^�C�v�錾
***************************************/


/**************************************
�X�V����
***************************************/
void UpdatePlayerModelTopView(PLAYERMODEL *player)
{
	if (GetKeyboardPress(DIK_LEFT))
	{
		player->pos.x -= 1.0f;
		player->destRot.z = -PLAYER_DESTROT_MAX;
	}
	else if (GetKeyboardPress(DIK_RIGHT))
	{
		player->pos.x += 1.0f;
		player->destRot.z = PLAYER_DESTROT_MAX;
	}
	else
	{
		player->destRot.z = 0.0f;
	}

	if (GetKeyboardPress(DIK_UP))
	{
		player->pos.z += 1.0f;
	}
	else if (GetKeyboardPress(DIK_DOWN))
	{
		player->pos.z -= 1.0f;
	}

	SetPlayerBullet(player->pos, PLAYERTOP_BULLETSPEED);

	player->pos.x = Clampf(-PLAYERTOP_RANGE_X, PLAYERTOP_RANGE_X, player->pos.x);
	player->pos.z = Clampf(-PLAYERTOP_RANGE_Z, PLAYERTOP_RANGE_Z, player->pos.z);
}

/**************************************
���ꏈ��
***************************************/
void EnterPlayerModelTopView(PLAYERMODEL *player)
{
	player->cntFrame = 0;
	player->initPos = player->pos;
}

/**************************************
�ޏꏈ��
***************************************/
void ExitPlayerModelTopView(PLAYERMODEL *player)
{

}