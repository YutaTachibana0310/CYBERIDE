//=============================================================================
//
// バトルシーンヘッダ [BattleScene.h]
// Author : GP11A341 21 立花雄太
//
//=============================================================================
#ifndef _BATTLESCENE_H_
#define _BATTLESCENE_H_

#include "main.h"
#include "sceneManager.h"

// マクロ定義

//*****************************************************************************
// 構造体定義
//*****************************************************************************

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitBattleScene(int num);		//バトルシーン初期化処理
void UninitBattleScene(int num);		//バトルシーン終了処理
void UpdateBattleScene(void);			//バトルシーン更新処理
void DrawBattleScene(void);				//バトルシーン描画処理

#endif
