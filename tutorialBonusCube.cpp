//=====================================
//
//�`���[�g���A���{�[�i�X�L���[�u����[tutorialBonusCube.cpp]
//Author:GP11A341 21 ���ԗY��
//
//=====================================
#include "tutorialController.h"
#include "Easing.h"
#include "enemyManager.h"

/**************************************
�}�N����`
***************************************/
#define TUTORIAL_BONUSCUBE_TEXTURE_NAME		"data/TEXTURE/UI/tutorial00.png"
#define TUTORIAL_BONUSCUBE_TEX_DIVIDE_Y		(2)
#define TUTORIAL_BONUSCUBE_TEX_SIZE_X		(400)
#define TUTORIAL_BONUSCUBE_TEX_SIZE_Y		(200)
#define TUTORIAL_BONUSCUBE_ANIM_END			(3)
#define TUTORIAL_BONUSCUBE_ANIM_MAX			(6)	
#define TUTORIAL_BONUSCUBE_BASEPOS			(D3DXVECTOR3(SCREEN_CENTER_X, 300.0f, 0.0f))

static const float AnimStartAlpha[TUTORIAL_BONUSCUBE_ANIM_MAX] = {
	0.0f, 1.0f, 1.0f,0.0f, 1.0f, 1.0f
};

static const float AnimEndAlpha[TUTORIAL_BONUSCUBE_ANIM_MAX] = {
	1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f,
};

static const int AnimDuration[TUTORIAL_BONUSCUBE_ANIM_MAX] = {
	30, 240, 30, 30, 240, 30
};

static const EASING_TYPE easingType[TUTORIAL_BONUSCUBE_ANIM_MAX] = {
	OutCubic, Linear, InCubic, OutCubic, Linear, InCubic,
};

/**************************************
�\���̒�`
***************************************/

/**************************************
�O���[�o���ϐ�
***************************************/
static VERTEX_2D vtxWk[NUM_VERTEX];
static int cntFrame;
static float vtxAngle, vtxRadius;
static int animIndex;

/**************************************
�v���g�^�C�v�錾
***************************************/
void MakeVertexTutorialBonusCube(void);
void SetVertexTutorialBonusCube(D3DXVECTOR3 pos);
void SetTextureTutorialBonusCube(int num);
void SetDiffuseTutorialBonusCube(float alpha);

/**************************************
���ꏈ��
***************************************/
void OnEnterTutorialBonusCube(void)
{

	MakeVertexTutorialBonusCube();
	cntFrame = 0;
	animIndex = 0;
	EmmittBonusCube(&D3DXVECTOR3(0.0f, 0.0f, -100.0f));
}

/**************************************
�X�V����
***************************************/
void OnUpdateTutorialBonusCube(void)
{
	cntFrame++;
	float t = (float)cntFrame / (float)AnimDuration[animIndex];
	float alpha = GetEasingValue(t, AnimStartAlpha[animIndex], AnimEndAlpha[animIndex], easingType[animIndex]);
	SetDiffuseTutorialBonusCube(alpha);
	SetVertexTutorialBonusCube(TUTORIAL_BONUSCUBE_BASEPOS);
	SetTextureTutorialBonusCube(animIndex / TUTORIAL_BONUSCUBE_ANIM_END);

	if (cntFrame == AnimDuration[animIndex])
	{
		animIndex++;
		cntFrame = 0;
		if (animIndex == TUTORIAL_BONUSCUBE_ANIM_MAX)
		{
			ChangeStateTutorialController(TutorialEnd);
		}
	}
}

/**************************************
�`�揈��
***************************************/
void OnDrawTutorialBonusCube(LPDIRECT3DTEXTURE9 tex)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	pDevice->SetFVF(FVF_VERTEX_2D);
	pDevice->SetTexture(0, tex);

	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, vtxWk, sizeof(VERTEX_2D));
}

/**************************************
���_�쐬����
***************************************/
void MakeVertexTutorialBonusCube(void)
{
	vtxWk[0].rhw =
		vtxWk[1].rhw =
		vtxWk[2].rhw =
		vtxWk[3].rhw = 1.0f;

	vtxWk[0].diffuse =
		vtxWk[1].diffuse =
		vtxWk[2].diffuse =
		vtxWk[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	vtxRadius = D3DXVec2Length(&D3DXVECTOR2(TUTORIAL_BONUSCUBE_TEX_SIZE_X, TUTORIAL_BONUSCUBE_TEX_SIZE_Y));
	vtxAngle = atan2f(TUTORIAL_BONUSCUBE_TEX_SIZE_Y, TUTORIAL_BONUSCUBE_TEX_SIZE_X);
}

/**************************************
���_���W�ݒ菈��
***************************************/
void SetVertexTutorialBonusCube(D3DXVECTOR3 pos)
{
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
�e�N�X�`�����W�ݒ菈��
***************************************/
void SetTextureTutorialBonusCube(int num)
{
	float sizeY = 1.0f / TUTORIAL_BONUSCUBE_TEX_DIVIDE_Y;

	vtxWk[0].tex = D3DXVECTOR2(0.0f, num * sizeY);
	vtxWk[1].tex = D3DXVECTOR2(1.0f, num * sizeY);
	vtxWk[2].tex = D3DXVECTOR2(0.0f, (num + 1) * sizeY);
	vtxWk[3].tex = D3DXVECTOR2(1.0f, (num + 1) * sizeY);
}

/**************************************
�f�B�t���[�Y�ݒ菈��
***************************************/
void SetDiffuseTutorialBonusCube(float alpha)
{
	vtxWk[0].diffuse =
		vtxWk[1].diffuse =
		vtxWk[2].diffuse =
		vtxWk[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, alpha);
}