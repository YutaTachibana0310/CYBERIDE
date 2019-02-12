//=====================================
//
//�v���C���[�~�T�C���X���b�O����[playerMissileSmog.cpp]
//Author:GP11A341 21 ���ԗY��
//
//=====================================
#include "playerMissileSmog.h"
#include "particleFramework.h"
#include "particleManager.h"
#include "battleCamera.h"

/**************************************
�}�N����`
***************************************/
#define PLAYERMISSILESMOG_MAX		(2048)
#define PLAYERMISSILESMOG_TEX_NAME	"data/TEXTURE/playerMissileSmog.png"
#define PLAYERMISSILESMOG_SIZE		(2.0f)
#define PLAYERMISSILESMOG_TEXDEVIDE_X	(4)
#define PLAYERMISSILESMOG_TEXDEVIDE_Y	(2)
#define PLAYERMISSILESMOG_ANIMMAX		(8)
#define PLAYERMISSILESMOG_ANIMTIME		(3)
/**************************************
�\���̒�`
***************************************/

/**************************************
�O���[�o���ϐ�
***************************************/
static D3DXMATRIX world[PLAYERMISSILESMOG_MAX];
static VERTEX_COLOR color[PLAYERMISSILESMOG_MAX];
static VERTEX_UV uv[PLAYERMISSILESMOG_MAX];

static VERTEX_PARTICLE vtx[PLAYERMISSILESMOG_MAX] = {
	{ -PLAYERMISSILESMOG_SIZE, PLAYERMISSILESMOG_SIZE, 0.0f, 0.0f, 0.0f },
	{  PLAYERMISSILESMOG_SIZE, PLAYERMISSILESMOG_SIZE, 0.0f, 0.25f, 0.0f },
	{ -PLAYERMISSILESMOG_SIZE, -PLAYERMISSILESMOG_SIZE, 0.0f, 0.0f, 0.5f },
	{  PLAYERMISSILESMOG_SIZE, -PLAYERMISSILESMOG_SIZE, 0.0f, 0.25f, 0.5f }
};

static LPDIRECT3DVERTEXBUFFER9 vtxBuf, uvBuff, worldBuff, colorBuff;
static LPDIRECT3DTEXTURE9 texture;
static PLAYERMISSILESMOG smog[PLAYERMISSILESMOG_MAX];
static LPDIRECT3DINDEXBUFFER9 indexBuff;

/**************************************
�v���g�^�C�v�錾
***************************************/

/**************************************
����������
***************************************/
void InitPlayerMissileSmog(int num)
{
	static bool initialized = false;

	if (!initialized)
	{
		LPDIRECT3DDEVICE9 pDevice = GetDevice();

		MakeParticleVertexBuffer(vtx, PLAYERMISSILESMOG_SIZE, &vtxBuf);
		MakeParticleUVBuffer(PLAYERMISSILESMOG_MAX, uv, &uvBuff);
		MakeParticleWorldBuffer(PLAYERMISSILESMOG_MAX, world, &worldBuff);
		MakeParticleColorBuffer(PLAYERMISSILESMOG_MAX, color, &colorBuff);

		WORD index[6] = { 0 ,1, 2, 2, 1, 3 };
		pDevice->CreateIndexBuffer(sizeof(index), 0, D3DFMT_INDEX16, D3DPOOL_MANAGED, &indexBuff, 0);
		void *p = NULL;
		indexBuff->Lock(0, 0, &p, 0);
		memcpy(p, index, sizeof(index));
		indexBuff->Unlock();

		texture = CreateTextureFromFile((LPSTR)PLAYERMISSILESMOG_TEX_NAME, pDevice);

		initialized = true;
	}

	for (int i = 0; i < PLAYERMISSILESMOG_MAX; i++)
	{
		color[i].r = color[i].g = color[i].b = 1.0f;
		color[i].a = 0.0f;
		smog[i].active = false;
	}
}

/**************************************
�I������
***************************************/
void UninitPlayerMissileSmog(int num)
{
	for (int i = 0; i < PLAYERMISSILESMOG_MAX; i++)
	{
		smog[i].active = false;
		color[i].a = 0.0f;
	}
	//CopyVtxBuff(sizeof(color), color, colorBuff);

	if (num == 0)
	{
		SAFE_RELEASE(texture);
		SAFE_RELEASE(vtxBuf);
		SAFE_RELEASE(worldBuff);
		SAFE_RELEASE(colorBuff);
		SAFE_RELEASE(uvBuff);
	}
}

/**************************************
�X�V����
***************************************/
void UpdatePlayerMissileSmog(void)
{
	PLAYERMISSILESMOG *ptr = &smog[0];
	D3DXMATRIX mtxTranslate;

	for (int i = 0; i < PLAYERMISSILESMOG_MAX; i++, ptr++)
	{
		if (!ptr->active)
			continue;

		ptr->cntFrame++;
		if (ptr->cntFrame % PLAYERMISSILESMOG_ANIMTIME == 0)
		{
			ptr->patternAnim++;

			if (ptr->patternAnim == PLAYERMISSILESMOG_ANIMMAX)
			{
				color[i].a = 0.0f;
				ptr->active = false;
				continue;
			}

			int x = ptr->patternAnim % PLAYERMISSILESMOG_TEXDEVIDE_X;
			int y = ptr->patternAnim / PLAYERMISSILESMOG_TEXDEVIDE_Y;
			float sizeX = 1.0f / PLAYERMISSILESMOG_TEXDEVIDE_X;
			float sizeY = 1.0f / PLAYERMISSILESMOG_TEXDEVIDE_Y;

			uv[i].u = x * sizeX;
			uv[i].v = y * sizeY;
		}

		D3DXMatrixIdentity(&world[i]);
		GetInvRotBattleCamera(&world[i]);
		D3DXMatrixTranslation(&mtxTranslate, ptr->pos.x, ptr->pos.y, ptr->pos.z);
		D3DXMatrixMultiply(&world[i], &world[i], &mtxTranslate);
	}

	CopyVtxBuff(sizeof(D3DXMATRIX) * PLAYERMISSILESMOG_MAX, world, worldBuff);
	CopyVtxBuff(sizeof(VERTEX_COLOR) * PLAYERMISSILESMOG_MAX, color, colorBuff);
	CopyVtxBuff(sizeof(VERTEX_UV) * PLAYERMISSILESMOG_MAX, uv, uvBuff);
}

/**************************************
�`�揈��
***************************************/
void DrawPlayerMissileSmog(LPD3DXEFFECT effect)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//���e�X�g�g�p
	//pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, true);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	//�X�g���[�����g����ݒ�
	pDevice->SetStreamSourceFreq(0, D3DSTREAMSOURCE_INDEXEDDATA | (PLAYERMISSILESMOG_MAX));
	pDevice->SetStreamSourceFreq(1, D3DSTREAMSOURCE_INSTANCEDATA | 1);
	pDevice->SetStreamSourceFreq(2, D3DSTREAMSOURCE_INSTANCEDATA | 1);
	pDevice->SetStreamSourceFreq(3, D3DSTREAMSOURCE_INSTANCEDATA | 1);

	//�X�g���[���\�[�X�ݒ�
	pDevice->SetStreamSource(0, vtxBuf, 0, sizeof(VERTEX_PARTICLE));
	pDevice->SetStreamSource(1, worldBuff, 0, sizeof(D3DXMATRIX));
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

	////�A���t�@�u�����f�B���O�ŕ`��
	//pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	//pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 4, 0, 2);

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
void SetPlayerMissileSmog(D3DXVECTOR3 pos)
{
	PLAYERMISSILESMOG *ptr = &smog[0];
	for (int i = 0; i < PLAYERMISSILESMOG_MAX; i++, ptr++)
	{
		if (ptr->active)
		{
			continue;
		}

		ptr->pos = pos;
		ptr->cntFrame = ptr->patternAnim = 0;
		color[i].a = 1.0f;
		uv[i].u = uv[i].v = 0.0f;
		ptr->active = true;
		return;
	}
}
