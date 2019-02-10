//=====================================
//
//�o�g���ʏ펞�X�V����[battleNormalTime.cpp]
//Author:GP11A341 21 ���ԗY��
//
//=====================================
#include "battleController.h"
#include "fuzzyLogic.h"
#include "playerModel.h"
#include "enemyManager.h"
#include "stageData.h"
#include "hardCubeObject.h"
#include "bonusCube.h"
#include "bonusTelop.h"
#include "dataContainer.h"

/**************************************
�}�N����`
***************************************/
#define BATTLE_DATATYPE_VIEWCHANGE		(999)
/**************************************
�\���̒�`
***************************************/

/**************************************
�O���[�o���ϐ�
***************************************/
static int EmmittInterbal[DATACONTAINER_LOCKLEVEL_MAX] = {
	60, 30, 40, 30, 25, 20, 15
};

/**************************************
�v���g�^�C�v�錾
***************************************/
void EmittFromStageData(BATTLECONTROLLER *controller);
void EmmittFromFuzzy(BATTLECONTROLLER *controller);

/**************************************
���ꏈ��
***************************************/
void OnEnterBattleNormalTime(BATTLECONTROLLER *controller)
{
	//�{�[�i�X�^�C���I���e���b�v�𗬂�
}

/**************************************
�X�V����
***************************************/
void OnUpdateBattleNormalTime(BATTLECONTROLLER *controller)
{
	controller->cntFrame[controller->viewMode]++;
	EmittFromStageData(controller);

	if (controller->cntFrame[controller->viewMode] % EmmittInterbal[GetLockonLevel()] == 0)
		EmmittFromFuzzy(controller);

}

/**************************************
�X�e�[�W�f�[�^����̃L���[�u���o����
***************************************/
void EmittFromStageData(BATTLECONTROLLER *controller)
{
	/*
	���������̃v���O�������Ԃɍ���Ȃ������Ȃ̂�
	�X�e�[�W�f�[�^����ł��ō쐬���Ďg�p
	*/
	int cntData = 0;
	STAGE_DATA *data = NULL;
	cntData = UpdateStageData(&data, controller->cntFrame[controller->viewMode], controller->viewMode);
	for (int i = 0; i < cntData; i++, data++)
	{
		if (data->type < HardCubeTypeMax)
		{
			SetHardCubeObjectFromData(data);
		}
		else if (data->type == BATTLE_DATATYPE_VIEWCHANGE)
		{
			controller->nextViewMode = data->initPos.x;		//�X�e�[�W�f�[�^��X���W�Ɏ��̎��_��񂪊i�[����Ă���
			ChangeStateBattleController(BattleChangeView);
		}
		else
		{
			ChangeStateBattleController(BattleWaitBonusTimeBegin);
			SetBonusCube();
		}
	}
}