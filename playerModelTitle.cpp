//=====================================
//
//�e���v���[�g����[template.cpp]
//Author:GP11A341 21 ���ԗY��
//
//=====================================
#include "playerModelTitle.h"
#include "playerBullet.h"

/**************************************
�}�N����`
***************************************/
#define PLAYERTITLE_INITPOS		(D3DXVECTOR3(0.0f, -10.0f, 100.0f))
#define PLAYERTITLE_MOVE_PERIOD	(180)
#define PLAYERTITLE_MOVE_END	(120)
#define PLAYERTITLE_MOVE_RANGE	(20.0f)

/**************************************
�\���̒�`
***************************************/

/**************************************
�O���[�o���ϐ�
***************************************/
static D3DXVECTOR3 targetPos[PLAYERMODEL_MAX];

/**************************************
�v���g�^�C�v�錾
***************************************/

/**************************************
���ꏈ��
***************************************/
void EnterPlayerModelTitle(PLAYERMODEL *player)
{
	player->cntFrame = 0;
	player->pos = PLAYERTITLE_INITPOS;

}

/**************************************
�X�V����
***************************************/
void UpdatePlayerModelTitle(PLAYERMODEL *player)
{
	player->cntFrame++;

	//�ړ�����������Őݒ�
	if (player->cntFrame % PLAYERTITLE_MOVE_PERIOD == 0)
	{
		targetPos[player->id] = PLAYERTITLE_INITPOS;
		targetPos[player->id].x = RandomRangef(-PLAYERTITLE_MOVE_RANGE, PLAYERTITLE_MOVE_RANGE);
		player->initPos = player->pos;
		player->cntFrame = 0;
	}

	//�ړ�
	float t = (float)player->cntFrame / (float)PLAYERTITLE_MOVE_END;
	player->pos = EaseInOutCubicVector(t, player->initPos, targetPos[player->id]);

	//��]
	float diff = targetPos[player->id].x - player->pos.x;
	float x = diff / fabsf(diff);
	player->destRot.z = x * PLAYER_DESTROT_MAX;

	//�U��
	if (player->cntFrame % PLAYER_SHOT_INTERBAL == 0)
	{


	}

}

/**************************************
�ޏꏈ��
***************************************/
void ExitPlayerModelTitle(PLAYERMODEL *player)
{

}
