//=====================================
//
//�o�g�����_�ύX�X�e�[�g����[battleChangeViewMode.cpp]
//Author:GP11A341 21 ���ԗY��
//
//=====================================
#include "battleController.h"
#include "cautionTelop.h"

/**************************************
�}�N����`
***************************************/
#define BATTLE_CHANGEVIEWMODE_DURATION		(270)
#define BATTLE_CHANGEVIEW_TIMING			(240)

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
����������
***************************************/
void OnEnterBattleChangeView(BATTLECONTROLLER *entity)
{
	cntFrame = 0;
	SetCautionTelop();
}

/**************************************
�X�V����
***************************************/
void OnUpdateBattleChangeView(BATTLECONTROLLER *entity)
{
	cntFrame++;

	if (cntFrame == BATTLE_CHANGEVIEW_TIMING)
	{
		ChangeViewModeBattleController(entity->nextViewMode);
	}

	if (cntFrame == BATTLE_CHANGEVIEWMODE_DURATION)
	{
		ChangeStateBattleController(BattleNormalTime);
	}
}
