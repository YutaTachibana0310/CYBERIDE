//=====================================
//
//�e���v���[�g����[targetSite.cpp]
//Author:GP11A341 21 ���ԗY��
//
//=====================================
#include "targetSite.h"
#include "playerModel.h"
#include "battleCamera.h"

/**************************************
�}�N����`
***************************************/
#define TARGETSITE_SIZE		(28)
#define TARGETSITE_TEXTURE	"data/TEXTURE/targetSite.png"
#define TARGETSITE_MAX		PLAYERMODEL_MAX

/**************************************
�\���̒�`
***************************************/

/**************************************
�O���[�o���ϐ�
***************************************/
static LPDIRECT3DVERTEXBUFFER9 vtxBuff;
static LPDIRECT3DTEXTURE9 texture;
static D3DXMATRIX mtxWorld;

static TARGETSITE targetSite[TARGETSITE_MAX];

/**************************************
�v���g�^�C�v�錾
***************************************/
void MakeVertexTargetSite(void);

/**************************************
����������
***************************************/
void InitTargetSite(int num)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	if (num == 0)
	{
		texture = CreateTextureFromFile((LPSTR)TARGETSITE_TEXTURE, pDevice);

		MakeVertexTargetSite();
	}

	TARGETSITE *ptr = &targetSite[0];
	for (int i = 0; i < TARGETSITE_MAX; i++, ptr++)
	{
		ptr->pos = D3DXVECTOR3(9999.9f, 9999.9f, -9999.9f);
	}
}

/**************************************
�I������
***************************************/
void UninitTargetSite(int num)
{
	TARGETSITE *ptr = &targetSite[0];
	for (int i = 0; i < TARGETSITE_MAX; i++, ptr++)
	{
		ptr->pos = D3DXVECTOR3(9999.9f, 9999.9f, -9999.9f);
	}

	if (num == 0)
	{
		SAFE_RELEASE(texture);
		SAFE_RELEASE(vtxBuff);
	}
}

/**************************************
�X�V����
***************************************/
void UpdateTargetSite(void)
{

}

/**************************************
�`�揈��
***************************************/
void DrawTargetSite(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTranslate;

	pDevice->SetFVF(FVF_VERTEX_3D);

	pDevice->SetTexture(0, texture);

	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, true);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	pDevice->SetRenderState(D3DRS_LIGHTING, false);
	pDevice->SetRenderState(D3DRS_LIGHTING, false);

	TARGETSITE *ptr = &targetSite[0];
	for (int i = 0; i < TARGETSITE_MAX; i++, ptr++)
	{
		if (!ptr->active)
		{
			continue;
		}

		D3DXMatrixIdentity(&mtxWorld);

		GetInvRotBattleCamera(&mtxWorld);

		D3DXMatrixTranslation(&mtxTranslate, ptr->pos.x, ptr->pos.y, ptr->pos.z);
		D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTranslate);

		pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);

		pDevice->SetStreamSource(0, vtxBuff, 0, sizeof(VERTEX_3D));

		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);
	}

	pDevice->SetRenderState(D3DRS_LIGHTING, true);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, true);
}

/**************************************
���_�쐬����
***************************************/
void MakeVertexTargetSite(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * NUM_VERTEX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&vtxBuff,
		NULL)))
	{
		return;
	}

	VERTEX_3D *pVtx;

	vtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].vtx = D3DXVECTOR3(-TARGETSITE_SIZE, TARGETSITE_SIZE, 0.0f);
	pVtx[1].vtx = D3DXVECTOR3(TARGETSITE_SIZE, TARGETSITE_SIZE, 0.0f);
	pVtx[2].vtx = D3DXVECTOR3(-TARGETSITE_SIZE, -TARGETSITE_SIZE, 0.0f);
	pVtx[3].vtx = D3DXVECTOR3(TARGETSITE_SIZE, -TARGETSITE_SIZE, 0.0f);

	pVtx[0].nor =
		pVtx[1].nor =
		pVtx[2].nor =
		pVtx[3].nor = D3DXVECTOR3(0.0f, -1.0f, 1.0f);

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	vtxBuff->Unlock();

	return;
}

/**************************************
���W�Z�b�g����
***************************************/
void SetTargetSitePosition(D3DXVECTOR3 pos, int id)
{
	targetSite[id].pos = pos;
}

/**************************************
�A�h���X�擾����
***************************************/
TARGETSITE *GetTargetSiteADr(int id)
{
	return &targetSite[id];
}