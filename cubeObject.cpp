//=====================================
//
//�L���[�u�I�u�W�F�N�g����[cubeObject.cpp]
//Author:GP11A341 21 ���ԗY��
//
//=====================================
#include "cubeObject.h"
#include "playerBullet.h"
#include "targetSite.h"
#include "playerModel.h"
#include "particleManager.h"
#include "cameraShaker.h"

/**************************************
�}�N����`
***************************************/
#define CUBEOBJECT_EFFECT_NAME			"data/EFFECT/cubeObject.fx"
#define CUBEOBJECT_SIZE					(10.0f)
#define CUBEOBJECT_VTX_NUM				(24)
#define CUBEOBJECT_NUM_MAX				(2048)
#define CUBEOBJECT_FIELD_NUM			(6)

static const char* texName[] = {
	"data/TEXTURE/OBJECT/circuit00.jpg",
	"data/TEXTURE/OBJECT/circuit04.png",
	"data/TEXTURE/OBJECT/circuit05.png",
};

/**************************************
�\���̒�`
***************************************/
typedef struct
{
	float posX, posY, posZ;
	float texU, texV;
	float norX, norY, norZ;
}CUBE_VTX;

/**************************************
�O���[�o���ϐ�
***************************************/
//�L���[�u�I�u�W�F�N�g�̒P�ʒ��_
static CUBE_VTX vtx[CUBEOBJECT_VTX_NUM] = {
	//��
	{ -CUBEOBJECT_SIZE, CUBEOBJECT_SIZE, CUBEOBJECT_SIZE, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f },
	{ CUBEOBJECT_SIZE, CUBEOBJECT_SIZE, CUBEOBJECT_SIZE, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f },
	{ -CUBEOBJECT_SIZE, CUBEOBJECT_SIZE,-CUBEOBJECT_SIZE, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f },
	{ CUBEOBJECT_SIZE, CUBEOBJECT_SIZE,-CUBEOBJECT_SIZE, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f },
	//�O
	{ -CUBEOBJECT_SIZE, CUBEOBJECT_SIZE,-CUBEOBJECT_SIZE, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f },
	{ CUBEOBJECT_SIZE, CUBEOBJECT_SIZE,-CUBEOBJECT_SIZE, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f },
	{ -CUBEOBJECT_SIZE,-CUBEOBJECT_SIZE,-CUBEOBJECT_SIZE, 0.0f, 1.0f, 0.0f, 0.0f, -1.0f },
	{ CUBEOBJECT_SIZE,-CUBEOBJECT_SIZE,-CUBEOBJECT_SIZE, 1.0f, 1.0f, 0.0f, 0.0f, -1.0f },
	//��
	{ -CUBEOBJECT_SIZE,-CUBEOBJECT_SIZE,-CUBEOBJECT_SIZE, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f },
	{ CUBEOBJECT_SIZE,-CUBEOBJECT_SIZE,-CUBEOBJECT_SIZE, 1.0f, 0.0f, 0.0f, -1.0f, 0.0f },
	{ -CUBEOBJECT_SIZE,-CUBEOBJECT_SIZE, CUBEOBJECT_SIZE, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f },
	{ CUBEOBJECT_SIZE,-CUBEOBJECT_SIZE, CUBEOBJECT_SIZE, 1.0f, 1.0f, 0.0f, -1.0f, 0.0f },
	//���
	{ CUBEOBJECT_SIZE, CUBEOBJECT_SIZE, CUBEOBJECT_SIZE, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f },
	{ -CUBEOBJECT_SIZE, CUBEOBJECT_SIZE, CUBEOBJECT_SIZE, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f },
	{ CUBEOBJECT_SIZE,-CUBEOBJECT_SIZE, CUBEOBJECT_SIZE, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f },
	{ -CUBEOBJECT_SIZE,-CUBEOBJECT_SIZE, CUBEOBJECT_SIZE, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f },
	//��
	{ -CUBEOBJECT_SIZE, CUBEOBJECT_SIZE, CUBEOBJECT_SIZE, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f },
	{ -CUBEOBJECT_SIZE, CUBEOBJECT_SIZE,-CUBEOBJECT_SIZE, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f },
	{ -CUBEOBJECT_SIZE,-CUBEOBJECT_SIZE, CUBEOBJECT_SIZE, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f },
	{ -CUBEOBJECT_SIZE,-CUBEOBJECT_SIZE,-CUBEOBJECT_SIZE, 1.0f, 1.0f, -1.0f, 0.0f, 0.0f },
	//�E
	{ CUBEOBJECT_SIZE, CUBEOBJECT_SIZE,-CUBEOBJECT_SIZE, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f },
	{ CUBEOBJECT_SIZE, CUBEOBJECT_SIZE, CUBEOBJECT_SIZE, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f },
	{ CUBEOBJECT_SIZE,-CUBEOBJECT_SIZE,-CUBEOBJECT_SIZE, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f },
	{ CUBEOBJECT_SIZE,-CUBEOBJECT_SIZE, CUBEOBJECT_SIZE, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f },
};

static LPDIRECT3DVERTEXBUFFER9 vtxBuff, worldBuff;		//���_�o�b�t�@
static LPDIRECT3DVERTEXDECLARATION9 declare;			//���_�錾
static LPDIRECT3DTEXTURE9 texture[3];					//�e�N�X�`��
static LPD3DXEFFECT effect;								//�V�F�[�_
static LPDIRECT3DINDEXBUFFER9 indexBuff;				//�C���f�b�N�X�o�b�t�@

static D3DXVECTOR3 pos[CUBEOBJECT_NUM_MAX], rot[CUBEOBJECT_NUM_MAX];	//�L���[�u�̊e�p�����[�^
static D3DXMATRIX mtxWorld[CUBEOBJECT_NUM_MAX];			//���[���h�ϊ��s��

//static D3DXVECTOR3 rotValue[CUBEOBJECT_NUM_MAX];		//�e�L���[�u�̉�]��
//static float cubeSpeed[CUBEOBJECT_NUM_MAX];				//�e�L���[�u�̈ړ��X�s�[�h
static CUBE_OBJECT cube[CUBEOBJECT_NUM_MAX];			//�L���[�u�I�u�W�F�N�g�z��
/**************************************
�v���g�^�C�v�錾
***************************************/
void MoveCubeObject(void);					//�ړ�����
void RotationCubeObject(void);				//��]����
void CalcCubeObjectWorldMartix(void);		//���[���h�ϊ��s��v�Z����
void CheckDestroyCubeObject(void);			//���S����

/**************************************
����������
***************************************/
void InitCubeObject(int num)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�L���[�u�����͈�
	const float PosRange = 150.0f;
	const float RotRange = 5.0f;

	//�p�����[�^������
	CUBE_OBJECT *ptr = &cube[0];
	for (int i = 0; i < CUBEOBJECT_NUM_MAX; i++, ptr++)
	{
		pos[i] = D3DXVECTOR3(RandomRangef(-PosRange, PosRange), RandomRangef(-PosRange, PosRange), RandomRangef(0.0f, 20000.0f));
		rot[i] = D3DXVECTOR3(RandomRangef(0.0f, 3.1415f), RandomRangef(0.0f, 3.1415f), RandomRangef(0.0f, 3.1415f));
		ptr->rotValue = D3DXVECTOR3(RandomRangef(-RotRange, RotRange), RandomRangef(-RotRange, RotRange), RandomRangef(-RotRange, RotRange));
		ptr->rotValue *= 0.01f;
		ptr->moveSpeed = RandomRangef(-10.0f, -5.0f);
		ptr->hp = 1.0f;
		ptr->active = true;

		ptr->collider.pos = &pos[i];
		ptr->collider.offset = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		ptr->collider.length = D3DXVECTOR3(CUBEOBJECT_SIZE*1.5f, CUBEOBJECT_SIZE*1.5f, CUBEOBJECT_SIZE*1.5f);
	}

	//����݂̂̏�����
	if (num == 0)
	{
		//���_�o�b�t�@�쐬
		pDevice->CreateVertexBuffer(sizeof(vtx), 0, 0, D3DPOOL_MANAGED, &vtxBuff, 0);
		pDevice->CreateVertexBuffer(sizeof(mtxWorld), 0, 0, D3DPOOL_MANAGED, &worldBuff, 0);
		CopyVtxBuff(sizeof(vtx), vtx, vtxBuff);
		CopyVtxBuff(sizeof(mtxWorld), mtxWorld, worldBuff);

		//���_�錾�쐬
		D3DVERTEXELEMENT9 declareElems[] =
		{
			{ 0, 0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },		//���_���W
			{ 0, 12, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0 },		//UV���W
			{ 0, 20, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL, 0 },		//�@��
			{ 1, 0, D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 1 },		//���[���h�ϊ��s��
			{ 1, 16, D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 2 },		//���[���h�ϊ��s��
			{ 1, 32, D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 3 },		//���[���h�ϊ��s��
			{ 1, 48, D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 4 },		//���[���h�ϊ��s��
			D3DDECL_END()
		};
		pDevice->CreateVertexDeclaration(declareElems, &declare);

		//�C���f�b�N�X�o�b�t�@�쐬
		WORD index[6 * CUBEOBJECT_FIELD_NUM];
		for (int i = 0; i < 6; i++)
		{
			index[i * 6] = i * NUM_VERTEX;
			index[i * 6 + 1] = i * NUM_VERTEX + 1;
			index[i * 6 + 2] = i * NUM_VERTEX + 2;
			index[i * 6 + 3] = i * NUM_VERTEX + 2;
			index[i * 6 + 4] = i * NUM_VERTEX + 1;
			index[i * 6 + 5] = i * NUM_VERTEX + 3;
		}

		pDevice->CreateIndexBuffer(sizeof(index), 0, D3DFMT_INDEX16, D3DPOOL_MANAGED, &indexBuff, 0);
		void *p = NULL;
		indexBuff->Lock(0, 0, &p, 0);
		memcpy(p, index, sizeof(index));
		indexBuff->Unlock();

		//�V�F�[�_�[�ǂݍ���
		D3DXCreateEffectFromFile(pDevice, CUBEOBJECT_EFFECT_NAME, 0, 0, 0, 0, &effect, NULL);

		//�e�N�X�`���ǂݍ���
		for (int i = 0; i < 3; i++)
		{
			D3DXCreateTextureFromFile(pDevice, texName[i], &texture[i]);
		}
	}
}

/**************************************
�I������
***************************************/
void UninitCubeObject(int num)
{
	if (num == 0)
	{
		SAFE_RELEASE(vtxBuff);
		SAFE_RELEASE(worldBuff);
		SAFE_RELEASE(effect);
		SAFE_RELEASE(declare);
		SAFE_RELEASE(indexBuff);

		for (int i = 0; i < 3; i++)
		{
			SAFE_RELEASE(texture[i]);
		}
	}
}

/**************************************
�X�V����
***************************************/
void UpdateCubeObject(void)
{
	CheckDestroyCubeObject();

	MoveCubeObject();

	RotationCubeObject();

	CalcCubeObjectWorldMartix();
}

/**************************************
�`�揈��
***************************************/
void DrawCubeObject(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DLIGHT9 light1, light2, light3;

	pDevice->GetLight(0, &light1);
	pDevice->GetLight(0, &light2);
	pDevice->GetLight(0, &light3);

	pDevice->SetStreamSourceFreq(0, D3DSTREAMSOURCE_INDEXEDDATA | (CUBEOBJECT_NUM_MAX));
	pDevice->SetStreamSourceFreq(1, D3DSTREAMSOURCE_INSTANCEDATA | 1);

	pDevice->SetVertexDeclaration(declare);
	pDevice->SetStreamSource(0, vtxBuff, 0, sizeof(CUBE_VTX));
	pDevice->SetStreamSource(1, worldBuff, 0, sizeof(D3DXMATRIX));
	pDevice->SetIndices(indexBuff);

	effect->SetMatrix("mtxView", &GetBattleCameraView());
	effect->SetMatrix("mtxProj", &GetBattleCameraProjection());
	effect->SetFloatArray("light1Dir", (float*)&light1.Direction, 3);
	effect->SetFloatArray("light1Diffuse", (float*)&light1.Diffuse, 4);
	effect->SetFloatArray("light1Ambient", (float*)&light1.Ambient, 4);

	effect->SetFloatArray("light2Dir", (float*)&light2.Direction, 3);
	effect->SetFloatArray("light2Diffuse", (float*)&light2.Diffuse, 4);
	effect->SetFloatArray("light2Ambient", (float*)&light2.Ambient, 4);

	effect->SetFloatArray("light3Dir", (float*)&light3.Direction, 3);
	effect->SetFloatArray("light3Diffuse", (float*)&light3.Diffuse, 4);
	effect->SetFloatArray("light3Ambient", (float*)&light3.Ambient, 4);

	for (int i = 0; i < 3; i++)
	{
		if (i == 0)
			pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
		else
			pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

		effect->SetTexture("tex", texture[i]);
		effect->SetTechnique("tech");
		UINT passNum = 0;
		effect->Begin(&passNum, 0);
		effect->BeginPass(0);

		pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, CUBEOBJECT_VTX_NUM, 0, CUBEOBJECT_FIELD_NUM * NUM_POLYGON);

		effect->EndPass();
		effect->End();
	}
	pDevice->SetStreamSourceFreq(0, 1);
	pDevice->SetStreamSourceFreq(1, 1);

#ifdef _DEBUG
	CUBE_OBJECT *ptr = &cube[0];
	for (int i = 0; i < CUBEOBJECT_NUM_MAX; i++, ptr++)
	{
		DrawBoundingCube(&ptr->collider);
	}
#endif

}

/**************************************
�ړ�����
***************************************/
void MoveCubeObject(void)
{
	D3DXVECTOR3 *pPos = &pos[0];
	CUBE_OBJECT *ptr = &cube[0];
	for (int i = 0; i < CUBEOBJECT_NUM_MAX; i++, ptr++, pPos++)
	{
		pPos->z += ptr->moveSpeed;
		if (pPos->z < 0.0f)
		{
			pPos->z = 2500.0f;
		}
	}
}

/**************************************
��]����
***************************************/
void RotationCubeObject(void)
{
	D3DXVECTOR3 *pRot = &rot[0];
	CUBE_OBJECT *ptr = &cube[0];
	for (int i = 0; i < CUBEOBJECT_NUM_MAX; i++, ptr++, pRot++)
	{
		*pRot += ptr->rotValue;
	}
}

/**************************************
���[���h�ϊ��s��v�Z����
***************************************/
void CalcCubeObjectWorldMartix(void)
{
	D3DXMATRIX *pWorld = &mtxWorld[0];
	D3DXMATRIX mtxRot, mtxTranslate;
	D3DXVECTOR3 *pPos = &pos[0];
	D3DXVECTOR3 *pRot = &rot[0];

	for (int i = 0; i < CUBEOBJECT_NUM_MAX; i++, pPos++, pRot++, pWorld++)
	{
		D3DXMatrixIdentity(pWorld);

		D3DXMatrixRotationYawPitchRoll(&mtxRot, pRot->y, pRot->x, pRot->z);
		D3DXMatrixMultiply(pWorld, pWorld, &mtxRot);

		D3DXMatrixTranslation(&mtxTranslate, pPos->x, pPos->y, pPos->z);
		D3DXMatrixMultiply(pWorld, pWorld, &mtxTranslate);
	}

	CopyVtxBuff(sizeof(mtxWorld), mtxWorld, worldBuff);
}

/**************************************
���S����
***************************************/
void CheckDestroyCubeObject(void)
{
	CUBE_OBJECT *ptr = &cube[0];
	D3DXVECTOR3 *pPos = &pos[0];
	for (int i = 0; i < CUBEOBJECT_NUM_MAX; i++, ptr++, pPos++)
	{
		if (ptr->hp <= 0.0f)
		{
			SetCubeExplosion(*pPos);

			ptr->hp = 1.0f;
			pPos->z = 20000.0f;
			ptr->active = true;
		}
	}
}

/**************************************
�����蔻��
***************************************/
void CollisionCubeObjectAndBullet(void)
{
	CUBE_OBJECT *ptr = &cube[0];
	PLAYERBULLET *bullet = GetPlayerBulletAdr(0);
	D3DXVECTOR3 *cubePos = &pos[0];

	for (int i = 0; i < CUBEOBJECT_NUM_MAX; i++, ptr++, cubePos++)
	{
		if (!ptr->active)
		{
			continue;
		}

		bullet = GetPlayerBulletAdr(0);
		for (int j = 0; j < PLAYERBULLET_MAX; j++, bullet++)
		{
			if (!bullet->active)
			{
				continue;
			}
			if(ChechHitBoundingCube(&ptr->collider, &bullet->collider2))
			{
				ptr->hp = 0.0f;
				//bullet->active = false;
			}
		}
	}
}

/*****************************************
�L���[�u���b�N�I������
******************************************/
void LockonCubeObject(void)
{
	CUBE_OBJECT *ptr = &cube[0];
	TARGETSITE *targetSite = GetTargetSiteAdr(0);
	D3DXVECTOR3 *cubePos = &pos[0];

	for (int i = 0; i < PLAYERMODEL_MAX; i++, targetSite++)
	{
		if (!targetSite->active)
		{
			continue;
		}

		ptr = &cube[0];
		for (int j = 0; j < CUBEOBJECT_NUM_MAX; j++, ptr++, cubePos++)
		{
			if (!ptr->active)
			{
				continue;
			}

			if (CollisionTargetSite(i, cubePos))
			{
				AddRockonTarget(i, cubePos, &ptr->active, &ptr->hp);
			}
		}
	}
}