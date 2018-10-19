//=====================================
//
//エネミーミサイル処理[enemyMissile.cpp]
//Author:GP11A341 21 立花雄太
//
//=====================================
#include "enemyMissile.h"
#include "enemyMissileLaunch.h"
#include "enemyMissileHoming.h"
#include "enemyMissileStraight.h"

/**************************************
マクロ定義
**************************************/
#define ENEMYMISSILE_MAX			(128)						//ミサイル最大数
#define ENEMYMISSILE_MODEL			"data/MODEL/missile.x"		//モデル名
#define ENEMYMISSILE_ROTATEVALUE	(0.017f)					//1フレームあたりの回転量

/**************************************
構造体定義
**************************************/
typedef void(*funcEnemyMissile)(ENEMYMISSILE*);

/*************************************
プロトタイプ宣言
**************************************/

/*************************************
グローバル変数
**************************************/
static LPD3DXMESH mesh;										//メッシュへのポインタ
static LPD3DXBUFFER materials;								//マテリアル情報
static DWORD numMaterial;									//属性情報の総数
static D3DXMATRIX worldMtx;									//ワールドマトリクス
static ENEMYMISSILE missile[ENEMYMISSILE_MAX];				//エネミーミサイル構造体

//更新処理の関数テーブル
static funcEnemyMissile Update[ENEMYMISSILE_STATEMAX] = { 
	EnemyMissileLaunchUpdate,
	EnemyMissileHomingUpdate,
	EnemyMissileStraightUpdate
};

//入場処理の関数テーブル
static funcEnemyMissile Enter[ENEMYMISSILE_STATEMAX] = {
	EnemyMissileLaunchEnter,
	EnemyMissileHomingEnter,
	EnemyMissileStraightEnter,
};

//退場処理の関数テーブル
static funcEnemyMissile Exit[ENEMYMISSILE_STATEMAX] = {
	EnemyMissileLaunchExit,
	EnemyMissileHomingExit,
	EnemyMissileStraightExit
};

/*************************************
初期化処理
**************************************/
void InitEnemyMissile(int num)
{
	if (num == 0)
	{
		LPDIRECT3DDEVICE9 pDevice = GetDevice();

		mesh = NULL;
		materials = NULL;

		if (FAILED(D3DXLoadMeshFromX(ENEMYMISSILE_MODEL,
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&materials,
			NULL,
			&numMaterial,
			&mesh)))
		{
			return;
		}
	}

	ENEMYMISSILE *ptr = &missile[0];
	for (int i = 0; i < ENEMYMISSILE_MAX; i++, ptr++)
	{
		ptr->active = false;
		ptr->pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		ptr->rot = D3DXQUATERNION(0.0f, 0.0f, 0.0f, 0.0f);
		ptr->moveDir = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		ptr->speed = 0.0f;
		ptr->collider.active = false;
#if 0
		ptr->flgHoming = false;
#else
		ptr->active = true;
		ptr->pos = D3DXVECTOR3(RandomRange(-500.0f, 500.0f), 200.0f, 10000);
		ptr->moveDir = D3DXVECTOR3(0.0f, 1.0f, 0.0);
		ptr->targetPos = D3DXVECTOR3(RandomRange(-100.0f, 100.0f), 200.0f, 0.0f);
#endif
	}
}

/****************************************
終了処理
*****************************************/
void UninitEnemyMissile(void)
{
	SAFE_RELEASE(mesh);
	SAFE_RELEASE(materials);
}

/****************************************
更新処理
*****************************************/
void UpdateEnemyMissile(void)
{

	ENEMYMISSILE *ptr = &missile[0];

	for (int i = 0; i < ENEMYMISSILE_MAX; i++, ptr++)
	{
		if (!ptr->active)
		{
			continue;
		}

		Update[ptr->state](ptr);
	}
}

/*****************************************
描画処理
******************************************/
void DrawEnemyMissile(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTranslate;
	D3DXMATERIAL *pMaterial;
	D3DMATERIAL9 matDef;

	pDevice->GetMaterial(&matDef);

	ENEMYMISSILE *ptr = &missile[0];
	for (int i = 0; i < ENEMYMISSILE_MAX; i++, ptr++)
	{
		if (!ptr->active)
		{
			continue;
		}

		//ワールドマトリクスの初期化
		D3DXMatrixIdentity(&worldMtx);

		//回転を反映
		D3DXMatrixRotationQuaternion(&mtxRot, &ptr->rot);
		D3DXMatrixMultiply(&worldMtx, &worldMtx, &mtxRot);

		//移動を反映
		D3DXMatrixTranslation(&mtxTranslate, ptr->pos.x, ptr->pos.y, ptr->pos.z);
		D3DXMatrixMultiply(&worldMtx, &worldMtx, &mtxTranslate);

		//ワールドマトリクスの設定
		pDevice->SetTransform(D3DTS_WORLD, &worldMtx);

		//テクスチャの設定（NULL）
		pDevice->SetTexture(0, NULL);

		//マテリアル情報に対するポインタを取得
		pMaterial = (D3DXMATERIAL*)materials->GetBufferPointer();

		//描画
		for (int i = 0; i < (int)numMaterial; i++)
		{
			pDevice->SetMaterial(&pMaterial[i].MatD3D);
			mesh->DrawSubset(i);
		}
	}

	//マテリアルをデフォルトに戻す
	pDevice->SetMaterial(&matDef);
}

/******************************************
エネミーミサイルアドレス取得関数
*******************************************/
ENEMYMISSILE *GetEnemyMissileAdr(int n)
{
	return (n < ENEMYMISSILE_MAX) ? &missile[n] : NULL;
}

/*****************************************
エネミーミサイル状態遷移関数
******************************************/
void ChangeStateEnemyMissile(ENEMYMISSILE *ptr, int targetState)
{
	//退場処理を呼び出し
	Exit[ptr->state];

	//状態遷移
	ptr->state = targetState;

	//入場処理を呼び出し
	Enter[ptr->state];
}