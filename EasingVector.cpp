//=============================================================================
//
// イージング処理 [Easing.cpp]
// Author : GP11A341 21 立花雄太
//
//=============================================================================
#include "EasingVector.h"
#include <math.h>

/*****************************************************************************
プロトタイプ宣言
*****************************************************************************/

/*****************************************************************************
構造体定義
*****************************************************************************/
typedef D3DXVECTOR3(*Easing)(float, D3DXVECTOR3, D3DXVECTOR3);

/*****************************************************************************
グローバル変数
*****************************************************************************/
static Easing EasingProcess[EasingMax] = {
	EaseInCubic,
	EaseOutCubic,
	EaseInOutCubic,
	EaseLinear,
	EaseInExponential,
	EaseOutExponential,
	EaseInOutExponential
};

/*******************************************************************
//関数名	：D3DXVECTOR3 GetEasingValue(D3DXVECTOR3, D3DXVECTOR3, D3DXVECTOR3, D3DXVECTOR3, EASINGVECTOR_TYPE type)
//指定したイージングタイプの値を取得する関数
********************************************************************/
D3DXVECTOR3 GetEasingValue(float time, D3DXVECTOR3 start, D3DXVECTOR3 goal, EASINGVECTOR_TYPE type)
{
	return EasingProcess[type](time, start, goal);
}

/*******************************************************************
//関数名	：D3DXVECTOR3 EaseInCubic
//引数1		：float time		：現在の進行度
//引数2		：D3DXVECTOR3 start		：初期値
//引数3		：D3DXVECTOR3 goal		：目標値
//引数4		：D3DXVECTOR3 duration	：進行度の採集地
//戻り値	：イージングの値
//説明		：イージング計算処理
********************************************************************/
D3DXVECTOR3 EaseInCubic(float time, D3DXVECTOR3 start, D3DXVECTOR3 goal)
{
	return (goal - start) * time * time + start;
}

/*******************************************************************
//関数名	：D3DXVECTOR3 EaseOutCubic
//引数1		：float time		：現在の進行度
//引数2		：D3DXVECTOR3 start		：初期値
//引数3		：D3DXVECTOR3 goal		：目標値
//引数4		：D3DXVECTOR3 duration	：進行度の採集地
//戻り値	：イージングの値
//説明		：イージング計算処理
********************************************************************/
D3DXVECTOR3 EaseOutCubic(float time, D3DXVECTOR3 start, D3DXVECTOR3 goal)
{
	return -(goal - start) * time * (time - 2.0f) + start;
}

/*******************************************************************
//関数名	：D3DXVECTOR3 EaseInOutCubic
//引数1		：float time		：現在の進行度
//引数2		：D3DXVECTOR3 start		：初期値
//引数3		：D3DXVECTOR3 goal		：目標値
//引数4		：D3DXVECTOR3 duration	：進行度の採集地
//戻り値	：イージングの値
//説明		：イージング計算処理
********************************************************************/
D3DXVECTOR3 EaseInOutCubic(float time, D3DXVECTOR3 start, D3DXVECTOR3 goal)
{
	time *= 2.0f;

	if (time < 1)
	{
		return (goal - start) / 2.0f * time * time + start;
	}
	else
	{
		time -= 1.0f;
		return -(goal - start) / 2.0f * (time * (time - 2) - 1) + start;
	}
}

/*******************************************************************
//関数名	：D3DXVECTOR3 EaseLinear
//引数1		：float time		：現在の進行度
//引数2		：D3DXVECTOR3 start		：初期値
//引数3		：D3DXVECTOR3 goal		：目標値
//引数4		：D3DXVECTOR3 duration	：進行度の採集地
//戻り値	：イージングの値
//説明		：イージング計算処理
********************************************************************/
D3DXVECTOR3 EaseLinear(float time, D3DXVECTOR3 start, D3DXVECTOR3 goal)
{
	return (goal - start) * time + start;
}

/*******************************************************************
//関数名	：D3DXVECTOR3 EaseInExponential
//引数1		：float time		：現在の進行度
//引数2		：D3DXVECTOR3 start		：初期値
//引数3		：D3DXVECTOR3 goal		：目標値
//引数4		：D3DXVECTOR3 duration	：進行度の採集地
//戻り値	：イージングの値
//説明		：イージング計算処理
********************************************************************/
D3DXVECTOR3 EaseInExponential(float time, D3DXVECTOR3 start, D3DXVECTOR3 goal)
{
	return (goal - start) *  powf(2, 10 * (time - 1)) + start;
}

/*******************************************************************
//関数名	：D3DXVECTOR3 EaseOuntExponential
//引数1		：float time		：現在の進行度
//引数2		：D3DXVECTOR3 start		：初期値
//引数3		：D3DXVECTOR3 goal		：目標値
//引数4		：D3DXVECTOR3 duration	：進行度の採集地
//戻り値	：イージングの値
//説明		：イージング計算処理
********************************************************************/
D3DXVECTOR3 EaseOutExponential(float time, D3DXVECTOR3 start, D3DXVECTOR3 goal)
{
	return (goal - start) * (-powf(2, (-10 * time)) + 1) + start;
}

/*******************************************************************
//関数名	：D3DXVECTOR3 EaseInOutExponential
//引数1		：float time		：現在の進行度
//引数2		：D3DXVECTOR3 start		：初期値
//引数3		：D3DXVECTOR3 goal		：目標値
//引数4		：D3DXVECTOR3 duration	：進行度の採集地
//戻り値	：イージングの値
//説明		：イージング計算処理
********************************************************************/
D3DXVECTOR3 EaseInOutExponential(float time, D3DXVECTOR3 start, D3DXVECTOR3 goal)
{
	//return 0.0f;
	return D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}