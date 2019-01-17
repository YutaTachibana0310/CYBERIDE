//=====================================
//
//�L���[�u�p�[�e�B�N������[cubeParticle.cpp]
//Author:GP11A341 21 ���ԗY��
//
//=====================================
#include "cubeParticle.h"
#include "battleCamera.h"
#include "Easing.h"

/**************************************
�}�N����`
***************************************/
#define CUBEPARTICLE_EFFECT_NAME			"data/EFFECT/cubeParticle.fx"
#define CUBEPARTICLE_SIZE					(10.0f)
#define CUBEPARTICLE_VTX_NUM				(24)
#define CUBEPARTICLE_NUM_MAX				(2048)
#define CUBEPARTICLE_FIELD_NUM				(6)
#define CUBEPARTICLE_MOVE_SPEED				(10.0f)
#define CUBEPARTICLE_LIFEFRAME				(30)

static const char* texName[] = {
	"data/TEXTURE/OBJECT/circuit01.jpg",
	"data/TEXTURE/OBJECT/circuit02.png",
	"data/TEXTURE/OBJECT/circuit03.png",
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
//�L���[�u�p�[�e�B�N���̒P�ʒ��_
static CUBE_VTX vtx[CUBEPARTICLE_VTX_NUM] = {
	//��
	{ -CUBEPARTICLE_SIZE, CUBEPARTICLE_SIZE, CUBEPARTICLE_SIZE, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f },
	{ CUBEPARTICLE_SIZE, CUBEPARTICLE_SIZE, CUBEPARTICLE_SIZE, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f },
	{ -CUBEPARTICLE_SIZE, CUBEPARTICLE_SIZE,-CUBEPARTICLE_SIZE, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f },
	{ CUBEPARTICLE_SIZE, CUBEPARTICLE_SIZE,-CUBEPARTICLE_SIZE, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f },
	//�O
	{ -CUBEPARTICLE_SIZE, CUBEPARTICLE_SIZE,-CUBEPARTICLE_SIZE, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f },
	{ CUBEPARTICLE_SIZE, CUBEPARTICLE_SIZE,-CUBEPARTICLE_SIZE, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f },
	{ -CUBEPARTICLE_SIZE,-CUBEPARTICLE_SIZE,-CUBEPARTICLE_SIZE, 0.0f, 1.0f, 0.0f, 0.0f, -1.0f },
	{ CUBEPARTICLE_SIZE,-CUBEPARTICLE_SIZE,-CUBEPARTICLE_SIZE, 1.0f, 1.0f, 0.0f, 0.0f, -1.0f },
	//��
	{ -CUBEPARTICLE_SIZE,-CUBEPARTICLE_SIZE,-CUBEPARTICLE_SIZE, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f },
	{ CUBEPARTICLE_SIZE,-CUBEPARTICLE_SIZE,-CUBEPARTICLE_SIZE, 1.0f, 0.0f, 0.0f, -1.0f, 0.0f },
	{ -CUBEPARTICLE_SIZE,-CUBEPARTICLE_SIZE, CUBEPARTICLE_SIZE, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f },
	{ CUBEPARTICLE_SIZE,-CUBEPARTICLE_SIZE, CUBEPARTICLE_SIZE, 1.0f, 1.0f, 0.0f, -1.0f, 0.0f },
	//���
	{ CUBEPARTICLE_SIZE, CUBEPARTICLE_SIZE, CUBEPARTICLE_SIZE, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f },
	{ -CUBEPARTICLE_SIZE, CUBEPARTICLE_SIZE, CUBEPARTICLE_SIZE, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f },
	{ CUBEPARTICLE_SIZE,-CUBEPARTICLE_SIZE, CUBEPARTICLE_SIZE, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f },
	{ -CUBEPARTICLE_SIZE,-CUBEPARTICLE_SIZE, CUBEPARTICLE_SIZE, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f },
	//��
	{ -CUBEPARTICLE_SIZE, CUBEPARTICLE_SIZE, CUBEPARTICLE_SIZE, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f },
	{ -CUBEPARTICLE_SIZE, CUBEPARTICLE_SIZE,-CUBEPARTICLE_SIZE, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f },
	{ -CUBEPARTICLE_SIZE,-CUBEPARTICLE_SIZE, CUBEPARTICLE_SIZE, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f },
	{ -CUBEPARTICLE_SIZE,-CUBEPARTICLE_SIZE,-CUBEPARTICLE_SIZE, 1.0f, 1.0f, -1.0f, 0.0f, 0.0f },
	//�E
	{ CUBEPARTICLE_SIZE, CUBEPARTICLE_SIZE,-CUBEPARTICLE_SIZE, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f },
	{ CUBEPARTICLE_SIZE, CUBEPARTICLE_SIZE, CUBEPARTICLE_SIZE, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f },
	{ CUBEPARTICLE_SIZE,-CUBEPARTICLE_SIZE,-CUBEPARTICLE_SIZE, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f },
	{ CUBEPARTICLE_SIZE,-CUBEPARTICLE_SIZE, CUBEPARTICLE_SIZE, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f },
};

static LPDIRECT3DVERTEXBUFFER9 vtxBuff, worldBuff, colorBuff;		//���_�o�b�t�@
static LPDIRECT3DVERTEXDECLARATION9 declare;						//���_�錾
static LPDIRECT3DTEXTURE9 texture[3];								//�e�N�X�`��
static LPD3DXEFFECT effect;											//�V�F�[�_
static LPDIRECT3DINDEXBUFFER9 indexBuff;							//�C���f�b�N�X�o�b�t�@

static D3DXVECTOR3 pos[CUBEPARTICLE_NUM_MAX], rot[CUBEPARTICLE_NUM_MAX];	//�L���[�u�̊e�p�����[�^
static float scale[CUBEPARTICLE_NUM_MAX];
static D3DXMATRIX mtxWorld[CUBEPARTICLE_NUM_MAX];			//���[���h�ϊ��s��
static D3DXCOLOR color[CUBEPARTICLE_NUM_MAX];				//�p�[�e�B�N���F

static CUBE_PARTICLE cube[CUBEPARTICLE_NUM_MAX];			//�L���[�u�p�[�e�B�N���z��

/**************************************
�v���g�^�C�v�錾
***************************************/
void MoveCubeParticle(void);					//�ړ�����
void ScaleCubeParticle(void);					//�X�P�[���v�Z����
void CalcCubeParticleWorldMartix(void);			//���[���h�ϊ��s��v�Z����
void CheckDestroyCubeParticle(void);			//���S����

/**************************************
����������
***************************************/
void InitCubeParticle(int num)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	const float InitPos = -9999.9f, InitScale = 0.0f, InitRot = 0.0f;

	//�p�����[�^������
	CUBE_PARTICLE *ptr = &cube[0];
	for (int i = 0; i < CUBEPARTICLE_NUM_MAX; i++, ptr++)
	{
		pos[i] = D3DXVECTOR3(InitPos, InitPos, InitPos);
		rot[i] = D3DXVECTOR3(InitRot, InitRot, InitRot);
		scale[i] = InitScale;
		color[i] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		ptr->active = false;
	}

	//����݂̂̏�����
	if (num == 0)
	{
		//���_�o�b�t�@�쐬
		pDevice->CreateVertexBuffer(sizeof(vtx), 0, 0, D3DPOOL_MANAGED, &vtxBuff, 0);
		pDevice->CreateVertexBuffer(sizeof(mtxWorld), 0, 0, D3DPOOL_MANAGED, &worldBuff, 0);
		pDevice->CreateVertexBuffer(sizeof(color), 0, 0, D3DPOOL_MANAGED, &colorBuff, 0);
		CopyVtxBuff(sizeof(vtx), vtx, vtxBuff);
		CopyVtxBuff(sizeof(mtxWorld), mtxWorld, worldBuff);
		CopyVtxBuff(sizeof(color), color, colorBuff);

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
			{ 2, 0, D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_COLOR, 0 },			//�F
			D3DDECL_END()
		};
		pDevice->CreateVertexDeclaration(declareElems, &declare);

		//�C���f�b�N�X�o�b�t�@�쐬
		WORD index[6 * CUBEPARTICLE_FIELD_NUM];
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
		D3DXCreateEffectFromFile(pDevice, CUBEPARTICLE_EFFECT_NAME, 0, 0, 0, 0, &effect, NULL);

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
void UninitCubeParticle(int num)
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
void UpdateCubeParticle(void)
{
	CheckDestroyCubeParticle();

	MoveCubeParticle();

	ScaleCubeParticle();

	CalcCubeParticleWorldMartix();

	CopyVtxBuff(sizeof(color), color, colorBuff);
}

/**************************************
�`�揈��
***************************************/
void DrawCubeParticle(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DLIGHT9 light1, light2, light3;

	pDevice->GetLight(0, &light1);
	pDevice->GetLight(0, &light2);
	pDevice->GetLight(0, &light3);

	pDevice->SetStreamSourceFreq(0, D3DSTREAMSOURCE_INDEXEDDATA | (CUBEPARTICLE_NUM_MAX));
	pDevice->SetStreamSourceFreq(1, D3DSTREAMSOURCE_INSTANCEDATA | 1);
	pDevice->SetStreamSourceFreq(2, D3DSTREAMSOURCE_INSTANCEDATA | 1);

	pDevice->SetVertexDeclaration(declare);
	pDevice->SetStreamSource(0, vtxBuff, 0, sizeof(CUBE_VTX));
	pDevice->SetStreamSource(1, worldBuff, 0, sizeof(D3DXMATRIX));
	pDevice->SetStreamSource(2, colorBuff, 0, sizeof(D3DXCOLOR));
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

		pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, CUBEPARTICLE_VTX_NUM, 0, CUBEPARTICLE_FIELD_NUM * NUM_POLYGON);

		effect->EndPass();
		effect->End();
	}

	pDevice->SetStreamSourceFreq(0, 1);
	pDevice->SetStreamSourceFreq(1, 1);
	pDevice->SetStreamSourceFreq(2, 1);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

/**************************************
�ړ�����
***************************************/
void MoveCubeParticle(void)
{
	D3DXVECTOR3 *pPos = &pos[0];
	CUBE_PARTICLE *ptr = &cube[0];
	for (int i = 0; i < CUBEPARTICLE_NUM_MAX; i++, ptr++, pPos++)
	{
		if (!ptr->active)
			continue;

		float t = ptr->cntFrame / (float)CUBEPARTICLE_LIFEFRAME;
		float speed = EaseOutCubic(t, CUBEPARTICLE_MOVE_SPEED, 0.0f);

		*pPos += ptr->moveDir * speed;
	}
}

/**************************************
�X�P�[���v�Z����
***************************************/
void ScaleCubeParticle(void)
{
	float *pScale = &scale[0];
	CUBE_PARTICLE *ptr = &cube[0];
	for (int i = 0; i < CUBEPARTICLE_NUM_MAX; i++, ptr++, pScale++)
	{
		if (!ptr->active)
			continue;

		float t = ptr->cntFrame / (float)CUBEPARTICLE_LIFEFRAME;
		float easingScale = EaseOutCubic(t, 1.0f, 0.1f);

		*pScale = easingScale;
	}
}

/**************************************
���[���h�ϊ��s��v�Z����
***************************************/
void CalcCubeParticleWorldMartix(void)
{
	D3DXMATRIX *pWorld = &mtxWorld[0];
	D3DXMATRIX mtxRot, mtxTranslate, mtxScale;
	D3DXVECTOR3 *pPos = &pos[0];
	D3DXVECTOR3 *pRot = &rot[0];
	float *pScale = &scale[0];

	for (int i = 0; i < CUBEPARTICLE_NUM_MAX; i++, pPos++, pRot++, pWorld++, pScale++)
	{
		D3DXMatrixIdentity(pWorld);

		D3DXMatrixScaling(&mtxScale, *pScale, *pScale, *pScale);
		D3DXMatrixMultiply(pWorld, pWorld, &mtxScale);

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
void CheckDestroyCubeParticle(void)
{
	CUBE_PARTICLE *ptr = &cube[0];
	float *pScale = &scale[0];
	for (int i = 0; i < CUBEPARTICLE_NUM_MAX; i++, ptr++, pScale++)
	{
		if (!ptr->active)
			continue;

		//�J�E���g�A�b�v
		ptr->cntFrame++;

		//�����ȑO�Ȃ瑁�����^�[��
		if (ptr->cntFrame < (float)CUBEPARTICLE_LIFEFRAME)
			continue;

		ptr->active = false;
		*pScale = 0.0f;
	}
}

/**************************************
�Z�b�g����
***************************************/
void SetCubeParticle(D3DXVECTOR3 setPos, D3DXCOLOR col)
{
	CUBE_PARTICLE *ptr = &cube[0];
	D3DXVECTOR3 *pPos = &pos[0], *pRot = &rot[0];
	D3DXCOLOR *pCol = &color[0];
	float * pScale = &scale[0];
	for (int i = 0; i < CUBEPARTICLE_NUM_MAX; i++, ptr++, pPos++, pScale++, pRot++, pCol++)
	{
		if (ptr->active)
			continue;

		*pPos = setPos;
		*pScale = 1.0f;
		*pRot = D3DXVECTOR3(RandomRangef(0.0f, D3DX_PI), RandomRangef(0.0f, D3DX_PI), RandomRangef(0.0f, D3DX_PI));
		*pCol = col;
		ptr->cntFrame = 0;
		D3DXVECTOR3 tmpVec = D3DXVECTOR3(RandomRangef(-1.0f, 1.0f), RandomRangef(-1.0f, 1.0f), RandomRangef(-1.0f, 1.0f));
		D3DXVec3Normalize(&ptr->moveDir, &tmpVec);
		ptr->active = true;

		return;
	}
}