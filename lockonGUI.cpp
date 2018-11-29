//=====================================
//
//���b�N�I��GUI����[lockonGUI.cpp]
//Author:GP11A341 21 ���ԗY��
//
//=====================================
#include "lockonGUI.h"
#include "playerModel.h"
#include "battleCamera.h"

/**************************************
�}�N����`
***************************************/
#define LOCKONGUI_TEXTTEX_NAME			"data/TEXTURE/UI/lockonText.png"
#define LOCKONGUI_TEXTTEX_DIVIDE_X		(1)
#define LOCKONGUI_TEXTTEX_DIVIDE_Y		(2)
#define LOCKONGUI_TEXTTEX_PATTERN		(2)
#define LOCKONGUI_TEXTTEX_SIZE_X		(128)
#define LOCKONGUI_TEXTTEX_SIZE_Y		(64)

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
static LPDIRECT3DTEXTURE9 texture;
static LOCKONGUI lockonGUI[PLAYERMODEL_MAX];

/**************************************
�v���g�^�C�v�錾
***************************************/
void CreateVertexLockonGUI(void);
void SetLockonGUITextVertex(int id);

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

		texture = CreateTextureFromFile((LPSTR)LOCKONGUI_TEXTTEX_NAME, pDevice);
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
		SAFE_RELEASE(texture);
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
		pDevice->SetTexture(0, texture);
		SetLockonGUITextVertex(i);
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, vtxWk, sizeof(VERTEX_2D));
		
		
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
void SetLockonGUITextVertex(int id)
{
	PLAYERMODEL *player = GetPlayerAdr(id);
	LOCKONGUI *ptr = &lockonGUI[id];

	int pattern = (player->atkInterbal >= PLAYER_HOMINGATK_INTERBAL) ? 0 : 1;
	float sizeY = 1.0f / LOCKONGUI_TEXTTEX_DIVIDE_Y;

	vtxWk[0].tex = D3DXVECTOR2(0.0f, sizeY * pattern);
	vtxWk[1].tex = D3DXVECTOR2(1.0f, sizeY * pattern);
	vtxWk[2].tex = D3DXVECTOR2(0.0f, sizeY * (pattern + 1));
	vtxWk[3].tex = D3DXVECTOR2(1.0f, sizeY * (pattern + 1));

	vtxWk[0].vtx = ptr->pos + D3DXVECTOR3(-LOCKONGUI_TEXTTEX_SIZE_X, -LOCKONGUI_TEXTTEX_SIZE_Y, 0.0f);
	vtxWk[1].vtx = ptr->pos + D3DXVECTOR3(LOCKONGUI_TEXTTEX_SIZE_X, -LOCKONGUI_TEXTTEX_SIZE_Y, 0.0f);
	vtxWk[2].vtx = ptr->pos + D3DXVECTOR3(-LOCKONGUI_TEXTTEX_SIZE_X, LOCKONGUI_TEXTTEX_SIZE_Y, 0.0f);
	vtxWk[3].vtx = ptr->pos + D3DXVECTOR3(LOCKONGUI_TEXTTEX_SIZE_X, LOCKONGUI_TEXTTEX_SIZE_Y, 0.0f);
}

/**************************************
���b�N�I��GUI�A�h���X�擾����
***************************************/
LOCKONGUI *GetLockonGUIAdr(int id)
{
	return &lockonGUI[id];
}