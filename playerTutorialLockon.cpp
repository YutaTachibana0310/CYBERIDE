//=====================================
//
//�v���C���[���f����l�̏���[playerTutorialLockon.cpp]
//Author:GP11A341 21 ���ԗY��
//
//=====================================
#include "playerModel.h"
#include "playerBullet.h"
#include "input.h"
#include "targetSite.h"
#include "lockonGUI.h"
#include "dataContainer.h"
#include "soundEffectManager.h"

/**************************************
�}�N����`
***************************************/
#define PLAYERTUTOLOCKON_RANGE_X			(85.0f)
#define PLAYERTUTOLOCKON_RANGE_Y			(55.0f)
#define PLAYERTUTOLOCKON_MOVESPEED			(1.5f)

#define PLAYERTUTOLOCKON_SHOTPOS_L			(D3DXVECTOR3(-10.0f, 0.0f, 5.0f))
#define PLAYERTUTOLOCKON_SHOTPOS_R			(D3DXVECTOR3( 10.0f, 0.0f, 5.0f))
#define PLAYERTUTOLOCKON_BULLETSPEED		(40.0f)
/**************************************
�\���̒�`
***************************************/

/**************************************
�O���[�o���ϐ�
***************************************/
static int lockonNum;

/**************************************
�v���g�^�C�v�錾
***************************************/


/**************************************
�X�V����
***************************************/
void UpdatePlayerModelTutorialLockon(PLAYERMODEL *player)
{
	int x = GetHorizontalInputPress();
	int y = GetVerticalInputPress();

	//�ړ�����
	D3DXVECTOR3 moveDir = D3DXVECTOR3((float)x, (float)y, 0.0f);
	moveDir = *D3DXVec3Normalize(&moveDir, &moveDir) * PLAYERTUTOLOCKON_MOVESPEED;
	player->pos = player->pos + moveDir;

	player->destRot.z = x * PLAYER_DESTROT_MAX;

	player->pos.x = Clampf(-PLAYERTUTOLOCKON_RANGE_X, PLAYERTUTOLOCKON_RANGE_X, player->pos.x);
	player->pos.y = Clampf(-PLAYERTUTOLOCKON_RANGE_Y, PLAYERTUTOLOCKON_RANGE_Y, player->pos.y);

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
	bool pressAtkButton = GetAttackButtonPress();
	UpdateTargetSite(pressAtkButton);
	if (GetAttackButtonTrigger())
		lockonNum++;
	

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

	if (GetAttackButtonRelease())
	{
		for (int i = 0; i < PLAYER_ROCKON_MAX; i++)
		{
			if (player->target[i].pos == NULL)
				continue;

			ReleaseRockonTarget(player, i);
			player->target[i].use = false;
			player->lockonNum = 0;
		}
		player->atkInterbal = 0;
	}

	//�V���b�g�|�W�V�����X�V
	D3DXVec3TransformCoord(&player->shotpos1, &PLAYERTUTOLOCKON_SHOTPOS_L, &player->mtxWorld);
	D3DXVec3TransformCoord(&player->shotpos2, &PLAYERTUTOLOCKON_SHOTPOS_R, &player->mtxWorld);

	//�V���b�g���ˏ���
	player->cntFrame++;
	if (player->cntFrame % PLAYER_SHOT_INTERBAL == 0 && !GetAttackButtonPress())
	{
		SetPlayerBullet(player->shotpos1, PLAYERTUTOLOCKON_BULLETSPEED);
		SetPlayerBullet(player->shotpos2, PLAYERTUTOLOCKON_BULLETSPEED);
	}
}

/**************************************
���ꏈ��
***************************************/
void EnterPlayerModelTutorialLockon(PLAYERMODEL *player)
{
	player->cntFrame = 0;
	player->atkInterbal = PLAYER_HOMINGATK_INTERBAL;

	//�^�[�Q�b�g�T�C�g�ݒ菈��
	TARGETSITE *site = GetTargetSiteAdr(player->id);
	site->active = true;
	site->pos = site->targetPos = player->pos;// + D3DXVECTOR3(0.0f, 0.0f, PLAYERTUTOLOCKON_TARGETSITE_POS_Z);

	//���b�N�I���Ώۏ�����
	for (int i = 0; i < PLAYER_ROCKON_MAX; i++)
	{
		player->target[i].use = false;
	}
	player->lockonNum = 0;

	//���b�N�I��GUI�\��
	GetLockonGUIAdr(player->id)->active = true;

	lockonNum = 0;

}

/**************************************
�ޏꏈ��
***************************************/
void ExitPlayerModelTutorialLockon(PLAYERMODEL *player)
{

}

/**************************************
�`���[�g���A�����b�N�I���񐔎擾����
***************************************/
int GetTutorialLockOnNum(void)
{
	return lockonNum;
}