//=====================================
//
//�o�g�����_�ύX�X�e�[�g����[battleChangeViewMode.cpp]
//Author:GP11A341 21 ���ԗY��
//
//=====================================
#include "battleController.h"
#include "cautionTelop.h"
#include "hardCubeObject.h"
#include "soundEffectManager.h"

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
static bool playedTelop;

/**************************************
�v���g�^�C�v�錾
***************************************/

/**************************************
����������
***************************************/
void OnEnterBattleChangeView(BATTLECONTROLLER *entity)
{
	cntFrame = 0;
	playedTelop = false;
	//SetCautionTelop();
}

/**************************************
�X�V����
***************************************/
void OnUpdateBattleChangeView(BATTLECONTROLLER *entity)
{
	//���ׂẴn�[�h�L���[�u����A�N�e�B�u�ɂȂ�����e���b�v�Đ�
	if (!playedTelop && IsAllHardCubeDisable())
	{
		PlaySE(DefineSE::CAUTION);
		SetCautionTelop();
		playedTelop = true;
	}

	//�e���b�v���Đ�����Ă���J�E���g���J�n����
	if (!playedTelop)
		return;

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
