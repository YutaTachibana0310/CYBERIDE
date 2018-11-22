//=============================================================================
//
// �v���C���[�o���b�g���� [scoreGUI.cpp]
// Author : GP11A341 21 ���ԗY��
//
//=============================================================================
#include "scoreGUI.h"

/*****************************************************************************
�}�N����`
*****************************************************************************/
#define SCOREGUI_TEXTURE_NAME	_T("data/TEXTURE/UI/scoreGUI.png")	// �v���C���[�o���b�g�̃e�N�X�`��

#define SCOREGUI_TEXTURE_SIZE_X					(60)					// �e�N�X�`���T�C�YX
#define SCOREGUI_TEXTURE_SIZE_Y					(60)					// �e�N�X�`���T�C�YY

#define SCOREGUI_TEXTURE_DIVIDE_X				(10)						// �A�j���p�^�[���̃e�N�X�`�����������iX)
#define SCOREGUI_TEXTURE_DIVIDE_Y				(1)						// �A�j���p�^�[���̃e�N�X�`�����������iY)

#define SCOREGUI_INITPOS_X						(SCREEN_WIDTH - SCOREGUI_TEXTURE_SIZE_X / 2.0f)		//�v���C���[�o���b�g�̏���X���W
#define SCOREGUI_INITPOS_Y						(SCOREGUI_TEXTURE_SIZE_Y * 0.9f)					//�v���C���[�o���b�g�̏���Y���W
#define SCOREGUI_OFFSETPOS						(-100.0f)

/*****************************************************************************
�v���g�^�C�v�錾
*****************************************************************************/
HRESULT MakeVertexScoreGUI(void);				//���_�쐬�֐�
void SetTextureScoreGUI(int cntPattern);	// �e�N�X�`�����W�̌v�Z����
void SetVertexScoreGUI(float offset);					// ���_�̌v�Z����

/*****************************************************************************
�\���̒�`
*****************************************************************************/

/*****************************************************************************
�O���[�o���ϐ�
*****************************************************************************/
static LPDIRECT3DTEXTURE9 texture = NULL;				// �e�N�X�`���ւ̃|�C���^
static VERTEX_2D vertexWk[NUM_VERTEX];					//���_���i�[���[�N

SCOREGUI scoreGUI;				//�v���C���[�o���b�g�z��

/******************************************************************************
����������
******************************************************************************/
HRESULT InitScoreGUI(int num)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	SCOREGUI* ptr = &scoreGUI;
	int i;

	ptr->pos = D3DXVECTOR3(SCOREGUI_INITPOS_X, SCOREGUI_INITPOS_Y, 0.0f);
	ptr->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	ptr->angle = atan2f(SCOREGUI_TEXTURE_SIZE_Y, SCOREGUI_TEXTURE_SIZE_X);
	ptr->radius = D3DXVec2Length(&D3DXVECTOR2(SCOREGUI_TEXTURE_SIZE_X, SCOREGUI_TEXTURE_SIZE_Y));
	ptr->active = false;

	// ���_���̍쐬
	MakeVertexScoreGUI();

	if (num == 0)
	{
		// �e�N�X�`���̓ǂݍ���
		texture = CreateTextureFromFile((LPSTR)SCOREGUI_TEXTURE_NAME, pDevice);
	}

	return S_OK;
}

/******************************************************************************
�I������
******************************************************************************/
void UninitScoreGUI(int num)
{
	if (texture != NULL)
	{	// �e�N�X�`���̊J��
		texture->Release();
		texture = NULL;
	}
}

/******************************************************************************
�X�V����
******************************************************************************/
void UpdateScoreGUI(void)
{

}

/******************************************************************************
�`�揈��
******************************************************************************/
void DrawScoreGUI(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	SCOREGUI *ptr = &scoreGUI;

	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, true);

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, texture);

	//�v���C���[�o���b�g��`��
	int score = 9999995;
	int digitMax = (score == 0) ? 1 : (int)log10f((float)score) + 1;
	int num = 0;
	for (int i = 0; i < digitMax; i++, score /= 10)
	{
		num = score % 10;

		//���_���W��ݒ�
		SetVertexScoreGUI(SCOREGUI_OFFSETPOS * i);

		// �e�N�X�`�����W��ݒ�
		SetTextureScoreGUI(num);

		// �|���S���̕`��
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, vertexWk, sizeof(VERTEX_2D));
	}

	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, false);
}


/******************************************************************************
���_�̍쐬
******************************************************************************/
HRESULT MakeVertexScoreGUI(void)
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

	return S_OK;
}

/******************************************************************************
�e�N�X�`�����W�̐ݒ�
******************************************************************************/
void SetTextureScoreGUI(int cntPattern)
{
	// �e�N�X�`�����W�̐ݒ�
	int x = cntPattern % SCOREGUI_TEXTURE_DIVIDE_X;
	int y = cntPattern / SCOREGUI_TEXTURE_DIVIDE_X;
	float sizeX = 1.0f / SCOREGUI_TEXTURE_DIVIDE_X;
	float sizeY = 1.0f / SCOREGUI_TEXTURE_DIVIDE_Y;

	vertexWk[0].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY);
	vertexWk[1].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY);
	vertexWk[2].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY + sizeY);
	vertexWk[3].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY + sizeY);
}


/******************************************************************************
���_���W�̐ݒ�
******************************************************************************/
void SetVertexScoreGUI(float offset)
{
	SCOREGUI *ptr = &scoreGUI;
	// ���_���W�̐ݒ�
	vertexWk[0].vtx.x = ptr->pos.x - cosf(ptr->angle + ptr->rot.z) * ptr->radius + offset;
	vertexWk[0].vtx.y = ptr->pos.y - sinf(ptr->angle + ptr->rot.z) * ptr->radius;
	vertexWk[1].vtx.x = ptr->pos.x + cosf(ptr->angle - ptr->rot.z) * ptr->radius + offset;
	vertexWk[1].vtx.y = ptr->pos.y - sinf(ptr->angle - ptr->rot.z) * ptr->radius;
	vertexWk[2].vtx.x = ptr->pos.x - cosf(ptr->angle - ptr->rot.z) * ptr->radius + offset;
	vertexWk[2].vtx.y = ptr->pos.y + sinf(ptr->angle - ptr->rot.z) * ptr->radius;
	vertexWk[3].vtx.x = ptr->pos.x + cosf(ptr->angle + ptr->rot.z) * ptr->radius + offset;
	vertexWk[3].vtx.y = ptr->pos.y + sinf(ptr->angle + ptr->rot.z) * ptr->radius;
}
