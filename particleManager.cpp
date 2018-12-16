//=====================================
//
//�p�[�e�B�N���}�l�[�W������[particleManager.cpp]
//Author:GP11A341 21 ���ԗY��
//
//=====================================
#include "particleManager.h"
#include "explosionFire.h"
#include "explosionFlare.h"
#include "explosionSmog.h"
#include "camera.h"

#include "debugWindow.h"

/**************************************
�}�N����`
***************************************/
#define PARTICLE_SHADER_PATH	"particle.fx"

/**************************************
�\���̒�`
***************************************/

/**************************************
�O���[�o���ϐ�
***************************************/
static LPDIRECT3DVERTEXDECLARATION9 declare = NULL;
static LPD3DXEFFECT effect = NULL;

static LARGE_INTEGER startFlare, endFlare;
static LARGE_INTEGER startSmog, endSmog;
static LARGE_INTEGER startFire, endFire;

/**************************************
�v���g�^�C�v�錾
***************************************/
void DrawDebugWindowParticle(void);

/**************************************
����������
***************************************/
void InitParticleManager(int num)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	if (num == 0)
	{
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

		D3DXCreateEffectFromFile(pDevice, PARTICLE_SHADER_PATH, 0, 0, 0, 0, &effect, NULL);
	}

	InitExplosionSmog(num);
	InitExplosionFire(num);
	InitExplosionFlare(num);
}

/**************************************
�I������
***************************************/
void UninitParticleManager(int num)
{
	UninitExplosionSmog(num);
	UninitExplosionFire(num);
	UninitExplosionFlare(num);
}

/**************************************
�X�V����
***************************************/
void UpdateParticleManager(void)
{
	GetTimerCount(&startSmog);
	UpdateExplosionSmog();
	GetTimerCount(&endSmog);

	GetTimerCount(&startFire);
	UpdateExplosionFire();
	GetTimerCount(&endFire);

	GetTimerCount(&startFlare);
	UpdateExplosionFlare();
	GetTimerCount(&endFlare);

	DrawDebugWindowParticle();
}

/**************************************
�`�揈��
***************************************/
void DrawParticleManager(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	GetDevice()->SetRenderState(D3DRS_LIGHTING, false);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	//���_�v�f�錾
	pDevice->SetVertexDeclaration(declare);

	DrawExplosionSmog(declare, effect);
	DrawExplosionFlare(declare, effect);
	DrawExplosionFire(declare, effect);

	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	GetDevice()->SetRenderState(D3DRS_LIGHTING, true);
}

/**************************************
�G�l�~�[�G�N�X�v���[�W�����Z�b�g����
***************************************/
void SetEnemyExplosion(D3DXVECTOR3 pos)
{
	for (int j = 0; j < 200; j++)
	{
		SetExplosionFlare(&pos);
	}
	for (int j = 0; j < 10; j++)
	{
		SetExplosionFire(&pos);
	}
	for (int j = 0; j < 100; j++)
	{
		SetExplosionSmog(&pos);
	}
}

/**************************************
�f�o�b�O���\��
***************************************/
void DrawDebugWindowParticle(void)
{
	ImGui::SetNextWindowSize(ImVec2(200.0f, 100.0f));
	ImGui::SetNextWindowPos(ImVec2(5.0f, 415.0f));
	ImGui::Begin("ParticleManager");

	ImGui::Text("Flare  : %fmsec", CalcProgressTime(startFlare, endFlare));
	ImGui::Text("Fire   : %fmsec", CalcProgressTime(startFire, endFire));
	ImGui::Text("Smog   : %fmsec", CalcProgressTime(startSmog, endSmog));

	ImGui::End();
}