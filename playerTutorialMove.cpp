//=====================================
//
//�v���C���[���f����l�̏���[playerModelTutorialMove.cpp]
//Author:GP11A341 21 ���ԗY��
//
//=====================================
#include "playerModel.h"
#include "playerBullet.h"
#include "input.h"
#include "lockonGUI.h"
#include "targetSite.h"

/**************************************
�}�N����`
***************************************/
#define PLAYERTUTOMOVE_RANGE_X			(85.0f)
#define PLAYERTUTOMOVE_RANGE_Y			(55.0f)
#define PLAYERTUTOMOVE_MOVESPEED			(1.5f)

#define PLAYERTUTOMOVE_SHOTPOS_L			(D3DXVECTOR3(-10.0f, 0.0f, 5.0f))
#define PLAYERTUTOMOVE_SHOTPOS_R			(D3DXVECTOR3( 10.0f, 0.0f, 5.0f))
#define PLAYERTUTOMOVE_BULLETSPEED		(40.0f)
/**************************************
�\���̒�`
***************************************/

/**************************************
�O���[�o���ϐ�
***************************************/
static const float targetSiteOffset[] = {
	-50.0f,
	0.0f,
	50.0f
};

/**************************************
�v���g�^�C�v�錾
***************************************/


/**************************************
�X�V����
***************************************/
void UpdatePlayerModelTutorialMove(PLAYERMODEL *player)
{
	int x = GetHorizontalInputPress();
	int y = GetVerticalInputPress();

	//�ړ�����
	D3DXVECTOR3 moveDir = D3DXVECTOR3((float)x, (float)y, 0.0f);
	moveDir = *D3DXVec3Normalize(&moveDir, &moveDir) * PLAYERTUTOMOVE_MOVESPEED;
	player->pos = player->pos + moveDir;

	player->destRot.z = x * PLAYER_DESTROT_MAX;

	player->pos.x = Clampf(-PLAYERTUTOMOVE_RANGE_X, PLAYERTUTOMOVE_RANGE_X, player->pos.x);
	player->pos.y = Clampf(-PLAYERTUTOMOVE_RANGE_Y, PLAYERTUTOMOVE_RANGE_Y, player->pos.y);

	//���b�N�I��GUI�Z�b�g����
	SetLockonGUIPos(player->id, player->pos + D3DXVECTOR3(0.0f, -10.0f, 0.0f));

	//�V���b�g�|�W�V�����X�V
	D3DXVec3TransformCoord(&player->shotpos1, &PLAYERTUTOMOVE_SHOTPOS_L, &player->mtxWorld);
	D3DXVec3TransformCoord(&player->shotpos2, &PLAYERTUTOMOVE_SHOTPOS_R, &player->mtxWorld);

	//�V���b�g���ˏ���
	player->cntFrame++;
	if (player->cntFrame % PLAYER_SHOT_INTERBAL == 0)
	{
		SetPlayerBullet(player->shotpos1, PLAYERTUTOMOVE_BULLETSPEED);
		SetPlayerBullet(player->shotpos2, PLAYERTUTOMOVE_BULLETSPEED);
	}
}

/**************************************
���ꏈ��
***************************************/
void EnterPlayerModelTutorialMove(PLAYERMODEL *player)
{
	player->cntFrame = 0;
	player->atkInterbal = PLAYER_HOMINGATK_INTERBAL;

	//�^�[�Q�b�g�T�C�g�ݒ菈��
	TARGETSITE *site = GetTargetSiteAdr(player->id);
	site->active = true;
	site->pos = site->targetPos = player->pos;

	//���b�N�I���Ώۏ�����
	for (int i = 0; i < PLAYER_ROCKON_MAX; i++)
	{
		player->target[i].use = false;
	}
	player->lockonNum = 0;


}

/**************************************
�ޏꏈ��
***************************************/
void ExitPlayerModelTutorialMove(PLAYERMODEL *player)
{

}