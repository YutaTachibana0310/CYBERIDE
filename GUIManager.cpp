//=====================================
//
//GUI�}�l�[�W������[GUIManager.cpp]
//Author:GP11A341 21 ���ԗY��
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
#include "gameoverTelop.h"
#include "stageClearTelop.h"
#include "nameEntryRanking.h"
#include "rankingScore.h"
#include "rankingName.h"
#include "nameEntryCursor.h"
#include "rankingTelop.h"
#include "tutorialController.h"
#include "titleTelop.h"
#include "entryTelop.h"
#include "bonusPositinoTelop.h"

#include "logoScene.h"
#include "titleScene.h"
#include "sceneFade.h"
#include <stdio.h>
#include "debugWindow.h"

/**************************************
�}�N����`
***************************************/
#define GUI_NUMTEX_DIVIDE_X				(5)
#define GUI_NUMTEX_DIVIDE_Y				(2)
#define GUI_NUMTEX_PATTERN_MAX			(10)

/**************************************
�\���̒�`
***************************************/
typedef void(*DrawGUI)(void);

/**************************************
�v���g�^�C�v�錾
***************************************/
void DrawGUIonBattleScene(void);
void DrawGUIonLogoScene(void);
void DrawGUIonTitleScene(void);
void LoadSettingsGUI(void);
void DrawGUIonGameoverScene(void);
void DrawGUIonStageClearScene(void);
void DrawGUIonNameEntryScene(void);
void DrawGUIonTutorialScene(void);

/**************************************
�O���[�o���ϐ�
***************************************/
static LPDIRECT3DTEXTURE9 texture[GUI_NUMTEX_MAX];
static const char* texturePath[GUI_NUMTEX_MAX] =
{
	"data/TEXTURE/UI/scoreNum.png",
	"data/TEXTURE/UI/lockonNum.png",
	"data/TEXTURE/UI/timeNum.png",
	"data/TEXTURE/UI/rankingNum.png"
};

//�e�V�[����GUI�`�揈���e�[�u��
static DrawGUI Draw[DefineSceneMax] = {
	DrawGUIonLogoScene,
	DrawGUIonTitleScene,
	DrawGUIonBattleScene,
	NULL,
	DrawGUIonTutorialScene,
	DrawGUIonGameoverScene,
	DrawGUIonStageClearScene,
	DrawGUIonNameEntryScene
};

/**************************************
����������
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
	InitGameoverTelop(num);
	InitStageClearTelop(num);
	InitNameEntryRanking(num);
	InitRankingScore(num);
	InitRankingName(num);
	InitNameEntryCursor(num);
	InitRankingTelop(num);
	InitTitleTelop(num);
	InitEntryTelop(num);
	InitBonusPositionTelop(num);

	//LoadSettingsGUI();
}

/**************************************
�I������
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
	UninitGameoverTelop(num);
	UninitStageClearTelop(num);
	UninitNameEntryRanking(num);
	UninitRankingScore(num);
	UninitRankingName(num);
	UninitNameEntryCursor(num);
	UninitRankingTelop(num);
	UninitTitleTelop(num);
	UninitEntryTelop(num);
	UninitBonusPositionTelop(num);
}

/**************************************
�X�V����
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
	UpdateGameoverTelop();
	UpdateStageClearTelop();
	UpdateNameEntryRanking();
	UpdateRankingScore();
	UpdateRankingName();
	UpdateNameEntryCursor();
	UpdateRankingTelop();
	UpdateTitleTelop();
	UpdateEntryTelop();
	UpdateBonusPositionTelop();
}

/**************************************
�`�揈��
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
���S�V�[��GUI�`�揈��
***************************************/
void DrawGUIonLogoScene(void)
{
	DrawCircleLogo();
}

/**************************************
�^�C�g���V�[��GUI�`�揈��
***************************************/
void DrawGUIonTitleScene(void)
{
	DrawTitleLogo();
	DrawTitleTelop();
}

/**************************************
�`���[�g���A���V�[���`�揈��
***************************************/
void DrawGUIonTutorialScene(void)
{
	DrawLockonGUI();
	DrawTutorialController();
}

/**************************************
�o�g���V�[��GUI�`�揈��
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
	DrawBonusPositionTelop();

#ifdef _DEBUG
	DrawLockNumlevelGUIDebug();
	DrawLockOnlevelGUIDebug();
	DrawHPGUIDebug();
	DrawScoreGUIDebug();

	if (DebugButton("Save"))
	{
		FILE *fp = NULL;
		fp = fopen("data/SETTINGS/gui.ini", "wb");

		if (fp == NULL)
			return;

		SaveSettingLockonNumGUI(fp);
		SaveSettingLockonLevelGUI(fp);
		SaveSettinghpGUIGUI(fp);
		SaveSettingScoreGUI(fp);

		fclose(fp);
	}
#endif
}

/**************************************
�Q�[���I�[�o�[�V�[���`�揈��
***************************************/
void DrawGUIonGameoverScene(void)
{
	DrawGameoverTelop();
}

/**************************************
�X�e�[�W�N���A�V�[���`�揈��
***************************************/
void DrawGUIonStageClearScene(void)
{
	DrawStageClearTelop();
}

/**************************************
�l�[���G���g���[�V�[���`�揈��
***************************************/
void DrawGUIonNameEntryScene(void)
{
	DrawNameEntryRanking();
	DrawRankingScore();
	DrawRankingName();
	DrawNameEntryCursor();
	DrawRankingTelop();
	DrawEntryTelop();
}

/**************************************
�����`�揈��
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

/**************************************
�ݒ�ǂݍ��ݏ���
**************************************/
void LoadSettingsGUI(void)
{
	FILE *fp = NULL;
	fp = fopen("data/SETTINGS/gui.ini", "rb");

	if (fp == NULL)
		return;

	LoadSettingsLockonNumGUI(fp);
	LoadSettingsLockonLevelGUI(fp);
	LoadSettingshpGUIGUI(fp);
	LoadSettingsScoreGUI(fp);

	fclose(fp);
}