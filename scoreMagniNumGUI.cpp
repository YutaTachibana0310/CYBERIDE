//=====================================
//
//�X�R�A�{����������[scoreMagniNumGUI.cpp]
//Author:GP11A341 21 ���ԗY��
//
//=====================================
#include "scoreMagniNumGUI.h"
#include "baseGUI.h"
#include "dataContainer.h"
#include "GUIManager.h"
#include "numGUI.h"

/**************************************
�}�N����`
***************************************/
#define SCOREMAGNINUM_TEXTURE_NAME		"data/TEXTURE/UI/scoreMagniCross.png"

#define SCOREMAGNINUM_TEXTURE_SIZE_X	(50)
#define SCOREMAGNINUM_TEXTURE_SIZE_Y	(20)
#define SCOREMAGNIGUI_BASEPOS			(D3DXVECTOR3(230.0f, 60.0f, 0.0f))

#define SCOREMAGNIGUI_NUM_BASEPOS		(D3DXVECTOR3(280.0f, 55.0f, 0.0f))
#define SCOREMAGNIGUI_NUM_OFFSET_FLOAT	(-30.0f)
#define SCOREMAGNIGUI_NUM_OFFSET_INT	(-25.0f)
#define SCOREMAGNIGUI_NUM_SIZE_X		(20.0f)
#define SCOREMAGNIGUI_NUM_SIZE_Y		(20.0f)

/**************************************
�\���̒�`
***************************************/

/**************************************
�O���[�o���ϐ�
***************************************/
static BaseGUI *gui;
static int cntFrame;

/**************************************
�v���g�^�C�v�錾
***************************************/

/**************************************
����������
***************************************/
void InitScoreMagniNumGUI(int num)
{
	static bool initialized = false;

	if (!initialized)
	{
		gui = new BaseGUI((LPSTR)SCOREMAGNINUM_TEXTURE_NAME, SCOREMAGNINUM_TEXTURE_SIZE_X, SCOREMAGNINUM_TEXTURE_SIZE_Y);
		gui->SetVertex(SCOREMAGNIGUI_BASEPOS);
	}
}

/**************************************
�I������
***************************************/
void UninitScoreMagniNumGUI(int num)
{
	if (num == 0)
	{
		delete gui;
	}
}

/**************************************
�X�V����
***************************************/
void UpdateScoreMagniNumGUI(void)
{

}

/**************************************
�`�揈��
***************************************/
void DrawScoreMagniNumGUI(float alpha)
{
	//GUI�w�i��`��
	gui->SetAlpha(alpha);
	gui->Draw();

	//GUI������`��
	NumGUI *numGui = NumGUI::GetInstance();
	int magni = (int)(GetScoreMagni() * 10);		//�����_��1�ʂ܂ŕ`�悷��̂�10�{���Ď擾
	int digitMax = (magni == 0) ? 1 : (int)log10f((float)magni) + 1;
	for (int i = 0; i < digitMax; i++, magni /= 10)
	{
		int num = magni % 10;
		float offset = (i == 1) ? SCOREMAGNIGUI_NUM_OFFSET_FLOAT : SCOREMAGNIGUI_NUM_OFFSET_INT;
		D3DXVECTOR3 pos = SCOREMAGNIGUI_NUM_BASEPOS + D3DXVECTOR3(offset * i, 0.0f, 0.0f);
		numGui->SetVertex(pos, SCOREMAGNIGUI_NUM_SIZE_X, SCOREMAGNIGUI_NUM_SIZE_Y);
		numGui->SetTexture(num);
		numGui->Draw(NumScore);
	}
}