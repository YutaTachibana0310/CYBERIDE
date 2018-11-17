//=============================================================================
//
// バトルシーン処理 [battleScene.cpp]
// Author : GP11A341 21 立花雄太
//
//=============================================================================
#include "main.h"
#include "battleScene.h"
#include "input.h"
#include "cloud.h"
#include "enemyMissile.h"
#include "playerModel.h"
#include "battleCamera.h"
#include "playerBullet.h"
#include "targetSite.h"

/*****************************************************************************
マクロ定義
*****************************************************************************/
#define BATTLESCENE_TEXTURE_NAME	_T("data/TEXTURE/UI/battle.png")	// プレイヤーバレットのテクスチャ

#define BATTLESCENE_TEXTURE_SIZE_X (200)			// テクスチャサイズX
#define BATTLESCENE_TEXTURE_SIZE_Y (200)			// テクスチャサイズY

/*****************************************************************************
プロトタイプ宣言
*****************************************************************************/

/*****************************************************************************
構造体定義
*****************************************************************************/

/*****************************************************************************
グローバル変数
*****************************************************************************/

/******************************************************************************
初期化処理
******************************************************************************/
HRESULT InitBattleScene(int num)
{
	InitCloud(num);
	InitEnemyMissile(num);
	InitPlayerModel(num);
	InitPlayerBullet(num);
	InitBattleCamera();
	InitTargetSite(num);

	return S_OK;
}

/******************************************************************************
終了処理
******************************************************************************/
void UninitBattleScene(int num)
{
	UninitCloud(num);
	UninitEnemyMissile(num);
	UninitPlayerModel(num);
	UninitPlayerBullet(num);
	UninitTargetSite(num);
}

/******************************************************************************
更新処理
******************************************************************************/
void UpdateBattleScene(void)
{
	UpdateCloud();
	UpdateEnemyMissile();
	UpdatePlayerBullet();
	UpdatePlayerModel();
	UpdateBattleCamera();
	UpdateTargetSite();

	if (GetKeyboardTrigger(DIK_RETURN))
	{
		SetScene(ResultScene);
	}
}

/******************************************************************************
描画処理
******************************************************************************/
void DrawBattleScene(void)
{
	SetBattleCamera();
	DrawCloud();
	DrawEnemyMissile();
	DrawPlayerModel();
	DrawPlayerBullet();
	DrawTargetSite();
}
