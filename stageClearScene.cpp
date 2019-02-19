//=====================================
//
//stageClearScene����[stageClearScene.cpp]
//Author:GP11A341 21 ���ԗY��
//
//=====================================
#include "stageClearScene.h"
#include "sceneManager.h"
#include "input.h"
#include "playerModel.h"
#include "battleCamera.h"
#include "playerBullet.h"
#include "targetSite.h"
#include "rockonSite.h"
#include "meshCylinder.h"
#include "playerMissile.h"
#include "playerMissileSmog.h"
#include "particleManager.h"
#include "enemyManager.h"
#include "playerBulletTrail.h"
#include "collisionManager.h"
#include "battleController.h"
#include "bgmManager.h"
#include "monotone.h"
#include "gameoverTelop.h"
#include "sceneFade.h"
#include "stageClearTelop.h"
#include "particleManager.h"

/**************************************
�}�N����`
***************************************/
#define STAGECLEAR_DURATION			(240)
			
/**************************************
�\���̒�`
***************************************/

/**************************************
�O���[�o���ϐ�
***************************************/
static int cntFrame;

/**************************************
�v���g�^�C�v�錾
***************************************/

/**************************************
����������
***************************************/
HRESULT InitStageClearScene(int num)
{
	//NOTE*�o�g���V�[���̏�Ԃ��g���񂷂̂Ŋe�I�u�W�F�N�g�̏������͂��Ȃ�

	//TODO:�e���b�v�Đ�,BGM�Đ�

	SetStageClearTelop();
	ChangeStatePlayerModel(PlayerTitleLaunch);
	cntFrame = 0;
	FadeInBGM(BGM_STAGECLEAR, 30);
	return S_OK;
}

/**************************************
�I������
***************************************/
void UninitStageClearScene(int num)
{
	UninitPlayerModel(num);
	UninitPlayerBullet(num);
	UninitTargetSite(num);
	UninitRockonSite(num);
	UninitMeshCylinder(num);
	UninitPlayerMissile(num);
	//UninitPlayerMissileSmog(num);
	UninitPlayerBulletTrail(num);
	UninitEnemyManager(num);
}

/**************************************
�X�V����
***************************************/
void UpdateStageClearScene(void)
{
	UpdatePlayerBullet();
	UpdatePlayerModel();
	UpdateBattleCamera();

	UpdateRockonSite();

	UpdateMeshCylinder();

	UpdatePlayerMissile();
	//UpdatePlayerMissileSmog();
	UpdatePlayerBulletTrail();

	UpdateParticleManager();

	UpdateEnemyManager();

	CheckEnemyCollision();
	UpdateCollisionManager();

	cntFrame++;
	if (cntFrame == STAGECLEAR_DURATION)
	{
		SetSceneFade(NameEntryScene);
		FadeOutBGM(BGM_STAGECLEAR, 60);
	}
}

/**************************************
�`�揈��
***************************************/
void DrawStageClearScene(void)
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
}
