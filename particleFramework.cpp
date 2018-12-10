//=====================================
//
//�p�[�e�B�N���t���[�����[�N����[particleFramework.cpp]
//Author:GP11A341 21 ���ԗY��
//
//=====================================
#include "particleFramework.h"

/**************************************
�P�ʒ��_�o�b�t�@�쐬����
***************************************/
void MakeParticleVertexBuffer(VERTEX_PARTICLE *vtx, float particleSize, LPDIRECT3DVERTEXBUFFER9 *buff)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_PARTICLE) * NUM_VERTEX,
		D3DUSAGE_WRITEONLY,
		0,
		D3DPOOL_MANAGED,
		buff,
		NULL)))
	{
		return;
	}

	//vtx[0] = { -particleSize, particleSize, 0.0f, 0.0f, 0.0f };
	//vtx[1] = { particleSize, particleSize, 0.0f, 1.0f, 0.0f };
	//vtx[2] = { -particleSize, -particleSize, 0.0f, 0.0f, 1.0f };
	//vtx[3] = { particleSize, -particleSize, 0.0f, 1.0f, 1.0f };

	CopyVtxBuff(sizeof(VERTEX_PARTICLE) * NUM_VERTEX, vtx, *buff);
}
/**************************************
UV���_�o�b�t�@�쐬����
***************************************/
void MakeParticleUVBuffer(int size, VERTEX_UV *uv, LPDIRECT3DVERTEXBUFFER9 *buff)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_UV) * size,
		D3DUSAGE_WRITEONLY,
		0,
		D3DPOOL_MANAGED,
		buff,
		NULL)))
	{
		return;
	}

	VERTEX_UV *ptr = uv;
	for (int i = 0; i < size; i++, ptr++)
	{
		ptr->u = ptr->v = 0.0f;
	}

	CopyVtxBuff(sizeof(VERTEX_UV) * size, uv, *buff);
}

/**************************************
���[���h�ϊ��o�b�t�@�쐬����
***************************************/
void MakeParticleWorldBuffer(int size, D3DXMATRIX *world, LPDIRECT3DVERTEXBUFFER9 *buff)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	if (FAILED(pDevice->CreateVertexBuffer(sizeof(D3DXMATRIX) * size,
		D3DUSAGE_WRITEONLY,
		0,
		D3DPOOL_MANAGED,
		buff,
		NULL)))
	{
		return;
	}

	D3DXMATRIX *ptr = world;
	for (int i = 0; i < size; i++, ptr++)
	{
		//D3DXMatrixIdentity(ptr);
	}

	CopyVtxBuff(sizeof(D3DXMATRIX) * size, world, *buff);
}

/**************************************
�J���[�o�b�t�@�쐬����
***************************************/
void MakeParticleColorBuffer(int size, VERTEX_COLOR *color, LPDIRECT3DVERTEXBUFFER9 *buff)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_COLOR) * size,
		D3DUSAGE_WRITEONLY,
		0,
		D3DPOOL_MANAGED,
		buff,
		NULL)))
	{
		return;
	}

	VERTEX_COLOR *ptr = color;
	for (int i = 0; i < size; i++, ptr++)
	{
		//ptr->r = ptr->g = ptr->b = 1.0f;
		//ptr->a = 0.0f;
	}

	CopyVtxBuff(sizeof(VERTEX_COLOR), color, *buff);

}
