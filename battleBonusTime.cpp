//=====================================
//
//ボーナスタイム更新処理[battleBonusTime.cpp]
//Author:GP11A341 21 立花雄太
//
//=====================================
#include "battleController.h"
#include "bonusTelop.h"
#include "bgmManager.h"
#include "enemyManager.h"
#include "bonusPositinoTelop.h"

/**************************************
マクロ定義
***************************************/
#define BATTLEBONUS_BGM_FADE_DURATION	(120)
#define BATTLE_BONUS_DURATION			(570)				//ボーナスタイム時間		
#define BATTLE_BONUS_WAIT				(120)				//ボーナスタイムのスタートオフセット
#define BATTLE_BONUS_EMMITT_RANGE		(200.0f)				//ボーナスタイムのキューブ生成範囲
#define BATTLE_BONUS_POS_Z				(6000.0f)			//ボーナスタイム時のキューブ生成位置（Z）
#define BATTLE_BONUS_SPEED				(35.0f)				//ボーナスタイムのキューブスピード
#define BATTLE_BONUS_EMMITTPOS_MAX		(6)
#define BATTLE_BONUS_SWITCH_TIMING		(150)
#define BATTLE_BONUS_EMMITT_NUM			(11)

/**************************************
構造体定義
***************************************/

/**************************************
グローバル変数
***************************************/

/**************************************
プロトタイプ宣言
***************************************/

/**************************************
入場処理
***************************************/
void OnEnterBattleBonusTime(BATTLECONTROLLER *controller)
{
	if (controller->prevState == BattleWaitBonusTimeBegin)
	{
		//テロップ再生
		StartBonusTelopAnim(true);

		//開始タイミングを保存
		controller->bonusStartFrame = controller->cntFrame[controller->viewMode];

		//BGM切り替え
		FadeInBGM(BGM_BONUSTIME, BATTLEBONUS_BGM_FADE_DURATION);
		FadeOutBGM(BGM_BATTLESCENE, BATTLEBONUS_BGM_FADE_DURATION);
	}
}

/**************************************
更新処理
***************************************/
void OnUpdateBattleBonusTime(BATTLECONTROLLER *controller)
{
	controller->cntFrame[controller->viewMode]++;

	int elapsedFrame = (int)(controller->cntFrame[controller->viewMode] - controller->bonusStartFrame);

	//ボーナスタイム中にキューブを放出する期間
	if (elapsedFrame < BATTLE_BONUS_DURATION)
	{
		for (int i = 0; i < BATTLE_BONUS_EMMITT_NUM; i++)
		{
			D3DXVECTOR3 emmittPos;
			emmittPos.x = RandomRangef(-BATTLE_BONUS_EMMITT_RANGE, BATTLE_BONUS_EMMITT_RANGE);
			emmittPos.y = RandomRangef(-BATTLE_BONUS_EMMITT_RANGE, BATTLE_BONUS_EMMITT_RANGE);
			emmittPos.z = BATTLE_BONUS_POS_Z;

			EmmittCubeObject(1, &emmittPos, BATTLE_BONUS_SPEED);
		}
	}


	//ボーナスタイム終了判定
	if (elapsedFrame > BATTLE_BONUS_DURATION + BATTLE_BONUS_WAIT)
	{
		controller->cntFrame[controller->viewMode] = controller->bonusStartFrame;
		FadeOutBGM(BGM_BONUSTIME, BATTLEBONUS_BGM_FADE_DURATION);
		FadeInBGM(BGM_BATTLESCENE, BATTLEBONUS_BGM_FADE_DURATION, true);
		SetStateBonusPositionTelop(false);
		ChangeStateBattleController(BattleNormalTime);
		return;
	}
}
