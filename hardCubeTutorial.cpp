//=====================================
//
//�n�[�h�L���[�u�`���[�g���A������[hardCubeTutorial.cpp]
//Author:GP11A341 21 ���ԗY��
//
//=====================================
#include "hardCubeObject.h"
#include "playerModel.h"
#include "enemyBullet.h"
#include "enemyHomingBullet.h"

/**************************************
�}�N����`
***************************************/
#define HARDCUBE_TUTORIAL_INTERBAL		(180)
#define HARDCUBE_TUTORIAL_DURATION		(HARDCUBE_TUTORIAL_INTERBAL*4)
#define HARDCUBE_TUTORIAL_BULLETSPEED	(10.0f)
#define HARDCUBE_TUTORIAL_HBULLETSPEED	(150.0f)
#define HARDCUBE_TUTORIAL_REACHFRAME	(100)
#define HARDCUBE_TUTORIAL_DIRNUM		(4)

/**************************************
�\���̒�`
***************************************/

/**************************************
�O���[�o���ϐ�
***************************************/
static const D3DXVECTOR3 BulletVelocity[HARDCUBE_TUTORIAL_DIRNUM] = {
	/*			dir			*		speed	*/
	D3DXVECTOR3(1.0f, 1.0f, 0.0f) * HARDCUBE_TUTORIAL_HBULLETSPEED,
	D3DXVECTOR3(-1.0f, 1.0f, 0.0f) * HARDCUBE_TUTORIAL_HBULLETSPEED,
	D3DXVECTOR3(1.0f, -1.0f, 0.0f) * HARDCUBE_TUTORIAL_HBULLETSPEED,
	D3DXVECTOR3(-1.0f, -1.0f, 0.0f) * HARDCUBE_TUTORIAL_HBULLETSPEED,
};

/**************************************
�v���g�^�C�v�錾
***************************************/
void AttackNormalBulletOnTutorial(HARD_CUBE_OBJECT *ptr);
void AttackHomingBulletOnTutorial(HARD_CUBE_OBJECT *ptr);

/**************************************
���ꏈ��
***************************************/
void OnEnterHardCubeTutorial(HARD_CUBE_OBJECT *ptr)
{
	ptr->cntFrame = 0;
}

/**************************************
�X�V����
***************************************/
void OnUpdateHardCubeTutorial(HARD_CUBE_OBJECT *ptr)
{
	if (ptr->cntFrame % HARDCUBE_TUTORIAL_INTERBAL == 0)
	{
		if (ptr->cntFrame % (HARDCUBE_TUTORIAL_INTERBAL * 2) == 0 && ptr->cntFrame != 0)
			AttackHomingBulletOnTutorial(ptr);
		else
			AttackNormalBulletOnTutorial(ptr);
	}

	ptr->cntFrame++;
	if (ptr->cntFrame == HARDCUBE_TUTORIAL_DURATION)
		ChangeStateHardCube(ptr, HardCubeEscape);
}

/**************************************
�ʏ�U������
***************************************/
void AttackNormalBulletOnTutorial(HARD_CUBE_OBJECT *ptr)
{
	D3DXVECTOR3 dir = GetPlayerAdr(0)->pos - ptr->pos;
	D3DXVec3Normalize(&dir, &dir);
	SetEnemyBullet(ptr->pos, dir, HARDCUBE_TUTORIAL_BULLETSPEED);
}

/**************************************
�z�[�~���O�U������
***************************************/
void AttackHomingBulletOnTutorial(HARD_CUBE_OBJECT *ptr)
{
	for (int i = 0; i < HARDCUBE_TUTORIAL_DIRNUM; i++)
	{
		SetEnemyHomingBullet(ptr->pos, BulletVelocity[i], HARDCUBE_TUTORIAL_REACHFRAME);
	}
}