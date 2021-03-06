//=====================================
//
//タイトルテロップヘッダ[titleTelop.h]
//Author:GP11A341 21 立花雄太
//
//=====================================
#ifndef _TITLETELOP_H_
#define _TITLETELOP_H_

#include "main.h"

/**************************************
マクロ定義
***************************************/

/**************************************
構造体定義
***************************************/

/**************************************
プロトタイプ宣言
***************************************/
void InitTitleTelop(int num);
void UninitTitleTelop(int num);
void UpdateTitleTelop(void);
void DrawTitleTelop(void);
int GetTitleMenuIndex(void);
#endif