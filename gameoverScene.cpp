//=====================================
//
//�Q�[���I�[�o�[�V�[������[gameoverScene.cpp]
//Author:GP11A341 21 ���ԗY��
//
//=====================================
#include "gameoverScene.h"
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
#include "particleManager.h"
#include "sceneFade.h"


/**************************************
�}�N����`
***************************************/
#define GAMEOVER_DURATION		(300)

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
HRESULT InitGameoverScene(int num)
{
	//NOTE:�o�g���V�[���̏�Ԃ��g���񂷂̂Ŋe�I�u�W�F�N�g�̏������͂��Ȃ�

	SetMonotoneEffect(true);
	SetGameoverTelop();
	cntFrame = 0;
	FadeInBGM(BGM_GAMEOVER, 30, false);
	return S_OK;
}

/**************************************
�I������
***************************************/
void UninitGameoverScene(int num)
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
	//UninitParticleManager(num);

	SetMonotoneEffect(false);
	FadeOutBGM(BGM_GAMEOVER, 10);
}

/**************************************
�X�V����
***************************************/
void UpdateGameoverScene(void)
{

	UpdatePlayerBullet();
	//UpdatePlayerModel();
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
	if (cntFrame == GAMEOVER_DURATION)
	{
		SetSceneFade(TitleScene);
	}
}

/**************************************
�`�揈��
***************************************/
void DrawGameoverScene(void)
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
}
