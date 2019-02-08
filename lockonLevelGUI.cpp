//=====================================
//
//���b�N�I�����x��GUI����[lockonLevelGUI.cpp]
//Author:GP11A341 21 ���ԗY��
//
//=====================================
#include "lockonLevelGUI.h"
#include "GUIManager.h"
#include "dataContainer.h"
#include "debugWindow.h"
#include "baseGUI.h"
#include "numGUI.h"

/**************************************
�}�N����`
***************************************/
#define LOCKONLEVELGUI_TEX_NAME					"data/TEXTURE/UI/lockonlevel.png"
#define LOCKONLEVELGUI_TEX_SIZE_X				(200.0f)
#define LOCKONLEVELGUI_TEX_SIZE_Y				(100.0f)
#define LOCKONLEVELGUI_TEX_INITPOS				(D3DXVECTOR3(170.0f, 770.0f, 0.0f))

#define LOCKONLEVELGUI_NUMTEX_SIZE_X			(40.0f)
#define LOCKONLEVELGUI_NUMTEX_SIZE_Y			(40.0f)
#define LOCKONLEVELGUI_NUMTEX_OFFSET			(-50.0f)
#define LOCKONLEVELGUI_NUMTEX_INITPOS			(D3DXVECTOR3(240.0f, 795.0f, 0.0f))

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
void InitLockonLevelGUI(int num)
{
	static bool initialized = false;

	if (initialized)
		return;

	back = new BaseGUI((LPSTR)LOCKONLEVELGUI_TEX_NAME, LOCKONLEVELGUI_TEX_SIZE_X, LOCKONLEVELGUI_TEX_SIZE_Y);
}

/**************************************
�I������
***************************************/
void UninitLockonLevelGUI(int num)
{
	if (num == 0)
	{
		delete back;
	}
}

/**************************************
�X�V����
***************************************/
void UpdateLockonLevelGUI(void)
{

}

/**************************************
�`�揈��
***************************************/
void DrawLockonLevelGUI(void)
{
	//GUI�w�i��`��
	back->SetVertex(LOCKONLEVELGUI_TEX_INITPOS);
	back->Draw();

	//������`��
	NumGUI *numGui = NumGUI::GetInstance();
	numGui->SetVertex(LOCKONLEVELGUI_NUMTEX_INITPOS, LOCKONLEVELGUI_NUMTEX_SIZE_X, LOCKONLEVELGUI_NUMTEX_SIZE_Y);
	numGui->SetTexture(GetLockonLevel() + 1);
	numGui->Draw(NumScore);
}

