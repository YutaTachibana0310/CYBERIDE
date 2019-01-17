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
#include "bonusCube.h"

/**************************************
�}�N����`
***************************************/
#define CUBEOBJECT_EMMITT_RANGE		(100.0f)

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
	InitBonusCube(num);

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
	UninitBonusCube(num);

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
	UpdateBonusCube();

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
	DrawCubeObject();
	DrawHardCubeObject();
	DrawBonusCube();

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
	LockonBonusCube();
	LockonHardCubeObject();
	LockonCubeObject();

	CollisionMiddleEnemyAndBullet();
	CollisionSmallEnemyAndBullet();
	//CollisionCubeObjectAndBullet();
}

/**************************************
�L���[�u�I�u�W�F�N�g��������
***************************************/
void EmmittCubeObject(int num, D3DXVECTOR3 *setPos, float setSpeed)
{
	for (int i = 0; i < num; i++)
	{
		D3DXVECTOR3 offsetPos;
		offsetPos.x = RandomRangef(-CUBEOBJECT_EMMITT_RANGE, CUBEOBJECT_EMMITT_RANGE);
		offsetPos.y = RandomRangef(-CUBEOBJECT_EMMITT_RANGE, CUBEOBJECT_EMMITT_RANGE);
		offsetPos.z = RandomRangef(-CUBEOBJECT_EMMITT_RANGE, CUBEOBJECT_EMMITT_RANGE);

		bool resultEmmitt = SetCubeObject(&(*setPos + offsetPos), setSpeed);
		if (!resultEmmitt)
			break;
	}
}

/**************************************
�{�[�i�X�L���[�u��������
***************************************/
void EmmittBonusCube(D3DXVECTOR3 *setPos)
{
	//�e���b�v�\���Ƃ�

	SetBonusCube(setPos);
}

/**************************************
�n�[�h�L���[�u��������
***************************************/
void EmittHardCubeObject(int num, D3DXVECTOR3 *setPos)
{
	for (int i = 0; i < num; i++)
	{
		SetHardCubeObject(setPos);
	}
}