//=====================================
//
//�X�J�CBG����[skyBG.cpp]
//Author:GP11A341 21 ���ԗY��
//
//=====================================
#include "skyBG.h"

/**************************************
�}�N����`
***************************************/
#define SKYBG_TEXNAME		"data/TEXTURE/skyBG.jpg"
#define SKYBG_MODELNAME		"data/MODEL/skyDome.x"

/**************************************
�\���̒�`
***************************************/

/**************************************
�O���[�o���ϐ�
***************************************/
static VERTEX_2D vtxWk[NUM_VERTEX];
static LPDIRECT3DTEXTURE9 texture = NULL;
static LPD3DXMESH mesh = NULL;
static LPD3DXBUFFER material = NULL;
static DWORD numMaterial = 0;
static D3DXMATRIX mtxWorld;

/**************************************
�v���g�^�C�v�錾
***************************************/
void MakeVertexSkyBG(void);

/**************************************
����������
***************************************/
void InitSkyBG(int num)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	if (num == 0)
	{
		if (FAILED(D3DXLoadMeshFromX(SKYBG_MODELNAME,
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&material,
			NULL,
			&numMaterial,
			&mesh
		)))
		{
			return;
		}

		texture = CreateTextureFromFile((LPSTR)SKYBG_TEXNAME, pDevice);
		//MakeVertexSkyBG();
	}
}

/**************************************
�I������
***************************************/
void UninitSkyBG(void)
{
	SAFE_RELEASE(texture);
	SAFE_RELEASE(mesh);
	SAFE_RELEASE(material);
}

/**************************************
�X�V����
***************************************/
void UpdateSkyBG(void)
{
	  
}

/**************************************
�`�揈��
***************************************/
void DrawSkyBG(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DMATERIAL9 mtrDefault;
	D3DXMATERIAL *pMat;

	//pDevice->SetRenderState(D3DRS_ZWRITEENABLE, false);

	pDevice->SetFVF(FVF_VERTEX_3D);

	pDevice->SetTexture(0, texture);

	D3DXMatrixIdentity(&mtxWorld);

	pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);
	
	pDevice->GetMaterial(&mtrDefault);

	pMat = (D3DXMATERIAL*)material->GetBufferPointer();

	for (int i = 0; i < (int)numMaterial; i++)
	{
		pDevice->SetMaterial(&pMat[i].MatD3D);

		mesh->DrawSubset(i);
	}

	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, true);
}

/**************************************
���_���쐬
***************************************/
void MakeVertexSkyBG(void)
{
	vtxWk[0].rhw =
		vtxWk[1].rhw =
		vtxWk[2].rhw =
		vtxWk[3].rhw = 1.0f;

	vtxWk[0].diffuse =
		vtxWk[1].diffuse =
		vtxWk[2].diffuse =
		vtxWk[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	vtxWk[0].vtx = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vtxWk[1].vtx = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
	vtxWk[2].vtx = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
	vtxWk[3].vtx = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

	vtxWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	vtxWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	vtxWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	vtxWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);


}