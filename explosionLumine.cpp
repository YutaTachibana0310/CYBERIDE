//=====================================
//
//�������~�l����[explosionLumine.cpp]
//Author:GP11A341 21 ���ԗY��
//
//=====================================
#include "explosionLumine.h"
#include "particleManager.h"
#include "Easing.h"
#include "battleCamera.h"
#include "particleFramework.h"

/**************************************
�}�N����`
***************************************/
#define EXPLOSIONLUMINE_NUM_MAX				(1024)
#define EXPLOSIONLUMINE_SIZE				(6.0f)
#define EXPLOSIONLUMINE_TEX_NAME			"data/TEXTURE/PARTICLE/explosionLumine.png"
#define EXPLOSIONLUMINE_LIFEFRAME_BASE		(60)
#define EXPLOSIONLUMINE_LIFEFRAME_RANGE		(30)
#define EXPLOSIONLUMINE_POS_RANGE			(30.0f)

/**************************************
�\���̒�`
***************************************/

/**************************************
�O���[�o���ϐ�
***************************************/
//�P�ʒ��_
static VERTEX_PARTICLE vtx[NUM_VERTEX] = {
	{ -EXPLOSIONLUMINE_SIZE, EXPLOSIONLUMINE_SIZE, 0.0f, 0.0f, 0.0f },
	{  EXPLOSIONLUMINE_SIZE, EXPLOSIONLUMINE_SIZE, 0.0f, 1.0f, 0.0f },
	{ -EXPLOSIONLUMINE_SIZE,-EXPLOSIONLUMINE_SIZE, 0.0f, 0.0f, 1.0f },
	{  EXPLOSIONLUMINE_SIZE,-EXPLOSIONLUMINE_SIZE, 0.0f, 1.0f, 1.0f },
};

static LPDIRECT3DVERTEXBUFFER9 vtxBuff, worldBuff, uvBuff, colorBuff;//���_�o�b�t�@
static LPDIRECT3DTEXTURE9 texture;								//�e�N�X�`��
static LPDIRECT3DINDEXBUFFER9 indexBuff;						//�C���f�b�N�X�o�b�t�@

static VERTEX_UV vtxUV[EXPLOSIONLUMINE_NUM_MAX];				//UV���W�z��
static D3DXVECTOR3 pos[EXPLOSIONLUMINE_NUM_MAX];				//���W�z��
static VERTEX_COLOR vtxColor[EXPLOSIONLUMINE_NUM_MAX];			//�f�B�t���[�Y�z��
static D3DXMATRIX mtxWorld[EXPLOSIONLUMINE_NUM_MAX];			//���[���h�ϊ��s��

static EXPLOSION_LUMINE lumine[EXPLOSIONLUMINE_NUM_MAX];		//�p�[�e�B�N���z��


/**************************************
�v���g�^�C�v�錾
***************************************/

/**************************************
����������
***************************************/
void InitExplosionLumine(int num)
{
	static bool initialized = false;
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	EXPLOSION_LUMINE *ptr = &lumine[0];

	//�z�񏉊���
	for (int i = 0; i < EXPLOSIONLUMINE_NUM_MAX; i++)
	{
		lumine[i].active = false;

		vtxUV[i].u = vtxUV[i].v = 0.0f;

		vtxColor[i].r = vtxColor[i].g = vtxColor[i].b = 1.0f;
		vtxColor[i].a = 0.0f;
	}

	if (!initialized)
	{
		//���_�o�b�t�@�쐬	
		MakeParticleVertexBuffer(vtx, EXPLOSIONLUMINE_SIZE, &vtxBuff);
		MakeParticleUVBuffer(EXPLOSIONLUMINE_NUM_MAX, vtxUV, &uvBuff);
		MakeParticleWorldBuffer(EXPLOSIONLUMINE_NUM_MAX, mtxWorld, &worldBuff);
		MakeParticleColorBuffer(EXPLOSIONLUMINE_NUM_MAX, vtxColor, &colorBuff);

		//�C���f�b�N�X�o�b�t�@�쐬		
		WORD index[6] = { 0, 1, 2, 2, 1, 3 };
		pDevice->CreateIndexBuffer(sizeof(index), 0, D3DFMT_INDEX16, D3DPOOL_MANAGED, &indexBuff, 0);
		void* p = NULL;
		indexBuff->Lock(0, 0, &p, 0);
		memcpy(p, index, sizeof(index));
		indexBuff->Unlock();

		//�e�N�X�`���ǂݍ���
		texture = CreateTextureFromFile((LPSTR)EXPLOSIONLUMINE_TEX_NAME, pDevice);

		initialized = true;
	}
}

/**************************************
�I������
***************************************/
void UninitExplosionLumine(int num)
{
	EXPLOSION_LUMINE *ptr = &lumine[0];
	VERTEX_COLOR *pColor = &vtxColor[0];
	for (int i = 0; i < EXPLOSIONLUMINE_NUM_MAX; i++, ptr++, pColor++)
	{
		ptr->active = false;
		pColor->a = 0.0f;
	}
	CopyVtxBuff(sizeof(vtxColor), vtxColor, colorBuff);

	if (num == 0)
	{
		SAFE_RELEASE(vtxBuff);
		SAFE_RELEASE(worldBuff);
		SAFE_RELEASE(uvBuff);
		SAFE_RELEASE(colorBuff);
		SAFE_RELEASE(texture);
	}
}

/**************************************
�X�V����
***************************************/
void UpdateExplosionLumine(void)
{
	EXPLOSION_LUMINE *ptr = &lumine[0];
	D3DXMATRIX mtxTranslate;
	D3DXVECTOR3 *pPos = &pos[0];
	VERTEX_COLOR *pColor = &vtxColor[0];
	D3DXMATRIX *pWorld = &mtxWorld[0];

	for (int i = 0; i < EXPLOSIONLUMINE_NUM_MAX; i++, pPos++, pColor++, pWorld++, ptr++)
	{
		if (!ptr->active)
			continue;

		ptr->cntFrame++;

		//��������	
		if (ptr->cntFrame > ptr->lifeFrame)
		{
			pColor->a = 0.0f;
			ptr->active = false;
			continue;
		}

		//�ړ�����
		*pPos += ptr->moveDir * 5.0f;

		//���[���h�ϊ��s��X�V
		D3DXMatrixIdentity(pWorld);
		GetInvRotBattleCamera(pWorld);
		D3DXMatrixTranslation(&mtxTranslate, pPos->x, pPos->y, pPos->z);
		D3DXMatrixMultiply(pWorld, pWorld, &mtxTranslate);

		//�f�B�t���[�Y�v�Z����
		float t = (float)ptr->cntFrame / (float)ptr->lifeFrame;
		pColor->a = EaseInCubic(t, 1.0f, 0.0f);
	}

	//���_�o�b�t�@�փR�s�[	
	CopyVtxBuff(sizeof(mtxWorld), mtxWorld, worldBuff);
	CopyVtxBuff(sizeof(vtxColor), vtxColor, colorBuff);
}

/**************************************
�`�揈��
***************************************/
void DrawExplosionLumine(LPD3DXEFFECT effect)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	pDevice->SetStreamSourceFreq(0, D3DSTREAMSOURCE_INDEXEDDATA | (EXPLOSIONLUMINE_NUM_MAX));
	pDevice->SetStreamSourceFreq(1, D3DSTREAMSOURCE_INSTANCEDATA | 1);
	pDevice->SetStreamSourceFreq(2, D3DSTREAMSOURCE_INSTANCEDATA | 1);
	pDevice->SetStreamSourceFreq(3, D3DSTREAMSOURCE_INSTANCEDATA | 1);

	pDevice->SetStreamSource(0, vtxBuff, 0, sizeof(VERTEX_PARTICLE));
	pDevice->SetStreamSource(1, worldBuff, 0, sizeof(D3DXMATRIX));
	pDevice->SetStreamSource(2, uvBuff, 0, sizeof(VERTEX_UV));
	pDevice->SetStreamSource(3, colorBuff, 0, sizeof(VERTEX_COLOR));

	pDevice->SetIndices(indexBuff);

	effect->SetTexture("tex", texture);
	effect->SetMatrix("mtxView", &GetBattleCameraView());
	effect->SetMatrix("mtxProj", &GetBattleCameraProjection());

	effect->SetTechnique("tech");
	UINT passNum = 0;
	effect->Begin(&passNum, 0);
	effect->BeginPass(0);

	//�ʏ�`��
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, NUM_VERTEX, 0, NUM_POLYGON);

	//���Z�`��
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, NUM_VERTEX, 0, NUM_POLYGON);

	effect->EndPass();
	effect->End();

	pDevice->SetStreamSourceFreq(0, 1);
	pDevice->SetStreamSourceFreq(1, 1);
	pDevice->SetStreamSourceFreq(2, 1);
	pDevice->SetStreamSourceFreq(3, 1);

	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

/**************************************
�Z�b�g����
***************************************/
void SetExplosionLumine(D3DXVECTOR3 *setPos)
{
	EXPLOSION_LUMINE *ptr = &lumine[0];
	D3DXVECTOR3 *pPos = &pos[0];
	VERTEX_COLOR *pColor = &vtxColor[0];

	for (int i = 0; i < EXPLOSIONLUMINE_NUM_MAX; i++, ptr++, pPos++, pColor++)
	{
		if (ptr->active)
			continue;

		*pPos = *setPos;

		pColor->a = 1.0f;

		ptr->cntFrame = 0;
		ptr->lifeFrame = EXPLOSIONLUMINE_LIFEFRAME_BASE + RandomRange(-EXPLOSIONLUMINE_LIFEFRAME_RANGE, EXPLOSIONLUMINE_LIFEFRAME_RANGE);
		ptr->moveDir = D3DXVECTOR3(RandomRangef(-1.0f, 1.0f), RandomRangef(-1.0f, 1.0f), RandomRangef(-1.0f, 1.0f));
		D3DXVec3Normalize(&ptr->moveDir, &ptr->moveDir);
		ptr->active = true;
		return;
	}
}