//=====================================
//
//�v���C���[���f����l�̏���[playerModelSideView.cpp]
//Author:GP11A341 21 ���ԗY��
//
//=====================================
#include "playerModelSideView.h"
#include "playerBullet.h"
#include "input.h"
#include "targetSite.h"
#include "dataContainer.h"
#include "lockonGUI.h"
#include "soundEffectManager.h"

/**************************************
�}�N����`
***************************************/
#define PLAYERSIDE_BULLETSPEED			(20.0f)
#define PLAYERSIDE_RANGE_Y				(90.0f)
#define PLAYERSIDE_RANGE_Z				(170.0f)
#define PLAYERSIDE_MOVESPEED			(3.5f)

#define PLAYERSIDE_SHOTPOS_L			(D3DXVECTOR3(-10.0f, 0.0f, 5.0f))
#define PLAYERSIDE_SHOTPOS_R			(D3DXVECTOR3(10.0f, 0.0f, 5.0f))
#define PLAYERSIDE_TARGETSITE_OFFSET	(D3DXVECTOR3(0.0f, 0.0, 200.0f))

/**************************************
�\���̒�`
***************************************/

/**************************************
�O���[�o���ϐ�
***************************************/

/**************************************
�v���g�^�C�v�錾
***************************************/
void ClampPlayerPositionSide(PLAYERMODEL *player);

/**************************************
�X�V����
***************************************/
void UpdatePlayerModelSideView(PLAYERMODEL *player)
{
	int x = GetHorizontalInputPress();
	int y = GetVerticalInputPress();

	//�ړ�����
	D3DXVECTOR3 moveDir = D3DXVECTOR3(0.0f, (float)y, (float)x);
	D3DXVec3Normalize(&moveDir, &moveDir);
	player->pos += moveDir * PLAYERSIDE_MOVESPEED;

	//player->pos.y = Clampf(-PLAYERSIDE_RANGE_Y, PLAYERSIDE_RANGE_Y, player->pos.y);
	ClampPlayerPositionSide(player);
	player->pos.z = Clampf(-PLAYERSIDE_RANGE_Z, PLAYERSIDE_RANGE_Z, player->pos.z);

	//���b�N�I���^�[�Q�b�g�̍X�V�m�F
	for (int i = 0; i < PLAYER_ROCKON_MAX; i++)
	{
		if (!player->target[i].use)
		{
			continue;
		}

		if (!*player->target[i].active)
		{
			ReleaseRockonTarget(player, i);
		}
	}

	//�^�[�Q�b�g�T�C�g�ړ�����
	//TARGETSITE *site = GetTargetSiteAdr(player->id);
	//site->pos = player->pos + PLAYERSIDE_TARGETSITE_OFFSET;
	SetTargetSitePosition(player->pos, player->id, D3DXVECTOR3(800.0f, 0.0f, 0.0f));
	UpdateTargetSite(GetAttackButtonPress());

	//���b�N�I���T�C�g�Z�b�g����
	int lockMax = GetLockonMax();
	for (int i = 0; i < lockMax; i++)
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
	if (player->atkInterbal == PLAYER_HOMINGATK_INTERBAL)
		PlaySE(SOUND_READY);

	if (GetAttackButtonRelease())
	{
		AttackPlayerMissile(player);
	}

	//�V���b�g�|�W�V�����X�V
	D3DXVec3TransformCoord(&player->shotpos1, &PLAYERSIDE_SHOTPOS_L, &player->mtxWorld);
	D3DXVec3TransformCoord(&player->shotpos2, &PLAYERSIDE_SHOTPOS_R, &player->mtxWorld);

	//�V���b�g���ˏ���
	player->cntFrame++;
	if (player->cntFrame % PLAYER_SHOT_INTERBAL == 0)// && !GetAttackButtonPress())
	{
		PlaySE(SOUND_SHOT);
		SetPlayerBullet(player->shotpos1, PLAYERSIDE_BULLETSPEED);
		SetPlayerBullet(player->shotpos2, PLAYERSIDE_BULLETSPEED);
	}
}

/**************************************
���ꏈ��
***************************************/
void EnterPlayerModelSideView(PLAYERMODEL *player)
{
	player->cntFrame = 0;
	player->isInvincible = false;
	player->atkInterbal = PLAYER_HOMINGATK_INTERBAL;

	//�^�[�Q�b�g�T�C�g�ݒ菈��
	TARGETSITE *site = GetTargetSiteAdr(player->id);
	site->active = true;
	site->pos = site->targetPos = player->pos;// + D3DXVECTOR3(0.0f, 0.0f, PLAYERFPS_TARGETSITE_POS_Z);

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
void ExitPlayerModelSideView(PLAYERMODEL *player)
{
	
}

/**************************************
�ړ��͈͐�������
***************************************/
void ClampPlayerPositionSide(PLAYERMODEL *player)
{
	float posZ = player->pos.z + PLAYERSIDE_RANGE_Z;
	float border = posZ / (PLAYERSIDE_RANGE_Z * 2) * 40.0f + PLAYERSIDE_RANGE_Y;
	player->pos.y = Clampf(-border, border, player->pos.y);
}