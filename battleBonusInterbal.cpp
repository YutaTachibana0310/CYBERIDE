//=====================================
//
//�e���v���[�g����[battleBonusInterbal.cpp]
//Author:GP11A341 21 ���ԗY��
//
//=====================================
#include "battleController.h"

/**************************************
�}�N����`
***************************************/
#define BATTLE_BONUSINTERBAL_DURATION	(120)

/**************************************
�\���̒�`
***************************************/

/**************************************
�O���[�o���ϐ�
***************************************/
static int cntFrame;

/**************************************
�v���g�^�C�v�錾
***************************************/

/**************************************
���ꏈ��
***************************************/
void OnEnterBattleBonusInterbal(BATTLECONTROLLER *entity)
{
	cntFrame = 0;
}

/**************************************
�X�V����
***************************************/
void OnUpdateBattleBonusInterbal(BATTLECONTROLLER *entity)
{
	cntFrame++;

	if (cntFrame == BATTLE_BONUSINTERBAL_DURATION)
	{
		ChangeStateBattleController(BattleBonusTime);
	}
}