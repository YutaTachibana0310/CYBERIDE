//=============================================================================
 //
 // �J�������� [battleCamera.h]
 // Author : 
 //
 //=============================================================================
#ifndef _BATTLECAMERA_H_
#define _BATTLECAMERA_H_

#include "main.h"

#define BATTLECAMERA_MOVEFRAME		(30)

 //*****************************************************************************
 // �\���̒�`
 //*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 at;
	D3DXVECTOR3 up;

	D3DXMATRIX view;
	D3DXMATRIX projection;

	int currentState;
	int nextState;

	bool isMoving;

	int cntFrame;

}BATTLECAMERA;

enum BATTLECAMERA_STATE
{
	FirstPersonCamera,
	TopViewCamera,
	SideViewCamera,
	QuaterViewCamera,
	BattleCameraStateMax
};

 //*****************************************************************************
 // �v���g�^�C�v�錾
 //*****************************************************************************
HRESULT InitBattleCamera(void);
void UninitBattleCamera(void);
void UpdateBattleCamera(void);

void SetBattleCamera(void);

D3DXMATRIX GetBattleCameraView(void);
D3DXMATRIX GetBattleCameraProjection(void);
void GetInvRotBattleCamera(D3DXMATRIX *mtx, D3DXVECTOR3 *pAt = NULL);
D3DXVECTOR3 GetBattleCameraPos(void);
void SetBattleCameraMove(int state);
BATTLECAMERA *GetBattleCameraAdr(void);
void SetBattleCameraState(int state);
#endif
