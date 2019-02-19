//=============================================================================
//
// ���U���g�V�[������ [resultScene.cpp]
// Author : GP11A341 21 ���ԗY��
//
//=============================================================================
#include "main.h"
#include "resultScene.h"
#include "input.h"
#include "cloud.h"
#include "enemyMissile.h"
#include "playerModel.h"
#include "camera.h"
#include "particleManager.h"

/*****************************************************************************
�}�N����`
*****************************************************************************/
#define RESULTSCENE_TEXTURE_NAME	_T("data/TEXTURE/UI/result.png")	// �v���C���[�o���b�g�̃e�N�X�`��

#define RESULTSCENE_TEXTURE_SIZE_X (200)			// �e�N�X�`���T�C�YX
#define RESULTSCENE_TEXTURE_SIZE_Y (200)			// �e�N�X�`���T�C�YY

/*****************************************************************************
�v���g�^�C�v�錾
*****************************************************************************/
HRESULT MakeVertexResultScene(void);	//���_�쐬�֐�
void SetTextureResultScene(void);		// �e�N�X�`�����W�̌v�Z����
void SetVertexResultScene(void);		// ���_�̌v�Z����

/*****************************************************************************
�\���̒�`
*****************************************************************************/

/*****************************************************************************
�O���[�o���ϐ�
*****************************************************************************/
static LPDIRECT3DTEXTURE9 texture = NULL;				// �e�N�X�`���ւ̃|�C���^
static VERTEX_2D vertexWk[NUM_VERTEX];					//���_���i�[���[�N
static D3DXVECTOR3 pos;
static float angle, radius;

/******************************************************************************
����������
******************************************************************************/
HRESULT InitResultScene(int num)
{
	static bool initialized = false;
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	pos = D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f);

	angle = atan2f(RESULTSCENE_TEXTURE_SIZE_Y, RESULTSCENE_TEXTURE_SIZE_X);
	radius = D3DXVec2Length(&D3DXVECTOR2(RESULTSCENE_TEXTURE_SIZE_X, RESULTSCENE_TEXTURE_SIZE_Y));

	// ���_���̍쐬
	MakeVertexResultScene();

	if (!initialized)
	{
		// �e�N�X�`���̓ǂݍ���
		texture = CreateTextureFromFile((LPSTR)RESULTSCENE_TEXTURE_NAME, pDevice);
		initialized = true;
	}
	return S_OK;
}

/******************************************************************************
�I������
******************************************************************************/
void UninitResultScene(int num)
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
void UpdateResultScene(void)
{
	if (GetKeyboardPress(DIK_Z))
	{
		SetScene(TitleScene);
		return;
	}
}

/******************************************************************************
�`�揈��
******************************************************************************/
void DrawResultScene(void)
{
	SetCamera();
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
HRESULT MakeVertexResultScene(void)
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

	SetVertexResultScene();
	SetTextureResultScene();

	return S_OK;
}

/******************************************************************************
�e�N�X�`�����W�̐ݒ�
******************************************************************************/
void SetTextureResultScene(void)
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
void SetVertexResultScene(void)
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
