//=====================================
//
//�{�[�i�X�L���[�u�Փ˔��菈��[collisionBonusCube.cpp]
//Author:GP11A341 21 ���ԗY��
//
//=====================================
#include "collisionManager.h"
#include "bonusCube.h"
#include "playerBullet.h"

/**************************************
�}�N����`
***************************************/
#define  BONUSCUBE_PLAYERBULLET_DAMAGE	(1.0f)
/**************************************
�\���̒�`
***************************************/

/**************************************
�O���[�o���ϐ�
***************************************/

/**************************************
�v���g�^�C�v�錾
***************************************/
bool CheckCollisionBonusCubeLower(DWORD elem, BONUS_CUBE_OBJECT *bonusCube, bool isCheckedUpper, COLLISION_MANAGER *manager);
bool CheckCollisionBonusCubeUpper(DWORD elem, BONUS_CUBE_OBJECT *bonusCube, COLLISION_MANAGER *manager);

/**************************************
�Փ˔���
***************************************/
void CheckCollisionBonusCube(COLLISION_MANAGER *manager)
{
	for (DWORD cntCell = 0; cntCell < manager->cellNum; cntCell++)
	{
		//��Ԃ��쐬����Ă��Ȃ��ꍇ�̔���
		if (!manager->cellArray[OFT_BONUSCUBE][cntCell])
			continue;

		//��ԂɃI�u�W�F�N�g���o�^����Ă��Ȃ��ꍇ�̔���
		if (manager->cellArray[OFT_BONUSCUBE][cntCell]->latestObj == NULL)
			continue;

		//��Ԃɓo�^����Ă���L���[�u�S�Ăɑ΂��Ĕ���
		OBJECT_FOR_TREE *bonusCubeOFT = manager->cellArray[OFT_BONUSCUBE][cntCell]->latestObj;
		for (; bonusCubeOFT != NULL; bonusCubeOFT = bonusCubeOFT->next)
		{
			BONUS_CUBE_OBJECT *bonusCube = (BONUS_CUBE_OBJECT*)bonusCubeOFT->object;
			CheckCollisionBonusCubeLower(cntCell, bonusCube, false, manager);
		}
	}

	return;
}

/**************************************
�q��Ԃł̏Փ˔���
***************************************/
bool CheckCollisionBonusCubeLower(DWORD elem, BONUS_CUBE_OBJECT *bonusCube, bool isCheckedUpper, COLLISION_MANAGER *manager)
{
	//��Ԑ��̔���
	if (elem >= manager->cellNum)
		return false;

	//�e��Ԃł̔���
	if (!isCheckedUpper)
	{
		CheckCollisionBonusCubeUpper(elem, bonusCube, manager);
	}

	//��Ԃ��쐬����Ă��Ȃ��ꍇ�̔���
	if (!manager->cellArray[OFT_PLAYERBULLET][elem])
		return false;

	//��Ԃɓo�^����Ă���o���b�g�Ɣ���
	if (manager->cellArray[OFT_PLAYERBULLET][elem]->latestObj != NULL)
	{
		OBJECT_FOR_TREE *bulletOFT = manager->cellArray[OFT_PLAYERBULLET][elem]->latestObj;
		for (; bulletOFT != NULL; bulletOFT = bulletOFT->next)
		{
			PLAYERBULLET *bullet = (PLAYERBULLET*)bulletOFT->object;
			if (ChechHitBoundingCube(&bullet->collider2, &bonusCube->collider))
			{
				BurstPlayerBullet(bullet);
				bonusCube->hp -= BONUSCUBE_PLAYERBULLET_DAMAGE;
			}
		}
	}

	//�q��Ԃł�����
	for (int i = 0; i < 4; i++)
	{
		DWORD nextElem = elem * 4 + 1 + i;
		CheckCollisionBonusCubeLower(nextElem, bonusCube, true, manager);
	}

	return false;
}

/**************************************
�e��Ԃł̏Փ˔���
***************************************/
bool CheckCollisionBonusCubeUpper(DWORD elem, BONUS_CUBE_OBJECT *bonusCube, COLLISION_MANAGER *manager)
{
	//���[�g��Ԃւ��ǂ�܂Ń��[�v
	for (elem = (elem - 1) >> 2; elem < manager->cellNum; elem = (elem - 1) >> 2)
	{
		//��Ԃ��쐬����Ă��邩����
		if (!manager->cellArray[OFT_PLAYERBULLET][elem])
			continue;

		if (manager->cellArray[OFT_PLAYERBULLET][elem]->latestObj != NULL)
		{
			OBJECT_FOR_TREE *bulletOFT = manager->cellArray[OFT_PLAYERBULLET][elem]->latestObj;
			while (bulletOFT != NULL)
			{
				PLAYERBULLET *bullet = (PLAYERBULLET*)bulletOFT->object;
				if (ChechHitBoundingCube(&bullet->collider2, &bonusCube->collider))
				{
					BurstPlayerBullet(bullet);
					bonusCube->hp -= BONUSCUBE_PLAYERBULLET_DAMAGE;
				}

				bulletOFT = bulletOFT->next;
			}
		}
	}

	return false;
}