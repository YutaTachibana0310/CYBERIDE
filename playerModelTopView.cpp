//=====================================
//
//�v���C���[���f����l�̏���[playerModelTopView.cpp]
//Author:GP11A341 21 ���ԗY��
//
//=====================================
#include "playerModelTopView.h"
#include "playerBullet.h"
#include "input.h"
#include "targetSite.h"
#include "playerMissile.h"
#include "lockonGUI.h"

/**************************************
�}�N����`
***************************************/
#define PLAYERTOP_MOVESPEED		(1.5f)
#define PLAYERTOP_RANGE_X		(80.0f)
#define PLAYERTOP_RANGE_Z		(70.0f)

#define PLAYERTOP_SHOTPOS_L		(D3DXVECTOR3(-10.0f, 0.0f, 5.0f))
#define PLAYERTOP_SHOTPOS_R		(D3DXVECTOR3( 10.0f, 0.0f, 5.0f))
#define PLAYERTOP_BULLETSPEED	(40.0f)
#define PLAYERTOP_SITEPOS		(D3DXVECTOR3(0.0f, 0.0f, 250.0f))

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
	int x = GetHorizontalInputPress();
	int y = GetVerticalInputPress();

	//�ړ�����
	D3DXVECTOR3 moveDir = D3DXVECTOR3((float)x, 0.0f, (float)y);
	D3DXVec3Normalize(&moveDir, &moveDir);
	player->pos += moveDir * PLAYERTOP_MOVESPEED;

	player->destRot.z = x * PLAYER_DESTROT_MAX;

	player->pos.x = Clampf(-PLAYERTOP_RANGE_X, PLAYERTOP_RANGE_X, player->pos.x);
	player->pos.z = Clampf(-PLAYERTOP_RANGE_Z, PLAYERTOP_RANGE_Z, player->pos.z);

	//�^�[�Q�b�g�̍X�V�m�F
	TARGETSITE *site = GetTargetSiteAdr(player->id);
	site->pos = player->pos + PLAYERTOP_SITEPOS;

	//���b�N�I���T�C�g�Z�b�g����
	for (int i = 0; i < PLAYER_ROCKON_MAX; i++)
	{
		if (player->target[i].use)
		{
			SetRockonSitePos(player->id * PLAYER_ROCKON_MAX + i, *player->target[i].pos);
		}
	}

	//���b�N�I��GUI�Z�b�g����
	SetLockonGUIPos(player->id, player->pos + D3DXVECTOR3(0.0f, -10.0f, 0.0f));

	//�U������
	player->atkInterbal++;
	if (GetKeyboardTrigger(DIK_Z))
	{
		AttackPlayerMissile(player);
	}

	//�V���b�g�|�W�V�����X�V
	D3DXVec3TransformCoord(&player->shotpos1, &PLAYERTOP_SHOTPOS_L, &player->mtxWorld);
	D3DXVec3TransformCoord(&player->shotpos2, &PLAYERTOP_SHOTPOS_R, &player->mtxWorld);

	//�V���b�g���ˏ���
	player->cntFrame++;
	if (player->cntFrame % PLAYER_SHOT_INTERBAL == 0)
	{
		SetPlayerBullet(player->shotpos1, PLAYERTOP_BULLETSPEED);
		SetPlayerBullet(player->shotpos2, PLAYERTOP_BULLETSPEED);
	}
}

/**************************************
���ꏈ��
***************************************/
void EnterPlayerModelTopView(PLAYERMODEL *player)
{
	player->cntFrame = 0;
	player->atkInterbal = PLAYER_HOMINGATK_INTERBAL;

	//�^�[�Q�b�g�T�C�g�ݒ菈��
	TARGETSITE *site = GetTargetSiteAdr(player->id);
	site->active = true;
	site->pos = player->pos;

	//���b�N�I���Ώۏ�����
	for (int i = 0; i < PLAYER_ROCKON_MAX; i++)
	{
		player->target[i].use = false;
	}
	player->lockonNum = 0;

	//���b�N�I��GUI�\��
	GetLockonGUIAdr(player->id)->active = true;
}

/**************************************
�ޏꏈ��
***************************************/
void ExitPlayerModelTopView(PLAYERMODEL *player)
{

}