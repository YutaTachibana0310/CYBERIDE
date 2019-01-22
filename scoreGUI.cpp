//=============================================================================
//
// �v���C���[�o���b�g���� [scoreGUI.cpp]
// Author : GP11A341 21 ���ԗY��
//
//=============================================================================
#include "scoreGUI.h"
#include "dataContainer.h"

/*****************************************************************************
�}�N����`
*****************************************************************************/
#define SCOREGUI_TEXTURE_NAME	_T("data/TEXTURE/UI/scoreGUI.png")		// UI�̃e�N�X�`��
#define SCOREGUI_NUMTEX_NAME	_T("data/TEXTURE/UI/scoreNum.png")		// �����̃e�N�X�`��
#define SCOREGUI_TEXTURE_SIZE_X					(480)					// �e�N�X�`���T�C�YX
#define SCOREGUI_TEXTURE_SIZE_Y					(200)					// �e�N�X�`���T�C�YY
#define SCOREGUI_INITPOS						(D3DXVECTOR3(0.0f, -5.0f, 0.0f))

#define SCOREGUI_NUMTEX_SIZE_X					(30.0f)					// �����e�N�X�`���T�C�Y
#define SCOREGUI_NUMTEX_SIZE_Y					(40.0f)					// �����e�N�X�`���T�C�Y
#define SCOREGUI_NUMTEX_DIVIDE_X				(5)						// �A�j���p�^�[���̃e�N�X�`�����������iX)
#define SCOREGUI_NUMTEX_DIVIDE_Y				(2)						// �A�j���p�^�[���̃e�N�X�`�����������iY)
#define SCOREGUI_NUM_OFFSETPOS					(-30.0f)				// �����̃I�t�Z�b�g���W
#define SCOREGUI_NUM_INITPOS					(D3DXVECTOR3(350.0f, 110.0f, 0.0f))	//�����e�N�X�`���̏������W

/*****************************************************************************
�v���g�^�C�v�錾
*****************************************************************************/
HRESULT MakeVertexScoreGUI(void);				//���_�쐬�֐�
void SetTextureScoreNum(int cntPattern);		// �e�N�X�`�����W�̌v�Z����
void SetVertexScoreGUI(void);					// ���_�̌v�Z����
void SetVertexScoreNum(float offset);			// �����e�N�X�`�����_�v�Z����

/*****************************************************************************
�\���̒�`
*****************************************************************************/

/*****************************************************************************
�O���[�o���ϐ�
*****************************************************************************/
static LPDIRECT3DTEXTURE9 texture = NULL;				// �e�N�X�`���ւ̃|�C���^
static LPDIRECT3DTEXTURE9 numTex = NULL;				// �����e�N�X�`��
static VERTEX_2D vertexWk[NUM_VERTEX];					//���_���i�[���[�N
static SCOREGUI scoreGUI;								//�X�R�AGUI�\����

/******************************************************************************
����������
******************************************************************************/
HRESULT InitScoreGUI(int num)
{
	static bool initialized = false;
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	SCOREGUI* ptr = &scoreGUI;

	ptr->angle = atan2f(SCOREGUI_NUMTEX_SIZE_Y, SCOREGUI_NUMTEX_SIZE_X);
	ptr->radius = D3DXVec2Length(&D3DXVECTOR2(SCOREGUI_NUMTEX_SIZE_X, SCOREGUI_NUMTEX_SIZE_Y));

	// ���_���̍쐬
	MakeVertexScoreGUI();

	if (!initialized)
	{
		// �e�N�X�`���̓ǂݍ���
		texture = CreateTextureFromFile((LPSTR)SCOREGUI_TEXTURE_NAME, pDevice);
		numTex = CreateTextureFromFile((LPSTR)SCOREGUI_NUMTEX_NAME, pDevice);
		initialized = true;
	}

	return S_OK;
}

/******************************************************************************
�I������
******************************************************************************/
void UninitScoreGUI(int num)
{
	if (num == 0)
	{
		// �e�N�X�`���̊J��
		SAFE_RELEASE(texture);
		SAFE_RELEASE(numTex);
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

	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, true);

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, texture);

	//�`��
	SetVertexScoreGUI();
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, vertexWk, sizeof(VERTEX_2D));

	//�X�R�A������`��
	pDevice->SetTexture(0, numTex);
	int score = GetCurrentScore();
	int digitMax = (score == 0) ? 1 : (int)log10f((float)score) + 1;
	int num = 0;
	for (int i = 0; i < digitMax; i++, score /= 10)
	{
		num = score % 10;

		//���_���W��ݒ�
		SetVertexScoreNum(SCOREGUI_NUM_OFFSETPOS * i);

		// �e�N�X�`�����W��ݒ�
		SetTextureScoreNum(num);

		// �|���S���̕`��
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, vertexWk, sizeof(VERTEX_2D));
	}
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

	//set uv
	vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	vertexWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	vertexWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	return S_OK;
}

/******************************************************************************
�e�N�X�`�����W�̐ݒ�
******************************************************************************/
void SetTextureScoreNum(int cntPattern)
{
	// �e�N�X�`�����W�̐ݒ�
	int x = cntPattern % SCOREGUI_NUMTEX_DIVIDE_X;
	int y = cntPattern / SCOREGUI_NUMTEX_DIVIDE_X;
	float sizeX = 1.0f / SCOREGUI_NUMTEX_DIVIDE_X;
	float sizeY = 1.0f / SCOREGUI_NUMTEX_DIVIDE_Y;

	vertexWk[0].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY);
	vertexWk[1].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY);
	vertexWk[2].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY + sizeY);
	vertexWk[3].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY + sizeY);
}


/******************************************************************************
���_���W�̐ݒ�
******************************************************************************/
void SetVertexScoreGUI(void)
{
	// ���_���W�̐ݒ�
	vertexWk[0].vtx = SCOREGUI_INITPOS;
	vertexWk[1].vtx = SCOREGUI_INITPOS + D3DXVECTOR3(SCOREGUI_TEXTURE_SIZE_X, 0.0f, 0.0f);
	vertexWk[2].vtx = SCOREGUI_INITPOS + D3DXVECTOR3(0.0f, SCOREGUI_TEXTURE_SIZE_Y, 0.0f);
	vertexWk[3].vtx = SCOREGUI_INITPOS + D3DXVECTOR3(SCOREGUI_TEXTURE_SIZE_X, SCOREGUI_TEXTURE_SIZE_Y, 0.0f);

	// UV���W�̐ݒ�
	vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	vertexWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	vertexWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);
}

/******************************************************************************
�����e�N�X�`�����_���W�̐ݒ�
******************************************************************************/
void SetVertexScoreNum(float offset)
{
	SCOREGUI *ptr = &scoreGUI;

	D3DXVECTOR3 pos = SCOREGUI_NUM_INITPOS;
	pos.x += offset;

	vertexWk[0].vtx.x = pos.x - cosf(ptr->angle) * ptr->radius;
	vertexWk[0].vtx.y = pos.y - sinf(ptr->angle) * ptr->radius;
	vertexWk[1].vtx.x = pos.x + cosf(ptr->angle) * ptr->radius;
	vertexWk[1].vtx.y = pos.y - sinf(ptr->angle) * ptr->radius;
	vertexWk[2].vtx.x = pos.x - cosf(ptr->angle) * ptr->radius;
	vertexWk[2].vtx.y = pos.y + sinf(ptr->angle) * ptr->radius;
	vertexWk[3].vtx.x = pos.x + cosf(ptr->angle) * ptr->radius;
	vertexWk[3].vtx.y = pos.y + sinf(ptr->angle) * ptr->radius;
}