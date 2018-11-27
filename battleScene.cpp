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
#include "targetSite.h"
#include "rockonSite.h"
#include "meshCylinder.h"
#include "scoreGUI.h"
#include "playerMissile.h"
#include "playerMissileSmog.h"
#include "particleManager.h"
#include "scoreGUI.h"

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
	InitTargetSite(num);
	InitRockonSite(num);
	InitPlayerModel(num);
	InitPlayerBullet(num);
	InitBattleCamera();
	InitMeshCylinder(num);
	InitScoreGUI(num);
	InitPlayerMissile(num);
	InitPlayerMissileSmog(num);
	InitScoreGUI(num);

	return S_OK;
}

/******************************************************************************
�I������
******************************************************************************/
void UninitBattleScene(int num)
{
	//UninitCloud(num);
	UninitEnemyMissile(num);
	UninitPlayerModel(num);
	UninitPlayerBullet(num);
	UninitTargetSite(num);
	UninitRockonSite(num);
	UninitMeshCylinder(num);
	UninitScoreGUI(num);
	UninitPlayerMissile(num);
	UninitPlayerMissileSmog(num);
	UninitScoreGUI(num);
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
	UpdateTargetSite();
	UpdateRockonSite();
	UpdateMeshCylinder();
	UpdatePlayerMissile();
	UpdateScoreGUI();
	UpdatePlayerMissileSmog();
	UpdateScoreGUI();

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
	//DrawScoreGUI();
	SetBattleCamera();
	DrawMeshCylinder();
	//DrawCloud();
	DrawEnemyMissile();
	DrawPlayerModel();
	DrawPlayerMissile();
	DrawPlayerMissileSmog();
	DrawPlayerBullet();
	DrawParticleManager();
	DrawRockonSite();
	DrawTargetSite();
	DrawScoreGUI();
}
