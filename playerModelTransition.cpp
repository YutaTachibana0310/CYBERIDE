//=====================================
//
//�v���C���[�J�ڏ���[playerTransition.cpp]
//Author:GP11A341 21 ���ԗY��
//
//=====================================
#include "playerModelTransition.h"
#include "battleCamera.h"
#include "targetSite.h"
#include "lockonGUI.h"

/**************************************
�}�N����`
***************************************/

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
void EnterPlayerModelTransition(PLAYERMODEL *player)
{
	player->cntFrame = 0;
	GetTargetSiteAdr(player->id)->active = false;
	GetLockonGUIAdr(player->id)->active = false;
	player->initPos = player->pos;
}

/**************************************
�X�V����
***************************************/
void UpdatePlayerModelTransition(PLAYERMODEL *player)
{
	player->cntFrame++;
	player->pos = EaseOutCubicVector((float)player->cntFrame / BATTLECAMERA_MOVEFRAME, player->initPos, D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	if (player->cntFrame == BATTLECAMERA_MOVEFRAME)
	{
		ChangeStatePlayerModel(player->nextState);
	}

}

/**************************************
�ޏꏈ��
***************************************/
void ExitPlayerModelTransition(PLAYERMODEL *player)
{

}