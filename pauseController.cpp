//=====================================
//
//�e���v���[�g����[pauseController.cpp]
//Author:GP11A341 21 ���ԗY��
//
//=====================================
#include "pauseController.h"
#include "baseGUI.h"
#include "input.h"
#include "bgmManager.h"
#include "sceneFade.h"

/**************************************
�}�N����`
***************************************/
#define PAUSEMENU_TEXTURE_NAME		"data/TEXTURE/UI/pauseMenu.png"
#define PAUSEMENU_CURSOE_TEX_NAME	"data/TEXTURE/UI/menuCusor.png"
#define PAUSEMENU_CURSOR_SIZE		(50.0f)
#define PAUSEMENU_MAXNUM			(3)
#define PAUSEMENU_ANIMTIME			(5)
#define PAUSEMENU_ANIMPATTERN		(6)
#define PAUSEMENU_TEX_DIV_X			(3)
#define PAUSEMENU_TEX_DIV_Y			(2)

/**************************************
�\���̒�`
***************************************/
typedef void(*funcPause)(void);

/**************************************
�v���g�^�C�v�錾
***************************************/
void PauseFuncResume(void);
void PauseFuncRestart(void);
void PauseFuncReturnTitle(void);

/**************************************
�O���[�o���ϐ�
***************************************/
static bool flgPause;
static BaseGUI *back;
static BaseGUI *cursor;

static const D3DXVECTOR3 cursorPos[PAUSEMENU_MAXNUM] = {
	D3DXVECTOR3(500.0f, 370.0f, 0.0f),		//500, 370, 0
	D3DXVECTOR3(630.0f, 500.0f, 0.0f),		//630, 500, 0
	D3DXVECTOR3(820.0f, 640.0f, 0.0f),		//760, 630, 0
};

static int menuIndex;
static int cntFrame;
static int cursorPattern;
static int animIndex;

//�|�[�Y���j���[�����e�[�u��
static funcPause menuTable[PAUSEMENU_MAXNUM] = {
	PauseFuncResume,
	PauseFuncRestart,
	PauseFuncReturnTitle
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
		cursor = new BaseGUI((LPSTR)PAUSEMENU_CURSOE_TEX_NAME, PAUSEMENU_CURSOR_SIZE, PAUSEMENU_CURSOR_SIZE);
		back->SetVertex(D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_CENTER_Y, 0.0f));
		initialized = true;
	}

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
		delete cursor;
	}
}

/**************************************
�X�V����
***************************************/
void UpdatePauseController(void)
{
	//�o�g���V�[���ȊO�̓|�[�Y���j���[���J���Ȃ�
	if (GetCurrentScene() != BattleScene)
		return;

	//�|�[�Y�{�^�����͔���
	if (GetPauseButtonTrigger())
		flgPause = !flgPause;

	//�|�[�Y��ԂłȂ���Έȉ��͎��s���Ȃ�
	if (!flgPause)
		return;

	//�J�[�\���A�j���[�V����
	cntFrame++;
	if (cntFrame % PAUSEMENU_ANIMTIME == 0)
	{
		animIndex = WrapAround(0, PAUSEMENU_ANIMPATTERN, animIndex + 1);
	}

	//�J�[�\���Z�b�g
	cursor->SetTexture(PAUSEMENU_TEX_DIV_X, PAUSEMENU_TEX_DIV_Y, animIndex);
	cursor->SetVertex(cursorPos[menuIndex]);

	//�J�[�\���ړ�
	int inputY = GetVerticalInputRepeat();
	menuIndex = WrapAround(0, PAUSEMENU_MAXNUM, menuIndex - inputY);
	
	//�I�����ꂽ���������s
	if(GetAttackButtonTrigger())
		menuTable[menuIndex]();
}

/**************************************
�`�揈��
***************************************/
void DrawPauseController(void)
{
	if (!flgPause)
		return;

	back->Draw();
	cursor->Draw();
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