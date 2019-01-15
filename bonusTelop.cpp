//=====================================
//
//�{�[�i�X�e���b�v����[bonusTelop.cpp]
//Author:GP11A341 21 ���ԗY��
//
//=====================================
#include "bonusTelop.h"
#include "EasingVector.h"

/**************************************
�}�N����`
***************************************/
#define BONUSTELOP_TEX_NAME				"data/TEXTURE/UI/bonusTelop.png"
#define BONUSTELOP_TEX_DIVIDE_Y			(2)
#define BONUSTELOP_TEX_SIZE_X			(400)
#define BONUSTELOP_TEX_SIZE_Y			(100)
#define BONUSTELOP_DISP_POS				(D3DXVECTOR3(SCREEN_CENTER_X, 300.0f, 0.0f))
#define BONUSTELOP_SEQUENCE_MAX			(3)

//�A�j���[�V�����J�n�ʒu
static const D3DXVECTOR3 StartOffset[BONUSTELOP_SEQUENCE_MAX] = {
	D3DXVECTOR3(SCREEN_CENTER_X + BONUSTELOP_TEX_SIZE_X, 0.0f, 0.0f),
	D3DXVECTOR3(0.0f, 0.0f, 0.0f),
	D3DXVECTOR3(0.0f, 0.0f, 0.0f),
};

//�A�j���[�V�����I���ʒu
static const D3DXVECTOR3 EndOffset[BONUSTELOP_SEQUENCE_MAX] = {
	D3DXVECTOR3(0.0f, 0.0f, 0.0f),
	D3DXVECTOR3(0.0f, 0.0f, 0.0f),
	D3DXVECTOR3(-SCREEN_CENTER_X - BONUSTELOP_TEX_SIZE_X, 0.0f, 0.0f)
};

//�A�j���[�V�����^�C�v
static const EASINGVECTOR_TYPE AnimType[BONUSTELOP_SEQUENCE_MAX] = {
	OutExponential_Vector,
	Linear_Vector,
	InExponential_Vector
};

//�A�j���[�V��������
static const int AnimDuration[BONUSTELOP_SEQUENCE_MAX] = {
	30, 60, 30
};

/**************************************
�\���̒�`
***************************************/
enum BONUSTELOP_DEFINE
{
	BonusTelopUpper,
	BonusTelopLower,
	BonusTelopDefineEnd
};

/**************************************
�O���[�o���ϐ�
***************************************/
static VERTEX_2D vtxWk[NUM_VERTEX];
static LPDIRECT3DTEXTURE9 texture;
static D3DXVECTOR3 offsetPos;
static float vtxAngle, vtxRadius;
static int animIndex, cntFrame;

/**************************************
�v���g�^�C�v�錾
***************************************/
void MakeVertexBonusTelop(void);
void SetVertexBonusTelop(BONUSTELOP_DEFINE define);
void SetTextureBonusTelop(BONUSTELOP_DEFINE define);

/**************************************
����������
***************************************/
void InitBonusTelop(int num)
{
	if (num == 0)
	{
		LPDIRECT3DDEVICE9 pDevice = GetDevice();
		texture = CreateTextureFromFile((LPSTR)BONUSTELOP_TEX_NAME, pDevice);
		MakeVertexBonusTelop();
	}

	animIndex = BONUSTELOP_SEQUENCE_MAX;
	cntFrame = 0;
}

/**************************************
�I������
***************************************/
void UninitBonusTelop(int num)
{
	animIndex = BONUSTELOP_SEQUENCE_MAX;
	cntFrame = 0;
}

/**************************************
�X�V����
***************************************/
void UpdateBonusTelop(void)
{
	if (animIndex >= BONUSTELOP_SEQUENCE_MAX)
		return;

	cntFrame++;

	float t = (float)cntFrame / (float)AnimDuration[animIndex];
	offsetPos = GetEasingValueVector(t, StartOffset[animIndex], EndOffset[animIndex], AnimType[animIndex]);

	if (cntFrame == AnimDuration[animIndex])
	{
		cntFrame = 0;
		animIndex++;
	}
}

/**************************************
�`�揈��
***************************************/
void DrawBonusTelop(void)
{
	if (animIndex >= BONUSTELOP_SEQUENCE_MAX)
		return;

	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	pDevice->SetTexture(0, texture);
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e���b�v�㕔�̕`��
	SetTextureBonusTelop(BonusTelopUpper);
	SetVertexBonusTelop(BonusTelopUpper);
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, vtxWk, sizeof(VERTEX_2D));

	//�e���b�v�����̕`��
	SetTextureBonusTelop(BonusTelopLower);
	SetVertexBonusTelop(BonusTelopLower);
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, vtxWk, sizeof(VERTEX_2D));

}

/**************************************
���_�쐬����
***************************************/
void MakeVertexBonusTelop(void)
{
	vtxWk[0].diffuse =
		vtxWk[1].diffuse =
		vtxWk[2].diffuse =
		vtxWk[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	vtxWk[0].rhw =
		vtxWk[1].rhw =
		vtxWk[2].rhw =
		vtxWk[3].rhw = 1.0f;

	vtxAngle = atan2f(BONUSTELOP_TEX_SIZE_Y, BONUSTELOP_TEX_SIZE_X);
	vtxRadius = D3DXVec2Length(&D3DXVECTOR2(BONUSTELOP_TEX_SIZE_X, BONUSTELOP_TEX_SIZE_Y));
}

/**************************************
���_���W�ݒ菈��
***************************************/
void SetVertexBonusTelop(BONUSTELOP_DEFINE define)
{
	D3DXVECTOR3 pos = BONUSTELOP_DISP_POS;
	pos += (define == BonusTelopUpper) ? -offsetPos : offsetPos;
	pos.y += (define == BonusTelopUpper) ? -BONUSTELOP_TEX_SIZE_Y : BONUSTELOP_TEX_SIZE_Y;

	vtxWk[0].vtx.x = pos.x - cosf(vtxAngle) * vtxRadius;
	vtxWk[0].vtx.y = pos.y - sinf(vtxAngle) * vtxRadius;
	vtxWk[1].vtx.x = pos.x + cosf(vtxAngle) * vtxRadius;
	vtxWk[1].vtx.y = pos.y - sinf(vtxAngle) * vtxRadius;
	vtxWk[2].vtx.x = pos.x - cosf(vtxAngle) * vtxRadius;
	vtxWk[2].vtx.y = pos.y + sinf(vtxAngle) * vtxRadius;
	vtxWk[3].vtx.x = pos.x + cosf(vtxAngle) * vtxRadius;
	vtxWk[3].vtx.y = pos.y + sinf(vtxAngle) * vtxRadius;
}

/**************************************
UV���W�ݒ菈��
***************************************/
void SetTextureBonusTelop(BONUSTELOP_DEFINE define)
{
	float sizeY = 1.0f / BONUSTELOP_TEX_DIVIDE_Y;
	int y = (define == BonusTelopUpper) ? 0 : 1;

	vtxWk[0].tex = D3DXVECTOR2(0.0f, y * sizeY);
	vtxWk[1].tex = D3DXVECTOR2(1.0f, y * sizeY);
	vtxWk[2].tex = D3DXVECTOR2(0.0f, (y + 1) * sizeY);
	vtxWk[3].tex = D3DXVECTOR2(1.0f, (y + 1) * sizeY);
}

/**************************************
�A�j���[�V�����J�n����
***************************************/
void StartBonusTelopAnim(void)
{
	animIndex = 0;
	cntFrame = 0;
}