//=====================================
//
//�|�[�Y�R���g���[���[����[pauseController.cpp]
//Author:GP11A341 21 ���ԗY��
//
//=====================================
#include "pauseController.h"
#include "baseGUI.h"
#include "input.h"
#include "bgmManager.h"
#include "sceneFade.h"
#include "pauseGUI.h"
#include "debugWindow.h"
#include "debugWindow.h"
#include "battleController.h"
#include "collisionManager.h"
#include "soundEffectManager.h"
#include "shockBlur.h"
#include "spikeNoise.h"

/**************************************
�}�N����`
***************************************/
#define PAUSEMENU_TEXTURE_NAME		"data/TEXTURE/UI/pausebg.png"
#define PAUSEMENU_ANIMTIME			(5)
#define PAUSEMENU_ANIMPATTERN		(6)
#define PAUSEMENU_TEX_DIV_X			(3)
#define PAUSEMENU_TEX_DIV_Y			(2)
#define PAUSEMENU_MENUMAX			(10)

/**************************************
�\���̒�`
***************************************/
typedef void(*funcPause)(void);

enum class DefinePauseMenu {
	Resume,
	Restart,
	ReturnTitle,
	SwitchDebugWindow,
	SwitchUseDivSpace,
	SwitchFPSView,
	SwitchSideView,
	SwitchTopView,
	SetShockBlur,
	SetSpikeNoise
};
/**************************************
�v���g�^�C�v�錾
***************************************/
void PauseFuncResume(void);
void PauseFuncRestart(void);
void PauseFuncReturnTitle(void);
void PuaseFuncSwitchDebugWindow(void);
void PauseFuncSwitchUseDivisionSpace(void);
void PauseFuncSwitchFPSView(void);
void PauseFuncSwitchTopView(void);
void PauseFuncSwitchSideView(void);
void PauseFuncSetShockBlur(void);
void PauseFuncSpikeNoise(void);
bool IsSetStateMenu(int index, bool *pState);

/**************************************
�O���[�o���ϐ�
***************************************/
static bool flgPause;
static BaseGUI *back;

static int menuIndex;
static int cntFrame;

static bool useDivSpace = true;;
static bool drawDebug = false;


//�|�[�Y���j���[�����e�[�u��
static funcPause menuTable[PAUSEMENU_MENUMAX] = {
	PauseFuncResume,
	PauseFuncRestart,
	PauseFuncReturnTitle,
	PuaseFuncSwitchDebugWindow,
	PauseFuncSwitchUseDivisionSpace,
	PauseFuncSwitchFPSView,
	PauseFuncSwitchSideView,
	PauseFuncSwitchTopView,
	PauseFuncSetShockBlur,
	PauseFuncSpikeNoise

};

/**************************************
����������
***************************************/
void InitPauseController(int num)
{
	static bool initialized = false;

	if (!initialized)
	{
		back = new BaseGUI((LPSTR)PAUSEMENU_TEXTURE_NAME, SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f);
		back->SetVertex(D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_CENTER_Y, 0.0f));
		initialized = true;
	}

	InitPauseGUI(num);

	flgPause = false;

}

/**************************************
�I������
***************************************/
void UninitPauseController(int num)
{
	if (num == 0)
	{
		delete back;

	}

	UninitPauseGUI(num);
}

/**************************************
�X�V����
***************************************/
void UpdatePauseController(void)
{
	//�o�g���V�[���ȊO�̓|�[�Y���j���[���J���Ȃ�
	//if (GetCurrentScene() != BattleScene)
	//	return;

	//�|�[�Y�{�^�����͔���
	if (GetPauseButtonTrigger())
	{
		PlaySE(DefineSE::PAUSE);
		flgPause = !flgPause;
	}

	//�|�[�Y��ԂłȂ���Έȉ��͎��s���Ȃ�
	if (!flgPause)
		return;

	//�J�[�\���Z�b�g
	int inputY = GetVerticalInputRepeat();
	menuIndex = WrapAround(0, PAUSEMENU_MENUMAX, menuIndex - inputY);

	if (inputY != 0)
		PlaySE(DefineSE::CURSOR);

	//�I�����ꂽ���������s
	if (GetAttackButtonTrigger())
	{
		PlaySE(DefineSE::MENUDICISION);
		menuTable[menuIndex]();
	}
}

/**************************************
�`�揈��
***************************************/
void DrawPauseController(void)
{
	if (!flgPause)
		return;

	back->Draw();

	for (int i = 0; i < PAUSEMENU_MENUMAX; i++)
	{
		DrawPauseGUI(i, i == menuIndex);

		bool state;
		if (IsSetStateMenu(i, &state))
			DrawPauseMenuState(i, i == menuIndex, state);
	}
}

/**************************************
�|�[�Y��Ԏ擾����
***************************************/
bool GetPauseState(void)
{
	return flgPause;
}

/**************************************
�|�[�Y��������
***************************************/
void PauseFuncResume(void)
{
	flgPause = false;
}

/**************************************
�Q�[�����X�^�[�g����
***************************************/
void PauseFuncRestart(void)
{
	SetSceneFade(BattleScene);
	flgPause = false;
}

/**************************************
�^�C�g�����^�[������
***************************************/
void PauseFuncReturnTitle(void)
{
	SetSceneFade(TitleScene);
	flgPause = false;
}

/**************************************
�f�o�b�O�E�B���h�EONOFF����
***************************************/
void PuaseFuncSwitchDebugWindow(void)
{
	drawDebug = !drawDebug;
	SetActiveDebugWindow(drawDebug);
}

/**************************************
��ԕ����ؑ֏���
***************************************/
void PauseFuncSwitchUseDivisionSpace(void)
{
	useDivSpace = !useDivSpace;
	SetUseDivisionSpace(useDivSpace);
}

/**************************************
FPS�r���[�ɐؑ�
***************************************/
void PauseFuncSwitchFPSView(void)
{
	ChangeViewModeBattleController(BattleViewFPS);
	flgPause = false;
}

/**************************************
�g�b�v�r���[�ɐ؂�ւ�
***************************************/
void PauseFuncSwitchTopView(void)
{
	ChangeViewModeBattleController(BattleViewTop);
	flgPause = false;
}

/**************************************
�T�C�h�r���[�ɐ؂�ւ�
***************************************/
void PauseFuncSwitchSideView(void)
{
	ChangeViewModeBattleController(BattleViewSide);
	flgPause = false;
}

/**************************************
�����u���[�\��
***************************************/
void PauseFuncSetShockBlur(void)
{
	SetShockBlur(D3DXVECTOR3(RandomRangef(-200.0f, 200.0f), RandomRangef(-100.0f, 100.0f), 500.0f), 50.0f);
	//flgPause = false;
}

/**************************************
�X�p�C�N�m�C�Y�\��
***************************************/
void PauseFuncSpikeNoise(void)
{
	SetSpikeNoise();
	//flgPause = false;
}

/**************************************
�X�e�[�g�ݒ�ł��郁�j���[���ǂ���
***************************************/
bool IsSetStateMenu(int index, bool *pState)
{
	if (index == static_cast<int>(DefinePauseMenu::SwitchDebugWindow))
	{
		*pState = drawDebug;
		return true;
	}

	if (index == static_cast<int>(DefinePauseMenu::SwitchUseDivSpace))
	{
		*pState = useDivSpace;
		return true;
	}

	return false;
}