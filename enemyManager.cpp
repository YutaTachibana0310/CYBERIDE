//=====================================
//
//�G�l�~�[�}�l�[�W������[enemyManager.cpp]
//Author:GP11A341 21 ���ԗY��
//
//=====================================
#include "enemyManager.h"
#include "enemyMissile.h"
#include "middleEnemyModel.h"
#include "smallEnemyModel.h"
#include "enemyBullet.h"
#include "enemyHomingBullet.h"
#include "enemyBulletTrail.h"
#include "cubeObject.h"
#include "hardCubeObject.h"

/**************************************
�}�N����`
***************************************/

/**************************************
�\���̒�`
***************************************/

/**************************************
�O���[�o���ϐ�
***************************************/

/**************************************
�v���g�^�C�v�錾
***************************************/

/**************************************
����������
***************************************/
void InitEnemyManager(int num)
{
	InitEnemyMissile(num);
	InitMiddleEnemy(num);
	InitSmallEnemy(num);
	InitCubeObject(num);
	InitHardCubeObject(num);

	InitEnemyBullet(num);
	InitEnemyHomingBullet(num);
	InitEnemyBulletTrail(num);
}

/**************************************
�I������
***************************************/
void UninitEnemyManager(int num)
{
	UninitEnemyMissile(num);
	UninitMiddleEnemy(num);
	UninitSmallEnemy(num);
	UninitCubeObject(num);
	UninitHardCubeObject(num);

	UninitEnemyBullet(num);
	UninitEnemyHomingBullet(num);
	UninitEnemyBulletTrail(num);
}

/**************************************
�X�V����
***************************************/
void UpdateEnemyManager(void)
{
	UpdateEnemyMissile();
	UpdateMiddleEnemy();
	UpdateSmallEnemy();
	UpdateCubeObject();
	UpdateHardCubeObject();

	UpdateEnemyBullet();
	UpdateEnemyHomingBullet();
	UpdateEnemyBulletTrail();
}

/**************************************
�`�揈��
***************************************/
void DrawEnemyManager(void)
{
	DrawMiddleEnemy();
	DrawEnemyMissile();
	DrawSmallEnemy();
	//DrawCubeObject();
	DrawHardCubeObject();

	DrawEnemyBullet();
	DrawEnemyHomingBullet();
	DrawEnemyBulletTrail();
}

/**************************************
�����蔻�菈��
***************************************/
void CheckEnemyCollision(void)
{
	LockonMiddleEnemy();
	LockonEnemyMissile();
	LockonSmallEnemy();
	LockonCubeObject();

	CollisionMiddleEnemyAndBullet();
	CollisionSmallEnemyAndBullet();
	//CollisionCubeObjectAndBullet();
}