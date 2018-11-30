//=====================================
//
//�v���C���[���f����l�̏���[playerModelSideView.cpp]
//Author:GP11A341 21 ���ԗY��
//
//=====================================
#include "playerModelSideView.h"
#include "playerBullet.h"
#include "input.h"

/**************************************
�}�N����`
***************************************/
#define PLAYERSIDE_BULLETSPEED		(10.0f)
#define PLAYERSIDE_RANGE_Y			(75.0f)
#define PLAYEYSIDE_RANGE_Z			(110.0f)

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
void UpdatePlayerModelSideView(PLAYERMODEL *player)
{
	if (GetKeyboardPress(DIK_LEFT))
	{
		player->pos.z -= 1.0f;
	}
	else if (GetKeyboardPress(DIK_RIGHT))
	{
		player->pos.z += 1.0f;
	}

	if (GetKeyboardPress(DIK_UP))
	{
		player->pos.y += 1.0f;
		player->destRot.z = -PLAYER_DESTROT_MAX;
	}
	else if (GetKeyboardPress(DIK_DOWN))
	{
		player->pos.y -= 1.0f;
		player->destRot.z = PLAYER_DESTROT_MAX;
	}
	else
	{
		player->destRot.z = 0.0f;
	}

	SetPlayerBullet(player->pos, PLAYERSIDE_BULLETSPEED);

	player->pos.y = Clampf(-PLAYERSIDE_RANGE_Y, PLAYERSIDE_RANGE_Y, player->pos.y);
	player->pos.z = Clampf(-PLAYEYSIDE_RANGE_Z, PLAYEYSIDE_RANGE_Z, player->pos.z);
}

/**************************************
���ꏈ��
***************************************/
void EnterPlayerModelSideView(PLAYERMODEL *player)
{
	player->cntFrame = 0;
	player->pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	player->initPos = player->pos;
}

/**************************************
�ޏꏈ��
***************************************/
void ExitPlayerModelSideView(PLAYERMODEL *player)
{
	
}