//=====================================
//
//�o�g���R���g���[������[battleController.cpp]
//Author:GP11A341 21 ���ԗY��
//
//=====================================
#include "battleController.h"
#include "fuzzyLogic.h"
#include "playerModel.h"
#include "debugWindow.h"
#include "battleCamera.h"
#include "enemyManager.h"
#include "bonusTelop.h"
#include "stageData.h"
#include "bgmManager.h"

#include "cubeObject.h"
#include "hardCubeObject.h"
#include "bonusCube.h"

/**************************************
�}�N����`
***************************************/
#define BATTLE_SPACE_LEFT_BORDER		(-300.0f)			//�G�l�~�[�̐������W�͈́i���[�j
#define BATTLE_SPACE_TOP_BORDER			(300.0f)			//�G�l�~�[�̐������W�͈́i��[�j
#define BATTLE_SPACE_RIGHT_BORDER		(300.0f)			//�G�l�~�[�̐������W�͈́i�E�[�j
#define BATTLE_SPACE_BOTTOM_BORDER		(-300.0f)			//�G�l�~�[�̐������W�͈́i���[�j
#define BATTLE_EMITTPOS_Z				(6000.0f)			//�G�l�~�[�������WZ�l

#define BATTLE_CUBEEMMITT_INTERBAL		(60)

#define BATTLE_CUBE_INITEMMITT_SPEED	(15.0f)

/**************************************
�\���̒�`
***************************************/
typedef void(*funcBattleController)(BATTLECONTROLLER *controller);

/**************************************
�v���g�^�C�v�錾
***************************************/
//void EmmittOnBonusTime(void);
//void EmmittOnNormalTime(void);
//void EmittFromStageData(void);

//���ꏈ��
void OnEnterBattleNormalTime(BATTLECONTROLLER *controller);
void OnEnterBattleWaitBonusTimeBegin(BATTLECONTROLLER *controller);
void OnEnterBattleBonusTime(BATTLECONTROLLER *controller);

//�X�V����
void OnUpdateBattleNormalTime(BATTLECONTROLLER *controller);
void OnUpdateBattleWaitBonusTimeBegin(BATTLECONTROLLER *controller);
void OnUpdateBattleBonusTime(BATTLECONTROLLER *controller);

/**************************************
�O���[�o���ϐ�
***************************************/
//static bool isBonusTime;
//static bool countState;

static BATTLECONTROLLER controller;

//���ꏈ���e�[�u��
static funcBattleController Enter[BattleStateMax] = {
	OnEnterBattleNormalTime,
	OnEnterBattleWaitBonusTimeBegin,
	OnEnterBattleBonusTime,
};

//�X�V�����e�[�u��
static funcBattleController Update[BattleStateMax] = {
	OnUpdateBattleNormalTime,
	OnUpdateBattleWaitBonusTimeBegin,
	OnUpdateBattleBonusTime,
};

/**************************************
����������
***************************************/
void InitBattleController(int num)
{
	InitStageData(num);

	//�����͈͂𕪊����ăG�l�~�[�̐������W���v�Z
	float spaceUnitWidth = SCREEN_WIDTH / BATTLE_SPACE_DIVIDE_NUM;
	float spaceUnitHeight = SCREEN_HEIGHT / BATTLE_SPACE_DIVIDE_NUM;

	for (int y = 0; y < BATTLE_SPACE_DIVIDE_NUM; y++)
	{
		for (int x = 0; x < BATTLE_SPACE_DIVIDE_NUM; x++)
		{
			controller.checkPos[y * BATTLE_SPACE_DIVIDE_NUM + x].x = spaceUnitWidth * (x + 0.5f);
			controller.checkPos[y * BATTLE_SPACE_DIVIDE_NUM + x].y = spaceUnitHeight * (y + 0.5f);

			controller.emmittPos[y * BATTLE_SPACE_DIVIDE_NUM + x].x = (BATTLE_SPACE_RIGHT_BORDER - BATTLE_SPACE_LEFT_BORDER) / BATTLE_SPACE_DIVIDE_NUM * (x + 0.5f) + BATTLE_SPACE_LEFT_BORDER;
			controller.emmittPos[y * BATTLE_SPACE_DIVIDE_NUM + x].y = (BATTLE_SPACE_TOP_BORDER - BATTLE_SPACE_BOTTOM_BORDER) / BATTLE_SPACE_DIVIDE_NUM * (y + 0.5f) + BATTLE_SPACE_BOTTOM_BORDER;
			controller.emmittPos[y * BATTLE_SPACE_DIVIDE_NUM + x].z = 5000.0f;
		}
	}

	//�L���[�u�������z�u
	for (int z = 0; z < 5000; z += 100)
	{
		int x = rand() % 3;
		int y = rand() % 3;

		D3DXVECTOR3 pos = D3DXVECTOR3(controller.emmittPos[y * BATTLE_SPACE_DIVIDE_NUM + x].x, controller.emmittPos[y * BATTLE_SPACE_DIVIDE_NUM + x].y, z);
		EmmittCubeObject(1, &pos, BATTLE_CUBE_INITEMMITT_SPEED);
	}

	//�e�p�����[�^��������
	controller.cntFrame = 0;
	for (int i = 0; i < BATTLE_SPACE_MAX; i++)
	{
		controller.lastEmittFrame[i] = 0xffffffff;
	}

	controller.currentState = BattleNormalTime;
	controller.prevState = BattleNormalTime;
}

/**************************************
�I������
***************************************/
void UninitBattleController(int num)
{
	UninitStageData(num);
}

/**************************************
�X�V����
***************************************/
void UpdateBattleController(void)
{
	Update[controller.currentState](&controller);
}

/**************************************
��ԑJ�ڏ���
***************************************/
void ChangeStateBattleController(int next)
{
	controller.currentState = next;
	Enter[controller.currentState](&controller);
}

/**************************************
�{�[�i�X�^�C�����ǂ���
***************************************/
bool IsBonusTime(void)
{
	if (controller.currentState == BattleBonusTime)
		return true;
	else
		return false;
}

/**************************************
�t�@�W�B���_�ł̃L���[�u���o����
***************************************/
void EmmittFromFuzzy(BATTLECONTROLLER *controller)
{
	float valueLength[BATTLE_SPACE_MAX];
	float valueTime[BATTLE_SPACE_MAX];
	float fuzzyValue[BATTLE_SPACE_MAX];
	int decidedPos = 0;

	D3DXVECTOR3 playerPos;
	float maxValue = -9999.9f;

	D3DXVec3TransformCoord(&playerPos, &GetPlayerAdr(0)->pos, &GetBattleCameraView());
	D3DXVec3TransformCoord(&playerPos, &playerPos, &GetBattleCameraProjection());
	TranslateViewPort(&playerPos, &playerPos);

	//�e�������W�ɑ΂��ăt�@�W�B���_�ŏd�݂��v�Z
	for (int i = 0; i < BATTLE_SPACE_MAX; i++)
	{
		float length = D3DXVec2Length(&(D3DXVECTOR2)(playerPos - controller->checkPos[i]));
		float elapsedTime = (float)(controller->cntFrame - controller->lastEmittFrame[i]);

		valueLength[i] = fFuzzyTriangle(length, BATTLE_FUZZY_NEAR_BORDER, BATTLE_FUZZY_MIDDLE_BORDER, BATTLE_FUZZY_FAR_BORDER);
		valueTime[i] = fFuzzyRightGrade(elapsedTime, BATTLE_FUZZY_RECENTLY_BORDER, BATTLE_FUZZY_LATELY_BORDER);
		fuzzyValue[i] = valueLength[i] * valueTime[i];
		if (maxValue < fuzzyValue[i])
		{
			decidedPos = i;
			maxValue = fuzzyValue[i];
		}
	}

	EmmittCubeObject(BATTLE_CUBEEMMITT_NUM, &(controller->emmittPos[decidedPos]), BATTLE_CUBEEMMITT_SPEED);
	controller->lastEmittFrame[decidedPos] = controller->cntFrame;
}