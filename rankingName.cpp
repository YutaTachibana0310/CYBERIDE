//=====================================
//
//�����L���O�l�[������[rankingName.cpp]
//Author:GP11A341 21 ���ԗY��
//
//=====================================
#include "rankingName.h"
#include "dataContainer.h"

/**************************************
�}�N����`
***************************************/
#define RANKINGNAME_TEXTURE_NAME		"data/TEXTURE/UI/charchip.png"
#define RANKINGNAME_TEX_SIZE_X			(30.0f)
#define RANKINGNAME_TEX_SIZE_Y			(30.0f)
#define RANKINGNAME_TEX_DIV_X			(15)
#define RANKINGNAME_TEX_DIV_Y			(2)
#define RANKINGNAME_BASEPOS				(D3DXVECTOR3(600.0f, 250.0f, 0.0f))
#define RANKINGNAME_CHARA_OFFSET		(50.0f)
#define RANKINGNAME_OFFSET_X			(900.0f)
#define RANKINGNAME_OFFSET_Y			(150.0f)
#define RANKINGNAME_DIV_X				(2)
#define RANKINGNAME_DIV_Y				(5)

/**************************************
�\���̒�`
***************************************/

/**************************************
�O���[�o���ϐ�
***************************************/
static LPDIRECT3DTEXTURE9 texture;
static VERTEX_2D vtxWk[NUM_VERTEX];

/**************************************
�v���g�^�C�v�錾
***************************************/
void MakeVertexRankingName(void);
void SetVertexRankingName(int rank, float offset);
void SetTextureRankingName(int chara);

/**************************************
����������
***************************************/
void InitRankingName(int num)
{
	static bool initialized = false;

	if (!initialized)
	{
		LPDIRECT3DDEVICE9 pDevice = GetDevice();
		texture = CreateTextureFromFile((LPSTR)RANKINGNAME_TEXTURE_NAME, pDevice);
		MakeVertexRankingName();
	}
}

/**************************************
�I������
***************************************/
void UninitRankingName(int num)
{
	if (num == 0)
	{
		SAFE_RELEASE(texture);
	}
}

/**************************************
�X�V����
***************************************/
void UpdateRankingName(void)
{

}

/**************************************
�`�揈��
***************************************/
void DrawRankingName(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	DATA_HIGHSCRE *data = GetHighScore();

	pDevice->SetTexture(0, texture);
	for (int cntData = 0; cntData < DATACONTAINER_HIGHSCORE_MAX; cntData++)
	{
		for (int i = 0; i < DATACONTAINER_PLAYERNAME_MAX; i++)
		{
			if (data[cntData].playerName[i] >= CHARCHIP_MAX)
				break;

			SetVertexRankingName(cntData, i * RANKINGNAME_CHARA_OFFSET);
			SetTextureRankingName(data[cntData].playerName[i]);
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, vtxWk, sizeof(VERTEX_2D));
		}
	}
}

/**************************************
���_�쐬����
***************************************/
void MakeVertexRankingName(void)
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
void SetVertexRankingName(int rank, float offset)
{
	int x = rank / RANKINGNAME_DIV_Y;
	int y = rank % RANKINGNAME_DIV_Y;

	D3DXVECTOR3 basePos = RANKINGNAME_BASEPOS + D3DXVECTOR3(RANKINGNAME_OFFSET_X * x, RANKINGNAME_OFFSET_Y * y, 0.0f);
	basePos.x += offset;

	vtxWk[0].vtx = basePos + D3DXVECTOR3(-RANKINGNAME_TEX_SIZE_X, -RANKINGNAME_TEX_SIZE_Y, 0.0f);
	vtxWk[1].vtx = basePos + D3DXVECTOR3(RANKINGNAME_TEX_SIZE_X, -RANKINGNAME_TEX_SIZE_Y, 0.0f);
	vtxWk[2].vtx = basePos + D3DXVECTOR3(-RANKINGNAME_TEX_SIZE_X, RANKINGNAME_TEX_SIZE_Y, 0.0f);
	vtxWk[3].vtx = basePos + D3DXVECTOR3(RANKINGNAME_TEX_SIZE_X, RANKINGNAME_TEX_SIZE_Y, 0.0f);
}

/**************************************
UV���W�ݒ菈��
***************************************/
void SetTextureRankingName(int chara)
{
	if (chara >= CHARCHIP_MAX)
		return;

	int x = chara % RANKINGNAME_TEX_DIV_X;
	int y = chara / RANKINGNAME_TEX_DIV_X;
	float sizeX = 1.0f / RANKINGNAME_TEX_DIV_X;
	float sizeY = 1.0f / RANKINGNAME_TEX_DIV_Y;

	vtxWk[0].tex = D3DXVECTOR2(x * sizeX, y * sizeY);
	vtxWk[1].tex = D3DXVECTOR2((x + 1) * sizeX, y * sizeY);
	vtxWk[2].tex = D3DXVECTOR2(x * sizeX, (y + 1) * sizeY);
	vtxWk[3].tex = D3DXVECTOR2((x + 1) * sizeX, (y + 1) * sizeY);
}