//=============================================================================
//
// �o�g���V�[������ [battleScene.cpp]
// Author : GP11A341 21 ���ԗY��
//
//=============================================================================
#include "main.h"
#include "battleScene.h"
#include "input.h"
#include "cloud.h"
#include "enemyMissile.h"
#include "playerModel.h"
#include "battleCamera.h"
#include "playerBullet.h"

/*****************************************************************************
�}�N����`
*****************************************************************************/
#define BATTLESCENE_TEXTURE_NAME	_T("data/TEXTURE/UI/battle.png")	// �v���C���[�o���b�g�̃e�N�X�`��

#define BATTLESCENE_TEXTURE_SIZE_X (200)			// �e�N�X�`���T�C�YX
#define BATTLESCENE_TEXTURE_SIZE_Y (200)			// �e�N�X�`���T�C�YY

/*****************************************************************************
�v���g�^�C�v�錾
*****************************************************************************/

/*****************************************************************************
�\���̒�`
*****************************************************************************/

/*****************************************************************************
�O���[�o���ϐ�
*****************************************************************************/

/******************************************************************************
����������
******************************************************************************/
HRESULT InitBattleScene(int num)
{
	InitCloud(num);
	InitEnemyMissile(num);
	InitPlayerModel(num);
	InitPlayerBullet(num);
	InitBattleCamera();

	return S_OK;
}

/******************************************************************************
�I������
******************************************************************************/
void UninitBattleScene(int num)
{
	UninitCloud(num);
	UninitEnemyMissile(num);
	UninitPlayerModel(num);
	UninitPlayerBullet(num);

}

/******************************************************************************
�X�V����
******************************************************************************/
void UpdateBattleScene(void)
{
	UpdateCloud();
	UpdateEnemyMissile();
	UpdatePlayerBullet();
	UpdatePlayerModel();
	UpdateBattleCamera();

	if (GetKeyboardTrigger(DIK_RETURN))
	{
		SetScene(ResultScene);
	}
}

/******************************************************************************
�`�揈��
******************************************************************************/
void DrawBattleScene(void)
{
	SetBattleCamera();
	DrawCloud();
	DrawEnemyMissile();
	DrawPlayerModel();
	DrawPlayerBullet();
}
