//=====================================
//
//�l�[���G���g���[BG����[nameEntryBG.cpp]
//Author:GP11A341 21 ���ԗY��
//
//=====================================
#include "nameEntryBG.h"

/**************************************
�}�N����`
***************************************/
#define NAMEENTRYBG_TEXTURE_NAME		"data/TEXTURE/nameEntryBG.jpg"
#define NAMEENTRYBG_VTX_NUM				(128)
#define NAMEENTRYBG_BLOCK_SIZE			(100.0f)


/**************************************
�\���̒�`
***************************************/

/**************************************
�O���[�o���ϐ�
***************************************/
static LPDIRECT3DTEXTURE9 texture;
static LPDIRECT3DVERTEXBUFFER9 vtxBuff;
static LPDIRECT3DINDEXBUFFER9 indexBuff;

static int numBlock;
static int numVertex;
static int numPolygon;
static int numIndex;
static float sizeX, sizeZ;
static float *heightMap;
static D3DXVECTOR3 rot;

/**************************************
�v���g�^�C�v�錾
***************************************/
void SetVertexBuffer(void);
void SetIndexBuffer(void);

/**************************************
����������
***************************************/
void InitNameEntryBG(int num)
{
	static bool initialized = false;

	if (!initialized)
	{
		LPDIRECT3DDEVICE9 pDevice = GetDevice();
		texture = CreateTextureFromFile((LPSTR)NAMEENTRYBG_TEXTURE_NAME, pDevice);

		//�e�p�����[�^�v�Z
		numBlock = NAMEENTRYBG_VTX_NUM - 1;
		numVertex = NAMEENTRYBG_VTX_NUM * NAMEENTRYBG_VTX_NUM;
		numIndex = (numBlock + 1) * 2 * numBlock + (numBlock - 1) * 2;
		numPolygon = numBlock * numBlock * 2 + (numBlock - 1) * 4;

		sizeX = sizeZ = NAMEENTRYBG_BLOCK_SIZE;

		//���_�o�b�t�@�쐬
		pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * numVertex,
			D3DUSAGE_WRITEONLY,
			FVF_VERTEX_3D,
			D3DPOOL_MANAGED,
			&vtxBuff,
			NULL);

		//�C���f�b�N�X�o�b�t�@�쐬
		pDevice->CreateIndexBuffer(sizeof(WORD) * numIndex,
			D3DUSAGE_WRITEONLY,
			D3DFMT_INDEX16,
			D3DPOOL_MANAGED,
			&indexBuff,
			NULL);

	}

	//���_�ψʖ@�ɂ�荂���}�b�v�𐶐�

	//���_�o�b�t�@�A�C���f�b�N�X�o�b�t�@��ݒ�
	SetVertexBuffer();
	SetIndexBuffer();
	initialized = true;
}

/**************************************
�I������
***************************************/
void UninitNameEntryBG(int num)
{
	if (num == 0)
	{
		SAFE_RELEASE(vtxBuff);
		SAFE_RELEASE(indexBuff);
		SAFE_RELEASE(texture);
	}
}

/**************************************
�X�V����
***************************************/
void UpdateNameEntryBG(void)
{

}

/**************************************
�`�揈��
***************************************/
void DrawNameEntryBG(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DXMATRIX mtxWorld, mtxRot;

	D3DXMatrixIdentity(&mtxWorld);

	D3DXMatrixRotationYawPitchRoll(&mtxRot, rot.y, rot.x, rot.y);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRot);

	pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);

	pDevice->SetFVF(FVF_VERTEX_3D);

	pDevice->SetStreamSource(0, vtxBuff, 0, sizeof(VERTEX_3D));

	pDevice->SetIndices(indexBuff);

	pDevice->SetTexture(0, texture);

	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, numVertex, 0, numPolygon);
}

/**************************************
���_�o�b�t�@�ݒ菈��
***************************************/
void SetVertexBuffer(void)
{
	VERTEX_3D *pVtx;

	const float texSize = 0.1f;

	vtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int z = 0; z < NAMEENTRYBG_VTX_NUM; z++)
	{
		for (int x = 0; x < NAMEENTRYBG_VTX_NUM; x++)
		{
			pVtx[x + z * NAMEENTRYBG_VTX_NUM].vtx.x = -(numBlock / 2.0f) * sizeX + x * sizeX;

			pVtx[x + z * NAMEENTRYBG_VTX_NUM].vtx.y = heightMap[x + z * NAMEENTRYBG_VTX_NUM];

			pVtx[x + z * NAMEENTRYBG_VTX_NUM].vtx.z = (numBlock)* sizeZ - z * sizeZ;

			pVtx[x + z * NAMEENTRYBG_VTX_NUM].diffuse = D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f);

			pVtx[x + z * NAMEENTRYBG_VTX_NUM].tex.x = texSize * x;
			pVtx[x + z * NAMEENTRYBG_VTX_NUM].tex.y = texSize * z;
		}
	}

	for (int z = 0; z < NAMEENTRYBG_VTX_NUM; z++)
	{
		for (int x = 0; x < NAMEENTRYBG_VTX_NUM; x++)
		{
			if (z == numBlock || x == numBlock)
			{
				pVtx[x + z * NAMEENTRYBG_VTX_NUM].nor = D3DXVECTOR3(0.0, 1.0f, 0.0);
			}
			else
			{
				D3DXVECTOR3 vec1 = pVtx[x + z * NAMEENTRYBG_VTX_NUM + 1].vtx - pVtx[x + z * NAMEENTRYBG_VTX_NUM].vtx;
				D3DXVECTOR3 vec2 = pVtx[x + (z + 1) * NAMEENTRYBG_VTX_NUM + 1].vtx - pVtx[x + z * NAMEENTRYBG_VTX_NUM].vtx;
				D3DXVECTOR3 normal;
				D3DXVec3Cross(&normal, &vec2, &vec1);
				D3DXVec3Normalize(&pVtx[x + z * NAMEENTRYBG_VTX_NUM].nor, &normal);
			}
		}
	}

	float minHeight = 0.0f;

	for (int i = 0; i < NAMEENTRYBG_VTX_NUM; i++)
	{
		for (int j = 0; j < NAMEENTRYBG_VTX_NUM; j++)
		{
			if (pVtx[i + j * NAMEENTRYBG_VTX_NUM].vtx.y < minHeight)
				minHeight = pVtx[i + j * NAMEENTRYBG_VTX_NUM].vtx.y;
		}
	}

	vtxBuff->Unlock();
}

/**************************************
�C���f�b�N�X�o�b�t�@�ݒ菈��
***************************************/
void SetIndexBuffer(void)
{
	WORD *pIdx;

	indexBuff->Lock(0, 0, (void**)&pIdx, 0);

	int cntIndex = 0;
	for (int z = 0; z < numBlock; z++)
	{
		if (z > 0)
		{
			pIdx[cntIndex] = (z + 1) * NAMEENTRYBG_VTX_NUM;
			cntIndex++;
		}

		for (int x = 0; x < NAMEENTRYBG_VTX_NUM; x++)
		{
			pIdx[cntIndex] = (z + 1) * NAMEENTRYBG_VTX_NUM + x;
			cntIndex++;
			pIdx[cntIndex] = z * NAMEENTRYBG_VTX_NUM + x;
			cntIndex++;
		}

		if (z < (numBlock - 1))
		{
			pIdx[cntIndex] = z * NAMEENTRYBG_VTX_NUM + numBlock;
			cntIndex++;
		}
	}

	indexBuff->Unlock();
}
