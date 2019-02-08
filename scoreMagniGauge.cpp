//=====================================
//
//�X�R�A�{���Q�[�W����[scoreMagniGauge.cpp]
//Author:GP11A341 21 ���ԗY��
//
//=====================================
#include "scoreMagniGauge.h"

/**************************************
�}�N����`
***************************************/
#define SCOREMAGNIGAUGE_TEXTURE_NAME	"data/TEXTURE/UI/scoreGauge.png"
#define SCOREMAGNIGAUGE_SIZE_X			(450.0f)
#define SCOREMAGNIGAUGE_SIZE_Y			(20.0f)
#define SCOREMAGNIGAUGE_PER_MAX			(120.0f)
#define SCOREMAGNIGAUGE_BASEPOS			(D3DXVECTOR3(0.0f, 160.0f, 0.0f))

/**************************************
�\���̒�`
***************************************/

/**************************************
�O���[�o���ϐ�
***************************************/
static LPDIRECT3DTEXTURE9 texture;
static VERTEX_2D vtxWk[NUM_VERTEX];
static int cntFrame;

/**************************************
�v���g�^�C�v�錾
***************************************/
void MakeVertexScoreMagniGauge(void);
void SetVertexScoreGaugeBG(void);
void SetTextureScoreGaugeBG(void);

void SetVertexScoreGauge(float percent);
void SetTextureScoreGauge(float percent);

void SetDiffuseScoreGauge(float alpha);

/**************************************
����������
***************************************/
void InitScoreMagniGauge(int num)
{
	static bool initialized = false;

	if (!initialized)
	{
		LPDIRECT3DDEVICE9 pDevice = GetDevice();
		MakeVertexScoreMagniGauge();
		texture = CreateTextureFromFile((LPSTR)SCOREMAGNIGAUGE_TEXTURE_NAME, pDevice);
	}
}

/**************************************
�I������
***************************************/
void UninitScoreMagniGauge(int num)
{
	if (num == 0)
	{
		SAFE_RELEASE(texture);
	}
}

/**************************************
�X�V����
***************************************/
void UpdateScoreMagniGauge(void)
{
	if (cntFrame <= 0)
		return;

	cntFrame--;
}

/**************************************
�`�揈��
***************************************/
void DrawScoreMagniGauge(float alpha)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	pDevice->SetTexture(0, texture);

	SetDiffuseScoreGauge(alpha);

	//�Q�[�W�{�̕`��
	if (cntFrame > 0)
	{
		SetVertexScoreGauge(cntFrame / SCOREMAGNIGAUGE_PER_MAX);
		SetTextureScoreGauge(cntFrame / SCOREMAGNIGAUGE_PER_MAX);
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, vtxWk, sizeof(VERTEX_2D));
	}


	//�Q�[�W�w�i�`��
	SetVertexScoreGaugeBG();
	SetTextureScoreGaugeBG();
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, vtxWk, sizeof(VERTEX_2D));

}

/**************************************
���_�쐬����
***************************************/
void MakeVertexScoreMagniGauge(void)
{
	vtxWk[0].diffuse =
		vtxWk[1].diffuse =
		vtxWk[2].diffuse =
		vtxWk[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	vtxWk[0].rhw =
		vtxWk[1].rhw =
		vtxWk[2].rhw =
		vtxWk[3].rhw = 1.0f;
}

/**************************************
���_�ݒ菈���i�w�i�p�j
***************************************/
void SetVertexScoreGaugeBG(void)
{
	vtxWk[0].vtx = SCOREMAGNIGAUGE_BASEPOS;
	vtxWk[1].vtx = SCOREMAGNIGAUGE_BASEPOS + D3DXVECTOR3(SCOREMAGNIGAUGE_SIZE_X, 0.0f, 0.0f);
	vtxWk[2].vtx = SCOREMAGNIGAUGE_BASEPOS + D3DXVECTOR3(0.0f, SCOREMAGNIGAUGE_SIZE_Y, 0.0f);
	vtxWk[3].vtx = SCOREMAGNIGAUGE_BASEPOS + D3DXVECTOR3(SCOREMAGNIGAUGE_SIZE_X, SCOREMAGNIGAUGE_SIZE_Y, 0.0f);
}

/**************************************
�e�N�X�`�����W�ݒ菈��(�w�i�p)
***************************************/
void SetTextureScoreGaugeBG(void)
{
	vtxWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	vtxWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	vtxWk[2].tex = D3DXVECTOR2(0.0f, 0.5f);
	vtxWk[3].tex = D3DXVECTOR2(1.0f, 0.5f);
}

/**************************************
�e�N�X�`�����W�ݒ菈��
***************************************/
void SetTextureScoreGauge(float percent)
{
	vtxWk[0].vtx = SCOREMAGNIGAUGE_BASEPOS;
	vtxWk[1].vtx = SCOREMAGNIGAUGE_BASEPOS + D3DXVECTOR3(SCOREMAGNIGAUGE_SIZE_X * percent, 0.0f, 0.0f);
	vtxWk[2].vtx = SCOREMAGNIGAUGE_BASEPOS + D3DXVECTOR3(0.0f, SCOREMAGNIGAUGE_SIZE_Y, 0.0f);
	vtxWk[3].vtx = SCOREMAGNIGAUGE_BASEPOS + D3DXVECTOR3(SCOREMAGNIGAUGE_SIZE_X * percent, SCOREMAGNIGAUGE_SIZE_Y, 0.0f);
}

/**************************************
���_�ݒ菈���i�Q�[�W�{�̗p�j
***************************************/
void SetVertexScoreGauge(float percent)
{
	vtxWk[0].tex = D3DXVECTOR2(0.0f, 0.5f);
	vtxWk[1].tex = D3DXVECTOR2(1.0f * percent, 0.5f);
	vtxWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	vtxWk[3].tex = D3DXVECTOR2(1.0f * percent, 1.0f);
}

/**************************************
�f�B�t���[�Y�ݒ菈��
***************************************/
void SetDiffuseScoreGauge(float alpha)
{
	vtxWk[0].diffuse =
		vtxWk[1].diffuse =
		vtxWk[2].diffuse =
		vtxWk[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, alpha);
}

/**************************************
�Q�[�W�Z�b�g����
***************************************/
void SetScoreMagniGauge(void)
{
	cntFrame = (int)SCOREMAGNIGAUGE_PER_MAX;
}