//=====================================
//
//�L���[�u�I�u�W�F�N�g����[cubeObject.cpp]
//Author:GP11A341 21 ���ԗY��
//
//=====================================
#include "cubeObject.h"
#include "targetSite.h"
#include "playerModel.h"
#include "particleManager.h"
#include "dataContainer.h"
#include "collisionManager.h"
#include "debugWindow.h"
#include "soundEffectManager.h"

/**************************************
�}�N����`
***************************************/
#define CUBEOBJECT_EFFECT_NAME			"data/EFFECT/cubeObject.fx"
#define CUBEOBJECT_SIZE					(12.0f)		//�L���[�u�I�u�W�F�N�g�̃T�C�Y
#define CUBEOBJECT_VTX_NUM				(24)		//�L���[�u�I�u�W�F�N�g�̒��_��
#define CUBEOBJECT_FIELD_NUM			(6)			//�L���[�u�I�u�W�F�N�g�̖ʐ�
#define CUBEOBJECT_TEX_NUM				(3)			//�e�N�X�`������
#define CUBEOBJECT_INIT_HP				(0.01f)		//����HP
#define CUBEOBJECT_ADD_SCORE			(100)		//�j�󎞂̉��Z�X�R�A
#define CUBEOBJECT_SCALE_MAX			(1.5f)		//�L���[�u�I�u�W�F�N�g�ő�X�P�[��
#define CUBEOBJECT_SCALE_MIN			(0.7f)		//�L���[�u�I�u�W�F�N�g�ŏ��X�P�[��
#define CUBEOBJECT_SPEED_MAX			(10.0f)		//�L���[�u�I�u�W�F�N�g�ő�X�s�[�h
#define CUBEOBJECT_SPEED_MIN			(5.0f)		//�L���[�u�I�u�W�F�N�g�ŏ��X�s�[�h

#define CUBEOBJECT_SPEED_RANGE			(3.0f)
#define PARTICLE_CUBE_COLOR				(D3DCOLOR_RGBA(103, 147, 255, 255))

//�e�N�X�`����
static const char* texName[CUBEOBJECT_TEX_NUM] = {
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
}CUBE_VTX;	//�P�ʒ��_�\����

/**************************************
�O���[�o���ϐ�
***************************************/
//�L���[�u�I�u�W�F�N�g�̒P�ʒ��_
//static CUBE_VTX vtx[CUBEOBJECT_VTX_NUM] = {
//	//��
//	{ -CUBEOBJECT_SIZE, CUBEOBJECT_SIZE, CUBEOBJECT_SIZE, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f },
//	{ CUBEOBJECT_SIZE, CUBEOBJECT_SIZE, CUBEOBJECT_SIZE, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f },
//	{ -CUBEOBJECT_SIZE, CUBEOBJECT_SIZE,-CUBEOBJECT_SIZE, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f },
//	{ CUBEOBJECT_SIZE, CUBEOBJECT_SIZE,-CUBEOBJECT_SIZE, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f },
//	//�O
//	{ -CUBEOBJECT_SIZE, CUBEOBJECT_SIZE,-CUBEOBJECT_SIZE, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f },
//	{ CUBEOBJECT_SIZE, CUBEOBJECT_SIZE,-CUBEOBJECT_SIZE, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f },
//	{ -CUBEOBJECT_SIZE,-CUBEOBJECT_SIZE,-CUBEOBJECT_SIZE, 0.0f, 1.0f, 0.0f, 0.0f, -1.0f },
//	{ CUBEOBJECT_SIZE,-CUBEOBJECT_SIZE,-CUBEOBJECT_SIZE, 1.0f, 1.0f, 0.0f, 0.0f, -1.0f },
//	//��
//	{ -CUBEOBJECT_SIZE,-CUBEOBJECT_SIZE,-CUBEOBJECT_SIZE, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f },
//	{ CUBEOBJECT_SIZE,-CUBEOBJECT_SIZE,-CUBEOBJECT_SIZE, 1.0f, 0.0f, 0.0f, -1.0f, 0.0f },
//	{ -CUBEOBJECT_SIZE,-CUBEOBJECT_SIZE, CUBEOBJECT_SIZE, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f },
//	{ CUBEOBJECT_SIZE,-CUBEOBJECT_SIZE, CUBEOBJECT_SIZE, 1.0f, 1.0f, 0.0f, -1.0f, 0.0f },
//	//���
//	{ CUBEOBJECT_SIZE, CUBEOBJECT_SIZE, CUBEOBJECT_SIZE, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f },
//	{ -CUBEOBJECT_SIZE, CUBEOBJECT_SIZE, CUBEOBJECT_SIZE, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f },
//	{ CUBEOBJECT_SIZE,-CUBEOBJECT_SIZE, CUBEOBJECT_SIZE, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f },
//	{ -CUBEOBJECT_SIZE,-CUBEOBJECT_SIZE, CUBEOBJECT_SIZE, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f },
//	//��
//	{ -CUBEOBJECT_SIZE, CUBEOBJECT_SIZE, CUBEOBJECT_SIZE, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f },
//	{ -CUBEOBJECT_SIZE, CUBEOBJECT_SIZE,-CUBEOBJECT_SIZE, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f },
//	{ -CUBEOBJECT_SIZE,-CUBEOBJECT_SIZE, CUBEOBJECT_SIZE, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f },
//	{ -CUBEOBJECT_SIZE,-CUBEOBJECT_SIZE,-CUBEOBJECT_SIZE, 1.0f, 1.0f, -1.0f, 0.0f, 0.0f },
//	//�E
//	{ CUBEOBJECT_SIZE, CUBEOBJECT_SIZE,-CUBEOBJECT_SIZE, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f },
//	{ CUBEOBJECT_SIZE, CUBEOBJECT_SIZE, CUBEOBJECT_SIZE, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f },
//	{ CUBEOBJECT_SIZE,-CUBEOBJECT_SIZE,-CUBEOBJECT_SIZE, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f },
//	{ CUBEOBJECT_SIZE,-CUBEOBJECT_SIZE, CUBEOBJECT_SIZE, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f },
//};

static CUBE_VTX vtx[24] = {
	{ 0.0f, 2 * CUBEOBJECT_SIZE,0.0f, 0.5f, 0.5f, 0.0f, 0.0f, 0.0f} ,
	{ CUBEOBJECT_SIZE, 0.0f, -CUBEOBJECT_SIZE, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f},
	{ -CUBEOBJECT_SIZE, 0.0f, -CUBEOBJECT_SIZE, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f},

	{ 0.0f, 2 * CUBEOBJECT_SIZE,0.0f, 0.5f, 0.5f, 0.0f, 0.0f, 0.0f } ,
	{ CUBEOBJECT_SIZE, 0.0f, CUBEOBJECT_SIZE, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f },
	{ CUBEOBJECT_SIZE, 0.0f, -CUBEOBJECT_SIZE, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f},

	{ 0.0f, 2 * CUBEOBJECT_SIZE,0.0f, 0.5f, 0.5f, 0.0f, 0.0f, 0.0f } ,
	{-CUBEOBJECT_SIZE, 0.0f, CUBEOBJECT_SIZE, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f},
	{CUBEOBJECT_SIZE, 0.0f, CUBEOBJECT_SIZE, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f},

	{ 0.0f, 2 * CUBEOBJECT_SIZE,0.0f, 0.5f, 0.5f, 0.0f, 0.0f, 0.0f } ,
	{ -CUBEOBJECT_SIZE, 0.0f, -CUBEOBJECT_SIZE, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f},
	{-CUBEOBJECT_SIZE, 0.0f, CUBEOBJECT_SIZE, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f},

	{ 0.0f, -2 * CUBEOBJECT_SIZE, 0.0f,0.5f, 0.5f, 0.0f, 0.0f, 0.0f } ,
	{ -CUBEOBJECT_SIZE, 0.0f, -CUBEOBJECT_SIZE, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f },
	{ CUBEOBJECT_SIZE, 0.0f, -CUBEOBJECT_SIZE, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f },

	{ 0.0f, -2 * CUBEOBJECT_SIZE,0.0f, 0.5f, 0.5f, 0.0f, 0.0f, 0.0f } ,
	{ CUBEOBJECT_SIZE, 0.0f, -CUBEOBJECT_SIZE, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f },
	{ CUBEOBJECT_SIZE, 0.0f, CUBEOBJECT_SIZE, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f },

	{ 0.0f, -2 * CUBEOBJECT_SIZE, 0.0f,0.5f, 0.5f, 0.0f, 0.0f, 0.0f } ,
	{ CUBEOBJECT_SIZE, 0.0f, CUBEOBJECT_SIZE, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f},
	{ -CUBEOBJECT_SIZE, 0.0f, CUBEOBJECT_SIZE, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f },

	{ 0.0f, -2 * CUBEOBJECT_SIZE, 0.0f,0.5f, 0.5f, 0.0f, 0.0f, 0.0f } ,
	{ -CUBEOBJECT_SIZE, 0.0f, CUBEOBJECT_SIZE, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f },
	{ -CUBEOBJECT_SIZE, 0.0f, -CUBEOBJECT_SIZE, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f },
};

static LPDIRECT3DVERTEXBUFFER9 vtxBuff, worldBuff;		//���_�o�b�t�@
static LPDIRECT3DVERTEXDECLARATION9 declare;			//���_�錾
static LPDIRECT3DTEXTURE9 texture[3];					//�e�N�X�`��
static LPD3DXEFFECT effect;								//�V�F�[�_
static LPDIRECT3DINDEXBUFFER9 indexBuff;				//�C���f�b�N�X�o�b�t�@

static D3DXMATRIX mtxWorld[CUBEOBJECT_NUM_MAX];			//���[���h�ϊ��s��

static CUBE_OBJECT cube[CUBEOBJECT_NUM_MAX];			//�L���[�u�I�u�W�F�N�g�z��
static OBJECT_FOR_TREE objectForTree[CUBEOBJECT_NUM_MAX]; //�Փ˔���pOBJECT_FOR_TREE�z��

static int cntCube;
/**************************************
�v���g�^�C�v�錾
***************************************/
void MoveCubeObject(void);					//�ړ�����
void RotationCubeObject(void);				//��]����
void CalcCubeObjectWorldMartix(void);		//���[���h�ϊ��s��v�Z����
void CheckDestroyCubeObject(void);			//���S����
void RegisterCubeObjectToSpace(void);		//�Փˋ�Ԃւ̓o�^����
void DisableCubeObject(CUBE_OBJECT *ptr);	//��A�N�e�B�u����

/**************************************
����������
***************************************/
void InitCubeObject(int num)
{
	static bool initialized = false;
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�L���[�u�����͈�
	const float PosRange = 150.0f;
	const float RotRange = 5.0f;

	//�p�����[�^������
	CUBE_OBJECT *ptr = &cube[0];
	OBJECT_FOR_TREE *oft = &objectForTree[0];
	for (int i = 0; i < CUBEOBJECT_NUM_MAX; i++, ptr++, oft++)
	{
		ptr->pos = D3DXVECTOR3(RandomRangef(-PosRange, PosRange), RandomRangef(-PosRange, PosRange), RandomRangef(0.0f, 20000.0f));
		ptr->rot = D3DXVECTOR3(RandomRangef(0.0f, 3.1415f), RandomRangef(0.0f, 3.1415f), RandomRangef(0.0f, 3.1415f));
		ptr->scale = 0.0f;

		ptr->rotValue = D3DXVECTOR3(RandomRangef(-RotRange, RotRange), RandomRangef(-RotRange, RotRange), RandomRangef(-RotRange, RotRange));
		ptr->rotValue *= 0.01f;
		ptr->hp = CUBEOBJECT_INIT_HP;
		ptr->id = i;
		ptr->active = false;

		ptr->collider.pos = &ptr->pos;
		ptr->collider.offset = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		ptr->collider.length = D3DXVECTOR3(CUBEOBJECT_SIZE*1.2f, CUBEOBJECT_SIZE*1.2f, CUBEOBJECT_SIZE*1.2f);

		CreateOFT(oft, (void*)ptr);
	}

	//����݂̂̏�����
	if (!initialized)
	{

		//�@���v�Z
		for (int i = 0; i < 8; i++)
		{
			D3DXVECTOR3 vec1, vec2;
			vec1 = D3DXVECTOR3(vtx[i * 3 + 2].posX, vtx[i * 3 + 2].posY, vtx[i * 3 + 2].posZ) - D3DXVECTOR3(vtx[i * 3].posX, vtx[i * 3].posY, vtx[i * 3].posZ);
			vec2 = D3DXVECTOR3(vtx[i * 3 + 1].posX, vtx[i * 3 + 1].posY, vtx[i * 3 + 1].posZ) - D3DXVECTOR3(vtx[i * 3].posX, vtx[i * 3].posY, vtx[i * 3].posZ);
			D3DXVECTOR3 normal;
			D3DXVec3Cross(&normal, &vec2, &vec1);
			D3DXVec3Normalize(&normal, &normal);
			for (int j = 0; j < 3; j++)
			{
				vtx[i * 3 + j].norX = normal.x;
				vtx[i * 3 + j].norY = normal.y;
				vtx[i * 3 + j].norZ = normal.z;
			}
		}

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
		/*WORD index[6 * CUBEOBJECT_FIELD_NUM];
		for (int i = 0; i < 6; i++)
		{
			index[i * 6] = i * NUM_VERTEX;
			index[i * 6 + 1] = i * NUM_VERTEX + 1;
			index[i * 6 + 2] = i * NUM_VERTEX + 2;
			index[i * 6 + 3] = i * NUM_VERTEX + 2;
			index[i * 6 + 4] = i * NUM_VERTEX + 1;
			index[i * 6 + 5] = i * NUM_VERTEX + 3;
		}*/

		WORD index[24];
		for (int i = 0; i < 24; i++)
		{
			index[i] = i;
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

		initialized = true;
	}
}

/**************************************
�I������
***************************************/
void UninitCubeObject(int num)
{
	OBJECT_FOR_TREE *oft = &objectForTree[0];
	CUBE_OBJECT *ptr = &cube[0];
	for (int i = 0; i < CUBEOBJECT_NUM_MAX; i++, ptr++, oft++)
	{
		DisableCubeObject(ptr);
	}

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

	RegisterCubeObjectToSpace();
}

/**************************************
�`�揈��
***************************************/
void DrawCubeObject(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DLIGHT9 light1, light2, light3;

	//���C�g�����擾���ăV�F�[�_�ɃZ�b�g
	pDevice->GetLight(0, &light1);
	effect->SetFloatArray("light1Dir", (float*)&light1.Direction, 3);
	effect->SetFloatArray("light1Diffuse", (float*)&light1.Diffuse, 4);
	effect->SetFloatArray("light1Ambient", (float*)&light1.Ambient, 4);

	pDevice->GetLight(0, &light2);
	effect->SetFloatArray("light2Dir", (float*)&light2.Direction, 3);
	effect->SetFloatArray("light2Diffuse", (float*)&light2.Diffuse, 4);
	effect->SetFloatArray("light2Ambient", (float*)&light2.Ambient, 4);

	pDevice->GetLight(0, &light3);
	effect->SetFloatArray("light3Dir", (float*)&light3.Direction, 3);
	effect->SetFloatArray("light3Diffuse", (float*)&light3.Diffuse, 4);
	effect->SetFloatArray("light3Ambient", (float*)&light3.Ambient, 4);

	//�X�g���[�����g���ݒ�
	pDevice->SetStreamSourceFreq(0, D3DSTREAMSOURCE_INDEXEDDATA | (CUBEOBJECT_NUM_MAX));
	pDevice->SetStreamSourceFreq(1, D3DSTREAMSOURCE_INSTANCEDATA | 1);

	//���_�錾�ƃX�g���[���\�[�X�A�C���f�b�N�X�o�b�t�@��ݒ�
	pDevice->SetVertexDeclaration(declare);
	pDevice->SetStreamSource(0, vtxBuff, 0, sizeof(CUBE_VTX));
	pDevice->SetStreamSource(1, worldBuff, 0, sizeof(D3DXMATRIX));
	pDevice->SetIndices(indexBuff);

	//�r���[�s��A�v���W�F�N�V�����s���ݒ�
	effect->SetMatrix("mtxView", &GetBattleCameraView());
	effect->SetMatrix("mtxProj", &GetBattleCameraProjection());

	//�e�N�X�`���̖��������`��
	for (int i = 0; i < CUBEOBJECT_TEX_NUM; i++)
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

#if 0
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
	CUBE_OBJECT *ptr = &cube[0];
	for (int i = 0; i < CUBEOBJECT_NUM_MAX; i++, ptr++)
	{
		if (!ptr->active)
			continue;

		ptr->pos.z += ptr->moveSpeed;
		if (ptr->pos.z < -1000.0f)
		{
			DisableCubeObject(ptr);
		}
	}
}

/**************************************
��]����
***************************************/
void RotationCubeObject(void)
{
	CUBE_OBJECT *ptr = &cube[0];
	for (int i = 0; i < CUBEOBJECT_NUM_MAX; i++, ptr++)
	{
		ptr->rot += ptr->rotValue;
	}
}

/**************************************
���[���h�ϊ��s��v�Z����
***************************************/
void CalcCubeObjectWorldMartix(void)
{
	D3DXMATRIX *pWorld = &mtxWorld[0];
	D3DXMATRIX mtxRot, mtxTranslate, mtxScale;
	CUBE_OBJECT *ptr = &cube[0];

	for (int i = 0; i < CUBEOBJECT_NUM_MAX; i++, pWorld++, ptr++)
	{
		D3DXMatrixIdentity(pWorld);

		D3DXMatrixRotationYawPitchRoll(&mtxRot, ptr->rot.y, ptr->rot.x, ptr->rot.z);
		D3DXMatrixMultiply(pWorld, pWorld, &mtxRot);

		D3DXMatrixScaling(&mtxScale, ptr->scale, ptr->scale, ptr->scale);
		D3DXMatrixMultiply(pWorld, pWorld, &mtxScale);

		D3DXMatrixTranslation(&mtxTranslate, ptr->pos.x, ptr->pos.y, ptr->pos.z);
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
	for (int i = 0; i < CUBEOBJECT_NUM_MAX; i++, ptr++)
	{
		if (!ptr->active)
			continue;

		if (ptr->hp <= 0.0f)
		{
			SetCubeExplosion(ptr->pos, PARTICLE_CUBE_COLOR);
			AddScore(CUBEOBJECT_ADD_SCORE);
			PlaySE_3D(SOUND_SMALLEXPL, ptr->pos.z);
			DisableCubeObject(ptr);
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

	for (int i = 0; i < PLAYERMODEL_MAX; i++, targetSite++)
	{
		if (!targetSite->active)
		{
			continue;
		}

		ptr = &cube[0];
		for (int j = 0; j < CUBEOBJECT_NUM_MAX; j++, ptr++)
		{
			if (!ptr->active)
			{
				continue;
			}

			if (CollisionTargetSite(i, &ptr->pos))
			{
				AddRockonTarget(i, &ptr->pos, &ptr->active, &ptr->hp);
			}
		}
	}
}

/*****************************************
�Փ˔����Ԃւ̓o�^����
******************************************/
void RegisterCubeObjectToSpace(void)
{
	CUBE_OBJECT *ptr = &cube[0];
	OBJECT_FOR_TREE *oft = &objectForTree[0];

	for (int i = 0; i < CUBEOBJECT_NUM_MAX; i++, ptr++, oft++)
	{
		RemoveObjectFromSpace(oft);

		if (ptr->active)
		{
			RegisterObjectToSpace(&ptr->collider, oft, OFT_CUBEOBJECT);
		}
	}
}

/*****************************************
�S�L���[�u�ւ̃_���[�W����
******************************************/
void DamageAllCubeObject(void)
{
	CUBE_OBJECT *ptr = &cube[0];
	for (int i = 0; i < CUBEOBJECT_NUM_MAX; i++, ptr++)
	{
		if (!ptr->active)
			continue;

		ptr->hp -= 1.0f;
	}
}

/*****************************************
��A�N�e�B�u����
******************************************/
void DisableCubeObject(CUBE_OBJECT *ptr)
{
	ptr->active = false;
	ptr->scale = 0.0f;
	cntCube--;
	RemoveObjectFromSpace(&objectForTree[ptr->id]);
}

/*****************************************
�Z�b�g����
******************************************/
bool SetCubeObject(D3DXVECTOR3 *setPos, float speed = 8.0f)
{
	CUBE_OBJECT *ptr = &cube[0];
	OBJECT_FOR_TREE *oft = &objectForTree[0];
	for (int i = 0; i < CUBEOBJECT_NUM_MAX; i++, ptr++, oft++)
	{
		if (ptr->active)
			continue;

		ptr->pos = *setPos;
		ptr->scale = RandomRangef(CUBEOBJECT_SCALE_MIN, CUBEOBJECT_SCALE_MAX);
		ptr->moveSpeed = -RandomRangef(CUBEOBJECT_SPEED_MIN, CUBEOBJECT_SPEED_MAX);
		ptr->hp = CUBEOBJECT_INIT_HP;
		ptr->collider.length = D3DXVECTOR3(CUBEOBJECT_SIZE * ptr->scale, CUBEOBJECT_SIZE * ptr->scale, CUBEOBJECT_SIZE * ptr->scale);
		ptr->moveSpeed = -RandomRangef(speed - CUBEOBJECT_SPEED_RANGE, speed + CUBEOBJECT_SPEED_RANGE);
		ptr->active = true;
		RegisterObjectToSpace(&ptr->collider, oft, OFT_CUBEOBJECT);
		cntCube++;
		return true;
	}

	return false;
}

/*****************************************
�A�h���X�擾����
******************************************/
CUBE_OBJECT *GetCubeObjectAdr(int num)
{
	return &cube[num];
}

/*****************************************
�f�o�b�O���\��
******************************************/
void DrawDebugWindowCube(void)
{
	BeginDebugWindow("CubeObject");

	DebugText("Active : %d", cntCube);

	EndDebugWindow("CubeObject");
}