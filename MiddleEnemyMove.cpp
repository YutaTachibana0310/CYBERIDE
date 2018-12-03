//=====================================
//
//ミドルエネミー移動状態処理[middleEnemyMove.cpp]
//Author:GP11A341 21 立花雄太
//
//=====================================
#include "middleEnemyModel.h"
#include "EasingVector.h"
#include "playerModel.h"
#include "enemyHomingBullet.h"
/**************************************
マクロ定義
***************************************/
#define MIDDLEENEMY_MOVE_END		(180)

/**************************************
構造体定義
***************************************/

/**************************************
グローバル変数
***************************************/

/**************************************
プロトタイプ宣言
***************************************/

/**************************************
更新処理
***************************************/
void UpdateMiddleEnemyMove(MIDDLEENEMYMODEL *enemy)
{
	enemy->cntFrame++;

	if (enemy->cntFrame > MIDDLEENEMY_MOVE_END)
	{
		if (enemy->cntFrame % 120 == 0)
		{
			for (int i = 0; i < 8; i++)
			{
				D3DXVECTOR3 dir = D3DXVECTOR3(sinf(i * 45 * 0.017f), cosf(i * 45 * 0.017f),  .0f) * 200;
				SetEnemyHomingBullet(enemy->pos, dir, rand() % 30 + 60);
			}
		}
		return;
	}


	float t = (float)enemy->cntFrame / MIDDLEENEMY_MOVE_END;
	enemy->pos = EaseOutCubicVector(t, enemy->startPos, enemy->goalPos);
	enemy->rot = EaseOutCubicVector(t, enemy->startRot, enemy->goalRot);
}

/**************************************
入場処理
***************************************/
void EnterMiddleEnemyMove(MIDDLEENEMYMODEL *enemy)
{
	enemy->cntFrame = 0;
	enemy->startPos = enemy->pos;
	enemy->startRot = enemy->rot;
}

/**************************************
退場処理
***************************************/
void ExitMiddleEnemyMove(MIDDLEENEMYMODEL *enemy)
{

}

