//=====================================
//
//���b�N�I����GUI����[lockonNumGUI.cpp]
//Author:GP11A341 21 ���ԗY��
//
//=====================================
#include "lockonNumGUI.h"
#include "GUIManager.h"
#include "dataContainer.h"
#include "playerModel.h"

/**************************************
�}�N����`
***************************************/
#define LOCKONNUMGUI_TEX_NAME				"data/TEXTURE/UI/lockonGUI.png"
#define LOCKONNUMGUI_TEX_SIZE_X				(400.0f)
#define LOCKONNUMGUI_TEX_SIZE_Y				(200.0f)
#define LOCKONNUMGUI_TEX_INITPOS			(D3DXVECTOR3(SCREEN_WIDTH - LOCKONNUMGUI_TEX_SIZE_X, 430.0f, 0.0f))

#define LOCKONNUMGUI_NUMTEX_SIZE_X			(80.0f)
#define LOCKONNUMGUI_NUMTEX_SIZE_Y			(80.0f)
#define LOCKONNUMGUI_NUMTEX_DIVIDE_X		(5)
#define LOCKONNUMGUI_NUMTEX_DIVIDE_Y		(2)
#define LOCKONNUMGUI_NUMTEX_OFFSET			(-50.0f)
#define LOCKONNUMGUI_NUMTEX_INITPOS			(D3DXVECTOR3(SCREEN_WIDTH - 250.0f, 525.0f, 0.0f))

#define LOCKONUMGUI_MAXTEX_INITPOS			(D3DXVECTOR3(SCREEN_WIDTH - 90.0f, 525.0f, 0.0f))

/**************************************
�\���̒�`
***************************************/

/**************************************
�O���[�o���ϐ�
***************************************/
static LPDIRECT3DTEXTURE9 texture;
static VERTEX_2D vtxWk[NUM_VERTEX];

/**************************************
�v���g�^�C�v�錾
***************************************/
void MakeVertexLockonNumGUI(void);
void SetVertexLockonNumGUI(void);
void SetTextureLockonNumGUI(void);
void SetVertexLockonNumNUM(float offsetX, bool isMaxNum);

/**************************************
����������
***************************************/
void InitLockonNumGUI(int num)
{
	static bool initialized = false;

	if (initialized)
		return;

	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	texture = CreateTextureFromFile((LPSTR)LOCKONNUMGUI_TEX_NAME, pDevice);
	MakeVertexLockonNumGUI();
}

/**************************************
�I������
***************************************/
void UninitLockonNumGUI(int num)
{
	if (num == 0)
	{
		SAFE_RELEASE(texture);
	}
}

/**************************************
�X�V����
***************************************/
void UpdateLockonNumGUI(void)
{

}

/**************************************
�`�揈��
***************************************/
void DrawLockonNumGUI(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	pDevice->SetFVF(FVF_VERTEX_2D);

	//GUI�w�i��`��
	pDevice->SetTexture(0, texture);
	SetVertexLockonNumGUI();
	SetTextureLockonNumGUI();
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, vtxWk, sizeof(VERTEX_2D));

	//���b�N�I������`��
	{
		int lockNum = GetPlayerAdr(0)->lockonNum;
		int digitMax = (lockNum == 0) ? 1 : (int)log10f((float)lockNum) + 1;
		for (int i = 0; i < digitMax; i++, lockNum /= 10)
		{
			int num = lockNum % 10;
			SetVertexLockonNumNUM(i * LOCKONNUMGUI_NUMTEX_OFFSET, false);
			DrawGUINum(GUI_NUMSCORE, num, vtxWk);
		}
	}

	//�ő働�b�N�I������`��
	{
		int lockNum = GetLockonMax();
		int digitMax = (lockNum == 0) ? 1 : (int)log10f((float)lockNum) + 1;
		for (int i = 0; i < digitMax; i++, lockNum /= 10)
		{
			int num = lockNum % 10;
			SetVertexLockonNumNUM(i * LOCKONNUMGUI_NUMTEX_OFFSET, true);
			DrawGUINum(GUI_NUMSCORE, num, vtxWk);
		}
	}
}

/**************************************
���_�쐬����
***************************************/
void MakeVertexLockonNumGUI(void)
{
	vtxWk[0].rhw =
		vtxWk[1].rhw =
		vtxWk[2].rhw =
		vtxWk[3].rhw = 1.0f;

	vtxWk[0].diffuse =
		vtxWk[1].diffuse =
		vtxWk[2].diffuse =
		vtxWk[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
}

/**************************************
�`�揈��
***************************************/
void SetVertexLockonNumGUI(void)
{
	vtxWk[0].vtx = LOCKONNUMGUI_TEX_INITPOS;
	vtxWk[1].vtx = LOCKONNUMGUI_TEX_INITPOS + D3DXVECTOR3(LOCKONNUMGUI_TEX_SIZE_X, 0.0f, 0.0f);
	vtxWk[2].vtx = LOCKONNUMGUI_TEX_INITPOS + D3DXVECTOR3(0.0f, LOCKONNUMGUI_TEX_SIZE_Y, 0.0f);
	vtxWk[3].vtx = LOCKONNUMGUI_TEX_INITPOS + D3DXVECTOR3(LOCKONNUMGUI_TEX_SIZE_X, LOCKONNUMGUI_TEX_SIZE_Y, 0.0f);
}

/**************************************
�`�揈��
***************************************/
void SetTextureLockonNumGUI(void)
{
	vtxWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	vtxWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	vtxWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	vtxWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);
}

/**************************************
�`�揈��
***************************************/
void SetVertexLockonNumNUM(float offsetX, bool isMaxNum)
{
	D3DXVECTOR3 basePos = (isMaxNum) ? LOCKONUMGUI_MAXTEX_INITPOS : LOCKONNUMGUI_NUMTEX_INITPOS;

	vtxWk[0].vtx = basePos;
	vtxWk[1].vtx = basePos + D3DXVECTOR3(LOCKONNUMGUI_NUMTEX_SIZE_X, 0.0f, 0.0f);
	vtxWk[2].vtx = basePos + D3DXVECTOR3(0.0f, LOCKONNUMGUI_NUMTEX_SIZE_Y, 0.0f);
	vtxWk[3].vtx = basePos + D3DXVECTOR3(LOCKONNUMGUI_NUMTEX_SIZE_X, LOCKONNUMGUI_NUMTEX_SIZE_Y, 0.0f);

	for (int i = 0; i < NUM_VERTEX; i++)
	{
		vtxWk[i].vtx.x += offsetX;
	}
}
