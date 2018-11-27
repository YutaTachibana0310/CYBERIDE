//=============================================================================
//
// �^�C�g���V�[������ [titleScene.cpp]
// Author : GP11A341 21 ���ԗY��
//
//=============================================================================
#include "main.h"
#include "camera.h"
#include "titleScene.h"
#include "input.h"
#include "Easing.h"

/*****************************************************************************
�}�N����`
*****************************************************************************/
#define TITLESCENE_TEXTURE_NAME	_T("data/TEXTURE/UI/title.png")	// �v���C���[�o���b�g�̃e�N�X�`��

#define TITLESCENE_TEXTURE_SIZE_X	(SCREEN_WIDTH / 2.0f)			// �e�N�X�`���T�C�YX
#define TITLESCENE_TEXTURE_SIZE_Y	 (SCREEN_HEIGHT / 2.0f)			// �e�N�X�`���T�C�YY
#define TITLESCENE_FADEIN_END		(60)

/*****************************************************************************
�v���g�^�C�v�錾
*****************************************************************************/
HRESULT MakeVertexTitleScene(void);			//���_�쐬�֐�
void SetTextureTitleScene(void);			// �e�N�X�`�����W�̌v�Z����
void SetVertexTitleScene(void);				// ���_�̌v�Z����
void SetTitleTextureAlpha(float alpha);		//�A���t�@�ݒ菈��

/*****************************************************************************
�\���̒�`
*****************************************************************************/
enum TITLESCENE_STATE
{
	TITLESCENE_FADEIN,
	TITLESCENE_STATEMAX
};
/*****************************************************************************
�O���[�o���ϐ�
*****************************************************************************/
static LPDIRECT3DTEXTURE9 texture = NULL;				// �e�N�X�`���ւ̃|�C���^
static VERTEX_2D vertexWk[NUM_VERTEX];					//���_���i�[���[�N
static D3DXVECTOR3 pos;
static float angle, radius;
static int cntFrame;
static TITLESCENE_STATE state;

/******************************************************************************
����������
******************************************************************************/
HRESULT InitTitleScene(int num)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	pos = D3DXVECTOR3(SCREEN_WIDTH / 2.0f, TITLESCENE_TEXTURE_SIZE_Y, 0.0f);

	angle = atan2f(TITLESCENE_TEXTURE_SIZE_Y, TITLESCENE_TEXTURE_SIZE_X);
	radius = D3DXVec2Length(&D3DXVECTOR2(TITLESCENE_TEXTURE_SIZE_X, TITLESCENE_TEXTURE_SIZE_Y));

	// ���_���̍쐬
	MakeVertexTitleScene();

	if (num == 0)
	{
		// �e�N�X�`���̓ǂݍ���
		texture = CreateTextureFromFile((LPSTR)TITLESCENE_TEXTURE_NAME, pDevice);
	}

	if (num != 0)
	{
		SetBackColor(D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f));
	}
	SetTitleTextureAlpha(0.0f);

	return S_OK;
}

/******************************************************************************
�I������
******************************************************************************/
void UninitTitleScene(int num)
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
void UpdateTitleScene(void)
{
	
	if (state == TITLESCENE_FADEIN)
	{
		cntFrame++;
		float t = (float)cntFrame / TITLESCENE_FADEIN_END;

		SetTitleTextureAlpha(EaseLinear(t, 0.0f, 1.0f));
		if (cntFrame == TITLESCENE_FADEIN_END)
		{
			state = TITLESCENE_STATEMAX;
		}
	}

	if (GetKeyboardTrigger(DIK_Z))
	{
		SetScene(BattleScene);
	}
}

/******************************************************************************
�`�揈��
******************************************************************************/
void DrawTitleScene(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	SetCamera();

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
HRESULT MakeVertexTitleScene(void)
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

	SetVertexTitleScene();
	SetTextureTitleScene();

	return S_OK;
}

/******************************************************************************
�e�N�X�`�����W�̐ݒ�
******************************************************************************/
void SetTextureTitleScene(void)
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
void SetVertexTitleScene(void)
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
�e�N�X�`���A���t�@�ݒ�
******************************************************************************/
void SetTitleTextureAlpha(float alpha)
{
	vertexWk[0].diffuse =
		vertexWk[1].diffuse =
		vertexWk[2].diffuse =
		vertexWk[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, alpha);
}