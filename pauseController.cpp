//=====================================
//
//�e���v���[�g����[pauseController.cpp]
//Author:GP11A341 21 ���ԗY��
//
//=====================================
#include "pauseController.h"
#include "baseGUI.h"
#include "input.h"

/**************************************
�}�N����`
***************************************/
#define PAUSEMENU_TEXTURE_NAME		"data/TEXTURE/UI/pauseMenu.png"

/**************************************
�\���̒�`
***************************************/

/**************************************
�O���[�o���ϐ�
***************************************/
static bool flgPause;
static BaseGUI *back;

/**************************************
�v���g�^�C�v�錾
***************************************/

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

	flgPause = false;
	
}

/**************************************
�I������
***************************************/
void UninitPauseController(int num)
{

}

/**************************************
�X�V����
***************************************/
void UpdatePauseController(void)
{
	if (GetKeyboardTrigger(DIK_Q))
	{
		flgPause = !flgPause;
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
}

/**************************************
�|�[�Y��Ԏ擾����
***************************************/
bool GetPauseState(void)
{
	return flgPause;
}