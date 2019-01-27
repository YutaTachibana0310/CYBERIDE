//=====================================
//
//�X�e�[�W�N���A�e���b�v����[stageClearTelop.cpp]
//Author:GP11A341 21 ���ԗY��
//
//=====================================
#include "stageClearTelop.h"
#include "EasingVector.h"

/**************************************
�}�N����`
***************************************/
#define STAGECLEARTELOP_TEX_NAME		"data/TEXTURE/UI/stageclear.png"
#define STAGECLEARTELOP_TEX_DIVIDE_X	(11)
#define STAGECLEARTELOP_TEX_SIZE_X		(120.0f)
#define STAGECLEARTELOP_TEX_SIZE_Y		(120.0f)
#define STAGECLEARTELOP_POS_Y			(300.0f)
#define STAGECLEARTELOP_BASEPOS			(D3DXVECTOR3(SCREEN_CENTER_X - STAGECLEARTELOP_TEX_DIVIDE_X * STAGECLEARTELOP_TEX_SIZE_X / 2.0f, STAGECLEARTELOP_POS_Y, 0.0f))
#define STAGECLEARTELOP_STARTPOS		(D3DXVECTOR3(SCREEN_WIDTH, STAGECLEARTELOP_POS_Y, 0.0f))
#define STAGECLEARTELOP_ENDPOS			(D3DXVECTOR3(- STAGECLEARTELOP_TEX_DIVIDE_X * STAGECLEARTELOP_TEX_SIZE_X / 2.0f, STAGECLEARTELOP_POS_Y, 0.0f))
#define STAGECLEARTELOP_ANIM_MAX		(3)

/**************************************
�\���̒�`
***************************************/

/**************************************
�O���[�o���ϐ�
***************************************/
static VERTEX_2D vtxWk[NUM_VERTEX];
static LPDIRECT3DTEXTURE9 texture;
int cntFrame;
int animIndex;

static const D3DXVECTOR3 AnimStartPos[STAGECLEARTELOP_ANIM_MAX] = {
	STAGECLEARTELOP_STARTPOS,
	STAGECLEARTELOP_BASEPOS,
	STAGECLEARTELOP_BASEPOS,
};

static const D3DXVECTOR3 AnimEndPos[STAGECLEARTELOP_ANIM_MAX] = {
	STAGECLEARTELOP_BASEPOS,
	STAGECLEARTELOP_BASEPOS,
	STAGECLEARTELOP_ENDPOS,
};

static const int AnimDuration[STAGECLEARTELOP_ANIM_MAX] = {
	20, 180, 20
};

static const EASINGVECTOR_TYPE AnimType[STAGECLEARTELOP_ANIM_MAX] = {
	OutCubic_Vector, Linear_Vector, InCubic_Vector
};


/**************************************
�v���g�^�C�v�錾
***************************************/
void MakeVertexStageClearTelop(void);
void SetVertexStageCleatTelop(D3DXVECTOR3 pos);
void SetTextureStageClearTelop(int num);

/**************************************
����������
***************************************/
void InitStageClearTelop(int num)
{
	static bool initialized = false;

	if (!initialized)
	{
		LPDIRECT3DDEVICE9 pDevice = GetDevice();
		texture = CreateTextureFromFile((LPSTR)STAGECLEARTELOP_TEX_NAME, pDevice);
		MakeVertexStageClearTelop();
	}

	animIndex = STAGECLEARTELOP_ANIM_MAX;
}

/**************************************
�I������
***************************************/
void UninitStageClearTelop(int num)
{
	animIndex = STAGECLEARTELOP_ANIM_MAX;
	if (num == 0)
	{
		SAFE_RELEASE(texture);
	}
}

/**************************************
�X�V����
***************************************/
void UpdateStageClearTelop(void)
{
	if (animIndex >= STAGECLEARTELOP_ANIM_MAX)
		return;

	cntFrame++;
	float t = (float)cntFrame / (float)AnimDuration[animIndex];
	D3DXVECTOR3 pos = GetEasingValueVector(t, AnimStartPos[animIndex], AnimEndPos[animIndex], AnimType[animIndex]);
	SetVertexStageCleatTelop(pos);
	SetTextureStageClearTelop(0);

	if (cntFrame == AnimDuration[animIndex])
	{
		animIndex++;
		cntFrame = 0;
	}
}

/**************************************
�`�揈��
***************************************/
void DrawStageClearTelop(void)
{
	if (animIndex >= STAGECLEARTELOP_ANIM_MAX)
		return;

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	pDevice->SetFVF(FVF_VERTEX_2D);
	pDevice->SetTexture(0, texture);

	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, vtxWk, sizeof(VERTEX_2D));
}

/**************************************
���_�쐬����
***************************************/
void MakeVertexStageClearTelop(void)
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
���_�ݒ�
***************************************/
void SetVertexStageCleatTelop(D3DXVECTOR3 pos)
{
	vtxWk[0].vtx = pos;
	vtxWk[1].vtx = pos + D3DXVECTOR3(STAGECLEARTELOP_TEX_SIZE_X * STAGECLEARTELOP_TEX_DIVIDE_X, 0.0f, 0.0f);
	vtxWk[2].vtx = pos + D3DXVECTOR3(0.0f, STAGECLEARTELOP_TEX_SIZE_Y, 0.0f);
	vtxWk[3].vtx = pos + D3DXVECTOR3(STAGECLEARTELOP_TEX_SIZE_X * STAGECLEARTELOP_TEX_DIVIDE_X, STAGECLEARTELOP_TEX_SIZE_Y, 0.0f);
}

/**************************************
�e�N�X�`���ݒ菈��
***************************************/
void SetTextureStageClearTelop(int num) 
{
	vtxWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	vtxWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	vtxWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	vtxWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);
}

/**************************************
�Z�b�g����
***************************************/
void SetStageClearTelop(void)
{
	animIndex = 0;
	cntFrame = 0;
}