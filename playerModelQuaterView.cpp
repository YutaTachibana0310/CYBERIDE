//=====================================
//
//�v���C���[���f����l�̏���[playerModelQuaterView.cpp]
//Author:GP11A341 21 ���ԗY��
//
//=====================================
#include "playerModelQuaterView.h"
#include "playerBullet.h"
#include "input.h"

/**************************************
�}�N����`
***************************************/
#define PLAYERQUATER_BULLETSPEED	(25.0f)
#define PLAYERQUATER_RANGE_X_MIN	(-100.0f)
#define PLAYERQUATER_RANGE_X_MAX	(70.0f)
#define PLAYERQUATER_RANGE_Y_MIN	(-40.0f)
#define PLAYERQUATER_RANGE_Y_MAX	(50.0f)

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
void UpdatePlayerModelQuaterView(PLAYERMODEL *player)
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

	SetPlayerBullet(player->pos, PLAYERQUATER_BULLETSPEED);

	player->pos.x = Clampf(PLAYERQUATER_RANGE_X_MIN, PLAYERQUATER_RANGE_X_MAX, player->pos.x);
	player->pos.y = Clampf(PLAYERQUATER_RANGE_Y_MIN, PLAYERQUATER_RANGE_Y_MAX, player->pos.y);
}

/**************************************
���ꏈ��
***************************************/
void EnterPlayerModelQuaterView(PLAYERMODEL *player)
{
	player->flgMove = true;
	player->cntFrame = 0;
	player->initPos = player->pos;
}
