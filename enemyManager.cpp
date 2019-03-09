//=====================================
//
//�G�l�~�[�}�l�[�W������[enemyManager.cpp]
//Author:GP11A341 21 ���ԗY��
//
//=====================================
#include "enemyManager.h"
#include "enemyBullet.h"
#include "enemyHomingBullet.h"
#include "enemyBulletTrail.h"
#include "cubeObject.h"
#include "hardCubeObject.h"
#include "bonusCube.h"
#include "DebugTimer.h"

/**************************************
�}�N����`
***************************************/
#define CUBEOBJECT_EMMITT_RANGE		(100.0f)
#define ENEMYMANAGER_LABEL "EnemyManager"

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
	InitCubeObject(num);
	InitHardCubeObject(num);
	InitBonusCube(num);

	InitEnemyBullet(num);
	InitEnemyHomingBullet(num);
	InitEnemyBulletTrail(num);

	RegisterDebugTimer(ENEMYMANAGER_LABEL);
}

/**************************************
�I������
***************************************/
void UninitEnemyManager(int num)
{
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
	CountDebugTimer(ENEMYMANAGER_LABEL, "CubeObjectUpdate");
	UpdateCubeObject();
	CountDebugTimer(ENEMYMANAGER_LABEL, "CubeObjectUpdate");

	CountDebugTimer(ENEMYMANAGER_LABEL, "HardCubeUpdate");
	UpdateHardCubeObject();
	CountDebugTimer(ENEMYMANAGER_LABEL, "HardCubeUpdate");

	CountDebugTimer(ENEMYMANAGER_LABEL, "BonusCubeUpdate");
	UpdateBonusCube();
	CountDebugTimer(ENEMYMANAGER_LABEL, "BonusCubeUpdate");

	UpdateEnemyBullet();
	UpdateEnemyHomingBullet();
	UpdateEnemyBulletTrail();
}

/**************************************
�`�揈��
***************************************/
void DrawEnemyManager(void)
{
	CountDebugTimer(ENEMYMANAGER_LABEL, "CubeObjectDraw");
	DrawCubeObject();
	CountDebugTimer(ENEMYMANAGER_LABEL, "CubeObjectDraw");

	CountDebugTimer(ENEMYMANAGER_LABEL, "HardCubeDraw");
	DrawHardCubeObject();
	CountDebugTimer(ENEMYMANAGER_LABEL, "HardCubeDraw");

	CountDebugTimer(ENEMYMANAGER_LABEL, "BonusCubeDraw");
	DrawBonusCube();
	CountDebugTimer(ENEMYMANAGER_LABEL, "BonusCubeDraw");

	DrawEnemyBullet();
	DrawEnemyHomingBullet();
	DrawEnemyBulletTrail();

	DrawDebugTimer(ENEMYMANAGER_LABEL);
}

/**************************************
�����蔻�菈��
***************************************/
void CheckEnemyCollision(void)
{
	LockonBonusCube();
	LockonHardCubeObject();
	LockonCubeObject();
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

	SetBonusCube();
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