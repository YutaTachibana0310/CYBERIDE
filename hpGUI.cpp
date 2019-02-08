//=====================================
//
//HPGUI����[hpGUI.cpp]
//Author:GP11A341 21 ���ԗY��
//
//=====================================
#include "hpGUI.h"
#include "GUIManager.h"
#include "debugWindow.h"
#include "dataContainer.h"
#include "baseGUI.h"
#include "numGUI.h"

/**************************************
�}�N����`
***************************************/
#define HPGUI_TEXTURE_NAME				_T("data/TEXTURE/UI/hpGUI.png")
#define HPGUI_TEXTURE_SIZE_X			(240.0f)
#define HPGUI_TEXTURE_SIZE_Y			(100.0f)
#define HPGUI_TEXTURE_INITPOS			(D3DXVECTOR3(130.0f, 330.0f, 0.0f))

#define HPGUI_NUMTEX_SIZE_X				(40.0f)
#define HPGUI_NUMTEX_SIZE_Y				(40.0f)
#define HPGUI_NUMTEX_OFFSET				(-50.0f)
#define HPGUI_NUMTEX_INITPOS			(D3DXVECTOR3(220.0f, 360.0f, 0.0f))

/**************************************
�\���̒�`
***************************************/

/**************************************
�O���[�o���ϐ�
***************************************/
static BaseGUI *back;

/**************************************
�v���g�^�C�v�錾
***************************************/

/**************************************
����������
***************************************/
void InitHpGUI(int num)
{
	static bool initialized = false;
	if (!initialized)
	{
		back = new BaseGUI((LPSTR)HPGUI_TEXTURE_NAME, HPGUI_TEXTURE_SIZE_X, HPGUI_TEXTURE_SIZE_Y);
		initialized = true;
	}
}

/**************************************
�I������
***************************************/
void UninitHpGUI(int num)
{
	if (num == 0)
	{
		delete back;
	}
}

/**************************************
�X�V����
***************************************/
void UpdateHpGUI(void)
{

}

/**************************************
�`�揈��
***************************************/
void DrawHpGUI(float alpha)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//GUI�w�i��`��
	back->SetVertex(HPGUI_TEXTURE_INITPOS);
	back->SetAlpha(alpha);
	back->Draw();

	//������`��
	NumGUI *numGui = NumGUI::GetInstance();
	int hp = (int)GetPlayerHP();
	int digitMax = (hp == 0) ? 1 : (int)log10f((float)hp) + 1;
	int num = 0;
	for (int i = 0; i < digitMax; i++, hp /= 10)
	{
		num = hp % 10;

		//SetVertexHPNum(i * numOffset);
		//DrawGUINum(GUI_NUMSCORE, num, vtxWk);

		D3DXVECTOR3 pos = D3DXVECTOR3(i * HPGUI_NUMTEX_OFFSET, 0.0f, 0.0f) + HPGUI_NUMTEX_INITPOS;
		numGui->SetVertex(pos, HPGUI_NUMTEX_SIZE_X, HPGUI_NUMTEX_SIZE_Y);
		numGui->SetTexture(num);
		numGui->Draw(NumScore);
	}
}

