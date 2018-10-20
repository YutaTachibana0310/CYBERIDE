//==========================================
//
//�_����[cloud.cpp]
//Author:GP11A341 21 ���ԗY��
//
//==========================================
#include "cloud.h"

/******************************************
�}�N����`
*******************************************/
#define CLOUD_TEXNAME		"data/TEXTURE/cloud.png"
#define CLOUD_SIZE			(1024)

/******************************************
�\���̒�`
*******************************************/

/******************************************
�v���g�^�C�v�錾
*******************************************/
void MakeVertexCloud(void);
void SetTextureCloud(void);

/******************************************
�O���[�o���ϐ�
*******************************************/
static const int widthTex = 512;
static const int heightTex = 512;

static LPDIRECT3DTEXTURE9 texture = NULL;
static LPDIRECT3DVERTEXBUFFER9 vtxBuff = NULL;
static D3DXMATRIX mtxWorld;
static D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 500.0f, 1000.0f);

#if 0
static LPDIRECT3DSURFACE9 surface = NULL;
static LPDIRECT3DSURFACE9 depthSurface = NULL;
static LPDIRECT3DSURFACE9 defaultSurface = NULL;
static LPDIRECT3DSURFACE9 defaultDepth = NULL;
#endif

/******************************************
����������
*******************************************/
void InitCloud(int num)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	if (num == 0)
	{
		texture = CreateTextureFromFile((LPSTR)CLOUD_TEXNAME, pDevice);
#if 0
		pDevice->GetRenderTarget(0, &defaultSurface);
		pDevice->GetDepthStencilSurface(&defaultDepth); 

		//�e�N�X�`���쐬
		if (FAILED(D3DXCreateTexture(
			pDevice,
			widthTex,
			heightTex,
			0,
			D3DUSAGE_RENDERTARGET,
			D3DFMT_A8R8G8B8,
			D3DPOOL_DEFAULT,
			&texture)))
		{
			return;
		}

		//�[�x�o�b�t�@�쐬
		if (FAILED(pDevice->CreateDepthStencilSurface(
			widthTex,
			heightTex,
			D3DFMT_D16,
			D3DMULTISAMPLE_NONE,
			0,
			true,
			&depthSurface,
			NULL
		)))
		{
			return;
		}
#endif
	}

	MakeVertexCloud();


}

/******************************************
�I������
*******************************************/
void UninitCloud(void)
{
	SAFE_RELEASE(texture);
}

/******************************************
�X�V����
*******************************************/
void UpdateCloud(void)
{
	SetTextureCloud();
}

/******************************************
�`�揈��
*******************************************/
void DrawCloud(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTranslate;

	//pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	pDevice->SetFVF(FVF_VERTEX_3D);

	pDevice->SetTexture(0, texture);

	D3DXMatrixIdentity(&mtxWorld);

	D3DXMatrixTranslation(&mtxTranslate, pos.x, pos.y, pos.z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTranslate);

	pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);

	pDevice->SetStreamSource(0, vtxBuff, 0, sizeof(VERTEX_3D));

	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);

	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

/******************************************
���_���쐬
*******************************************/
void MakeVertexCloud(void)
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

	pVtx[0].vtx = pos + D3DXVECTOR3(-CLOUD_SIZE, 0.0f, -CLOUD_SIZE);
	pVtx[1].vtx = pos + D3DXVECTOR3(CLOUD_SIZE, 0.0f, -CLOUD_SIZE);
	pVtx[2].vtx = pos + D3DXVECTOR3(-CLOUD_SIZE, 0.0f, CLOUD_SIZE);
	pVtx[3].vtx = pos + D3DXVECTOR3(CLOUD_SIZE, 0.0f, CLOUD_SIZE);

	pVtx[0].nor =
		pVtx[1].nor =
		pVtx[2].nor =
		pVtx[3].nor = D3DXVECTOR3(0.0f, -1.0f, 0.0f);

	pVtx[0].diffuse =
		pVtx[1].diffuse =
		pVtx[2].diffuse =
		pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	vtxBuff->Unlock();

	return;
}

/******************************************
�e�N�X�`�����W�ݒ�
*******************************************/
void  SetTextureCloud(void)
{
	static float offset = 0.0f;
	VERTEX_3D *pVtx;

	vtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	offset += 0.1f;

	if (offset > 5.0f)
	{
		offset -=5.0f;
	}

	pVtx[0].tex = D3DXVECTOR2(0.0f, offset);
	pVtx[1].tex = D3DXVECTOR2(5.0f, offset);
	pVtx[2].tex = D3DXVECTOR2(0.0f, offset + 5.0f);
	pVtx[3].tex = D3DXVECTOR2(5.0f, offset + 5.0f);

	vtxBuff->Unlock();
}
