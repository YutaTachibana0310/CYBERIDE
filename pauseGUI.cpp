//=====================================
//
//�|�[�YGUI����[pauseGUI.cpp]
//Author:GP11A341 21 ���ԗY��
//
//=====================================
#include "pauseGUI.h"
#include "baseGUI.h"

/**************************************
�}�N����`
***************************************/
#define PAUSEGUI_TEXTURE_NAME			"data/TEXTURE/UI/pausemenu.png"
#define PAUSEGUI_TEX_SIZE_X				(210.0f)
#define PAUSEGUI_TEX_SIZE_Y				(70.0f)
#define PAUSEGUI_DIV_X					(5)
#define PAUSEGUI_DIV_Y					(2)

#define PAUSEGUI_BASEPOS				(D3DXVECTOR3(400.0f, 80.0f, 0.0f))
#define PAUSEGUI_OFFSET_X				(150.0f)
#define PAUSEGUI_OFFSET_Y				(120.0f)

#define PAUSEGUI_STATETEX_NAME			"data/TEXTURE/UI/menuonoff.png"
#define PAUSEGUI_STATETEX_SIZE_X		(60.0f)
#define PAUSEGUI_STATETEX_SIZE_Y		(40.0f)
#define PAUSEGUI_STATETEX_OFFSET		(260.0f)
#define PAUSEGUI_STATETEX_DIV_X			(1)
#define PAUSEGUI_STATETEX_DIV_Y			(2)

/**************************************
�\���̒�`
***************************************/

/**************************************
�O���[�o���ϐ�
***************************************/
static BaseGUI *menu;
static BaseGUI *onoff;

/**************************************
�v���g�^�C�v�錾
***************************************/

/**************************************
����������
***************************************/
void InitPauseGUI(int num)
{
	static bool initialized = false;

	if (!initialized)
	{
		menu = new BaseGUI((LPSTR)PAUSEGUI_TEXTURE_NAME, PAUSEGUI_TEX_SIZE_X, PAUSEGUI_TEX_SIZE_Y);
		onoff = new BaseGUI((LPSTR)PAUSEGUI_STATETEX_NAME, PAUSEGUI_STATETEX_SIZE_X, PAUSEGUI_STATETEX_SIZE_Y);
		initialized = false;
	}
}

/**************************************
�I������
***************************************/
void UninitPauseGUI(int num)
{
	if (num == 0)
	{
		delete menu;
		delete onoff;
	}
}

/**************************************
�X�V����
***************************************/
void UpdatePauseGUI(void)
{

}

/**************************************
�`�揈��
***************************************/
void DrawPauseGUI(int index, bool selected)
{
	D3DXVECTOR3 pos = PAUSEGUI_BASEPOS + D3DXVECTOR3(index * PAUSEGUI_OFFSET_X, index * PAUSEGUI_OFFSET_Y, 0.0f);
	menu->SetVertex(pos);

	D3DXCOLOR color = selected ? D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f) : D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
	menu->SetColor(color);

	menu->SetTexture(PAUSEGUI_DIV_X, PAUSEGUI_DIV_Y, index);

	menu->Draw();
}

/**************************************
ON/OFF�\������
***************************************/
void DrawPauseMenuState(int index, bool selected, bool state)
{
	D3DXVECTOR3 pos = PAUSEGUI_BASEPOS + D3DXVECTOR3(index * PAUSEGUI_OFFSET_X, index * PAUSEGUI_OFFSET_Y, 0.0f);
	pos.x += PAUSEGUI_STATETEX_OFFSET;
	onoff->SetVertex(pos);

	D3DXCOLOR color = selected ? D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f) : D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
	onoff->SetColor(color);

	int pattern = state ? 0 : 1;
	onoff->SetTexture(PAUSEGUI_STATETEX_DIV_X, PAUSEGUI_STATETEX_DIV_Y, pattern);

	onoff->Draw();
}