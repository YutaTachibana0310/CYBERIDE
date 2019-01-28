//=====================================
//
//�{�[�i�X�L���[�u����[bonusCube.cpp]
//Author:GP11A341 21 ���ԗY��
//
//=====================================
#include "bonusCube.h"
#include "targetSite.h"
#include "particleManager.h"
#include "dataContainer.h"
#include "collisionManager.h"
#include "battleCamera.h"
#include "playerModel.h"
#include "battleController.h"
#include "EasingVector.h"
#include "soundEffectManager.h"
#include "cameraShaker.h"
#include "shockBlur.h"

#include "debugWindow.h"
#include <math.h>
/**************************************
�}�N����`
***************************************/
#define BONUSCUBE_EFFECT_NAME			"data/EFFECT/cubeObject.fx"
#define BONUSCUBE_SIZE					(15.0f)
#define BONUSCUBE_NUM_MAX				(9)
#define BONUSCUBE_VTX_NUM				(24)
#define BONUSCUBE_FIELD_NUM				(6)
#define BONUSCUBE_TEX_NUM				(3)
#define BONUSCUBE_INIT_HP				(30.0f)
#define BONUSCUBE_MOVE_MAX				(10)
#define BONUSCUBE_MOVE_Z_NEAR			(300.0f)
#define BONUSCUBE_MOVE_Z_FAR			(1000.0f)
#define BONUSCUBE_MOVE_END_Z			(10000.0f)
#define BONUSCUBE_MOVE_X_RANGE			(300.0f)
#define BONUSCUBE_MOVE_Y_RANGE			(200.0f)
#define BONUSCUBE_MOVE_DURATION			(90)
#define BONUSCUBE_MOVE_WAIT				(30)
#define PARTICLE_BONUSCUBE_COLOR		(D3DCOLOR_RGBA(255, 228, 121, 255))
#define BONUSCUBE_CAMERASHAKE_LENGTH	(5.0f)
#define BONUSCUBE_EMMITT_OFFST			(300.0f)
#define BONUSCUBE_EMMITT_BASE			(D3DXVECTOR3(-BONUSCUBE_EMMITT_OFFST, -BONUSCUBE_EMMITT_OFFST, -100.0f))

static const char* TextureName[BONUSCUBE_TEX_NUM] = {
	"data/TEXTURE/OBJECT/circuit09.png",
	"data/TEXTURE/OBJECT/circuit10.png",
	"data/TEXTURE/OBJECT/circuit11.png",
};

/**************************************
�\���̒�`
***************************************/
typedef struct {
	float posX, posY, posZ;
	float texU, texV;
	float norX, norY, norZ;
}BONUSCUBE_VTX;

/**************************************
�O���[�o���ϐ�
***************************************/
//�P�ʒ��_
static BONUSCUBE_VTX vtx[BONUSCUBE_VTX_NUM] = {
	//��
	{ -BONUSCUBE_SIZE, BONUSCUBE_SIZE, BONUSCUBE_SIZE, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f },
	{ BONUSCUBE_SIZE, BONUSCUBE_SIZE, BONUSCUBE_SIZE, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f },
	{ -BONUSCUBE_SIZE, BONUSCUBE_SIZE,-BONUSCUBE_SIZE, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f },
	{ BONUSCUBE_SIZE, BONUSCUBE_SIZE,-BONUSCUBE_SIZE, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f },
	//�O
	{ -BONUSCUBE_SIZE, BONUSCUBE_SIZE,-BONUSCUBE_SIZE, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f },
	{ BONUSCUBE_SIZE, BONUSCUBE_SIZE,-BONUSCUBE_SIZE, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f },
	{ -BONUSCUBE_SIZE,-BONUSCUBE_SIZE,-BONUSCUBE_SIZE, 0.0f, 1.0f, 0.0f, 0.0f, -1.0f },
	{ BONUSCUBE_SIZE,-BONUSCUBE_SIZE,-BONUSCUBE_SIZE, 1.0f, 1.0f, 0.0f, 0.0f, -1.0f },
	//��
	{ -BONUSCUBE_SIZE,-BONUSCUBE_SIZE,-BONUSCUBE_SIZE, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f },
	{ BONUSCUBE_SIZE,-BONUSCUBE_SIZE,-BONUSCUBE_SIZE, 1.0f, 0.0f, 0.0f, -1.0f, 0.0f },
	{ -BONUSCUBE_SIZE,-BONUSCUBE_SIZE, BONUSCUBE_SIZE, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f },
	{ BONUSCUBE_SIZE,-BONUSCUBE_SIZE, BONUSCUBE_SIZE, 1.0f, 1.0f, 0.0f, -1.0f, 0.0f },
	//���
	{ BONUSCUBE_SIZE, BONUSCUBE_SIZE, BONUSCUBE_SIZE, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f },
	{ -BONUSCUBE_SIZE, BONUSCUBE_SIZE, BONUSCUBE_SIZE, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f },
	{ BONUSCUBE_SIZE,-BONUSCUBE_SIZE, BONUSCUBE_SIZE, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f },
	{ -BONUSCUBE_SIZE,-BONUSCUBE_SIZE, BONUSCUBE_SIZE, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f },
	//��
	{ -BONUSCUBE_SIZE, BONUSCUBE_SIZE, BONUSCUBE_SIZE, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f },
	{ -BONUSCUBE_SIZE, BONUSCUBE_SIZE,-BONUSCUBE_SIZE, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f },
	{ -BONUSCUBE_SIZE,-BONUSCUBE_SIZE, BONUSCUBE_SIZE, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f },
	{ -BONUSCUBE_SIZE,-BONUSCUBE_SIZE,-BONUSCUBE_SIZE, 1.0f, 1.0f, -1.0f, 0.0f, 0.0f },
	//�E
	{ BONUSCUBE_SIZE, BONUSCUBE_SIZE,-BONUSCUBE_SIZE, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f },
	{ BONUSCUBE_SIZE, BONUSCUBE_SIZE, BONUSCUBE_SIZE, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f },
	{ BONUSCUBE_SIZE,-BONUSCUBE_SIZE,-BONUSCUBE_SIZE, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f },
	{ BONUSCUBE_SIZE,-BONUSCUBE_SIZE, BONUSCUBE_SIZE, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f },
};

static LPDIRECT3DVERTEXBUFFER9 vtxBuff, worldBuff;			//���_�o�b�t�@
static LPDIRECT3DVERTEXDECLARATION9 declare;				//���_�錾
static LPDIRECT3DTEXTURE9 texture[BONUSCUBE_TEX_NUM];		//�e�N�X�`��
static LPD3DXEFFECT effect;									//�V�F�[�_
static LPDIRECT3DINDEXBUFFER9 indexBuff;					//�C���f�b�N�X�o�b�t�@

static D3DXMATRIX mtxWorld[BONUSCUBE_NUM_MAX];				//���[���h�ϊ��s��
static BONUS_CUBE_OBJECT cube[BONUSCUBE_NUM_MAX];			//�{�[�i�X�L���[�u�z��
static OBJECT_FOR_TREE objectForTree[BONUSCUBE_NUM_MAX];	//�Փ˔���pOBJECT_FOR_TREE�z��
static bool isAllCubeDisable;								//�L���[�u�S�Ŕ���
static bool escapedAnyCube;									//�L���[�u��������

/**************************************
�v���g�^�C�v�錾
***************************************/
void MoveBonusCube(void);						//�ړ�����
void RotateBonusCube(void);						//��]����
void CalcBonusCubeWorldMatrix(void);			//���[���h�ϊ��s��v�Z����
void CheckDestroyBonusCube(void);				//���S����	
void RegisterBonusCubeToSpace(void);			//�Փˋ�Ԃւ̓o�^����
void DisableBonusCube(BONUS_CUBE_OBJECT *ptr);	//��A�N�e�B�u����
void StartBonusCubeMove(BONUS_CUBE_OBJECT *ptr);//�ړ��J�n����

/**************************************
����������
***************************************/
void InitBonusCube(int num)
{
	static bool initialized = false;
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�L���[�u�����͈�
	const float PosRange = 50.0f;
	const float RotRange = 5.0f;

	//�p�����[�^������
	BONUS_CUBE_OBJECT *ptr = &cube[0];
	OBJECT_FOR_TREE *oft = &objectForTree[0];
	for (int i = 0; i < BONUSCUBE_NUM_MAX; i++, ptr++, oft++)
	{
		ptr->id = i;
		ptr->pos = D3DXVECTOR3(RandomRangef(-PosRange, PosRange), RandomRangef(-PosRange, PosRange), RandomRangef(0.0f, 10000.0f));
		ptr->rot = D3DXVECTOR3(RandomRangef(0.0f, 3.1415f), RandomRangef(0.0f, 3.1415f), RandomRangef(0.0f, 3.1415f));
		ptr->scale = 0.0f;

		ptr->rotValue = D3DXVECTOR3(RandomRangef(-RotRange, RotRange), RandomRangef(-RotRange, RotRange), RandomRangef(-RotRange, RotRange));
		ptr->rotValue *= 0.01f;
		ptr->moveSpeed = RandomRangef(-10.0f, -5.0f);
		ptr->hp = BONUSCUBE_INIT_HP;

		ptr->active = false;

		ptr->collider.pos = &ptr->pos;
		ptr->collider.offset = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		ptr->collider.length = D3DXVECTOR3(BONUSCUBE_SIZE*1.5f, BONUSCUBE_SIZE*1.5f, BONUSCUBE_SIZE*1.5f);

		CreateOFT(oft, (void*)ptr);
	}

	//����݂̂̏�����
	if (!initialized)
	{
		//���_�o�b�t�@�쐬
		pDevice->CreateVertexBuffer(sizeof(vtx), 0, 0, D3DPOOL_MANAGED, &vtxBuff, 0);
		pDevice->CreateVertexBuffer(sizeof(mtxWorld), 0, 0, D3DPOOL_MANAGED, &worldBuff, 0);
		CopyVtxBuff(sizeof(vtx), vtx, vtxBuff);
		CopyVtxBuff(sizeof(mtxWorld), mtxWorld, worldBuff);

		//���_�錾�쐬
		D3DVERTEXELEMENT9 declareElems[] =
		{
			{ 0, 0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },	//���_���W
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
		WORD index[6 * BONUSCUBE_FIELD_NUM];
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
		D3DXCreateEffectFromFile(pDevice, BONUSCUBE_EFFECT_NAME, 0, 0, 0, 0, &effect, NULL);

		//�e�N�X�`���ǂݍ���
		for (int i = 0; i < 3; i++)
		{
			D3DXCreateTextureFromFile(pDevice, TextureName[i], &texture[i]);
		}

		initialized = true;
	}
}

/**************************************
�I������
***************************************/
void UninitBonusCube(int num)
{
	BONUS_CUBE_OBJECT *ptr = &cube[0];
	for (int i = 0; i < BONUSCUBE_NUM_MAX; i++, ptr++)
	{
		DisableBonusCube(ptr);
	}

	if (num == 0)
	{
		SAFE_RELEASE(vtxBuff);
		SAFE_RELEASE(worldBuff);
		SAFE_RELEASE(effect);
		SAFE_RELEASE(declare);
		SAFE_RELEASE(indexBuff);

		for (int i = 0; i < BONUSCUBE_TEX_NUM; i++)
		{
			SAFE_RELEASE(texture[i]);
		}
	}
}

/**************************************
�X�V����
***************************************/
void UpdateBonusCube(void)
{
	CheckDestroyBonusCube();
	MoveBonusCube();
	RotateBonusCube();
	CalcBonusCubeWorldMatrix();
	RegisterBonusCubeToSpace();
}

/**************************************
�`�揈��
***************************************/
void DrawBonusCube(void)
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

	//�X�g���[�����g�����Z�b�g
	pDevice->SetStreamSourceFreq(0, D3DSTREAMSOURCE_INDEXEDDATA | (BONUSCUBE_NUM_MAX));
	pDevice->SetStreamSourceFreq(1, D3DSTREAMSOURCE_INSTANCEDATA | 1);

	//���_�錾�A�X�g���[���\�[�X�A�C���f�b�N�X�o�b�t�@���Z�b�g
	pDevice->SetVertexDeclaration(declare);
	pDevice->SetStreamSource(0, vtxBuff, 0, sizeof(BONUSCUBE_VTX));
	pDevice->SetStreamSource(1, worldBuff, 0, sizeof(D3DXMATRIX));
	pDevice->SetIndices(indexBuff);

	//�r���[�s��A�v���W�F�N�V�����s���ݒ�
	effect->SetMatrix("mtxView", &GetBattleCameraView());
	effect->SetMatrix("mtxProj", &GetBattleCameraProjection());

	//�e�N�X�`���̖��������`��
	for (int i = 0; i < BONUSCUBE_TEX_NUM; i++)
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

		pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, BONUSCUBE_VTX_NUM, 0, BONUSCUBE_FIELD_NUM * NUM_POLYGON);

		effect->EndPass();
		effect->End();
	}
	pDevice->SetStreamSourceFreq(0, 1);
	pDevice->SetStreamSourceFreq(1, 1);

#if 0
	BONUS_CUBE_OBJECT *ptr = &cube[0];
	for (int i = 0; i < BONUSCUBE_NUM_MAX; i++, ptr++)
	{
		DrawBoundingCube(&ptr->collider);
	}
#endif
}

/**************************************
�ړ�����
***************************************/
void MoveBonusCube(void)
{
	BONUS_CUBE_OBJECT *ptr = &cube[0];
	for (int i = 0; i < BONUSCUBE_NUM_MAX; i++, ptr++)
	{
		if (!ptr->active)
			continue;

		ptr->cntFrame++;
		float t = (float)ptr->cntFrame / BONUSCUBE_MOVE_DURATION;
		ptr->pos = EaseInOutExponentialVector(t, ptr->startPos, ptr->goalPos);

		if (ptr->cntFrame == BONUSCUBE_MOVE_DURATION + BONUSCUBE_MOVE_WAIT)
		{
			ptr->cntMove++;
			if (ptr->cntMove > BONUSCUBE_MOVE_MAX)
			{
				escapedAnyCube = true;
				DisableBonusCube(ptr);
			}
			else
			{
				StartBonusCubeMove(ptr);
			}
		}
	}
}

/**************************************
��]����
***************************************/
void RotateBonusCube(void)
{
	BONUS_CUBE_OBJECT *ptr = &cube[0];
	for (int i = 0; i < BONUSCUBE_NUM_MAX; i++, ptr++)
	{
		ptr->rot += ptr->rotValue;
	}
}

/**************************************
���[���h�ϊ��s��v�Z����
***************************************/
void CalcBonusCubeWorldMatrix(void)
{
	D3DXMATRIX *pWorld = &mtxWorld[0];
	D3DXMATRIX mtxRot, mtxTranslate, mtxScale;
	BONUS_CUBE_OBJECT *ptr = &cube[0];
	for (int i = 0; i < BONUSCUBE_NUM_MAX; i++, ptr++, pWorld++)
	{
		D3DXMatrixIdentity(pWorld);

		D3DXMatrixScaling(&mtxScale, ptr->scale, ptr->scale, ptr->scale);
		D3DXMatrixMultiply(pWorld, pWorld, &mtxScale);

		D3DXMatrixRotationYawPitchRoll(&mtxRot, ptr->rot.y, ptr->rot.x, ptr->rot.z);
		D3DXMatrixMultiply(pWorld, pWorld, &mtxRot);

		D3DXMatrixTranslation(&mtxTranslate, ptr->pos.x, ptr->pos.y, ptr->pos.z);
		D3DXMatrixMultiply(pWorld, pWorld, &mtxTranslate);
	}

	CopyVtxBuff(sizeof(mtxWorld), mtxWorld, worldBuff);
}

/**************************************
���S����
***************************************/
void CheckDestroyBonusCube(void)
{
	BONUS_CUBE_OBJECT *ptr = &cube[0];
	int cntActive = 0;
	for (int i = 0; i < BONUSCUBE_NUM_MAX; i++, ptr++)
	{
		if (!ptr->active)
		{
			continue;
		}

		if (ptr->hp <= 0.0f)
		{
			//TODO:���ʉ����p�̂��̂ɍ����ւ�
			PlaySE(SOUND_BONUSEXPL);
			SetCameraShaker(BONUSCUBE_CAMERASHAKE_LENGTH);
			SetCubeExplosion(ptr->pos, PARTICLE_BONUSCUBE_COLOR);
			SetShockBlur(ptr->pos);
			DisableBonusCube(ptr);
			StartBonusTime();
		}
		else
		{
			cntActive++;
		}
	}

	isAllCubeDisable = (cntActive == 0) ? true : false;
}

/**************************************
�Փˋ�Ԃւ̓o�^����
***************************************/
void RegisterBonusCubeToSpace(void)
{
	BONUS_CUBE_OBJECT *ptr = &cube[0];
	OBJECT_FOR_TREE *oft = &objectForTree[0];

	for (int i = 0; i < BONUSCUBE_NUM_MAX; i++, ptr++, oft++)
	{
		RemoveObjectFromSpace(oft);

		if (ptr->active)
		{
			RegisterObjectToSpace(&ptr->collider, oft, OFT_BONUSCUBE);
		}
	}
}

/**************************************
���b�N�I������
***************************************/
void LockonBonusCube(void)
{
	BONUS_CUBE_OBJECT *ptr = &cube[0];
	TARGETSITE *targetSite = GetTargetSiteAdr(0);

	for (int i = 0; i < PLAYERMODEL_MAX; i++, targetSite++)
	{
		if (!targetSite->active)
			continue;

		ptr = &cube[0];
		for (int j = 0; j < BONUSCUBE_NUM_MAX; j++, ptr++)
		{
			if (!ptr->active)
				continue;

			if (CollisionTargetSite(i, &ptr->pos))
			{
				AddRockonTarget(i, &ptr->pos, &ptr->active, &ptr->hp);
			}

		}
	}

}

/**************************************
�Z�b�g����
***************************************/
bool SetBonusCube(void)
{
	BONUS_CUBE_OBJECT *ptr = &cube[0];
	OBJECT_FOR_TREE *oft = &objectForTree[0];
	int loopMax = (int)sqrt(BONUSCUBE_NUM_MAX);
	for (int i = 0; i < loopMax; i++)
	{
		for (int j = 0; j < loopMax; j++, ptr++, oft++)
		{
			ptr->hp = BONUSCUBE_INIT_HP;
			ptr->pos = BONUSCUBE_EMMITT_BASE + D3DXVECTOR3(BONUSCUBE_EMMITT_OFFST * i, BONUSCUBE_EMMITT_OFFST * j, 0.0f);
			ptr->scale = 1.0f;
			ptr->active = true;
			RegisterObjectToSpace(&ptr->collider, oft, OFT_BONUSCUBE);
			ptr->cntMove = 0;
			StartBonusCubeMove(ptr);
		}
	}

	escapedAnyCube = false;
	isAllCubeDisable = false;
	return false;
}

/**************************************
��A�N�e�B�u����
***************************************/
void DisableBonusCube(BONUS_CUBE_OBJECT *ptr)
{
	ptr->active = false;
	ptr->scale = 0.0f;
	RemoveObjectFromSpace(&objectForTree[ptr->id]);
}

/**************************************
�ړ��J�n����
***************************************/
void StartBonusCubeMove(BONUS_CUBE_OBJECT *ptr)
{
	ptr->cntFrame = 0;
	ptr->startPos = ptr->pos;

	if (ptr->cntMove == BONUSCUBE_MOVE_MAX)
	{
		ptr->goalPos = ptr->startPos + D3DXVECTOR3(0.0f, 0.0f, BONUSCUBE_MOVE_END_Z);
	}
	else if (ptr->cntMove == 0)
	{
		ptr->goalPos = ptr->startPos;
		ptr->goalPos.z = BONUSCUBE_MOVE_Z_FAR;
	}
	else
	{
		ptr->goalPos.x = RandomRangef(-BONUSCUBE_MOVE_X_RANGE, BONUSCUBE_MOVE_X_RANGE);
		ptr->goalPos.y = RandomRangef(-BONUSCUBE_MOVE_Y_RANGE, BONUSCUBE_MOVE_Y_RANGE);
		ptr->goalPos.z = RandomRangef(BONUSCUBE_MOVE_Z_NEAR, BONUSCUBE_MOVE_Z_FAR);
	}
}

/**************************************
�{�[�i�X�L���[�u�S�Ŕ���
***************************************/
bool IsAllBonusCubeDisable(void)
{
	return isAllCubeDisable;
}

/**************************************
�{�[�i�X�L���[�u��������
***************************************/
bool CheckEscapedBonusCube(void)
{
	return escapedAnyCube;
}