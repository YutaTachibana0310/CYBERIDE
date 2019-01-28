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

/**************************************
�}�N����`
***************************************/
#define BATTLEBONUS_BGM_FADE_DURATION		(120)
#define BATTLE_BONUS_DURATION			(570)				//�{�[�i�X�^�C������		
#define BATTLE_BONUS_WAIT				(120)				//�{�[�i�X�^�C���̃X�^�[�g�I�t�Z�b�g
#define BATTLE_BONUS_EMMITT_RANGE		(200.0f)			//�{�[�i�X�^�C���̃L���[�u�����͈�
#define BATTLE_BONUS_POS_Z				(6000.0f)			//�{�[�i�X�^�C�����̃L���[�u�����ʒu�iZ�j
#define BATTLE_BONUS_SPEED				(35.0f)				//�{�[�i�X�^�C���̃L���[�u�X�s�[�h

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
void OnEnterBattleBonusTime(BATTLECONTROLLER *controller)
{
	//�e���b�v�Đ�
	StartBonusTelopAnim(true);

	//�J�n�^�C�~���O��ۑ�
	controller->bonusStartFrame = controller->cntFrame;

	//BGM�؂�ւ�
	FadeInBGM(BGM_BONUSTIME, BATTLEBONUS_BGM_FADE_DURATION);
	FadeOutBGM(BGM_BATTLESCENE, BATTLEBONUS_BGM_FADE_DURATION);
}

/**************************************
�X�V����
***************************************/
void OnUpdateBattleBonusTime(BATTLECONTROLLER *controller)
{
	controller->cntFrame++;
	//�{�[�i�X�^�C�����ɃL���[�u����o�������
	if ((int)(controller->cntFrame - controller->bonusStartFrame) < BATTLE_BONUS_DURATION)
	{
		for (int i = 0; i < 10; i++)
		{
			D3DXVECTOR3 emmittPos;
			emmittPos.x = RandomRangef(-BATTLE_BONUS_EMMITT_RANGE, BATTLE_BONUS_EMMITT_RANGE);
			emmittPos.y = RandomRangef(-BATTLE_BONUS_EMMITT_RANGE, BATTLE_BONUS_EMMITT_RANGE);
			emmittPos.z = BATTLE_BONUS_POS_Z;

			EmmittCubeObject(1, &emmittPos, BATTLE_BONUS_SPEED);
		}
	}

	//�{�[�i�X�^�C���I������
	if ((int)(controller->cntFrame - controller->bonusStartFrame) > BATTLE_BONUS_DURATION + BATTLE_BONUS_WAIT)
	{
		controller->cntFrame = controller->bonusStartFrame;
		FadeOutBGM(BGM_BONUSTIME, BATTLEBONUS_BGM_FADE_DURATION);
		FadeInBGM(BGM_BATTLESCENE, BATTLEBONUS_BGM_FADE_DURATION, true);
		ChangeStateBattleController(BattleNormalTime);
	}
}
