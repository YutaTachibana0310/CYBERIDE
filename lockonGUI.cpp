//=====================================
//
//���b�N�I��GUI����[lockonGUI.cpp]
//Author:GP11A341 21 ���ԗY��
//
//=====================================
#include "lockonGUI.h"
#include "playerModel.h"
#include "battleCamera.h"
#include "GUIManager.h"

/**************************************
�}�N����`
***************************************/
#define LOCKONGUI_TEXTTEX_NAME			"data/TEXTURE/UI/lockonText.png"
#define LOCKONGUI_TEXTTEX_DIVIDE_X		(1)
#define LOCKONGUI_TEXTTEX_DIVIDE_Y		(2)
#define LOCKONGUI_TEXTTEX_PATTERN		(2)
#define LOCKONGUI_TEXTTEX_SIZE_X		(90)
#define LOCKONGUI_TEXTTEX_SIZE_Y		(45)

#define LOCKONGUI_NUMTEX_SIZE_X			(23)
#define LOCKONGUI_NUMTEX_SIZE_Y			(23)
#define LOCKONGUI_NUMTEX_OFFSET_X		(-25.0f)
#define LOCKONGUI_NUMTEX_OFFSET_Y		(50)
#define LOCKONGUI_NUMTEX_BASE_X			(-30)

#define LOCKONGUI_BARTEX_NAME			"data/TEXTURE/UI/lockonBar.png"
#define LOCKONGUI_BARTEX_SIZE_X			(180.0f)
#define LOCKONGUI_BARTEX_SIZE_Y			(34.4f)
#define LOCKONGUI_BARTEX_OFFSET_Y		(50)

#define LOCKONGUI_MAXTEX_NAME			"data/TEXTURE/UI/lockonMax.png"
#define LOCKONGUI_MAXTEX_SIZE_X			(60)
#define LOCKONGUI_MAXTEX_SIZE_Y			(30)
#define LOCKONGUI_MAXTEX_OFFSET_Y		(50)
#define LOCKONGUI_MAXTEX_OFFSET_X		(40)

/**************************************
�\���̒�`
***************************************/
enum LOCKONGUI_STATE
{
	LOCKONGUI_LOCKABLE,
	LOCKONGUI_RECGARGE,
	LOCKONGUI_STATEMAX,
};
/**************************************
�O���[�o���ϐ�
***************************************/
static VERTEX_2D vtxWk[NUM_VERTEX];
static LPDIRECT3DTEXTURE9 textTexture, barTexture, maxTexture;
static LOCKONGUI lockonGUI[PLAYERMODEL_MAX];

/**************************************
�v���g�^�C�v�錾
***************************************/
void CreateVertexLockonGUI(void);
void SetLockonGUITextTexture(int id);
void SetLockonGUITextVertex(int id);
void SetLockonGUINumVertex(int id, float offset);
void SetLockonGUIBarVertex(int id);
void SetLockonGUIBarTexture(int id);
void SetLockonGUIMaxVertex(int id);
void SetLockonGUIMaxTexture(int id);

/**************************************
����������
***************************************/
void InitLockonGUI(int num)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	LOCKONGUI *ptr = &lockonGUI[0];

	if (num == 0)
	{
		CreateVertexLockonGUI();

		textTexture = CreateTextureFromFile((LPSTR)LOCKONGUI_TEXTTEX_NAME, pDevice);
		barTexture = CreateTextureFromFile((LPSTR)LOCKONGUI_BARTEX_NAME, pDevice);
		maxTexture = CreateTextureFromFile((LPSTR)LOCKONGUI_MAXTEX_NAME, pDevice);
	}

	for (int i = 0; i < PLAYERMODEL_MAX; i++, ptr++)
	{
		ptr->active = false;
	}
}

/**************************************
�I������
***************************************/
void UninitLockonGUI(int num)
{
	if (num == 0)
	{
		SAFE_RELEASE(textTexture);
		SAFE_RELEASE(barTexture);
	}
}

/**************************************
�X�V����
***************************************/
void UpdateLockonGUI(void)
{

}

/**************************************
�`�揈��
***************************************/
void DrawLockonGUI(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	LOCKONGUI *ptr = &lockonGUI[0];
	D3DXMATRIX mtxTranslate, mtxWorld;

	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < PLAYERMODEL_MAX; i++, ptr++)
	{
		if (!ptr->active)
		{
			continue;
		}

		//�e�L�X�g��`��
		pDevice->SetTexture(0, textTexture);
		SetLockonGUITextTexture(i);
		SetLockonGUITextVertex(i);
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, vtxWk, sizeof(VERTEX_2D));

		//���b�N�I������`��
		if (GetPlayerAdr(i)->atkInterbal >= PLAYER_HOMINGATK_INTERBAL)
		{
			int lockonNum = GetPlayerAdr(i)->lockonNum;
			int digitMax = (lockonNum == 0) ? 1 : (int)log10f((float)lockonNum) + 1;
			for (int j = 0; j < digitMax; j++, lockonNum /= 10)
			{
				SetLockonGUINumVertex(i, j * LOCKONGUI_NUMTEX_OFFSET_X * j);
				DrawGUINum(GUI_NUMLOCKON, lockonNum % 10, vtxWk);
			}

			pDevice->SetTexture(0, maxTexture);
			SetLockonGUIMaxVertex(i);
			SetLockonGUIMaxTexture(i);
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, vtxWk, sizeof(VERTEX_2D));
		}
		//���`���[�W�o�[��\��
		else
		{
			pDevice->SetTexture(0, barTexture);
			SetLockonGUIBarVertex(i);
			SetLockonGUIBarTexture(i);
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, vtxWk, sizeof(VERTEX_2D));
		}
	}

	pDevice->SetRenderState(D3DRS_LIGHTING, true);
}

/**************************************
���_�쐬����
***************************************/
void CreateVertexLockonGUI(void)
{
	vtxWk[0].rhw =
		vtxWk[1].rhw =
		vtxWk[2].rhw =
		vtxWk[3].rhw = 1.0f;

	vtxWk[0].diffuse =
		vtxWk[1].diffuse =
		vtxWk[2].diffuse =
		vtxWk[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	vtxWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	vtxWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	vtxWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	vtxWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);
}

/**************************************
���W�ݒ菈��
***************************************/
void SetLockonGUIPos(int id, D3DXVECTOR3 pos)
{
	LOCKONGUI *ptr = &lockonGUI[id];

	ptr->pos = pos;

	//�ݒ肵�����W���X�N���[�����W�֕ϊ�
	D3DXVec3TransformCoord(&ptr->pos, &ptr->pos, &GetBattleCameraView());
	D3DXVec3TransformCoord(&ptr->pos, &ptr->pos, &GetBattleCameraProjection());
	TranslateViewPort(&ptr->pos, &ptr->pos);
	ptr->pos.z = 0.0f;
}

/**************************************
�e�L�X�g�e�N�X�`���ݒ菈��
***************************************/
void SetLockonGUITextTexture(int id)
{
	PLAYERMODEL *player = GetPlayerAdr(id);

	int pattern = (player->atkInterbal >= PLAYER_HOMINGATK_INTERBAL) ? 0 : 1;
	float sizeY = 1.0f / LOCKONGUI_TEXTTEX_DIVIDE_Y;

	vtxWk[0].tex = D3DXVECTOR2(0.0f, sizeY * pattern);
	vtxWk[1].tex = D3DXVECTOR2(1.0f, sizeY * pattern);
	vtxWk[2].tex = D3DXVECTOR2(0.0f, sizeY * (pattern + 1));
	vtxWk[3].tex = D3DXVECTOR2(1.0f, sizeY * (pattern + 1));
}

/**************************************
�e�L�X�g���_�ݒ菈��
***************************************/
void SetLockonGUITextVertex(int id)
{
	LOCKONGUI *ptr = &lockonGUI[id];

	vtxWk[0].vtx = ptr->pos + D3DXVECTOR3(-LOCKONGUI_TEXTTEX_SIZE_X, -LOCKONGUI_TEXTTEX_SIZE_Y, 0.0f);
	vtxWk[1].vtx = ptr->pos + D3DXVECTOR3(LOCKONGUI_TEXTTEX_SIZE_X, -LOCKONGUI_TEXTTEX_SIZE_Y, 0.0f);
	vtxWk[2].vtx = ptr->pos + D3DXVECTOR3(-LOCKONGUI_TEXTTEX_SIZE_X, LOCKONGUI_TEXTTEX_SIZE_Y, 0.0f);
	vtxWk[3].vtx = ptr->pos + D3DXVECTOR3(LOCKONGUI_TEXTTEX_SIZE_X, LOCKONGUI_TEXTTEX_SIZE_Y, 0.0f);
}

/**************************************
�������_�ݒ菈��
***************************************/
void SetLockonGUINumVertex(int id, float offsetX)
{
	LOCKONGUI *ptr = &lockonGUI[id];

	vtxWk[0].vtx = ptr->pos + D3DXVECTOR3(-LOCKONGUI_NUMTEX_SIZE_X, -LOCKONGUI_NUMTEX_SIZE_Y, 0.0f);
	vtxWk[1].vtx = ptr->pos + D3DXVECTOR3(LOCKONGUI_NUMTEX_SIZE_X, -LOCKONGUI_NUMTEX_SIZE_Y, 0.0f);
	vtxWk[2].vtx = ptr->pos + D3DXVECTOR3(-LOCKONGUI_NUMTEX_SIZE_X, LOCKONGUI_NUMTEX_SIZE_Y, 0.0f);
	vtxWk[3].vtx = ptr->pos + D3DXVECTOR3(LOCKONGUI_NUMTEX_SIZE_X, LOCKONGUI_NUMTEX_SIZE_Y, 0.0f);

	for (int i = 0; i < NUM_VERTEX; i++)
	{
		vtxWk[i].vtx.x += offsetX + LOCKONGUI_NUMTEX_BASE_X;
		vtxWk[i].vtx.y += LOCKONGUI_NUMTEX_OFFSET_Y;
	}

}
/**************************************
�o�[���_�ݒ菈��
***************************************/
void SetLockonGUIBarVertex(int id)
{
	LOCKONGUI *ptr = &lockonGUI[id];
	PLAYERMODEL *player = GetPlayerAdr(id);

	float scale = (float)player->atkInterbal / PLAYER_HOMINGATK_INTERBAL;
	vtxWk[0].vtx = ptr->pos + D3DXVECTOR3(-LOCKONGUI_BARTEX_SIZE_X / 2.0f, -LOCKONGUI_BARTEX_SIZE_Y, 0.0f);
	vtxWk[1].vtx = vtxWk[0].vtx + D3DXVECTOR3(LOCKONGUI_BARTEX_SIZE_X * scale, 0.0f, 0.0f);
	vtxWk[2].vtx = vtxWk[0].vtx + D3DXVECTOR3(0.0f, LOCKONGUI_BARTEX_SIZE_Y, 0.0f);
	vtxWk[3].vtx = vtxWk[0].vtx + D3DXVECTOR3(LOCKONGUI_BARTEX_SIZE_X * scale, LOCKONGUI_BARTEX_SIZE_Y, 0.0f);

	for (int i = 0; i < NUM_VERTEX; i++)
	{
		vtxWk[i].vtx.y += LOCKONGUI_BARTEX_OFFSET_Y;
	}
}

/**************************************
�������_�ݒ菈��
***************************************/
void SetLockonGUIBarTexture(int id)
{
	LOCKONGUI *ptr = &lockonGUI[id];
	PLAYERMODEL *player = GetPlayerAdr(id);

	float scale = (float)player->atkInterbal / PLAYER_HOMINGATK_INTERBAL;
	vtxWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	vtxWk[1].tex = D3DXVECTOR2(scale, 0.0f);
	vtxWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	vtxWk[3].tex = D3DXVECTOR2(scale, 1.0f);
}

/**************************************
�}�b�N�X���_�ݒ菈��
***************************************/
void SetLockonGUIMaxVertex(int id)
{
	LOCKONGUI *ptr = &lockonGUI[id];
	vtxWk[0].vtx = ptr->pos + D3DXVECTOR3(-LOCKONGUI_MAXTEX_SIZE_X, -LOCKONGUI_MAXTEX_SIZE_Y, 0.0f);
	vtxWk[1].vtx = ptr->pos + D3DXVECTOR3(LOCKONGUI_MAXTEX_SIZE_X, -LOCKONGUI_MAXTEX_SIZE_Y, 0.0f);
	vtxWk[2].vtx = ptr->pos + D3DXVECTOR3(-LOCKONGUI_MAXTEX_SIZE_X, LOCKONGUI_MAXTEX_SIZE_Y, 0.0f);
	vtxWk[3].vtx = ptr->pos + D3DXVECTOR3(LOCKONGUI_MAXTEX_SIZE_X, LOCKONGUI_MAXTEX_SIZE_Y, 0.0f);

	for (int i = 0; i < NUM_VERTEX; i++)
	{
		vtxWk[i].vtx.y += LOCKONGUI_MAXTEX_OFFSET_Y;
		vtxWk[i].vtx.x += LOCKONGUI_MAXTEX_OFFSET_X;
	}
}

/**************************************
�}�b�N�X�e�N�X�`���ݒ菈��
***************************************/
void SetLockonGUIMaxTexture(int id)
{
	vtxWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	vtxWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	vtxWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	vtxWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);
}
/**************************************
���b�N�I��GUI�A�h���X�擾����
***************************************/
LOCKONGUI *GetLockonGUIAdr(int id)
{
	return &lockonGUI[id];
}