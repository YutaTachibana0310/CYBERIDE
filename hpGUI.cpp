//=====================================
//
//HPGUI����[hpGUI.cpp]
//Author:GP11A341 21 ���ԗY��
//
//=====================================
#include "hpGUI.h"

/**************************************
�}�N����`
***************************************/
#define HPGUI_TEXTURE_NAME				_T("data/TEXTURE/UI/hpGUI.png")
#define HPGUI_TEXTURE_SIZE_X			(400.0f)
#define HPGUI_TEXTURE_SIZE_Y			(200.0f)
#define HPGUI_TEXTURE_INITPOS			(D3DXVECTOR3(SCREEN_WIDTH - HPGUI_TEXTURE_SIZE_X, -10.0f, 0.0f))

#define HPGUI_NUMTEX_NAME				_T("data/TEXTURE/UI/scoreNum.png")
#define HPGUI_NUMTEX_SIZE_X				(40.0f)
#define HPGUI_NUMTEX_SIZE_Y				(40.0f)
#define HPGUI_NUMTEX_DIVIDE_X			(5)
#define HPGUI_NUMTEX_DIVIDE_Y			(2)
#define HPGUI_NUMTEX_OFFSET				(-50.0f)
#define HPGUI_NUMTEX_INITPOS			(D3DXVECTOR3(SCREEN_WIDTH - 150.0f, 120.0f, 0.0f))

/**************************************
�\���̒�`
***************************************/

/**************************************
�O���[�o���ϐ�
***************************************/
static LPDIRECT3DTEXTURE9 texture = NULL;
static LPDIRECT3DTEXTURE9 numTex = NULL;
static VERTEX_2D vtxWk[NUM_VERTEX];
static HPGUI hpGUI;

/**************************************
�v���g�^�C�v�錾
***************************************/
HRESULT MakeVertexHPGUI(void);
void SetVertexHPGUI(void);
void SetVertexHPNum(float offset);
void SetTextureHPNum(int num);

/**************************************
����������
***************************************/
void InitHpGUI(int num)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	HPGUI *ptr = &hpGUI;

	ptr->angle = atan2f(HPGUI_NUMTEX_SIZE_Y, HPGUI_NUMTEX_SIZE_X);
	ptr->radius = D3DXVec2Length(&(D3DXVECTOR2(HPGUI_NUMTEX_SIZE_X, HPGUI_NUMTEX_SIZE_Y)));

	MakeVertexHPGUI();

	if (num == 0)
	{
		texture = CreateTextureFromFile((LPSTR)HPGUI_TEXTURE_NAME, pDevice);
		numTex = CreateTextureFromFile((LPSTR)HPGUI_NUMTEX_NAME, pDevice);
	}
}

/**************************************
�I������
***************************************/
void UninitHpGUI(int num)
{
	if (num == 0)
	{
		SAFE_RELEASE(texture);
		SAFE_RELEASE(numTex);
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
void DrawHpGUI(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	pDevice->SetFVF(FVF_VERTEX_2D);

	//GUI�w�i��`��
	pDevice->SetTexture(0, texture);
	SetVertexHPGUI();
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, vtxWk, sizeof(VERTEX_2D));

	//������`��
	pDevice->SetTexture(0, numTex);
	int hp = 100;
	int digitMax = (hp == 0) ? 1 : (int)log10f((float)hp) + 1;
	int num = 0;
	for (int i = 0; i < digitMax; i++, hp /= 10)
	{
		num = hp % 10;

		SetVertexHPNum(i * HPGUI_NUMTEX_OFFSET);
		SetTextureHPNum(num);
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, vtxWk, sizeof(VERTEX_2D));
	}
}

/**************************************
���_�쐬����
***************************************/
HRESULT MakeVertexHPGUI(void)
{
	vtxWk[0].rhw =
		vtxWk[1].rhw =
		vtxWk[2].rhw =
		vtxWk[3].rhw = 1.0f;

	vtxWk[0].diffuse = 
		vtxWk[1].diffuse =
		vtxWk[2].diffuse =
		vtxWk[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	return S_OK;
}

/**************************************
���_�ݒ菈��
***************************************/
void SetVertexHPGUI(void)
{
	vtxWk[0].vtx = HPGUI_TEXTURE_INITPOS;
	vtxWk[1].vtx = HPGUI_TEXTURE_INITPOS + D3DXVECTOR3(HPGUI_TEXTURE_SIZE_X, 0.0f, 0.0f);
	vtxWk[2].vtx = HPGUI_TEXTURE_INITPOS + D3DXVECTOR3(0.0f, HPGUI_TEXTURE_SIZE_Y, 0.0f);
	vtxWk[3].vtx = HPGUI_TEXTURE_INITPOS + D3DXVECTOR3(HPGUI_TEXTURE_SIZE_X, HPGUI_TEXTURE_SIZE_Y, 0.0f);

	vtxWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	vtxWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	vtxWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	vtxWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);
}

/**************************************
HP�������_�ݒ菈��
***************************************/
void SetVertexHPNum(float offset)
{
	D3DXVECTOR3 pos = HPGUI_NUMTEX_INITPOS;
	pos.x += offset;

	HPGUI *ptr = &hpGUI;
	vtxWk[0].vtx.x = pos.x - cosf(ptr->angle) * ptr->radius;
	vtxWk[0].vtx.y = pos.y - sinf(ptr->angle) * ptr->radius;
	vtxWk[1].vtx.x = pos.x + cosf(ptr->angle) * ptr->radius;
	vtxWk[1].vtx.y = pos.y - sinf(ptr->angle) * ptr->radius;
	vtxWk[2].vtx.x = pos.x - cosf(ptr->angle) * ptr->radius;
	vtxWk[2].vtx.y = pos.y + sinf(ptr->angle) * ptr->radius;
	vtxWk[3].vtx.x = pos.x + cosf(ptr->angle) * ptr->radius;
	vtxWk[3].vtx.y = pos.y + sinf(ptr->angle) * ptr->radius;
}

/**************************************
HP�����e�N�X�`���ݒ菈��
***************************************/
void SetTextureHPNum(int num)
{
	int x = num % HPGUI_NUMTEX_DIVIDE_X;
	int y = num / HPGUI_NUMTEX_DIVIDE_X;
	float sizeX = 1.0f / HPGUI_NUMTEX_DIVIDE_X;
	float sizeY = 1.0f / HPGUI_NUMTEX_DIVIDE_Y;

	vtxWk[0].tex = D3DXVECTOR2(x * sizeX, y * sizeY);
	vtxWk[1].tex = D3DXVECTOR2((x + 1) * sizeX, y * sizeY);
	vtxWk[2].tex = D3DXVECTOR2(x * sizeX, (y + 1) * sizeY);
	vtxWk[3].tex = D3DXVECTOR2((x + 1) * sizeX, (y + 1) * sizeY);
}