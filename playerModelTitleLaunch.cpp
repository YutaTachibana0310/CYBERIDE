//=====================================
//
//�e���v���[�g����[playerModelTitleLaunch.cpp]
//Author:GP11A341 21 ���ԗY��
//
//=====================================
#include "playerModelTitleLaunch.h"
#include "Easing.h"

/**************************************
�}�N����`
***************************************/
#define PLAYERTITLELAUNCH_SPEED			(8.0f)
#define PLAYERTITLELAUNCH_DIR_START		(-0.2f)
#define PLAYERTITLELAUNCH_DIR_END		(5.0f)
#define PLAYERTITLELAUNCH_ACCEL_END		(60.0f)

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
���ꏈ��
***************************************/
void EnterPlayerModelTitleLaunch(PLAYERMODEL *player)
{
	player->cntFrame = 0;
}

/**************************************
�X�V����
***************************************/
void UpdatePlayerModelTitleLaunch(PLAYERMODEL *player)
{
	player->cntFrame++;

	float t = (float)player->cntFrame / (float)PLAYERTITLELAUNCH_ACCEL_END;
	float dir = EaseInExponential(t, PLAYERTITLELAUNCH_DIR_START, PLAYERTITLELAUNCH_DIR_END);
	player->pos.z += dir * PLAYERTITLELAUNCH_SPEED;
}

/**************************************
�ޏꏈ��
***************************************/
void ExitPlayerModelTitleLaunch(PLAYERMODEL *player)
{

}

