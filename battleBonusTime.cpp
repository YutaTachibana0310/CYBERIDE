//=====================================
//
//�{�[�i�X�^�C���X�V����[battleBonusTime.cpp]
//Author:GP11A341 21 ���ԗY��
//
//=====================================
#include "battleController.h"
#include "bonusTelop.h"
#include "bgmManager.h"
#include "enemyManager.h"
#include "bonusPositinoTelop.h"

/**************************************
�}�N����`
***************************************/
#define BATTLEBONUS_BGM_FADE_DURATION	(120)
#define BATTLE_BONUS_DURATION			(570)				//�{�[�i�X�^�C������		
#define BATTLE_BONUS_WAIT				(120)				//�{�[�i�X�^�C���̃X�^�[�g�I�t�Z�b�g
#define BATTLE_BONUS_EMMITT_RANGE		(200.0f)				//�{�[�i�X�^�C���̃L���[�u�����͈�
#define BATTLE_BONUS_POS_Z				(6000.0f)			//�{�[�i�X�^�C�����̃L���[�u�����ʒu�iZ�j
#define BATTLE_BONUS_SPEED				(35.0f)				//�{�[�i�X�^�C���̃L���[�u�X�s�[�h
#define BATTLE_BONUS_EMMITTPOS_MAX		(6)
#define BATTLE_BONUS_SWITCH_TIMING		(150)

#define BATTLE_BONUS_EMMITT_X			(50.0)
#define BATTLE_BONUS_EMMITT_Y			(35.0)

/**************************************
�\���̒�`
***************************************/

/**************************************
�O���[�o���ϐ�
***************************************/
static const D3DXVECTOR3 EmmittPos[BATTLE_BONUS_EMMITTPOS_MAX] = {
	D3DXVECTOR3(-BATTLE_BONUS_EMMITT_X, BATTLE_BONUS_EMMITT_Y, 0.0f),
	D3DXVECTOR3(0.0f, BATTLE_BONUS_EMMITT_Y, 0.0f),
	D3DXVECTOR3(BATTLE_BONUS_EMMITT_X, BATTLE_BONUS_EMMITT_Y, 0.0f),
	D3DXVECTOR3(-BATTLE_BONUS_EMMITT_X, -BATTLE_BONUS_EMMITT_Y, 0.0f),
	D3DXVECTOR3(0.0f, -BATTLE_BONUS_EMMITT_Y, 0.0f),
	D3DXVECTOR3(BATTLE_BONUS_EMMITT_X, -BATTLE_BONUS_EMMITT_Y, 0.0f)
};

static int posIndex;

/**************************************
�v���g�^�C�v�錾
***************************************/

/**************************************
���ꏈ��
***************************************/
void OnEnterBattleBonusTime(BATTLECONTROLLER *controller)
{
	if (controller->prevState == BattleWaitBonusTimeBegin)
	{
		//�e���b�v�Đ�
		StartBonusTelopAnim(true);

		//�J�n�^�C�~���O��ۑ�
		controller->bonusStartFrame = controller->cntFrame[controller->viewMode];

		//BGM�؂�ւ�
		FadeInBGM(BGM_BONUSTIME, BATTLEBONUS_BGM_FADE_DURATION);
		FadeOutBGM(BGM_BATTLESCENE, BATTLEBONUS_BGM_FADE_DURATION);
	}
	//�ʒu�\��
	//posIndex = RandomRange(0, BATTLE_BONUS_EMMITTPOS_MAX);
	//SetStateBonusPositionTelop(true);
	//SetPositionBonusPositionTelop(EmmittPos[posIndex]);
}

/**************************************
�X�V����
***************************************/
void OnUpdateBattleBonusTime(BATTLECONTROLLER *controller)
{
	controller->cntFrame[controller->viewMode]++;

	int elapsedFrame = (int)(controller->cntFrame[controller->viewMode] - controller->bonusStartFrame);

	//�{�[�i�X�^�C�����ɃL���[�u����o�������
	if (elapsedFrame < BATTLE_BONUS_DURATION)
	{
		for (int i = 0; i < 10; i++)
		{
			D3DXVECTOR3 emmittPos;
			emmittPos.x = /*EmmittPos[posIndex].x +*/ RandomRangef(-BATTLE_BONUS_EMMITT_RANGE, BATTLE_BONUS_EMMITT_RANGE);
			emmittPos.y = /*EmmittPos[posIndex].y +*/ RandomRangef(-BATTLE_BONUS_EMMITT_RANGE, BATTLE_BONUS_EMMITT_RANGE);
			emmittPos.z = BATTLE_BONUS_POS_Z;

			EmmittCubeObject(1, &emmittPos, BATTLE_BONUS_SPEED);
		}
	}


	//�{�[�i�X�^�C���I������
	if (elapsedFrame > BATTLE_BONUS_DURATION + BATTLE_BONUS_WAIT)
	{
		controller->cntFrame[controller->viewMode] = controller->bonusStartFrame;
		FadeOutBGM(BGM_BONUSTIME, BATTLEBONUS_BGM_FADE_DURATION);
		FadeInBGM(BGM_BATTLESCENE, BATTLEBONUS_BGM_FADE_DURATION, true);
		SetStateBonusPositionTelop(false);
		ChangeStateBattleController(BattleNormalTime);
		return;
	}

	//�C���^�[�o������
	//if (elapsedFrame % BATTLE_BONUS_SWITCH_TIMING == 0 && elapsedFrame + BATTLE_BONUS_SWITCH_TIMING < BATTLE_BONUS_DURATION + BATTLE_BONUS_WAIT)
	//{
	//	ChangeStateBattleController(BattleBonusIntebal);
	//	return;
	//}
}
