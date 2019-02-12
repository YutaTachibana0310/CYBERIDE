//=====================================
//
//�^�C�g���e���b�v����[titleTelop.cpp]
//Author:GP11A341 21 ���ԗY��
//
//=====================================
#include "titleTelop.h"
#include "baseGUI.h"
#include "input.h"

/**************************************
�}�N����`
***************************************/
#define TITLETELOP_TEXTURE_NAME			"data/TEXTURE/UI/titlemenu.png"
#define TITLETELOP_TEXTURE_SIZE_X		(450.0f)
#define TITLETELOP_TEXTYRE_SIZE_Y		(90.0f)
#define TITLETELOP_BASEPOS				(D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_HEIGHT - 300.0f, 0.0f))
#define TITLETELOP_FADE_DURATION		(50)
#define TITLETELOP_TEX_DIV_X			(1)
#define TITLETELOP_TEX_DIV_Y			(2)

/**************************************
�\���̒�`
***************************************/

/**************************************
�O���[�o���ϐ�
***************************************/
static bool isFadeIn;
static int cntFrame;
static BaseGUI *menu;
static int menuIndex;

/**************************************
�v���g�^�C�v�錾
***************************************/

/**************************************
����������
***************************************/
void InitTitleTelop(int num)
{
	static bool initialized = false;

	if (!initialized)
	{
		LPDIRECT3DDEVICE9 pDevice = GetDevice();
		menu = new BaseGUI((LPSTR)TITLETELOP_TEXTURE_NAME, TITLETELOP_TEXTURE_SIZE_X, TITLETELOP_TEXTYRE_SIZE_Y);
		initialized = true;
	}

	cntFrame = 0;
	menuIndex = 0;
	isFadeIn = true;
}

/**************************************
�I������
***************************************/
void UninitTitleTelop(int num)
{
	if (num == 0)
	{
		delete menu;
	}
}

/**************************************
�X�V����
***************************************/
void UpdateTitleTelop(void)
{
	int addValue = isFadeIn ? 1 : -1;
	cntFrame += addValue;

	if (cntFrame == 0 || cntFrame == TITLETELOP_FADE_DURATION)
	{
		isFadeIn = !isFadeIn;
	}

	int inputX = GetHorizontalInputRepeat();
	menuIndex = WrapAround(0, TITLETELOP_TEX_DIV_Y, menuIndex + inputX);
}

/**************************************
�`�揈��
***************************************/
void DrawTitleTelop(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	menu->SetAlpha((float)cntFrame / (float)TITLETELOP_FADE_DURATION);
	menu->SetTexture(TITLETELOP_TEX_DIV_X, TITLETELOP_TEX_DIV_Y, menuIndex);
	menu->SetVertex(TITLETELOP_BASEPOS);

	menu->Draw();
}

/**************************************
���j���[�C���f�b�N�X�擾����
***************************************/
int GetTitleMenuIndex(void)
{
	return menuIndex;
}