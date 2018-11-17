//=====================================
//
//�v���C���[���f����l�̏���[playerModelFPS.cpp]
//Author:GP11A341 21 ���ԗY��
//
//=====================================
#include "playerModelFPS.h"
#include "playerBullet.h"
#include "input.h"

/**************************************
�}�N����`
***************************************/
#define PLAYERFPS_BULLETSPEED		(10.0f)
#define PLAYERFPS_RANGE_X			(85.0f)
#define PLAYERFPS_RANGE_Y			(55.0f)

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
�X�V����
***************************************/
void UpdatePlayerModelFPS(PLAYERMODEL *player)
{
	if (player->flgMove)
	{
		player->cntFrame++;
		player->pos = EaseOutCubic((float)player->cntFrame / BATTLECAMERA_MOVEFRAME, player->initPos, D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		if (player->cntFrame == BATTLECAMERA_MOVEFRAME)
		{
			player->flgMove = false;
		}
	}
	else
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
			player->pos.y += 1.0f;
		}
		else if (GetKeyboardPress(DIK_DOWN))
		{
			player->pos.y -= 1.0f;
		}
	}

	SetPlayerBullet(player->pos, PLAYERFPS_BULLETSPEED);

	player->pos.x = Clampf(-PLAYERFPS_RANGE_X, PLAYERFPS_RANGE_X, player->pos.x);
	player->pos.y = Clampf(-PLAYERFPS_RANGE_Y, PLAYERFPS_RANGE_Y, player->pos.y);
}

/**************************************
���ꏈ��
***************************************/
void EnterPlayerModelFPS(PLAYERMODEL *player)
{
	player->flgMove = true;
	player->cntFrame = 0;
	player->initPos = player->pos;
}
