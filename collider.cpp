//=============================================================================
//
// �R���C�_�[���� [collider.cpp]
// Author : GP11A341 21 ���ԗY��
//
//=============================================================================
#include "collider.h"
/*****************************************************************************
�}�N����`
*****************************************************************************/

/*****************************************************************************
�\���̒�`
*****************************************************************************/

/*****************************************************************************
�O���[�o���ϐ�
*****************************************************************************/
static LPD3DXMESH meshSphere;		//���̃��b�V��
static D3DMATERIAL9 material;		//�����蔻��\���p�}�e���A��
static D3DMATERIAL9 matDef;			//�f�t�H���g�}�e���A��

/*****************************************************************************
����������
*****************************************************************************/
void InitCollider(int num)
{
	if (num == 0)
	{
		LPDIRECT3DDEVICE9 pDevice = GetDevice();

		//���b�V���쐬
		D3DXCreateSphere(pDevice,
			1.0f,
			8,
			8,
			&meshSphere,
			NULL);

		//�}�e���A���쐬
		ZeroMemory(&material, sizeof(material));
		material.Diffuse.r = 1.0f;
		material.Diffuse.g = 0.0f;
		material.Diffuse.b = 0.0f;
		material.Diffuse.a = 1.0f;

		material.Ambient.r = 1.0f;
		material.Ambient.g = 0.0f;
		material.Ambient.b = 0.0f;
		material.Ambient.a = 1.0f;

		material.Specular.r = 1.0f;
		material.Specular.g = 0.0f;
		material.Specular.b = 0.0f;
		material.Specular.a = 1.0f;

		material.Emissive.r = 1.0f;
		material.Emissive.g = 0.0f;
		material.Emissive.b = 0.0f;
		material.Emissive.a = 1.0f;

		//�f�t�H���g�}�e���A�����o�b�N�A�b�v
		pDevice->GetMaterial(&matDef);
	}
}

/*****************************************************************************
�I������
*****************************************************************************/
void UninitCollider(int num)
{
	if (num == 0)
	{
		SAFE_RELEASE(meshSphere);
	}
}

/*****************************************************************************
�o�E���f�B���O�X�t�B�A�`�揈��
*****************************************************************************/
void DrawBoundingSphere(D3DXVECTOR3 pos, float radius)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxTranslate, mtxScale, mtxWorld;

	//set renderstate & material
	pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	pDevice->SetMaterial(&material);

	//identify
	D3DXMatrixIdentity(&mtxWorld);

	//scaling
	D3DXMatrixScaling(&mtxScale, radius, radius, radius);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxScale);

	//translate
	D3DXMatrixTranslation(&mtxTranslate, pos.x, pos.y, pos.z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTranslate);
	
	//set world
	pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);

	//draw
	meshSphere->DrawSubset(0);

	//reset renderstate & material0
	pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	pDevice->SetMaterial(&matDef);
}

/*****************************************************************************
�֐���	�Fbool CheckHitTriangleAndLine(D3DXVECTOR3 start, D3DXVECTOR3 end, TRIANGLE tri, D3DXVECTOR3 *out)
����1	�FD3DXVECTOR3 start	�c�@�����̎n�_
����2	�FD3DXVECTOR3 end	�c�@�����̏I�_
����3	�FTRIANGLE tri		�c�@�O�p�`�|���S��
����4	�FD3DXVECTOR3 *out	�c�@��_���i�[����|�C���^
����	�F�����ƎO�p�`�|���S���̓����蔻��
*****************************************************************************/
bool CheckHitTriangleAndLine(D3DXVECTOR3 start, D3DXVECTOR3 end, TRIANGLE tri, D3DXVECTOR3 *out)
{
	//�����̎n�_�A�I�_�ƃt�B�[���h�̖@���x�N�g���Ƃ̓��ς��v�Z
	D3DXVECTOR3 v1 = start - tri.a;
	D3DXVECTOR3 v2 = end - tri.a;

	float dotV1 = D3DXVec3Dot(&tri.nor, &v1);
	float dotV2 = D3DXVec3Dot(&tri.nor, &v2);

	//���ʂƐ������������Ă��Ȃ�(���ϓ��m�̐ς̕��������ł���)�ꍇ�Afalse�����^�[��
	if (dotV1 * dotV2 > 0)
	{
		return false;
	}

	//�����ƕ��ʂ̌�_���v�Z
	D3DXVECTOR3 line = end - start;	//������\���x�N�g��

	float ratio = fabsf(dotV1) / (fabsf(dotV1) + fabsf(dotV2));

	float x = start.x + (line.x * ratio);	//x���W
	float y = start.y + (line.y * ratio);	//y���W
	float z = start.z + (line.z * ratio);	//z���W
	D3DXVECTOR3 p = D3DXVECTOR3(x, y, z);	//��_

	//��_���|���S���̈�����`�F�b�N
	D3DXVECTOR3 n1, n2, n3;

	D3DXVec3Cross(&n1, &(tri.b - tri.a), &(p - tri.a));	//�t�B�[���h�̕ӂƁA���_����_�x�N�g���̖@���x�N�g�����v�Z
	D3DXVec3Cross(&n2, &(tri.c - tri.b), &(p - tri.b));
	D3DXVec3Cross(&n3, &(tri.a - tri.c), &(p - tri.c));

	float dot_n12 = D3DXVec3Dot(&n1, &n2);
	float dot_n23 = D3DXVec3Dot(&n2, &n3);

	//�S�Ă̖@���x�N�g�������������i���ς����ɂȂ�Ȃ��j�ł���Ό�_�̓t�B�[���h���ɂ���
	if (dot_n12 >= 0 && dot_n23 >= 0)
	{
		*out = p;
		return true;
	}

	return false;
}

/*****************************************************************************
�֐���	�Fbool CheckHitTriangleAndLine(D3DXVECTOR3 start, D3DXVECTOR3 end, PLANE plane, D3DXVECTOR3 *out)
����1	�FD3DXVECTOR3 start	�c�@�����̎n�_
����2	�FD3DXVECTOR3 end	�c�@�����̏I�_
����3	�FTRIANGLE tri		�c�@�l�p�`�|���S�����a
����4	�FD3DXVECTOR3 *out	�c�@��_���i�[����|�C���^
����	�F�l�p�`�|���S���Ɛ����̓����蔻��
*****************************************************************************/
bool CheckHitPlaneAndLine(D3DXVECTOR3 start, D3DXVECTOR3 goal, PLANE plane, D3DXVECTOR3 *out)
{
	//�����̎n�_�A�I�_�ƃt�B�[���h�̖@���x�N�g���Ƃ̓��ς��v�Z
	D3DXVECTOR3 v1 = start - plane.topL;
	D3DXVECTOR3 v2 = goal - plane.topL;

	float dotV1 = D3DXVec3Dot(&D3DXVECTOR3(0, 1, 0), &v1);
	float dotV2 = D3DXVec3Dot(&D3DXVECTOR3(0, 1, 0), &v2);

	//���ʂƐ������������Ă��Ȃ�(���ϓ��m�̐ς̕��������ł���)�ꍇ�Afalse�����^�[��
	if (dotV1 * dotV2 > 0)
	{
		return false;
	}

	//�����ƕ��ʂ̌�_���v�Z
	D3DXVECTOR3 line = goal - start;	//������\���x�N�g��

	float ratio = fabsf(dotV1) / (fabsf(dotV1) + fabsf(dotV2));

	float x = start.x + (line.x * ratio);	//x���W
	float y = start.y + (line.y * ratio);	//y���W
	float z = start.z + (line.z * ratio);	//z���W
	D3DXVECTOR3 p = D3DXVECTOR3(x, y, z);			//��_

											//��_���|���S���̈�����`�F�b�N
	D3DXVECTOR3 n1, n2, n3, n4;

	D3DXVec3Cross(&n1, &(plane.bottomL - plane.topL), &(p - plane.bottomL));	//�t�B�[���h�̕ӂƁA���_����_�x�N�g���̖@���x�N�g�����v�Z
	D3DXVec3Cross(&n2, &(plane.bottomR - plane.bottomL), &(p - plane.bottomR));
	D3DXVec3Cross(&n3, &(plane.topR - plane.bottomR), &(p - plane.topR));
	D3DXVec3Cross(&n4, &(plane.topL- plane.topR), &(p - plane.topL));

	float dot_n12 = D3DXVec3Dot(&n1, &n2);
	float dot_n23 = D3DXVec3Dot(&n2, &n3);
	float dot_n34 = D3DXVec3Dot(&n3, &n4);

	//�S�Ă̖@���x�N�g�������������i���ς����ɂȂ�Ȃ��j�ł���Ό�_�̓t�B�[���h���ɂ���
	if (dot_n12 >= 0 && dot_n23 >= 0 && dot_n34 >= 0)
	{
		*out = p;
		return true;
	}

	return false;
}

/*****************************************************************************
�֐���	�Fbool CheckHitTriangleAndLine(D3DXVECTOR3 start, D3DXVECTOR3 end, PLANE plane, D3DXVECTOR3 *out)
����1	�FD3DXVECTOR3 start	�c�@�����̎n�_
����2	�FD3DXVECTOR3 end	�c�@�����̏I�_
����3	�FTRIANGLE tri		�c�@�l�p�`�|���S�����a
����4	�FD3DXVECTOR3 *out	�c�@��_���i�[����|�C���^
����	�F�l�p�`�|���S���Ɛ����̓����蔻��
*****************************************************************************/
bool ChechHitBoundingSphere(SPHERE s1, SPHERE s2)
{
	if (!s1.active || !s2.active)
	{
		return false;
	}

	D3DXVECTOR3 d = (s2.pos - s1.pos);
	float lenghtSq = D3DXVec3LengthSq(&d);

	return (lenghtSq > (s1.radius + s2.radius) * (s1.radius + s2.radius)) ? false : true;
}