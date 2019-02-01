//=====================================
//
//�^�C�g���e���b�v����[titleTelop.cpp]
//Author:GP11A341 21 ���ԗY��
//
//=====================================
#include "titleTelop.h"

/**************************************
�}�N����`
***************************************/
#define TITLETELOP_TEXTURE_NAME			"data/TEXTURE/UI/titleTelop.png"
#define TITLETELOP_TEXTURE_SIZE_X		(600.0f)
#define TITLETELOP_TEXTYRE_SIZE_Y		(60.0f)
#define TITLETELOP_BASEPOS				(D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_HEIGHT - 200.0f, 0.0f))
#define TITLETELOP_FADE_DURATION		(50)

/**************************************
�\���̒�`
***************************************/

/**************************************
�O���[�o���ϐ�
***************************************/
static LPDIRECT3DTEXTURE9 texture;
static VERTEX_2D vtxWk[NUM_VERTEX];
static bool isFadeIn;
static int cntFrame;
/**************************************
�v���g�^�C�v�錾
***************************************/
void MakeVertexTitleTelop(void);
void SetDiffuseTitleTelop(float alpha);

/**************************************
����������
***************************************/
void InitTitleTelop(int num)
{
	static bool initialized = false;

	if (!initialized)
	{
		LPDIRECT3DDEVICE9 pDevice = GetDevice();
		MakeVertexTitleTelop();
		texture = CreateTextureFromFile((LPSTR)TITLETELOP_TEXTURE_NAME, pDevice);
		initialized = true;
	}

	cntFrame = 0;
	isFadeIn = true;
}

/**************************************
�I������
***************************************/
void UninitTitleTelop(int num)
{
	if (num == 0)
	{
		SAFE_RELEASE(texture);
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
}

/**************************************
�`�揈��
***************************************/
void DrawTitleTelop(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	pDevice->SetFVF(FVF_VERTEX_2D);

	pDevice->SetTexture(0, texture);

	SetDiffuseTitleTelop((float)cntFrame / (float)TITLETELOP_FADE_DURATION);

	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, vtxWk, sizeof(VERTEX_2D));
}

/**************************************
���_�쐬����
***************************************/
void MakeVertexTitleTelop(void)
{
	vtxWk[0].rhw =
		vtxWk[1].rhw =
		vtxWk[2].rhw =
		vtxWk[3].rhw = 1.0f;

	vtxWk[0].vtx = TITLETELOP_BASEPOS + D3DXVECTOR3(-TITLETELOP_TEXTURE_SIZE_X, -TITLETELOP_TEXTYRE_SIZE_Y, 0.0f);
	vtxWk[1].vtx = TITLETELOP_BASEPOS + D3DXVECTOR3(TITLETELOP_TEXTURE_SIZE_X, -TITLETELOP_TEXTYRE_SIZE_Y, 0.0f);
	vtxWk[2].vtx = TITLETELOP_BASEPOS + D3DXVECTOR3(-TITLETELOP_TEXTURE_SIZE_X, TITLETELOP_TEXTYRE_SIZE_Y, 0.0f);
	vtxWk[3].vtx = TITLETELOP_BASEPOS + D3DXVECTOR3(TITLETELOP_TEXTURE_SIZE_X, TITLETELOP_TEXTYRE_SIZE_Y, 0.0f);

	vtxWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	vtxWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	vtxWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	vtxWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);
}

/**************************************
�f�B�t���[�Y�ݒ菈��
***************************************/
void SetDiffuseTitleTelop(float alpha)
{
	vtxWk[0].diffuse =
		vtxWk[1].diffuse =
		vtxWk[2].diffuse =
		vtxWk[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, alpha);
}