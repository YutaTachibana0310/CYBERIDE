//=====================================
//
//�n�[�h�L���[�u�ʏ�U������[hardCubeNormalAttack.cpp]
//Author:GP11A341 21 ���ԗY��
//
//=====================================
#include "hardCubeObject.h"
#include "playerModel.h"
#include "enemyBullet.h"
#include "battleController.h"

/**************************************
�}�N����`
***************************************/
#define HARDCUBE_NORMALATTACK_INTERBAL			(120)
#define HARDCUBE_NORMALATTACK_DURATION			(HARDCUBE_NORMALATTACK_INTERBAL*5)
#define HARDCUBE_NORNALATTACL_BULLETSPEED		(6.0f)
#define HARDCUBE_NORMALATTACK_BULLETSPEED_FPS	(10.0f)
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
���ꏈ��
***************************************/
void OnEnterHardCubeNormalAttack(HARD_CUBE_OBJECT *ptr)
{
	ptr->cntFrame = 0;
}

/**************************************
�X�V����
***************************************/
void OnUpdateHardCubeNormalAttack(HARD_CUBE_OBJECT *ptr)
{
	if (ptr->cntFrame % HARDCUBE_NORMALATTACK_INTERBAL == 0)
	{
		D3DXVECTOR3 dir = GetPlayerAdr(0)->pos - ptr->pos;
		D3DXVec3Normalize(&dir, &dir);
		float speed = (GetBattleViewMode() == BattleViewFPS) ? HARDCUBE_NORMALATTACK_BULLETSPEED_FPS : HARDCUBE_NORNALATTACL_BULLETSPEED;
		SetEnemyBullet(ptr->pos, dir, speed);
	}

	ptr->cntFrame++;
	if (ptr->cntFrame == HARDCUBE_NORMALATTACK_DURATION)
		ChangeStateHardCube(ptr, HardCubeEscape);
}