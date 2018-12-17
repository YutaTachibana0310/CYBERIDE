//=====================================
//
//プレイヤーバレットトレイル処理[playerBulletTrail.cpp]
//Author:GP11A341 21 立花雄太
//
//=====================================
#include "playerBulletTrail.h"
#include "battleCamera.h"
#include "particleFramework.h"

/**************************************
マクロ定義
***************************************/
#define PLAYERBULLETTRAIL_TEXTURE_NAME		"data/TEXTURE/PLAYER/playerbullet.png"
#define PLAYERBULLETTRAIL_TEXTURE_SIZE_X	(4)
#define PLAYERBULLETTRAIL_TEXTURE_SIZE_Y	(4)
#define PLAYERBULLETTRAIL_LIFE_END			(10)
#define PLAYERBULLETTRAIL_SHADER_NAME		"data/EFFECT/particle.fx"

/**************************************
構造体定義
***************************************/

/**************************************
グローバル変数
***************************************/
static PLAYERBULLET_TRAIL trail[PLAYERBULLETTRAIL_MAX];
static LPDIRECT3DTEXTURE9 texture;

//単位頂点
static VERTEX_PARTICLE vtx[NUM_VERTEX] = {
	{ -PLAYERBULLETTRAIL_TEXTURE_SIZE_X, PLAYERBULLETTRAIL_TEXTURE_SIZE_Y, 0.0f, 0.0f, 0.0f },
	{ PLAYERBULLETTRAIL_TEXTURE_SIZE_X, PLAYERBULLETTRAIL_TEXTURE_SIZE_Y, 0.0f, 1.0f, 0.0f },
	{ -PLAYERBULLETTRAIL_TEXTURE_SIZE_X, -PLAYERBULLETTRAIL_TEXTURE_SIZE_Y, 0.0f, 0.0f, 1.0f },
	{ PLAYERBULLETTRAIL_TEXTURE_SIZE_X, -PLAYERBULLETTRAIL_TEXTURE_SIZE_Y, 0.0f, 1.0f, 1.0f }
};

//各種配列
static D3DXMATRIX pos[PLAYERBULLETTRAIL_MAX];
static VERTEX_COLOR vtxColor[PLAYERBULLETTRAIL_MAX];
static VERTEX_UV vtxUV[PLAYERBULLETTRAIL_MAX];

//各種頂点バッファ
static LPDIRECT3DVERTEXBUFFER9 vtxBuff = NULL;
static LPDIRECT3DVERTEXBUFFER9 uvBuff = NULL;
static LPDIRECT3DVERTEXBUFFER9 posBuff = NULL;
static LPDIRECT3DVERTEXBUFFER9 colorBuff = NULL;

static LPDIRECT3DVERTEXDECLARATION9 declare = NULL;		//頂点宣言
static LPD3DXEFFECT effect = NULL;						//シェーダー
static LPDIRECT3DINDEXBUFFER9 indexBuff = NULL;			//インデックスバッファ

/**************************************
プロトタイプ宣言
***************************************/

/**************************************
初期化処理
***************************************/
void InitPlayerBulletTrail(int num)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	if (num == 0)
	{
		//頂点作成
		MakeParticleVertexBuffer(vtx, PLAYERBULLETTRAIL_TEXTURE_SIZE_X, &vtxBuff);
		MakeParticleUVBuffer(PLAYERBULLETTRAIL_MAX, vtxUV, &uvBuff);
		MakeParticleWorldBuffer(PLAYERBULLETTRAIL_MAX, pos, &posBuff);
		MakeParticleColorBuffer(PLAYERBULLETTRAIL_MAX, vtxColor, &colorBuff);

		//頂点宣言作成
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

		//シェーダー読み込み
		D3DXCreateEffectFromFile(pDevice, PLAYERBULLETTRAIL_SHADER_NAME, 0, 0, 0, 0, &effect, NULL);

		//インデックスバッファ作成
		WORD index[6] = { 0, 1, 2, 2, 1, 3 };
		pDevice->CreateIndexBuffer(sizeof(index), 0, D3DFMT_INDEX16, D3DPOOL_MANAGED, &indexBuff, 0);
		void *p = NULL;
		indexBuff->Lock(0, 0, &p, 0);
		memcpy(p, index, sizeof(index));
		indexBuff->Unlock();

		//テクスチャ読み込み
		texture = CreateTextureFromFile((LPSTR)PLAYERBULLETTRAIL_TEXTURE_NAME, pDevice);
	}

	PLAYERBULLET_TRAIL *ptr = &trail[0];
	for (int i = 0; i < PLAYERBULLETTRAIL_MAX; i++, ptr++)
	{
		ptr->active = false;
		vtxColor[i].r = vtxColor[i].g = vtxColor[i].b = 1.0f;
		vtxColor[i].a = 0.0f;
	}
}

/**************************************
終了処理
***************************************/
void UninitPlayerBulletTrail(int num)
{
	if (num == 0)
	{
		SAFE_RELEASE(texture);
		SAFE_RELEASE(vtxBuff);
		SAFE_RELEASE(uvBuff);
		SAFE_RELEASE(posBuff);
		SAFE_RELEASE(colorBuff);
		SAFE_RELEASE(declare);
		SAFE_RELEASE(indexBuff);
		SAFE_RELEASE(effect);
	}

	PLAYERBULLET_TRAIL *ptr = &trail[0];
	for (int i = 0; i < PLAYERBULLETTRAIL_MAX; i++, ptr++)
	{
		ptr->active = false;
		vtxColor[i].a = 0.0f;
	}
}

/**************************************
更新処理
***************************************/
void UpdatePlayerBulletTrail(void)
{
	PLAYERBULLET_TRAIL *ptr = &trail[0];
	D3DXMATRIX mtxTranslate;
	D3DXMATRIX *pPos = &pos[0];
	VERTEX_COLOR *pColor = &vtxColor[0];

	for (int i = 0; i < PLAYERBULLETTRAIL_MAX; i++, ptr++, pPos++, pColor++)
	{
		if (!ptr->active)
		{
			continue;
		}

		ptr->cntFrame--;

		//透過処理
		//pColor->a = (float)ptr->cntFrame / PLAYERBULLETTRAIL_LIFE_END;

		//寿命判定
		if (ptr->cntFrame <= 0)
		{
			ptr->active = false;
			pColor->a = 0.0f;
			continue;
		}

		//ワールド配列の更新
		D3DXMatrixIdentity(pPos);
		D3DXMatrixTranslation(&mtxTranslate, ptr->pos.x, ptr->pos.y, ptr->pos.z);
		D3DXMatrixMultiply(pPos, pPos, &mtxTranslate);

		//ptr->active = false;
	}

	//頂点バッファにコピー
	CopyVtxBuff(sizeof(D3DXMATRIX) * PLAYERBULLETTRAIL_MAX, pos, posBuff);
	CopyVtxBuff(sizeof(VERTEX_COLOR) * PLAYERBULLETTRAIL_MAX, vtxColor, colorBuff);
}

/**************************************
描画処理
***************************************/
void DrawPlayerBulletTrail(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//set renderstate
	pDevice->SetRenderState(D3DRS_LIGHTING, false);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, false);
	pDevice->SetFVF(FVF_VERTEX_3D);

	//頂点要素宣言
	pDevice->SetVertexDeclaration(declare);

	//ストリーム周波数を設定
	pDevice->SetStreamSourceFreq(0, D3DSTREAMSOURCE_INDEXEDDATA | PLAYERBULLETTRAIL_MAX);
	pDevice->SetStreamSourceFreq(1, D3DSTREAMSOURCE_INSTANCEDATA | 1);
	pDevice->SetStreamSourceFreq(2, D3DSTREAMSOURCE_INSTANCEDATA | 1);
	pDevice->SetStreamSourceFreq(3, D3DSTREAMSOURCE_INSTANCEDATA | 1);

	//ストリームソース設定
	pDevice->SetStreamSource(0, vtxBuff, 0, sizeof(VERTEX_PARTICLE));
	pDevice->SetStreamSource(1, posBuff, 0, sizeof(D3DXMATRIX));
	pDevice->SetStreamSource(2, uvBuff, 0, sizeof(VERTEX_UV));
	pDevice->SetStreamSource(3, colorBuff, 0, sizeof(VERTEX_COLOR));
	pDevice->SetIndices(indexBuff);

	//シェーダーのグローバル変数を設定
	effect->SetTexture("tex", texture);
	effect->SetMatrix("mtxView", &GetBattleCameraView());
	effect->SetMatrix("mtxProj", &GetBattleCameraProjection());

	//使用シェーダー設定
	effect->SetTechnique("tech");
	UINT passNum = 0;
	effect->Begin(&passNum, 0);
	effect->BeginPass(0);

	//描画
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, NUM_VERTEX, 0, NUM_POLYGON);

	//加算描画
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, NUM_VERTEX, 0, NUM_POLYGON);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//シェーダー終了宣言
	effect->EndPass();
	effect->End();

	//ストリーム周波数をもとに戻す
	pDevice->SetStreamSourceFreq(0, 1);
	pDevice->SetStreamSourceFreq(1, 1);
	pDevice->SetStreamSourceFreq(2, 1);
	pDevice->SetStreamSourceFreq(3, 1);

	pDevice->SetRenderState(D3DRS_LIGHTING, true);
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, false);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, true);
}

/**************************************
セット処理
***************************************/
void SetPlayerBulletTrail(D3DXVECTOR3 pos, float alpha)
{
	PLAYERBULLET_TRAIL *ptr = &trail[0];
	for (int i = 0; i < PLAYERBULLETTRAIL_MAX; i++, ptr++)
	{
		if (ptr->active)
		{
			continue;
		}

		ptr->pos = pos;
		ptr->cntFrame = PLAYERBULLETTRAIL_LIFE_END;
		vtxColor[i].a = alpha;
		ptr->active = true;
		return;
	}
}