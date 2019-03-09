//=====================================
//
//�G�N�X�v���[�W�����t���A����[explosionFlare.cpp]
//Author:GP11A341 21 ���ԗY��
//
//=====================================
#include "particleManager.h"
#include "battleCamera.h"
#include "debugproc.h"
#include "particleFramework.h"

#include "debugWindow.h"

/**********************************************
�}�N����`
**********************************************/
#define EXPLOSIONFLARE_MAX (2048)
#define EXPLOSIONFLARE_TEXNAME "data/TEXTURE/EFFECT/explosionFlare.png"
#define EXPLOSIONFLARE_SIZE (4)

/**********************************************
�O���[�o���ϐ�
**********************************************/
static D3DXMATRIX pos[EXPLOSIONFLARE_MAX];				//���[���h�ϊ��s��̔z��
static VERTEX_COLOR vtxColor[EXPLOSIONFLARE_MAX];		//���_�f�B�t���[�Y�̔z��
static VERTEX_UV vtxUV[EXPLOSIONFLARE_MAX];				//�e�N�X�`�����W�̔z��

//�P�ʃp�[�e�B�N���̊e���_�ݒ�
static VERTEX_PARTICLE vtx[4] = {
	{-EXPLOSIONFLARE_SIZE, EXPLOSIONFLARE_SIZE, 0.0f, 0.0f, 0.0f},
	{ EXPLOSIONFLARE_SIZE, EXPLOSIONFLARE_SIZE, 0.0f, 1.0f, 0.0f },
	{ -EXPLOSIONFLARE_SIZE, -EXPLOSIONFLARE_SIZE, 0.0f,  0.0f, 1.0f },
	{ EXPLOSIONFLARE_SIZE, -EXPLOSIONFLARE_SIZE, 0.0f, 1.0f, 1.0f }
};

//�e��̒��_�o�b�t�@
static LPDIRECT3DVERTEXBUFFER9 vtxBuff = NULL;
static LPDIRECT3DVERTEXBUFFER9 uvBuff = NULL;
static LPDIRECT3DVERTEXBUFFER9 posBuff = NULL;
static LPDIRECT3DVERTEXBUFFER9 colorBuff = NULL;

static LPDIRECT3DTEXTURE9 texture;					//�e�N�X�`��
static LPDIRECT3DINDEXBUFFER9 indexBuff;			//�C���f�b�N�X�o�b�t�@
static PARTICLE flare[EXPLOSIONFLARE_MAX];			//�p�[�e�B�N���\����

static LARGE_INTEGER startMove, endMove;
static LARGE_INTEGER startFade, endFade;
static LARGE_INTEGER startMtx, endMtx;
static LARGE_INTEGER startCopy, endCopy;

/**********************************************
�v���g�^�C�v�錾
**********************************************/
void MoveExplosionFlare(void);
void FadeExplosionFlare(void);
void CalcMtxExplosionFlare(void);
void CheckDestroyExplosionFlare(void);

void DrawDebugWindowExplosionFlare(void);

/**********************************************
����������
**********************************************/
void InitExplosionFlare(int num)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	static bool initialized = false;

	//�z�񏉊���
	for (int i = 0; i < EXPLOSIONFLARE_MAX; i++)
	{
		flare[i].pos = D3DXVECTOR3(-99999, -99999, -99999);
		D3DXMatrixIdentity(&pos[i]);

		vtxUV[i].u = vtxUV[i].v = 0.0f;

		vtxColor[i].r = vtxColor[i].g = vtxColor[i].g = 1.0f;
		vtxColor[i].a = 0.0f;

		flare[i].active = false;
	}

	if (!initialized)
	{	//���_�o�b�t�@�쐬
	//pDevice->CreateV
		MakeParticleVertexBuffer(vtx, EXPLOSIONFLARE_SIZE, &vtxBuff);
		MakeParticleUVBuffer(EXPLOSIONFLARE_MAX, vtxUV, &uvBuff);
		MakeParticleWorldBuffer(EXPLOSIONFLARE_MAX, pos, &posBuff);
		MakeParticleColorBuffer(EXPLOSIONFLARE_MAX, vtxColor, &colorBuff);

		//�C���f�b�N�X�o�b�t�@�쐬
		WORD index[6] = { 0, 1, 2, 2, 1, 3 };
		pDevice->CreateIndexBuffer(sizeof(index), 0, D3DFMT_INDEX16, D3DPOOL_MANAGED, &indexBuff, 0);
		void *p = NULL;
		indexBuff->Lock(0, 0, &p, 0);
		memcpy(p, index, sizeof(index));
		indexBuff->Unlock();

		//�e�N�X�`���ǂݍ���
		texture = CreateTextureFromFile((LPSTR)EXPLOSIONFLARE_TEXNAME, pDevice);

		initialized = true;
	}
}

/**********************************************
�I������
**********************************************/
void UninitExplosionFlare(int num)
{
	PARTICLE *ptr = &flare[0];
	D3DXMATRIX mtxScale, mtxTranslate;

	for (int i = 0; i < EXPLOSIONFLARE_MAX; i++, ptr++)
	{
		ptr->pos.z = -10000.0f;
		ptr->active = false;

		D3DXMatrixIdentity(&pos[i]);
		GetInvRotBattleCamera(&pos[i]);
		D3DXMatrixScaling(&mtxScale, 1.0f, 1.0f, 1.0f);
		D3DXMatrixMultiply(&pos[i], &pos[i], &mtxScale);
		D3DXMatrixTranslation(&mtxTranslate, ptr->pos.x, ptr->pos.y, ptr->pos.z);
		D3DXMatrixMultiply(&pos[i], &pos[i], &mtxTranslate);
	}
	CopyVtxBuff(sizeof(D3DXMATRIX) * EXPLOSIONFLARE_MAX, pos, posBuff);

	if (num == 0)
	{
		SAFE_RELEASE(vtxBuff);
		SAFE_RELEASE(uvBuff);
		SAFE_RELEASE(posBuff);
		SAFE_RELEASE(colorBuff);
		SAFE_RELEASE(texture);
	}
}

/**********************************************
�X�V����
**********************************************/
void UpdateExplosionFlare(void)
{
	GetTimerCount(&startMove);
	MoveExplosionFlare();
	GetTimerCount(&endMove);

	GetTimerCount(&startFade);
	FadeExplosionFlare();
	GetTimerCount(&endFade);

	CheckDestroyExplosionFlare();

	GetTimerCount(&startMtx);
	CalcMtxExplosionFlare();
	GetTimerCount(&endMtx);

	GetTimerCount(&startCopy);
	//���_�o�b�t�@�Ƀ������R�s�[
	CopyVtxBuff(sizeof(D3DXMATRIX) * EXPLOSIONFLARE_MAX, pos, posBuff);
	CopyVtxBuff(sizeof(VERTEX_COLOR) * EXPLOSIONFLARE_MAX, vtxColor, colorBuff);
	GetTimerCount(&endCopy);

	DrawDebugWindowExplosionFlare();
}

/**********************************************
�`�揈��
**********************************************/
void DrawExplosionFlare(LPDIRECT3DVERTEXDECLARATION9 declare, LPD3DXEFFECT effect)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//���e�X�g�g�p
	//pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, true);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	//�X�g���[�����g����ݒ�
	pDevice->SetStreamSourceFreq(0, D3DSTREAMSOURCE_INDEXEDDATA | (EXPLOSIONFLARE_MAX));
	pDevice->SetStreamSourceFreq(1, D3DSTREAMSOURCE_INSTANCEDATA | 1);
	pDevice->SetStreamSourceFreq(2, D3DSTREAMSOURCE_INSTANCEDATA | 1);
	pDevice->SetStreamSourceFreq(3, D3DSTREAMSOURCE_INSTANCEDATA | 1);

	//�X�g���[���\�[�X�ݒ�
	pDevice->SetStreamSource(0, vtxBuff, 0, sizeof(VERTEX_PARTICLE));
	pDevice->SetStreamSource(1, posBuff, 0, sizeof(D3DXMATRIX));
	pDevice->SetStreamSource(2, uvBuff, 0, sizeof(VERTEX_UV));
	pDevice->SetStreamSource(3, colorBuff, 0, sizeof(VERTEX_COLOR));
	pDevice->SetIndices(indexBuff);

	//�V�F�[�_�̃O���[�o���ϐ���ݒ�
	effect->SetTexture("tex", texture);
	effect->SetMatrix("mtxView", &GetBattleCameraView());
	effect->SetMatrix("mtxProj", &GetBattleCameraProjection());

	//�g�p�V�F�[�_�ݒ�
	effect->SetTechnique("tech");
	UINT passNum = 0;
	effect->Begin(&passNum, 0);
	effect->BeginPass(0);

	//�C���f�b�N�X�o�b�t�@�ݒ�
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 4, 0, 2);

	//���Z�����ŕ`��
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 4, 0, 2);

	//�V�F�[�_�I���錾
	effect->EndPass();
	effect->End();

	//�X�g���[�����g�������Ƃɖ߂�
	pDevice->SetStreamSourceFreq(0, 1);
	pDevice->SetStreamSourceFreq(1, 1);
	pDevice->SetStreamSourceFreq(2, 1);

	//�A���t�@�e�X�g��߂�
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, false);

	//�`����@�����Ƃɖ߂�
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}


/**********************************************
�p�[�e�B�N���Z�b�g����1
**********************************************/
bool SetExplosionFlare(const D3DXVECTOR3 *pos)
{
	PARTICLE *ptr = &flare[0];

	for (int i = 0; i < EXPLOSIONFLARE_MAX; i++, ptr++)
	{
		if (ptr->active)
		{
			continue;
		}

		ptr->active = true;

		//�t���[���֘A�̐ݒ�
		ptr->cntFrame = 0;
		ptr->lifeFrame = (int)RandomRangef(30, 70);

		//�X�s�[�h�̐ݒ�
		ptr->initSpeed = RandomRangef(4.0f, 8.0f);
		ptr->endSpeed = 0.0f;
		ptr->speedType = OutExponential;

		//�X�P�[���̐ݒ�
		ptr->initScale = RandomRangef(0.8f, 1.4f);
		ptr->endScale = 1.0f;
		ptr->scaleType = Linear;

		//�J���[�̐ݒ�
		ptr->initRed = ptr->initGreen = ptr->initBlue = 1.0f;
		ptr->initAlpha = 0.5f;
		ptr->endRed = ptr->endGreen = ptr->endBlue = 1.0f;
		ptr->endAlpha = 0.0f;
		ptr->colorType = InCubic;

		//���W�̐ݒ�
		ptr->pos = *pos;
		ptr->moveDir = D3DXVECTOR3(RandomRangef(-1.0f, 1.0f), RandomRangef(-1.0f, 1.0f), RandomRangef(-1.0f, 1.0f));
		D3DXVec3Normalize(&ptr->moveDir, &ptr->moveDir);

		return true;
	}

	return false;
}

/**********************************************
�ړ�����
**********************************************/
void MoveExplosionFlare(void)
{
	PARTICLE *ptr = &flare[0];
	float t = 0.0f;

	for (int i = 0; i < EXPLOSIONFLARE_MAX; i++, ptr++)
	{
		if (!ptr->active)
		{
			continue;
		}

		ptr->cntFrame++;

		t = (float)ptr->cntFrame / (float)ptr->lifeFrame;
		ptr->pos += ptr->moveDir * GetEasingValue(t, ptr->initSpeed, ptr->endSpeed, ptr->speedType);
		ptr->pos.z += PARTICLE_SCROLLSPEED;
	}
}

/**********************************************
���ߏ���
**********************************************/
void FadeExplosionFlare(void)
{
	PARTICLE *ptr = &flare[0];
	float t = 0.0f;

	for (int i = 0; i < EXPLOSIONFLARE_MAX; i++, ptr++)
	{
		if (!ptr->active)
		{
			continue;
		}

		t = (float)ptr->cntFrame / (float)ptr->lifeFrame;
		vtxColor[i].a = GetEasingValue(t, ptr->initAlpha, ptr->endAlpha, ptr->colorType);
	}
}

/**********************************************
�}�g���N�X�v�Z����
**********************************************/
void CalcMtxExplosionFlare(void)
{
	PARTICLE *ptr = &flare[0];
	D3DXMATRIX mtxTranslate, mtxScale;
	D3DXMATRIX *pPos = &pos[0];

	for (int i = 0; i < EXPLOSIONFLARE_MAX; i++, pPos++, ptr++)
	{	
		if (!ptr->active)
		{
			continue;
		}

		//���W�ɉ��������[���h�ϊ��s���pos�z����X�V
		D3DXMatrixIdentity(pPos);
		GetInvRotBattleCamera(pPos);
		D3DXMatrixScaling(&mtxScale, 1.0f, 1.0f, 1.0f);
		D3DXMatrixMultiply(pPos, pPos, &mtxScale);
		D3DXMatrixTranslation(&mtxTranslate, ptr->pos.x, ptr->pos.y, ptr->pos.z);
		D3DXMatrixMultiply(pPos, pPos, &mtxTranslate);
	}
}

/**********************************************
��������
**********************************************/
void CheckDestroyExplosionFlare(void)
{
	PARTICLE *ptr = &flare[0];
	for (int i = 0; i < EXPLOSIONFLARE_MAX; i++, ptr++)
	{	
		if (!ptr->active)
		{
			continue;
		}

		//���������Ă����猩���Ȃ�����
		if (ptr->cntFrame == ptr->lifeFrame)
		{
			ptr->pos.z = -10000.0f;
			ptr->active = false;
		}
	}
}

/**********************************************
�f�o�b�O�E�B���h�E�\��
**********************************************/
void DrawDebugWindowExplosionFlare(void)
{

}