//=====================================
//
//GUIマネージャ処理[GUIManager.cpp]
//Author:GP11A341 21 立花雄太
//
//=====================================
#include "GUIManager.h"
#include "sceneManager.h"
#include "scoreGUI.h"
#include "hpGUI.h"
#include "lockonGUI.h"
#include "powerUpTelop.h"
#include "bonusTelop.h"
#include "bonusTimeGUI.h"
#include "lockonLevelGUI.h"
#include "lockonNumGUI.h"

#include "logoScene.h"
#include "titleScene.h"
#include "sceneFade.h"

/**************************************
マクロ定義
***************************************/
#define GUI_NUMTEX_DIVIDE_X				(5)
#define GUI_NUMTEX_DIVIDE_Y				(2)
#define GUI_NUMTEX_PATTERN_MAX			(10)

/**************************************
構造体定義
***************************************/
typedef void(*DrawGUI)(void);

/**************************************
プロトタイプ宣言
***************************************/
void DrawGUIonBattleScene(void);
void DrawGUIonLogoScene(void);
void DrawGUIonTitleScene(void);

/**************************************
グローバル変数
***************************************/
static LPDIRECT3DTEXTURE9 texture[GUI_NUMTEX_MAX];
static const char* texturePath[GUI_NUMTEX_MAX] =
{
	"data/TEXTURE/UI/scoreNum.png",
	"data/TEXTURE/UI/lockonNum.png",
	"data/TEXTURE/UI/timeNum.png"
};

//各シーンのGUI描画処理テーブル
static DrawGUI Draw[DefineSceneMax] = {
	DrawGUIonLogoScene,
	DrawGUIonTitleScene,
	DrawGUIonBattleScene,
	NULL,
	NULL
};

/**************************************
初期化処理
***************************************/
void InitGUIManager(int num)
{
	static bool initialized = false;
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	if (!initialized)
	{
		for (int i = 0; i < GUI_NUMTEX_MAX; i++)
		{
			texture[i] = CreateTextureFromFile((LPSTR)texturePath[i], pDevice);
		}
		initialized = true;
	}

	InitScoreGUI(num);
	InitHpGUI(num);
	InitLockonGUI(num);
	InitPowerUpTelop(num);
	InitBonusTelop(num);
	InitBonusTimeGUI(num);
	InitSceneFade(num);
	InitLockonLevelGUI(num);
	InitLockonNumGUI(num);
}

/**************************************
終了処理
***************************************/
void UninitGUIManager(int num)
{
	if (num == 0)
	{
		for (int i = 0; i < GUI_NUMTEX_MAX; i++)
		{
			SAFE_RELEASE(texture[i]);
		}
	}

	UninitScoreGUI(num);
	UninitHpGUI(num);
	UninitLockonGUI(num);
	UninitPowerUpTelop(num);
	UninitBonusTelop(num);
	UninitBonusTimeGUI(num);
	UninitSceneFade(num);
	UninitLockonLevelGUI(num);
	UninitLockonNumGUI(num);
}

/**************************************
更新処理
***************************************/
void UpdateGUIManager(void)
{
	UpdateScoreGUI();
	UpdateHpGUI();
	UpdateLockonGUI();
	UpdatePowerUpTelop();
	UpdateBonusTelop();
	UpdateBonusTimeGUI();
	UpdateSceneFade();
	UpdateLockonLevelGUI();
	UpdateLockonNumGUI();
}

/**************************************
描画処理
***************************************/
void DrawGUIManager(void)
{
	int scene = GetCurrentScene();
	if (Draw[scene] != NULL)
	{
		Draw[scene]();
	}

	DrawSceneFade();
}

/**************************************
ロゴシーンGUI描画処理
***************************************/
void DrawGUIonLogoScene(void)
{
	DrawCircleLogo();
}

/**************************************
タイトルシーンGUI描画処理
***************************************/
void DrawGUIonTitleScene(void)
{
	DrawTitleLogo();
}

/**************************************
バトルシーンGUI描画処理
***************************************/
void DrawGUIonBattleScene(void)
{
	DrawScoreGUI();
	DrawHpGUI();
	DrawLockonGUI();
	DrawPowerUpTelop();
	DrawBonusTelop();
	DrawBonusTimeGUI();
	DrawLockonLevelGUI();
	DrawLockonNumGUI();
}

/**************************************
数字描画処理
***************************************/
void DrawGUINum(GUI_NUMTEXTURE textureID, int num, VERTEX_2D *vtxWk)
{
	int x = num % GUI_NUMTEX_DIVIDE_X;
	int y = num / GUI_NUMTEX_DIVIDE_X;
	float sizeX = 1.0f / GUI_NUMTEX_DIVIDE_X;
	float sizeY = 1.0f / GUI_NUMTEX_DIVIDE_Y;

	vtxWk[0].tex = D3DXVECTOR2(x * sizeX, y * sizeY);
	vtxWk[1].tex = D3DXVECTOR2((x + 1) * sizeX, y * sizeY);
	vtxWk[2].tex = D3DXVECTOR2(x * sizeX, (y + 1) * sizeY);
	vtxWk[3].tex = D3DXVECTOR2((x + 1) * sizeX, (y + 1) * sizeY);

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	pDevice->SetFVF(FVF_VERTEX_2D);
	pDevice->SetTexture(0, texture[textureID]);
	
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, vtxWk, sizeof(VERTEX_2D));
}