//=====================================
//
//�o���b�g�p�[�e�B�N������[bulletParticle.cpp]
//Author:GP11A341 21 ���ԗY��
//
//=====================================
#include "particleManager.h"
#include "bulletParticle.h"
#include "particleFramework.h"
#include "battleCamera.h"
#include "Easing.h"

/**************************************
�}�N����`
***************************************/
#define BULLETPARTICLE_MAX			(1024)
#define BULLETPARTICLE_TEXNAME		"data/TEXTURE/ENEMY/enemyBulletTrail.png"
#define BULLETPARTICLE_SIZE			(4.0f)

/**************************************
�\���̒�`
***************************************/

/**************************************
�O���[�o���ϐ�
***************************************/
static D3DXMATRIX pos[BULLETPARTICLE_MAX];
static VERTEX_COLOR vtxColor[BULLETPARTICLE_MAX];
static VERTEX_UV vtxUV[BULLETPARTICLE_MAX];

//�P�ʒ��_
static VERTEX_PARTICLE vtx[NUM_VERTEX] = {
	{ -BULLETPARTICLE_SIZE, BULLETPARTICLE_SIZE, 0.0f, 0.0f, 0.0f },
	{ BULLETPARTICLE_SIZE, BULLETPARTICLE_SIZE, 0.0f, 0.5f, 0.0f },
	{ -BULLETPARTICLE_SIZE, -BULLETPARTICLE_SIZE, 0.0f, 0.0f, 1.0f },
	{ BULLETPARTICLE_SIZE, -BULLETPARTICLE_SIZE, 0.0f, 0.5f, 1.0f }
};

//�e�풸�_�o�b�t�@
static LPDIRECT3DVERTEXBUFFER9 vtxBuff;
static LPDIRECT3DVERTEXBUFFER9 uvBuff;
static LPDIRECT3DVERTEXBUFFER9 posBuff;
static LPDIRECT3DVERTEXBUFFER9 colorBuff;

static LPDIRECT3DTEXTURE9 texture;
static LPDIRECT3DINDEXBUFFER9 indexBuff;
static BULLETPARTICLE particle[BULLETPARTICLE_MAX];

/**************************************
�v���g�^�C�v�錾
***************************************/

/**************************************
����������
***************************************/
void InitBulletParticle(int num)
{
	static bool initialized = false;

	//�z�񏉊���
	for (int i = 0; i < BULLETPARTICLE_MAX; i++)
	{
		vtxColor[i].r = vtxColor[i].g = vtxColor[i].b = 1.0f;
		vtxColor[i].a = 0.0f;
		particle[i].active = false;
	}

	//����̂ݏ�����
	if (!initialized)
	{
		LPDIRECT3DDEVICE9 pDevice = GetDevice();
		//���_�o�b�t�@�쐬
		MakeParticleVertexBuffer(vtx, BULLETPARTICLE_SIZE, &vtxBuff);
		MakeParticleUVBuffer(BULLETPARTICLE_MAX, vtxUV, &uvBuff);
		MakeParticleWorldBuffer(BULLETPARTICLE_MAX, pos, &posBuff);
		MakeParticleColorBuffer(BULLETPARTICLE_MAX, vtxColor, &colorBuff);

		//�C���f�b�N�X�o�b�t�@�쐬
		WORD index[6] = { 0, 1, 2, 2, 1, 3 };
		pDevice->CreateIndexBuffer(sizeof(index), 0, D3DFMT_INDEX16, D3DPOOL_MANAGED, &indexBuff, 0);
		void *p = NULL;
		indexBuff->Lock(0, 0, &p, 0);
		memcpy(p, index, sizeof(index));
		indexBuff->Unlock();

		//�e�N�X�`���ǂݍ���
		texture = CreateTextureFromFile((LPSTR)BULLETPARTICLE_TEXNAME, pDevice);

		initialized = true;
	}
}

/**************************************
�I������
***************************************/
void UninitBulletParticle(int num)
{
	for (int i = 0; i < BULLETPARTICLE_MAX; i++)
	{
		particle[i].active = false;
		vtxColor[i].a = 0.0f;
	}
	CopyVtxBuff(sizeof(vtxColor), vtxColor, colorBuff);

	if (num == 0)
	{
		SAFE_RELEASE(vtxBuff);
		SAFE_RELEASE(uvBuff);
		SAFE_RELEASE(posBuff);
		SAFE_RELEASE(colorBuff);
		SAFE_RELEASE(texture);
	}
}

/**************************************
�X�V����
***************************************/
void UpdateBulletParticle(void)
{
	BULLETPARTICLE *ptr = &particle[0];
	D3DXMATRIX mtxTranslate, mtxScale;

	//�p�[�e�B�N���̍X�V
	for (int i = 0; i < BULLETPARTICLE_MAX; i++, ptr++)
	{
		if (!ptr->active)
			continue;

		//�ړ�
		float t = (float)ptr->cntFrame / (float)ptr->lifeFrame;
		float speed = GetEasingValue(t, ptr->initSpeed, ptr->endSpeed, OutCubic);
		ptr->pos += speed * ptr->moveDir;
		ptr->pos.z += PARTICLE_SCROLLSPEED;

		//����
		vtxColor[i].a = 1.0f;// EaseLinear(t, 1.0f, 0.0f);

		ptr->cntFrame++;

		//��������
		if (ptr->cntFrame == ptr->lifeFrame)
		{
			vtxColor[i].a = 0.0f;
			ptr->active = false;
		}

		//���[���h�ϊ��s��X�V
		D3DXMatrixIdentity(&pos[i]);
		GetInvRotBattleCamera(&pos[i]);
		D3DXMatrixScaling(&mtxScale, 1.0f, 1.0f, 1.0f);
		D3DXMatrixMultiply(&pos[i], &pos[i], &mtxScale);
		D3DXMatrixTranslation(&mtxTranslate, ptr->pos.x, ptr->pos.y, ptr->pos.z);
		D3DXMatrixMultiply(&pos[i], &pos[i], &mtxTranslate);
	}

	//���_�o�b�t�@�Ƀ������R�s�[
	CopyVtxBuff(sizeof(D3DXMATRIX) * BULLETPARTICLE_MAX, pos, posBuff);
	CopyVtxBuff(sizeof(VERTEX_COLOR) * BULLETPARTICLE_MAX, vtxColor, colorBuff);
	CopyVtxBuff(sizeof(VERTEX_UV) * BULLETPARTICLE_MAX, vtxUV, uvBuff);
}

/**************************************
�`�揈��
***************************************/
void DrawBulletParticle(LPDIRECT3DVERTEXDECLARATION9 declare, LPD3DXEFFECT effect)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//���e�X�g�g�p
	//pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, true);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	//�X�g���[�����g����ݒ�
	pDevice->SetStreamSourceFreq(0, D3DSTREAMSOURCE_INDEXEDDATA | (BULLETPARTICLE_MAX));
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

	//�A���t�@�u�����f�B���O�ŕ`��
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
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

/**************************************
�Z�b�g����
***************************************/
void SetBulletParticle(const D3DXVECTOR3 *setPos, BULLETEXPL_TYPE type)
{
	BULLETPARTICLE *ptr = &particle[0];
	for (int i = 0; i < BULLETPARTICLE_MAX; i++, ptr++)
	{
		if (ptr->active)
			continue;

		ptr->active = true;

		//�t���[���֘A�̐ݒ�
		ptr->cntFrame = 0;
		ptr->lifeFrame = 30;

		//�X�s�[�h�̐ݒ�
		ptr->initSpeed = RandomRangef(5.0f, 10.0f);
		ptr->endSpeed = 1.0f;

		//���W�̐ݒ�
		ptr->pos = *setPos;
		ptr->moveDir = D3DXVECTOR3(RandomRangef(-1.0f, 1.0f), RandomRangef(-1.0f, 1.0f), RandomRangef(0.0f, 1.0f));
		D3DXVec3Normalize(&ptr->moveDir, &ptr->moveDir);

		vtxUV[i].u = type * 1.0f / BULLETEXPL_TYPEMAX;
		return;
	}
}

/**************************************
���o����
***************************************/
void EmmittBulletParticle(const D3DXVECTOR3 *setPos, BULLETEXPL_TYPE type, int num)
{
	for (int i = 0; i < num; i++)
	{
		SetBulletParticle(setPos, type);
	}
}