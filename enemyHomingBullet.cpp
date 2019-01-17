//=====================================
//
//�G�l�~�[�z�[�~���O�o���b�g����[enemyHomingBullette.cpp]
//Author:GP11A341 21 ���ԗY��
//
//=====================================
#include "enemyHomingBullet.h"
#include "battleCamera.h"
#include "playerModel.h"
#include "particleFramework.h"
#include "enemyBulletTrail.h"

/**************************************
�}�N����`
***************************************/
#define ENEMYHOMINGBULLET_TEXTURE_NAME			"data/TEXTURE/ENEMY/enemyBullet01.png"
#define ENEMYHOMINGBULLET_TEXTURE_SIZE_X		(6)
#define ENEMYHOMINGBULLET_TEXTURE_SIZE_Y		(6)
#define ENEMYHOMINGBULLET_DISABLE_BORDER_Z		(-200.0f)
#define ENEMYHOMINGBULLET_ACCELERATION_MAX		(1500.0f)
#define ENEMYHOMINGBULLET_SHADER_NAME			"data/EFFECT/particle.fx"

/**************************************
�\���̒�`
***************************************/

/**************************************
�O���[�o���ϐ�
***************************************/
static LPDIRECT3DTEXTURE9 texture;
static ENEMYHOMINGBULLET bullet[ENEMYHOMINGBULLET_MAX];

static D3DXMATRIX pos[ENEMYHOMINGBULLET_MAX];			//���[���h���W�z��
static VERTEX_COLOR vtxColor[ENEMYHOMINGBULLET_MAX];	//���_�f�B�t���[�Y�z��
static VERTEX_UV vtxUV[ENEMYHOMINGBULLET_MAX];			//UV���W�z��

//�P�ʒ��_�̐ݒ�
static VERTEX_PARTICLE vtx[NUM_VERTEX] = {
	{ -ENEMYHOMINGBULLET_TEXTURE_SIZE_X,  ENEMYHOMINGBULLET_TEXTURE_SIZE_Y, 0.0f, 0.0f, 0.0f },
	{  ENEMYHOMINGBULLET_TEXTURE_SIZE_X,  ENEMYHOMINGBULLET_TEXTURE_SIZE_Y, 0.0f, 1.0f, 0.0f },
	{ -ENEMYHOMINGBULLET_TEXTURE_SIZE_X, -ENEMYHOMINGBULLET_TEXTURE_SIZE_Y, 0.0f, 0.0f, 1.0f },
	{  ENEMYHOMINGBULLET_TEXTURE_SIZE_X, -ENEMYHOMINGBULLET_TEXTURE_SIZE_Y, 0.0f, 1.0f, 1.0f },
};

//�e�풸�_�o�b�t�@
static LPDIRECT3DVERTEXBUFFER9 vtxBuff = NULL;
static LPDIRECT3DVERTEXBUFFER9 uvBuff = NULL;
static LPDIRECT3DVERTEXBUFFER9 posBuff = NULL;
static LPDIRECT3DVERTEXBUFFER9 colorBuff = NULL;

static LPDIRECT3DVERTEXDECLARATION9 declare = NULL;		//���_�錾
static LPD3DXEFFECT effect = NULL;						//�V�F�[�_�[
static LPDIRECT3DINDEXBUFFER9 indexBuff = NULL;			//�C���f�b�N�X�o�b�t�@		

/**************************************
�v���g�^�C�v�錾
***************************************/
//void CreateEnemyHomingBulletVertexBuffer(void);
void CalcEnemyHomingBulletAcceleration(ENEMYHOMINGBULLET *ptr);

/**************************************
����������
***************************************/
void InitEnemyHomingBullet(int num)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	if (num == 0)
	{
		//�e�N�X�`���ǂݍ���
		texture = CreateTextureFromFile((LPSTR)ENEMYHOMINGBULLET_TEXTURE_NAME, pDevice);

		//���_�쐬
		//CreateEnemyHomingBulletVertexBuffer();
		MakeParticleVertexBuffer(vtx, ENEMYHOMINGBULLET_MAX, &vtxBuff);
		MakeParticleUVBuffer(ENEMYHOMINGBULLET_MAX, vtxUV, &uvBuff);
		MakeParticleWorldBuffer(ENEMYHOMINGBULLET_MAX, pos, &posBuff);
		MakeParticleColorBuffer(ENEMYHOMINGBULLET_MAX, vtxColor, &colorBuff);

		//���_�錾�쐬
		D3DVERTEXELEMENT9 declareElems[] = {
			{ 0, 0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
			{ 0, 12, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0 },
			{ 1, 0, D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 1 },
			{ 1, 16, D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 2 },
			{ 1, 32, D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 3 },
			{ 1, 48, D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 4 },
			{ 2, 0, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 5 },
			{ 3, 0, D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_COLOR, 0 },
			D3DDECL_END()
		};
		pDevice->CreateVertexDeclaration(declareElems, &declare);

		//�V�F�[�_�[�ǂݍ���
		D3DXCreateEffectFromFile(pDevice, ENEMYHOMINGBULLET_SHADER_NAME, 0, 0, 0, 0, &effect, NULL);

		//�C���f�b�N�X�o�b�t�@�쐬
		WORD index[6] = { 0, 1, 2, 2, 1, 3 };
		pDevice->CreateIndexBuffer(sizeof(index), 0, D3DFMT_INDEX16, D3DPOOL_MANAGED, &indexBuff, 0);
		void *p = NULL;
		indexBuff->Lock(0, 0, &p, 0);
		memcpy(p, index, sizeof(index));
		indexBuff->Unlock();
	}

	ENEMYHOMINGBULLET *ptr = &bullet[0];
	for (int i = 0; i < ENEMYHOMINGBULLET_MAX; i++, ptr++)
	{
		ptr->active = false;
		vtxColor[i].r = vtxColor[i].g = vtxColor[i].b = 1.0f;
		ptr->alpha = 0.0f;
	}
}

/**************************************
�I������
***************************************/
void UninitEnemyHomingBullet(int num)
{
	if (num == 0)
	{
		SAFE_RELEASE(texture);
		SAFE_RELEASE(vtxBuff);
		SAFE_RELEASE(vtxBuff);
		SAFE_RELEASE(uvBuff);
		SAFE_RELEASE(posBuff);
		SAFE_RELEASE(colorBuff);
	}

	ENEMYHOMINGBULLET *ptr = &bullet[0];
	for (int i = 0; i < ENEMYHOMINGBULLET_MAX; i++, ptr++)
	{
		ptr->active = false;
		ptr->alpha = 0.0f;
	}
}

/**************************************
�X�V����
***************************************/
void UpdateEnemyHomingBullet(void)
{
	ENEMYHOMINGBULLET *ptr = &bullet[0];
	D3DXMATRIX mtxTranslate;
	D3DXMATRIX *pPos = &pos[0];

	for (int i = 0; i < ENEMYHOMINGBULLET_MAX; i++, ptr++, pPos++)
	{

		if (!ptr->active)
		{
			continue;
		}

		//�g���C���ݒ�
		SetEnemyHomingBulletTrail(ptr->pos, HomingEnemyBulletTrail);

		//�z�[�~���O�̉����x�v�Z����
		CalcEnemyHomingBulletAcceleration(ptr);

		//���W�X�V
		ptr->pos += ptr->velocity / 60.0f;

		//�J���������Ȃ��A�N�e�B�u��
		if (ptr->pos.z < ENEMYHOMINGBULLET_DISABLE_BORDER_Z)
		{
			ptr->active = false;
			ptr->alpha = 0.0f;
			vtxColor[i].a = 0.0f;
		}

		//���[���h�z��̍X�V
		D3DXMatrixIdentity(pPos);
		GetInvRotBattleCamera(pPos);
		D3DXMatrixTranslation(&mtxTranslate, ptr->pos.x, ptr->pos.y, ptr->pos.z);
		D3DXMatrixMultiply(pPos, pPos, &mtxTranslate);
	}

	//���_�o�b�t�@�Ƀ������R�s�[
	CopyVtxBuff(sizeof(D3DXMATRIX) * ENEMYHOMINGBULLET_MAX, pos, posBuff);
	CopyVtxBuff(sizeof(VERTEX_COLOR) * ENEMYHOMINGBULLET_MAX, vtxColor, colorBuff);
	
}

/**************************************
�`�揈��
***************************************/
void DrawEnemyHomingBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//set RenderState
	pDevice->SetRenderState(D3DRS_LIGHTING, false);
	//pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, true);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, false);
	pDevice->SetFVF(FVF_VERTEX_3D);

	//���_�v�f�錾
	pDevice->SetVertexDeclaration(declare);

	//�X�g���[�����g����ݒ�
	pDevice->SetStreamSourceFreq(0, D3DSTREAMSOURCE_INDEXEDDATA | ENEMYHOMINGBULLET_MAX);
	pDevice->SetStreamSourceFreq(1, D3DSTREAMSOURCE_INSTANCEDATA | 1);
	pDevice->SetStreamSourceFreq(2, D3DSTREAMSOURCE_INSTANCEDATA | 1);
	pDevice->SetStreamSourceFreq(3, D3DSTREAMSOURCE_INSTANCEDATA | 1);

	//�X�g���[���\�[�X�ݒ�
	pDevice->SetStreamSource(0, vtxBuff, 0, sizeof(VERTEX_PARTICLE));
	pDevice->SetStreamSource(1, posBuff, 0, sizeof(D3DXMATRIX));
	pDevice->SetStreamSource(2, uvBuff, 0, sizeof(VERTEX_UV));
	pDevice->SetStreamSource(3, colorBuff, 0, sizeof(VERTEX_COLOR));
	pDevice->SetIndices(indexBuff);

	//�V�F�[�_�[�̃O���[�o���ϐ���ݒ�
	effect->SetTexture("tex", texture);
	effect->SetMatrix("mtxView", &GetBattleCameraView());
	effect->SetMatrix("mtxProj", &GetBattleCameraProjection());

	//�g�p�V�F�[�_�[�ݒ�
	effect->SetTechnique("tech");
	UINT passNum = 0;
	effect->Begin(&passNum, 0);
	effect->BeginPass(0);

	//�`��
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, NUM_VERTEX, 0, NUM_POLYGON);

	//���Z�`��
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, NUM_VERTEX, 0, NUM_POLYGON);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//�V�F�[�_�I���錾
	effect->EndPass();
	effect->End();

	//�X�g���[�����g�������Ƃɖ߂�
	pDevice->SetStreamSourceFreq(0, 1);
	pDevice->SetStreamSourceFreq(1, 1);
	pDevice->SetStreamSourceFreq(2, 1);

	pDevice->SetRenderState(D3DRS_LIGHTING, true);
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, false);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, true);
}

#if 0
/**************************************
���_�쐬����
***************************************/
void CreateEnemyHomingBulletVertexBuffer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * NUM_VERTEX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&vtxBuff,
		0)))
	{
		return;
	}

	VERTEX_3D *pVtx;
	vtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].vtx = D3DXVECTOR3(-ENEMYHOMINGBULLET_TEXTURE_SIZE_X, ENEMYHOMINGBULLET_TEXTURE_SIZE_Y, 0.0f);
	pVtx[1].vtx = D3DXVECTOR3(ENEMYHOMINGBULLET_TEXTURE_SIZE_X, ENEMYHOMINGBULLET_TEXTURE_SIZE_Y, 0.0f);
	pVtx[2].vtx = D3DXVECTOR3(-ENEMYHOMINGBULLET_TEXTURE_SIZE_X, -ENEMYHOMINGBULLET_TEXTURE_SIZE_Y, 0.0f);
	pVtx[3].vtx = D3DXVECTOR3(ENEMYHOMINGBULLET_TEXTURE_SIZE_X, -ENEMYHOMINGBULLET_TEXTURE_SIZE_Y, 0.0f);

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
#endif

/**************************************
�Z�b�g����
***************************************/
void SetEnemyHomingBullet(D3DXVECTOR3 pos, D3DXVECTOR3 initVelocity, int reachFrame)
{
	ENEMYHOMINGBULLET *ptr = &bullet[0];

	for (int i = 0; i < ENEMYHOMINGBULLET_MAX; i++, ptr++)
	{
		if (ptr->active)
		{
			continue;
		}

		ptr->pos = pos;
		ptr->targetPlayerID = 0;
		ptr->cntFrame = ptr->reachFrame = reachFrame;
		ptr->alpha = 1.0f;
		vtxColor[i].a = 1.0f;
		ptr->velocity = initVelocity;
		ptr->active = true;
		return;
	}
}

/**************************************
�����x�v�Z����
***************************************/
void CalcEnemyHomingBulletAcceleration(ENEMYHOMINGBULLET *ptr)
{
	if (ptr->cntFrame <= 0)
	{
		return;
	}

	float time = ptr->cntFrame / 60.0f;

	PLAYERMODEL *player = GetPlayerAdr(ptr->targetPlayerID);
	D3DXVECTOR3 diff = player->pos - ptr->pos;

 	D3DXVECTOR3 acceleration = (diff - ptr->velocity * time) * 2.0f / (time * time);
	if (D3DXVec3LengthSq(&acceleration) > powf(ENEMYHOMINGBULLET_ACCELERATION_MAX, 2))
	{
		D3DXVec3Normalize(&acceleration, &acceleration);
		acceleration = acceleration * ENEMYHOMINGBULLET_ACCELERATION_MAX;
	}

	ptr->velocity += acceleration / 60.0f;

	ptr->cntFrame--;
}