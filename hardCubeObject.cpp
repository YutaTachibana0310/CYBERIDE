//=====================================
//
//�n�[�h�L���[�u�I�u�W�F�N�g����[hardCubeObject.cpp]
//Author:GP11A341 21 ���ԗY��
//
//=====================================
#include "hardCubeObject.h"
#include "targetSite.h"
#include "particleManager.h"
#include "dataContainer.h"
#include "collisionManager.h"
#include "battleCamera.h"
#include "playerModel.h"
#include "cubeObject.h"
#include "cameraShaker.h"
#include "soundEffectManager.h"
#include "shockBlur.h"

#include "stageData.h"

/**************************************
�}�N����`
***************************************/
#define HARDCUBE_EFFECT_NAME			"data/EFFECT/cubeObject.fx"	//�V�F�[�_��
#define HARDCUBE_SIZE					(10.0f)						//�I�u�W�F�N�g�T�C�Y
#define HARDCUBE_NUM_MAX				(128)						//�ő吔
#define HARDCUBE_VTX_NUM				(24)						//���_��
#define HARDCUBE_FIELD_NUM				(6)							//�ʐ�
#define HARDCUBE_TEX_NUM				(3)							//�e�N�X�`����
#define HARDCUBE_INIT_HP				(10.0f)						//����HP
#define BONUSCUBE_CAMERA_SHAKE_LENGTH	(10.0f)						//���j���̃J�����̗h�ꕝ
#define HARDCUBE_SPEED_MAX				(10.0f)						//�ő�X�s�[�h
#define HARDCUBE_SPEED_MIN				(5.0f)						//�ŏ��X�s�[�h
#define PARTICLE_HARDCUBE_COLOR			(D3DCOLOR_RGBA(255, 121, 121, 255))

//�e�N�X�`����
static const char* TextureName[HARDCUBE_TEX_NUM] = {
	"data/TEXTURE/OBJECT/circuit06.png",
	"data/TEXTURE/OBJECT/circuit07.png",
	"data/TEXTURE/OBJECT/circuit08.png",
};

/**************************************
�\���̒�`
***************************************/
typedef struct {
	float posX, posY, posZ;
	float texU, texV;
	float norX, norY, norZ;
}HARDCUBE_VTX;

typedef void(*funcHardCube)(HARD_CUBE_OBJECT *ptr);

/**************************************
�O���[�o���ϐ�
***************************************/
//�P�ʒ��_
static HARDCUBE_VTX vtx[HARDCUBE_VTX_NUM] = {
	//��
	{ -HARDCUBE_SIZE, HARDCUBE_SIZE, HARDCUBE_SIZE, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f },
	{ HARDCUBE_SIZE, HARDCUBE_SIZE, HARDCUBE_SIZE, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f },
	{ -HARDCUBE_SIZE, HARDCUBE_SIZE,-HARDCUBE_SIZE, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f },
	{ HARDCUBE_SIZE, HARDCUBE_SIZE,-HARDCUBE_SIZE, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f },
	//�O
	{ -HARDCUBE_SIZE, HARDCUBE_SIZE,-HARDCUBE_SIZE, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f },
	{ HARDCUBE_SIZE, HARDCUBE_SIZE,-HARDCUBE_SIZE, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f },
	{ -HARDCUBE_SIZE,-HARDCUBE_SIZE,-HARDCUBE_SIZE, 0.0f, 1.0f, 0.0f, 0.0f, -1.0f },
	{ HARDCUBE_SIZE,-HARDCUBE_SIZE,-HARDCUBE_SIZE, 1.0f, 1.0f, 0.0f, 0.0f, -1.0f },
	//��
	{ -HARDCUBE_SIZE,-HARDCUBE_SIZE,-HARDCUBE_SIZE, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f },
	{ HARDCUBE_SIZE,-HARDCUBE_SIZE,-HARDCUBE_SIZE, 1.0f, 0.0f, 0.0f, -1.0f, 0.0f },
	{ -HARDCUBE_SIZE,-HARDCUBE_SIZE, HARDCUBE_SIZE, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f },
	{ HARDCUBE_SIZE,-HARDCUBE_SIZE, HARDCUBE_SIZE, 1.0f, 1.0f, 0.0f, -1.0f, 0.0f },
	//���
	{ HARDCUBE_SIZE, HARDCUBE_SIZE, HARDCUBE_SIZE, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f },
	{ -HARDCUBE_SIZE, HARDCUBE_SIZE, HARDCUBE_SIZE, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f },
	{ HARDCUBE_SIZE,-HARDCUBE_SIZE, HARDCUBE_SIZE, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f },
	{ -HARDCUBE_SIZE,-HARDCUBE_SIZE, HARDCUBE_SIZE, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f },
	//��
	{ -HARDCUBE_SIZE, HARDCUBE_SIZE, HARDCUBE_SIZE, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f },
	{ -HARDCUBE_SIZE, HARDCUBE_SIZE,-HARDCUBE_SIZE, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f },
	{ -HARDCUBE_SIZE,-HARDCUBE_SIZE, HARDCUBE_SIZE, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f },
	{ -HARDCUBE_SIZE,-HARDCUBE_SIZE,-HARDCUBE_SIZE, 1.0f, 1.0f, -1.0f, 0.0f, 0.0f },
	//�E
	{ HARDCUBE_SIZE, HARDCUBE_SIZE,-HARDCUBE_SIZE, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f },
	{ HARDCUBE_SIZE, HARDCUBE_SIZE, HARDCUBE_SIZE, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f },
	{ HARDCUBE_SIZE,-HARDCUBE_SIZE,-HARDCUBE_SIZE, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f },
	{ HARDCUBE_SIZE,-HARDCUBE_SIZE, HARDCUBE_SIZE, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f },
};

static LPDIRECT3DVERTEXBUFFER9 vtxBuff, worldBuff;		//���_�o�b�t�@
static LPDIRECT3DVERTEXDECLARATION9 declare;			//���_�錾
static LPDIRECT3DTEXTURE9 texture[HARDCUBE_TEX_NUM];	//�e�N�X�`��
static LPD3DXEFFECT effect;								//�V�F�[�_
static LPDIRECT3DINDEXBUFFER9 indexBuff;				//�C���f�b�N�X�o�b�t�@

static D3DXMATRIX mtxWorld[HARDCUBE_NUM_MAX];			//���[���h�ϊ��s��
static HARD_CUBE_OBJECT cube[HARDCUBE_NUM_MAX];			//�n�[�h�L���[�u�z��
static OBJECT_FOR_TREE objectForTree[HARDCUBE_NUM_MAX];	//�Փ˔���pOBJECT_FOR_TREE�z��

//���ꏈ���֐��e�[�u��
static funcHardCube Enter[HardCubeStateMax] = {
	OnEnterHardCubeInit,
	OnEnterHardCubeMove,
	OnEnterHardCubeNormalAttack,
	OnEnterHardCubeHomingAttack,
	OnEnterHardCubeCharge,
	OnEnterHardCubeEscape,
	OnEnterHardCubeBezier,
	OnEnterHardCubeTutorial
};

//�X�V�����֐��e�[�u��
static funcHardCube Update[HardCubeStateMax] = {
	OnUpdateHardCubeInit,
	OnUpdateHardCubeMove,
	OnUpdateHardCubeNormalAttack,
	OnUpdateHardCubeHomingAttack,
	OnUpdateHardCubeCharge,
	OnUpdateHardCubeEscape,
	OnUpdateHardCubeBezier,
	OnUpdateHardCubeTutorial
};

/**************************************
�v���g�^�C�v�錾
***************************************/
void MoveHardCube(void);						//�ړ�����
void RotateHardCube(void);						//��]����
void CalcHardCubeWorldMatrix(void);				//���[���h�ϊ��s��v�Z����
void CheckDestroyHardCube(void);				//���S����	
void RegisterHardCubeToSpace(void);				//�Փˋ�Ԃւ̓o�^����
void OnUpdateHardCube(void);					//�e��ԍX�V����

/**************************************
����������
***************************************/
void InitHardCubeObject(int num)
{
	static bool initialized = false;
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�L���[�u�����͈�
	const float PosRange = 50.0f;
	const float RotRange = 5.0f;

	//�p�����[�^������
	HARD_CUBE_OBJECT *ptr = &cube[0];
	OBJECT_FOR_TREE *oft = &objectForTree[0];
	for (int i = 0; i < HARDCUBE_NUM_MAX; i++, ptr++, oft++)
	{
		ptr->pos = D3DXVECTOR3(RandomRangef(-PosRange, PosRange), RandomRangef(-PosRange, PosRange), RandomRangef(0.0f, 10000.0f));
		ptr->rot = D3DXVECTOR3(RandomRangef(0.0f, 3.1415f), RandomRangef(0.0f, 3.1415f), RandomRangef(0.0f, 3.1415f));
		ptr->scale = 0.0f;
		ptr->rotValue = D3DXVECTOR3(RandomRangef(-RotRange, RotRange), RandomRangef(-RotRange, RotRange), RandomRangef(-RotRange, RotRange));
		ptr->rotValue *= 0.01f;
		ptr->moveSpeed = RandomRangef(-10.0f, -5.0f);
		ptr->hp = HARDCUBE_INIT_HP;
		ptr->id = i;
		ptr->active = false;

		ptr->collider.pos = &ptr->pos;
		ptr->collider.offset = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		ptr->collider.length = D3DXVECTOR3(HARDCUBE_SIZE*1.5f, HARDCUBE_SIZE*1.5f, HARDCUBE_SIZE*1.5f);

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
		WORD index[6 * HARDCUBE_FIELD_NUM];
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
		D3DXCreateEffectFromFile(pDevice, HARDCUBE_EFFECT_NAME, 0, 0, 0, 0, &effect, NULL);

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
void UninitHardCubeObject(int num)
{
	HARD_CUBE_OBJECT *ptr = &cube[0];
	for (int i = 0; i < HARDCUBE_NUM_MAX; i++, ptr++)
	{
		DisableHardCube(ptr);
	}

	if (num == 0)
	{
		SAFE_RELEASE(vtxBuff);
		SAFE_RELEASE(worldBuff);
		SAFE_RELEASE(effect);
		SAFE_RELEASE(declare);
		SAFE_RELEASE(indexBuff);

		for (int i = 0; i < HARDCUBE_TEX_NUM; i++) 
		{
			SAFE_RELEASE(texture[i]);
		}
	}
}

/**************************************
�X�V����
***************************************/
void UpdateHardCubeObject(void)
{
	CheckDestroyHardCube();
	OnUpdateHardCube();
	RotateHardCube();
	CalcHardCubeWorldMatrix();
	RegisterHardCubeToSpace();
}

/**************************************
�`�揈��
***************************************/
void DrawHardCubeObject(void)
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
	pDevice->SetStreamSourceFreq(0, D3DSTREAMSOURCE_INDEXEDDATA | (HARDCUBE_NUM_MAX));
	pDevice->SetStreamSourceFreq(1, D3DSTREAMSOURCE_INSTANCEDATA | 1);

	//���_�錾�A�X�g���[���\�[�X�A�C���f�b�N�X�o�b�t�@���Z�b�g
	pDevice->SetVertexDeclaration(declare);
	pDevice->SetStreamSource(0, vtxBuff, 0, sizeof(HARDCUBE_VTX));
	pDevice->SetStreamSource(1, worldBuff, 0, sizeof(D3DXMATRIX));
	pDevice->SetIndices(indexBuff);

	//�r���[�s��A�v���W�F�N�V�����s���ݒu
	effect->SetMatrix("mtxView", &GetBattleCameraView());
	effect->SetMatrix("mtxProj", &GetBattleCameraProjection());

	//�e�N�X�`���̐������`��
	for (int i = 0; i < HARDCUBE_TEX_NUM; i++)
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

		pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, HARDCUBE_VTX_NUM, 0, HARDCUBE_FIELD_NUM * NUM_POLYGON);

		effect->EndPass();
		effect->End();
	}
	pDevice->SetStreamSourceFreq(0, 1);
	pDevice->SetStreamSourceFreq(1, 1);

#if 0
	HARD_CUBE_OBJECT *ptr = &cube[0];
	for (int i = 0; i < HARDCUBE_NUM_MAX; i++, ptr++)
	{
		DrawBoundingCube(&ptr->collider);
	}
#endif
}

/**************************************
��]����
***************************************/
void RotateHardCube(void)
{
	HARD_CUBE_OBJECT *ptr = &cube[0];
	for (int i = 0; i < HARDCUBE_NUM_MAX; i++, ptr++)
	{
		ptr->rot += ptr->rotValue;
	}
}

/**************************************
���[���h�ϊ��s��v�Z����
***************************************/
void CalcHardCubeWorldMatrix(void)
{
	D3DXMATRIX *pWorld = &mtxWorld[0];
	D3DXMATRIX mtxRot, mtxTranslate, mtxScale;
	HARD_CUBE_OBJECT *ptr = &cube[0];
	for (int i = 0; i < HARDCUBE_NUM_MAX; i++, ptr++, pWorld++)
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
void CheckDestroyHardCube(void)
{
	HARD_CUBE_OBJECT *ptr = &cube[0];
	for (int i = 0; i < HARDCUBE_NUM_MAX; i++, ptr++)
	{
		if (!ptr->active)
			continue;

		if (ptr->hp <= 0.0f)
		{
			SetCubeExplosion(ptr->pos, PARTICLE_HARDCUBE_COLOR);
			PlaySE(SOUND_SMALLEXPL);
			//DamageAllCubeObject();

			if (ptr->type == HardCubeHomingType)
			{
				SetCameraShaker(BONUSCUBE_CAMERA_SHAKE_LENGTH);
				SetShockBlur(ptr->pos);
				PlaySE(SOUND_MIDDLEEXPL);
			}
			
			DisableHardCube(ptr);
		}
	}
}

/**************************************
�Փˋ�Ԃւ̓o�^����
***************************************/
void RegisterHardCubeToSpace(void)
{
	HARD_CUBE_OBJECT *ptr = &cube[0];
	OBJECT_FOR_TREE *oft = &objectForTree[0];

	for (int i = 0; i < HARDCUBE_NUM_MAX; i++, ptr++, oft++)
	{
		RemoveObjectFromSpace(oft);

		if (ptr->active)
		{
			RegisterObjectToSpace(&ptr->collider, oft, OFT_HARDCUBE);
		}
	}
}

/**************************************
���b�N�I������
***************************************/
void LockonHardCubeObject(void)
{
	HARD_CUBE_OBJECT *ptr = &cube[0];
	TARGETSITE *targetSite = GetTargetSiteAdr(0);

	for (int i = 0; i < PLAYERMODEL_MAX; i++, targetSite++)
	{
		if (!targetSite->active)
			continue;

		ptr = &cube[0];
		for (int j = 0; j < HARDCUBE_NUM_MAX; j++, ptr++)
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
��A�N�e�B�u����
***************************************/
void DisableHardCube(HARD_CUBE_OBJECT *ptr)
{
	ptr->active = false;
	ptr->scale = 0.0f;
	RemoveObjectFromSpace(&objectForTree[ptr->id]);
}

/**************************************
�n�[�h�L���[�u�Z�b�g����
***************************************/
bool SetHardCubeObject(D3DXVECTOR3 *setPos)
{
	HARD_CUBE_OBJECT *ptr = &cube[0];
	OBJECT_FOR_TREE *oft = &objectForTree[0];
	for (int i = 0; i < HARDCUBE_NUM_MAX; i++, ptr++, oft++)
	{
		if (ptr->active)
			continue;

		ptr->pos = *setPos;
		ptr->active = true;
		RegisterObjectToSpace(&ptr->collider, oft, OFT_HARDCUBE);
		ChangeStateHardCube(ptr, HardCubeInit);
		return true;
	}

	return false;
}

/**************************************
��ԑJ�ڏ���
***************************************/
void ChangeStateHardCube(HARD_CUBE_OBJECT *ptr, int nextState)
{
	ptr->currentState = nextState;
	Enter[ptr->currentState](ptr);
}

/**************************************
�e��ԍX�V����
***************************************/
void OnUpdateHardCube(void)
{
	HARD_CUBE_OBJECT *ptr = &cube[0];
	for (int i = 0; i < HARDCUBE_NUM_MAX; i++, ptr++)
	{
		if(ptr->active)
			Update[ptr->currentState](ptr);
	}
}

/**************************************
�n�[�h�L���[�u�Z�b�g����(from�X�e�[�W�f�[�^)
***************************************/
bool SetHardCubeObjectFromData(STAGE_DATA *data)
{
	HARD_CUBE_OBJECT *ptr = &cube[0];
	OBJECT_FOR_TREE *oft = &objectForTree[0];
	for (int i = 0; i < HARDCUBE_NUM_MAX; i++, ptr++, oft++)
	{
		if (ptr->active)
			continue;

		ptr->pos = data->initPos;
		ptr->goalPos = data->targetPos;
		ptr->type = data->type;
		ptr->controller1 = data->controller1;
		ptr->controller2 = data->controller2;
		ptr->active = true;
		RegisterObjectToSpace(&ptr->collider, oft, OFT_HARDCUBE);
		ChangeStateHardCube(ptr, HardCubeInit);
		return true;
	}

	return false;
}

/**************************************
�n�[�h�L���[�u�Z�b�g����(�p�����[�^���ڎw��)
***************************************/
HARD_CUBE_OBJECT* SetHardCubeObjectDirectData(D3DXVECTOR3 startPos, D3DXVECTOR3 goalPos, int type, D3DXVECTOR3 ctrl1, D3DXVECTOR3 ctrl2)
{
	HARD_CUBE_OBJECT *ptr = &cube[0];
	OBJECT_FOR_TREE *oft = &objectForTree[0];
	for (int i = 0; i < HARDCUBE_NUM_MAX; i++, ptr++, oft++)
	{
		if (ptr->active)
			continue;

		ptr->pos = startPos;
		ptr->goalPos = goalPos;
		ptr->type = type;
		ptr->controller1 = ctrl1;
		ptr->controller2 = ctrl2;
		ptr->active = true;
		RegisterObjectToSpace(&ptr->collider, oft, OFT_HARDCUBE);
		ChangeStateHardCube(ptr, HardCubeInit);
		return ptr;
	}

	return NULL;
}