//=====================================
//
//�v���C���[���f����l�̏���[playerModelFPS.cpp]
//Author:GP11A341 21 ���ԗY��
//
//=====================================
#include "playerModelFPS.h"
#include "playerBullet.h"
#include "input.h"
#include "targetSite.h"
#include "enemyMissile.h"
#include "playerMissile.h"
#include "lockonGUI.h"
#include "dataContainer.h"
#include "soundEffectManager.h"
#include "dataContainer.h"

/**************************************
�}�N����`
***************************************/
#define PLAYERFPS_RANGE_X			(85.0f)
#define PLAYERFPS_RANGE_Y			(55.0f)
#define PLAYERFPS_MOVESPEED			(1.5f)

#define PLAYERFPS_SHOTPOS_L			(D3DXVECTOR3(-5.0f, 0.0f, -15.0f))
#define PLAYERFPS_SHOTPOS_R			(D3DXVECTOR3( 5.0f, 0.0f, -15.0f))
#define PLAYERFPS_BULLETSPEED		(40.0f)
#define PLAYERFPS_GUI_OFFSET		(D3DXVECTOR3(0.0f, -10.0f, 0.0))
/**************************************
�\���̒�`
***************************************/

/**************************************
�O���[�o���ϐ�
***************************************/
static int attackNum;

/**************************************
�v���g�^�C�v�錾
***************************************/


/**************************************
�X�V����
***************************************/
void UpdatePlayerModelFPS(PLAYERMODEL *player)
{
	int x = GetHorizontalInputPress();
	int y = GetVerticalInputPress();

	//�ړ�����
	D3DXVECTOR3 moveDir = D3DXVECTOR3((float)x, (float)y, 0.0f);
	moveDir = *D3DXVec3Normalize(&moveDir, &moveDir) * PLAYERFPS_MOVESPEED;
	player->pos = player->pos + moveDir;

	player->destRot.z = x * PLAYER_DESTROT_MAX;

	player->pos.x = Clampf(-PLAYERFPS_RANGE_X, PLAYERFPS_RANGE_X, player->pos.x);
	player->pos.y = Clampf(-PLAYERFPS_RANGE_Y, PLAYERFPS_RANGE_Y, player->pos.y);

	//���b�N�I���^�[�Q�b�g�̍X�V�m�F
	for (int i = 0; i < PLAYER_ROCKON_MAX; i++)
	{
		if (!player->target[i].use)
		{
			continue;
		}

		if (!*player->target[i].active)
		{
			//player->target[i].use = false;
			//player->target[i].pos = NULL;
			ReleaseRockonTarget(player, i);
		}
	}

	//�^�[�Q�b�g�T�C�g�ړ�����
	//TARGETSITE *site = GetTargetSiteAdr(player->id);
	//site->pos = player->pos;
	SetTargetSitePosition(player->pos, player->id, D3DXVECTOR3(0.0f, 0.0f, 0.0f));
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
	SetLockonGUIPos(player->id, player->pos + PLAYERFPS_GUI_OFFSET);

	//�U������
	player->atkInterbal++;
	if (player->atkInterbal == PLAYER_HOMINGATK_INTERBAL)
		PlaySE(DefineSE::READY);

	if (GetAttackButtonRelease())
	{
		attackNum++;
		AttackPlayerMissile(player);
	}

	//�V���b�g�|�W�V�����X�V
	D3DXVec3TransformCoord(&player->shotpos1, &PLAYERFPS_SHOTPOS_L, &player->mtxWorld);
	D3DXVec3TransformCoord(&player->shotpos2, &PLAYERFPS_SHOTPOS_R, &player->mtxWorld);

	//�V���b�g���ˏ���
	player->cntFrame++;
	if (player->cntFrame % PLAYER_SHOT_INTERBAL == 0)// && !GetAttackButtonPress())
	{
		PlaySE(DefineSE::SHOT);
		SetPlayerBullet(player->shotpos1, PLAYERFPS_BULLETSPEED);
		SetPlayerBullet(player->shotpos2, PLAYERFPS_BULLETSPEED);
	}
}

/**************************************
���ꏈ��
***************************************/
void EnterPlayerModelFPS(PLAYERMODEL *player)
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

	attackNum = 0;
}

/**************************************
�ޏꏈ��
***************************************/
void ExitPlayerModelFPS(PLAYERMODEL *player)
{

}

/**************************************
�z�[�~���O�U���񐔎擾����
***************************************/
int GetTutorialHomingAttackNum(void)
{
	return attackNum;
}

#if 0
/**************************************
�z�[�~���O�U������
***************************************/
void AttackPlayerModelFPS(PLAYERMODEL *player)
{
	if (player->atkInterbal < PLAYER_HOMINGATK_INTERBAL)
	{
		return;
	}

	if (player->lockonNum == 0)
	{
		return;
	}

	for (int i = 0; i < PLAYER_ROCKON_MAX; i++)
	{
		if (player->target[i].pos == NULL)
		{
			continue;
		}

		for (int j = 0; j < 4; j++)
		{
			SetPlayerMissile(player->target[i].pos, player->target[i].hp, player->target[i].active, player->pos);
		}
		ReleaseRockonTarget(player, i);
		player->target[i].use = false;
	}
	player->atkInterbal = 0;
	player->lockonNum = 0;
}
#endif