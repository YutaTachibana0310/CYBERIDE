//=============================================================================
//
// ���S�V�[������ [logoScene.cpp]
// Author : GP11A341 21 ���ԗY��
//
//=============================================================================
#include "main.h"
#include "camera.h"
#include "logoScene.h"
#include "input.h"
#include "Easing.h"
#include "titleScene.h"

/*****************************************************************************
�}�N����`
*****************************************************************************/
#define LOGOSCENE_TEXTURE_NAME	_T("data/TEXTURE/UI/logo.png")	// �v���C���[�o���b�g�̃e�N�X�`��

#define LOGOSCENE_TEXTURE_SIZE_X	(300)			// �e�N�X�`���T�C�YX
#define LOGOSCENE_TEXTURE_SIZE_Y	(150)			// �e�N�X�`���T�C�YY

#define LOGOSCENE_FADEIN_END		(30)
#define LOGOSCENE_FADEWAIT_END		(60)
#define LOGOSCENE_FADEOUT_END		(30)

/*****************************************************************************
�v���g�^�C�v�錾
*****************************************************************************/
HRESULT MakeVertexLogoScene(void);			//���_�쐬�֐�
void SetTextureLogoScene(void);				// �e�N�X�`�����W�̌v�Z����
void SetVertexLogoScene(void);				// ���_�̌v�Z����
void SetLogoTextureAlpha(float alpha);		// �A���t�@�ݒ菈��
/*****************************************************************************
�\���̒�`
*****************************************************************************/
enum LOGOSCENE_STATE
{
	LOGOSCENE_FADEIN,
	LOGOSCENE_FADEWAIT,
	LOGOSCENE_FADEOUT,
	LOGOSCENE_STATEMAX
};

/*****************************************************************************
�O���[�o���ϐ�
*****************************************************************************/
static LPDIRECT3DTEXTURE9 texture = NULL;				// �e�N�X�`���ւ̃|�C���^
static VERTEX_2D vertexWk[NUM_VERTEX];					//���_���i�[���[�N
static D3DXVECTOR3 pos;
static float angle, radius;
static int cntFrame;
static LOGOSCENE_STATE state = LOGOSCENE_FADEIN;

/******************************************************************************
����������
******************************************************************************/
HRESULT InitLogoScene(int num)
{
	static bool initialized = false;
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	pos = D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f);

	angle = atan2f(LOGOSCENE_TEXTURE_SIZE_Y, LOGOSCENE_TEXTURE_SIZE_X);
	radius = D3DXVec2Length(&D3DXVECTOR2(LOGOSCENE_TEXTURE_SIZE_X, LOGOSCENE_TEXTURE_SIZE_Y));

	// ���_���̍쐬
	MakeVertexLogoScene();

	if (!initialized)
	{
		// �e�N�X�`���̓ǂݍ���
		texture = CreateTextureFromFile((LPSTR)LOGOSCENE_TEXTURE_NAME, pDevice);
		initialized = true;
	}

	//�J�E���g���Z�b�g
	cntFrame = 0;

	return S_OK;
}

/******************************************************************************
�I������
******************************************************************************/
void UninitLogoScene(int num)
{
	if (num == 0)
	{
		if (texture != NULL)
		{	// �e�N�X�`���̊J��
			texture->Release();
			texture = NULL;
		}
	}
}

/******************************************************************************
�X�V����
******************************************************************************/
void UpdateLogoScene(void)
{
	cntFrame++;
	float t = 0.0f;

	switch (state)
	{
		//�t�F�[�h�C��
	case LOGOSCENE_FADEIN:
		t = (float)cntFrame / LOGOSCENE_FADEIN_END;
		SetLogoTextureAlpha(EaseLinear(t, 0.0f, 1.0f));

		if (cntFrame == LOGOSCENE_FADEIN_END)
		{
			cntFrame = 0;
			state = LOGOSCENE_FADEWAIT;
		}
		break;

		//�t�F�[�h�ҋ@
	case LOGOSCENE_FADEWAIT:
		if (cntFrame == LOGOSCENE_FADEWAIT_END)
		{
			cntFrame = 0;
			InitTitleScene(0);			//�ǂݍ��݂Ōł܂�̂ł����ň�U���[�h
			state = LOGOSCENE_FADEOUT;
		}
		break;

		//�t�F�[�h�A�E�g
	case LOGOSCENE_FADEOUT:
		t = (float)cntFrame / LOGOSCENE_FADEOUT_END;
		SetLogoTextureAlpha(EaseLinear(t, 1.0f, 0.0f));

		if (cntFrame == LOGOSCENE_FADEOUT_END)
		{
			//cntFrame = 0;
			//state = LOGOSCENE_INPUTWAIT;
			SetScene(TitleScene);
		}
		break;
	}
}

/******************************************************************************
�`�揈��
******************************************************************************/
void DrawLogoScene(void)
{
	SetCamera();

	
}

/******************************************************************************
���S�`��
******************************************************************************/
void DrawCircleLogo(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, texture);

	// �|���S���̕`��
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, vertexWk, sizeof(VERTEX_2D));
}

/******************************************************************************
���_�̍쐬
******************************************************************************/
HRESULT MakeVertexLogoScene(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// rhw�̐ݒ�
	vertexWk[0].rhw =
		vertexWk[1].rhw =
		vertexWk[2].rhw =
		vertexWk[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	SetVertexLogoScene();
	SetTextureLogoScene();

	return S_OK;
}

/******************************************************************************
�e�N�X�`�����W�̐ݒ�
******************************************************************************/
void SetTextureLogoScene(void)
{
	// �e�N�X�`�����W�̐ݒ�
	vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	vertexWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	vertexWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);
}


/******************************************************************************
���_���W�̐ݒ�
******************************************************************************/
void SetVertexLogoScene(void)
{
	// ���_���W�̐ݒ�
	vertexWk[0].vtx.x = pos.x - cosf(angle) * radius;
	vertexWk[0].vtx.y = pos.y - sinf(angle) * radius;
	vertexWk[1].vtx.x = pos.x + cosf(angle) * radius;
	vertexWk[1].vtx.y = pos.y - sinf(angle) * radius;
	vertexWk[2].vtx.x = pos.x - cosf(angle) * radius;
	vertexWk[2].vtx.y = pos.y + sinf(angle) * radius;
	vertexWk[3].vtx.x = pos.x + cosf(angle) * radius;
	vertexWk[3].vtx.y = pos.y + sinf(angle) * radius;
}

/******************************************************************************
�A���t�@�ݒ菈��
******************************************************************************/
void SetLogoTextureAlpha(float alpha)
{
	vertexWk[0].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, alpha);
	vertexWk[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, alpha);
	vertexWk[2].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, alpha);
	vertexWk[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, alpha);
}