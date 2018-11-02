//=====================================
//
//�G�N�X�v���[�W�����t���A����[explosionFire.cpp]
//Author:GP11A341 21 ���ԗY��
//
//=====================================
#include "particleManager.h"
#include "camera.h"
#include "debugproc.h"
#include "particleFramework.h"

/**********************************************
�}�N����`
**********************************************/
#define EXPLOSIONFIRE_MAX (2048)
#define EXPLOSIONFIRE_TEXNAME "data/TEXTURE/explosionFire.png"
#define EXPLOSIONFIRE_SIZE (24)

/**********************************************
�O���[�o���ϐ�
**********************************************/
static D3DXMATRIX pos[EXPLOSIONFIRE_MAX];				//���[���h�ϊ��s��̔z��
static VERTEX_COLOR vtxColor[EXPLOSIONFIRE_MAX];		//���_�f�B�t���[�Y�̔z��
static VERTEX_UV vtxUV[EXPLOSIONFIRE_MAX];				//�e�N�X�`�����W�̔z��

//�P�ʃp�[�e�B�N���̊e���_�ݒ�
static VERTEX_PARTICLE vtx[4] = {
	{-EXPLOSIONFIRE_SIZE, EXPLOSIONFIRE_SIZE, 0.0f, 0.0f, 0.0f},
	{ EXPLOSIONFIRE_SIZE, EXPLOSIONFIRE_SIZE, 0.0f, 1.0f, 0.0f },
	{ -EXPLOSIONFIRE_SIZE, -EXPLOSIONFIRE_SIZE, 0.0f,  0.0f, 1.0f },
	{ EXPLOSIONFIRE_SIZE, -EXPLOSIONFIRE_SIZE, 0.0f, 1.0f, 1.0f }
};

//�e��̒��_�o�b�t�@
static LPDIRECT3DVERTEXBUFFER9 vtxBuff = NULL;
static LPDIRECT3DVERTEXBUFFER9 uvBuff = NULL;
static LPDIRECT3DVERTEXBUFFER9 posBuff = NULL;
static LPDIRECT3DVERTEXBUFFER9 colorBuff = NULL;

static LPDIRECT3DTEXTURE9 texture;					//�e�N�X�`��
static LPDIRECT3DINDEXBUFFER9 indexBuff;			//�C���f�b�N�X�o�b�t�@
static PARTICLE smog[EXPLOSIONFIRE_MAX];			//�p�[�e�B�N���\����
static int cntExplosionFire = 0;					//�p�[�e�B�N���J�E���g

/**********************************************
�v���g�^�C�v�錾
**********************************************/

/**********************************************
����������
**********************************************/
void InitExplosionFire(int num)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�z�񏉊���
	for (int i = 0; i < EXPLOSIONFIRE_MAX; i++)
	{
		smog[i].pos = D3DXVECTOR3(-99999, -99999, -99999);
		D3DXMatrixIdentity(&pos[i]);

		vtxUV[i].u = vtxUV[i].v = 0.0f;

		vtxColor[i].r = vtxColor[i].g = vtxColor[i].g = 1.0f;
		vtxColor[i].a = 0.0f;

		smog[i].active = false;
	}

	//���_�o�b�t�@�쐬
	MakeParticleVertexBuffer(vtx, EXPLOSIONFIRE_SIZE, &vtxBuff);
	MakeParticleUVBuffer(EXPLOSIONFIRE_MAX, vtxUV, &uvBuff);
	MakeParticleWorldBuffer(EXPLOSIONFIRE_MAX, pos, &posBuff);
	MakeParticleColorBuffer(EXPLOSIONFIRE_MAX, vtxColor, &colorBuff);

	//�C���f�b�N�X�o�b�t�@�쐬
	WORD index[6] = { 0, 1, 2, 2, 1, 3 };
	pDevice->CreateIndexBuffer(sizeof(index), 0, D3DFMT_INDEX16, D3DPOOL_MANAGED, &indexBuff, 0);
	void *p = NULL;
	indexBuff->Lock(0, 0, &p, 0);
	memcpy(p, index, sizeof(index));
	indexBuff->Unlock();

	//�e�N�X�`���ǂݍ���
	texture = CreateTextureFromFile((LPSTR)EXPLOSIONFIRE_TEXNAME, pDevice);	
}

/**********************************************
�I������
**********************************************/
void UninitExplosionFire(void)
{
	SAFE_RELEASE(vtxBuff);
	SAFE_RELEASE(uvBuff);
	SAFE_RELEASE(posBuff);
	SAFE_RELEASE(colorBuff);
	SAFE_RELEASE(texture);
}

/**********************************************
�X�V����
**********************************************/
void UpdateExplosionFire(void)
{
	PARTICLE *ptr = &smog[0];
	D3DXMATRIX mtxTranslate, mtxScale;

	//�����p�[�e�B�N���̍X�V
	for (int i = 0; i < EXPLOSIONFIRE_MAX; i++, ptr++)
	{
		if (!ptr->active)
		{
			continue;
		}

		//�p�[�e�B�N���̈ړ��A����
		ptr->pos += ptr->moveDir * GetEasingValue((float)ptr->cntFrame / ptr->lifeFrame, ptr->initSpeed, ptr->endSpeed, ptr->speedType);;
		vtxColor[i].r = GetEasingValue((float)ptr->cntFrame / ptr->lifeFrame, ptr->initRed, ptr->endRed, ptr->colorType);
		vtxColor[i].g = GetEasingValue((float)ptr->cntFrame / ptr->lifeFrame, ptr->initGreen, ptr->endGreen, ptr->colorType);
		vtxColor[i].b = GetEasingValue((float)ptr->cntFrame / ptr->lifeFrame, ptr->initBlue, ptr->endBlue, ptr->colorType);
		vtxColor[i].a = GetEasingValue((float)ptr->cntFrame / ptr->lifeFrame, ptr->initAlpha, ptr->endAlpha, ptr->colorType);
		ptr->cntFrame++;

		//���������Ă����猩���Ȃ�����
		if (ptr->cntFrame == ptr->lifeFrame)
		{
			ptr->pos.z = -10000.0f;
			cntExplosionFire--;
			ptr->active = false;
		}

		//���W�ɉ��������[���h�ϊ��s���pos�z����X�V
		D3DXMatrixIdentity(&pos[i]);
		GetInvCameraRotMtx(&pos[i]);
		D3DXMatrixScaling(&mtxScale, 1.0f, 1.0f, 1.0f);
		D3DXMatrixMultiply(&pos[i], &pos[i], &mtxScale);
		D3DXMatrixTranslation(&mtxTranslate, ptr->pos.x, ptr->pos.y, ptr->pos.z);
		D3DXMatrixMultiply(&pos[i], &pos[i], &mtxTranslate);
	}

	//���_�o�b�t�@�Ƀ������R�s�[
	CopyVtxBuff(sizeof(D3DXMATRIX) * EXPLOSIONFIRE_MAX, pos, posBuff);
	CopyVtxBuff(sizeof(VERTEX_COLOR) * EXPLOSIONFIRE_MAX, vtxColor, colorBuff);

	PrintDebugProc("ExplosionFire:%d\n", cntExplosionFire);
}

/**********************************************
�`�揈��
**********************************************/
void DrawExplosionFire(LPDIRECT3DVERTEXDECLARATION9 declare, LPD3DXEFFECT effect)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//���e�X�g�g�p
	//pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, true);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	//�X�g���[�����g����ݒ�
	pDevice->SetStreamSourceFreq(0, D3DSTREAMSOURCE_INDEXEDDATA | (EXPLOSIONFIRE_MAX));
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
	effect->SetMatrix("mtxView", &GetMtxView());
	effect->SetMatrix("mtxProj", &GetMtxProjection());

	//�g�p�V�F�[�_�ݒ�
	effect->SetTechnique("tech");
	UINT passNum = 0;
	effect->Begin(&passNum, 0);
	effect->BeginPass(0);

	//�C���f�b�N�X�o�b�t�@�ݒ�
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 4, 0, 2);

	//�A���t�@�u�����f�B���O�ŕ`��
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


/**********************************************
�p�[�e�B�N���Z�b�g����1
**********************************************/
void SetExplosionFire(const D3DXVECTOR3 *pos)
{
	PARTICLE *ptr = &smog[0];

	for (int i = 0; i < EXPLOSIONFIRE_MAX; i++, ptr++)
	{
		if (ptr->active)
		{
			continue;
		}

		ptr->active = true;

		//�t���[���֘A�̐ݒ�
		ptr->cntFrame = 0;
		ptr->lifeFrame = 60;

		//�X�s�[�h�̐ݒ�
		ptr->initSpeed = RandomRange(0.1f, 0.5f);
		ptr->endSpeed = 0.0f;
		ptr->speedType = OutExponential;

		//�X�P�[���̐ݒ�
		ptr->initScale = 1.0f;
		ptr->endScale = 1.0f;
		ptr->scaleType = Linear;

		//�J���[�̐ݒ�
		ptr->initRed = ptr->initGreen = ptr->initBlue = 1.0f;
		ptr->initAlpha = 0.5f;
		ptr->endRed = ptr->endGreen = ptr->endBlue = 0.0f;
		ptr->endAlpha = 0.0f;
		ptr->colorType = InCubic;

		//���W�̐ݒ�
		ptr->pos = *pos;
		ptr->moveDir = D3DXVECTOR3(RandomRange(-1.0f, 1.0f), RandomRange(-1.0f, 1.0f), RandomRange(-1.0f, 1.0f));
		D3DXVec3Normalize(&ptr->moveDir, &ptr->moveDir);

		cntExplosionFire++;
		return;
	}
}
