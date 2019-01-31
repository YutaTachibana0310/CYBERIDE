//=====================================
//
//�l�[���G���g���[�J�[�\������[nameEntryCursor.cpp]
//Author:GP11A341 21 ���ԗY��
//
//=====================================
#include "nameEntryCursor.h"

/**************************************
�}�N����`
***************************************/
#define NAMEENTRYCURSOR_TEXTURE_NAME	"data/TEXTURE/UI/nameEntryCursor.png"
#define NAMEENTRYCURSOR_TEX_DIV_X		(2)
#define NAMEENTRYCURSOR_TEX_DIV_Y		(2)
#define NAMEENTRYCURSOR_TEX_SIZE_X		(50.0f)
#define NAMEENTRYCURSOR_TEX_SIZE_Y		(50.0f)
#define NAMEENTRYCURSOR_BASEPOS			(D3DXVECTOR3(600.0f, 150.0f, 0.0f))
#define NAMEENTRYCURSOR_CHARA_OFFSET	(50.0f)
#define NAMEENTRYCURSOR_OFFSETPOS_X		(900.0f)
#define NAMEENTRYCURSOR_OFFSETPOS_Y		(150.0f)
#define NAMEENTRYCURSOR_DIV_X			(2)
#define NAMEENTRYCURSOR_DIV_Y			(5)

/**************************************
�\���̒�`
***************************************/

/**************************************
�O���[�o���ϐ�
***************************************/
static LPDIRECT3DTEXTURE9 texture;
static VERTEX_2D vtxWk[NUM_VERTEX];
static int cntFrame;
static int cntAnim;
/**************************************
�v���g�^�C�v�錾
***************************************/
void MakeVertexNameEntryCursor(void);
void SetTextureNameEntryCursor(int num);

/**************************************
����������
***************************************/
void InitNameEntryCursor(int num)
{
	static bool initialized = false;

	if (!initialized)
	{
		LPDIRECT3DDEVICE9 pDevice = GetDevice();
		texture = CreateTextureFromFile((LPSTR)NAMEENTRYCURSOR_TEXTURE_NAME, pDevice);
		MakeVertexNameEntryCursor();
	}

	cntFrame = 0;
	cntAnim = 0;
}

/**************************************
�I������
***************************************/
void UninitNameEntryCursor(int num)
{
	if (num == 0)
	{
		SAFE_RELEASE(texture);
	}
}

/**************************************
�X�V����
***************************************/
void UpdateNameEntryCursor(void)
{
	cntFrame++;

	if (cntFrame % 5 == 0)
	{
		cntAnim = (cntAnim + 1) % (NAMEENTRYCURSOR_TEX_DIV_X * NAMEENTRYCURSOR_TEX_DIV_Y);
	}
}

/**************************************
�`�揈��
***************************************/
void DrawNameEntryCursor(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	pDevice->SetTexture(0, texture);
	pDevice->SetFVF(FVF_VERTEX_2D);

	SetTextureNameEntryCursor(cntAnim);
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, vtxWk, sizeof(VERTEX_2D));
}

/**************************************
���_�쐬����
***************************************/
void MakeVertexNameEntryCursor(void)
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
���_�ݒ菈��
***************************************/
void SetNameEntryCursor(int rank, int offsetIndex)
{
	int x = rank / NAMEENTRYCURSOR_DIV_Y;
	int y = rank % NAMEENTRYCURSOR_DIV_Y;

	D3DXVECTOR3 basePos = NAMEENTRYCURSOR_BASEPOS + D3DXVECTOR3(NAMEENTRYCURSOR_OFFSETPOS_X * x, NAMEENTRYCURSOR_OFFSETPOS_Y * y, 0.0f);
	basePos.x += offsetIndex * NAMEENTRYCURSOR_CHARA_OFFSET;

	vtxWk[0].vtx = basePos + D3DXVECTOR3(-NAMEENTRYCURSOR_TEX_SIZE_X, -NAMEENTRYCURSOR_TEX_SIZE_Y, 0.0f);
	vtxWk[1].vtx = basePos + D3DXVECTOR3( NAMEENTRYCURSOR_TEX_SIZE_X, -NAMEENTRYCURSOR_TEX_SIZE_Y, 0.0f);
	vtxWk[2].vtx = basePos + D3DXVECTOR3(-NAMEENTRYCURSOR_TEX_SIZE_X,  NAMEENTRYCURSOR_TEX_SIZE_Y, 0.0f);
	vtxWk[3].vtx = basePos + D3DXVECTOR3( NAMEENTRYCURSOR_TEX_SIZE_X,  NAMEENTRYCURSOR_TEX_SIZE_Y, 0.0f);
}

/**************************************
�e�N�X�`�����W�ݒ菈��
***************************************/
void SetTextureNameEntryCursor(int num)
{
	int x = num % NAMEENTRYCURSOR_TEX_DIV_X;
	int y = num / NAMEENTRYCURSOR_TEX_DIV_X;
	float sizeX = 1.0f / NAMEENTRYCURSOR_TEX_DIV_X;
	float sizeY = 1.0f / NAMEENTRYCURSOR_TEX_DIV_Y;

	vtxWk[0].tex = D3DXVECTOR2(x * sizeX, y * sizeY);
	vtxWk[1].tex = D3DXVECTOR2((x+1) * sizeX, y * sizeY);
	vtxWk[2].tex = D3DXVECTOR2(x * sizeX, (y+1) * sizeY);
	vtxWk[3].tex = D3DXVECTOR2((x+1) * sizeX, (y+1) * sizeY);
}