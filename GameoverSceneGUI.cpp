//=====================================
//
//ゲームオーバーシーンGUI処理[GameoverSceneGUI.cpp]
//Author:GP11A341 21 立花雄太
//
//=====================================
#include "gameoverTelop.h"

/**************************************
マクロ定義
***************************************/

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
void OnEnterGameoverSceneGUI(void)
{
	InitGameoverTelop(0);
}

/**************************************
更新処理
***************************************/
void OnUpdateGameoverSceneGUI(void)
{
	UpdateGameoverTelop();
}

/**************************************
描画処理
***************************************/
void OnDrawGameoverSceneGUI(void)
{
	DrawGameoverTelop();
}