//=====================================
//
//�`���[�g���A���V�[������[tutorialScene.cpp]
//Author:GP11A341 21 ���ԗY��
//
//=====================================
#include "tutorialScene.h"
#include "playerModel.h"
#include "battleCamera.h"
#include "playerBullet.h"
#include "stageData.h"
#include "targetSite.h"
#include "rockonSite.h"
#include "meshCylinder.h"
#include "playerMissile.h"
#include "playerMissileSmog.h"
#include "particleManager.h"
#include "GUIManager.h"
#include "enemyManager.h"
#include "playerBulletTrail.h"
#include "collisionManager.h"
#include "tutorialController.h"
#include "bgmManager.h"
#include "input.h"
#include "sceneFade.h"
#include "soundEffectManager.h"

/**************************************
�}�N����`
***************************************/
#define TUTORIALSCENE_FADE_DURATION		(60)

/**************************************
�\���̒�`
***************************************/

/**************************************
�O���[�o���ϐ�
***************************************/
static bool isTransition;

/**************************************
�v���g�^�C�v�錾
***************************************/

/**************************************
����������
***************************************/
HRESULT InitTutorialScene(int num)
{
	InitTargetSite(num);
	InitRockonSite(num);
	InitPlayerModel(num);
	InitPlayerBullet(num);
	InitBattleCamera();
	InitMeshCylinder(num);
	InitPlayerMissile(num);
	//InitPlayerMissileSmog(num);
	InitPlayerBulletTrail(num);
	InitEnemyManager(num);
	InitTutorialController(num);

	FadeInBGM(BGM_TUTORIALSCENE, TUTORIALSCENE_FADE_DURATION);
	isTransition = false;
	return S_OK;
}

/**************************************
�I������
***************************************/
void UninitTutorialScene(int num)
{
	UninitTargetSite(num);
	UninitRockonSite(num);
	UninitPlayerModel(num);
	UninitPlayerBullet(num);
	UninitMeshCylinder(num);
	UninitPlayerMissile(num);
	//UninitPlayerMissileSmog(num);
	UninitPlayerBulletTrail(num);
	UninitEnemyManager(num);
	UninitTutorialController(num);
}

/**************************************
�X�V����
***************************************/
void UpdateTutorialScene(void)
{
	UpdateBattleCamera();

	UpdatePlayerModel();
	UpdatePlayerBullet();

	UpdateRockonSite();

	UpdateMeshCylinder();

	UpdatePlayerMissile();
	//UpdatePlayerMissileSmog();
	UpdatePlayerBulletTrail();

	UpdateParticleManager();

	UpdateEnemyManager();

	CheckEnemyCollision();
	UpdateCollisionManager();

	UpdateTutorialController();

	if (GetKeyboardPress(DIK_RETURN) && !isTransition)
	{
		isTransition = true;
		FadeOutBGM(BGM_TUTORIALSCENE, TUTORIALSCENE_FADE_DURATION);
		SetSceneFade(BattleScene);
	}
}

/**************************************
�`�揈��
***************************************/
void DrawTutorialScene(void)
{
	SetBattleCamera();

	DrawMeshCylinder();

	DrawEnemyManager();

	DrawPlayerModel();

	DrawPlayerMissile();
	//DrawPlayerMissileSmog();
	DrawPlayerBullet();
	DrawPlayerBulletTrail();

	DrawParticleManager();

	DrawRockonSite();
	DrawTargetSite();

	//rawGUIManager();

	//DrawTutorialController();
}
