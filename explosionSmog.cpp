//=====================================
//
//エクスプロージョンスモッグ処理[explosionSmog.cpp]
//Author:GP11A341 21 立花雄太
//
//=====================================
#include "particleManager.h"
#include "battleCamera.h"
#include "debugproc.h"
#include "particleFramework.h"

/**********************************************
マクロ定義
**********************************************/
#define EXPLOSIONSMOG_MAX (1024)
#define EXPLOSIONSMOG_TEXNAME "data/TEXTURE/EFFECT/explosionSmog.png"
#define EXPLOSIONSMOG_SIZE (6)
#define EXPLOSIONSMOG_POSRANGE (10.0f)
/**********************************************
グローバル変数
**********************************************/
static D3DXMATRIX pos[EXPLOSIONSMOG_MAX];		//ワールド変換行列の配列
static VERTEX_COLOR vtxColor[EXPLOSIONSMOG_MAX];		//頂点ディフューズの配列
static VERTEX_UV vtxUV[EXPLOSIONSMOG_MAX];				//テクスチャ座標の配列

//単位パーティクルの各頂点設定
static VERTEX_PARTICLE vtx[4] = {
	{-EXPLOSIONSMOG_SIZE, EXPLOSIONSMOG_SIZE, 0.0f, 0.0f, 0.0f},
	{ EXPLOSIONSMOG_SIZE, EXPLOSIONSMOG_SIZE, 0.0f, 1.0f, 0.0f },
	{ -EXPLOSIONSMOG_SIZE, -EXPLOSIONSMOG_SIZE, 0.0f,  0.0f, 1.0f },
	{ EXPLOSIONSMOG_SIZE, -EXPLOSIONSMOG_SIZE, 0.0f, 1.0f, 1.0f }
};

//各種の頂点バッファ
static LPDIRECT3DVERTEXBUFFER9 vtxBuff = NULL;
static LPDIRECT3DVERTEXBUFFER9 uvBuff = NULL;
static LPDIRECT3DVERTEXBUFFER9 posBuff = NULL;
static LPDIRECT3DVERTEXBUFFER9 colorBuff = NULL;

static LPDIRECT3DTEXTURE9 texture;					//テクスチャ
static LPDIRECT3DINDEXBUFFER9 indexBuff;			//インデックスバッファ
static PARTICLE smog[EXPLOSIONSMOG_MAX];			//パーティクル構造体

/**********************************************
プロトタイプ宣言
**********************************************/

/**********************************************
初期化処理
**********************************************/
void InitExplosionSmog(int num)
{
	static bool initialized = false;
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//配列初期化
	for (int i = 0; i < EXPLOSIONSMOG_MAX; i++)
	{
		smog[i].pos = D3DXVECTOR3(-99999, -99999, -99999);
		D3DXMatrixIdentity(&pos[i]);

		vtxUV[i].u = vtxUV[i].v = 0.0f;

		vtxColor[i].r = vtxColor[i].g = vtxColor[i].g = 1.0f;
		vtxColor[i].a = 0.0f;

		smog[i].active = false;
	}

	if (!initialized)
	{
		//頂点バッファ作成
		MakeParticleVertexBuffer(vtx, EXPLOSIONSMOG_SIZE, &vtxBuff);
		MakeParticleUVBuffer(EXPLOSIONSMOG_SIZE, vtxUV, &uvBuff);
		MakeParticleWorldBuffer(EXPLOSIONSMOG_MAX, pos, &posBuff);
		MakeParticleColorBuffer(EXPLOSIONSMOG_MAX, vtxColor, &colorBuff);

		//インデックスバッファ作成
		WORD index[6] = { 0, 1, 2, 2, 1, 3 };
		pDevice->CreateIndexBuffer(sizeof(index), 0, D3DFMT_INDEX16, D3DPOOL_MANAGED, &indexBuff, 0);
		void *p = NULL;
		indexBuff->Lock(0, 0, &p, 0);
		memcpy(p, index, sizeof(index));
		indexBuff->Unlock();

		//テクスチャ読み込み
		texture = CreateTextureFromFile((LPSTR)EXPLOSIONSMOG_TEXNAME, pDevice);

		initialized = true;
	}
}

/**********************************************
終了処理
**********************************************/
void UninitExplosionSmog(int num)
{
	PARTICLE *ptr = &smog[0];
	D3DXMATRIX mtxScale, mtxTranslate;

	for (int i = 0; i < EXPLOSIONSMOG_MAX; i++, ptr++)
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
	CopyVtxBuff(sizeof(D3DXMATRIX) * EXPLOSIONSMOG_MAX, pos, posBuff);

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
更新処理
**********************************************/
void UpdateExplosionSmog(void)
{
	PARTICLE *ptr = &smog[0];
	D3DXMATRIX mtxTranslate, mtxScale;

	//書くパーティクルの更新
	for (int i = 0; i < EXPLOSIONSMOG_MAX; i++, ptr++)
	{
		if (!ptr->active)
		{
			continue;
		}

		//パーティクルの移動、透過
		ptr->pos += ptr->moveDir * GetEasingValue((float)ptr->cntFrame / ptr->lifeFrame, ptr->initSpeed, ptr->endSpeed, ptr->speedType);
		ptr->pos.z += PARTICLE_SCROLLSPEED;
		vtxColor[i].a = GetEasingValue((float)ptr->cntFrame / ptr->lifeFrame, ptr->initAlpha, ptr->endAlpha, ptr->colorType);
		ptr->cntFrame++;

		//寿命が来ていたら見えなくする
		if (ptr->cntFrame == ptr->lifeFrame)
		{
			ptr->pos.z = -10000.0f;
			ptr->active = false;
		}

		//座標に応じたワールド変換行列にpos配列を更新
		D3DXMatrixIdentity(&pos[i]);
		GetInvRotBattleCamera(&pos[i]);
		D3DXMatrixScaling(&mtxScale, 1.0f, 1.0f, 1.0f);
		D3DXMatrixMultiply(&pos[i], &pos[i], &mtxScale);
		D3DXMatrixTranslation(&mtxTranslate, ptr->pos.x, ptr->pos.y, ptr->pos.z);
		D3DXMatrixMultiply(&pos[i], &pos[i], &mtxTranslate);
	}

	//頂点バッファにメモリコピー
	CopyVtxBuff(sizeof(D3DXMATRIX) * EXPLOSIONSMOG_MAX, pos, posBuff);
	CopyVtxBuff(sizeof(VERTEX_COLOR) * EXPLOSIONSMOG_MAX, vtxColor, colorBuff);
}

/**********************************************
描画処理
**********************************************/
void DrawExplosionSmog(LPDIRECT3DVERTEXDECLARATION9 declare, LPD3DXEFFECT effect)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//αテスト使用
	//pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, true);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	//ストリーム周波数を設定
	pDevice->SetStreamSourceFreq(0, D3DSTREAMSOURCE_INDEXEDDATA | (EXPLOSIONSMOG_MAX));
	pDevice->SetStreamSourceFreq(1, D3DSTREAMSOURCE_INSTANCEDATA | 1);
	pDevice->SetStreamSourceFreq(2, D3DSTREAMSOURCE_INSTANCEDATA | 1);
	pDevice->SetStreamSourceFreq(3, D3DSTREAMSOURCE_INSTANCEDATA | 1);

	//ストリームソース設定
	pDevice->SetStreamSource(0, vtxBuff, 0, sizeof(VERTEX_PARTICLE));
	pDevice->SetStreamSource(1, posBuff, 0, sizeof(D3DXMATRIX));
	pDevice->SetStreamSource(2, uvBuff, 0, sizeof(VERTEX_UV));
	pDevice->SetStreamSource(3, colorBuff, 0, sizeof(VERTEX_COLOR));
	pDevice->SetIndices(indexBuff);

	//シェーダのグローバル変数を設定
	effect->SetTexture("tex", texture);
	effect->SetMatrix("mtxView", &GetBattleCameraView());
	effect->SetMatrix("mtxProj", &GetBattleCameraProjection());

	//使用シェーダ設定
	effect->SetTechnique("tech");
	UINT passNum = 0;
	effect->Begin(&passNum, 0);
	effect->BeginPass(0);

	//インデックスバッファ設定
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 4, 0, 2);

	//アルファブレンディングで描画
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 4, 0, 2);

	//加算合成で描画
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 4, 0, 2);

	//シェーダ終了宣言
	effect->EndPass();
	effect->End();

	//ストリーム周波数をもとに戻す
	pDevice->SetStreamSourceFreq(0, 1);
	pDevice->SetStreamSourceFreq(1, 1);
	pDevice->SetStreamSourceFreq(2, 1);

	//アルファテストを戻す
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, false);

	//描画方法をもとに戻す
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}


/**********************************************
パーティクルセット処理1
**********************************************/
void SetExplosionSmog(const D3DXVECTOR3 *pos)
{
	PARTICLE *ptr = &smog[0];

	for (int i = 0; i < EXPLOSIONSMOG_MAX; i++, ptr++)
	{
		if (ptr->active)
		{
			continue;
		}

		ptr->active = true;

		//フレーム関連の設定
		ptr->cntFrame = 0;
		ptr->lifeFrame = 70;

		//スピードの設定
		ptr->initSpeed = 0.5f;
		ptr->endSpeed = 0.0f;
		ptr->speedType = OutExponential;

		//スケールの設定
		ptr->initScale = RandomRangef(0.7f, 1.5f);
		ptr->endScale = 1.0f;
		ptr->scaleType = Linear;

		//カラーの設定
		ptr->initRed = ptr->initGreen = ptr->initBlue = ptr->initAlpha = 1.0f;
		ptr->endRed = ptr->endGreen = ptr->endBlue = 1.0f;
		ptr->endAlpha = 0.0f;
		ptr->colorType = InCubic;

		//座標の設定
		ptr->pos = *pos;
		//ptr->pos.x += RandomRangef(-EXPLOSIONSMOG_POSRANGE, EXPLOSIONSMOG_POSRANGE);
		//ptr->pos.z += RandomRangef(-EXPLOSIONSMOG_POSRANGE, EXPLOSIONSMOG_POSRANGE);
		//ptr->pos.x += RandomRangef(-EXPLOSIONSMOG_POSRANGE, EXPLOSIONSMOG_POSRANGE);
		ptr->moveDir = D3DXVECTOR3(RandomRangef(-1.0f, 1.0f), RandomRangef(-1.0f, 1.0f), RandomRangef(-1.0f, 1.0f));
		D3DXVec3Normalize(&ptr->moveDir, &ptr->moveDir);

		return;
	}
}
