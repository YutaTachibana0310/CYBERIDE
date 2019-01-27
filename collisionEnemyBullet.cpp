//=====================================
//
//�G�l�~�[�o���b�g�Փ˔��菈��[collisionEnemyBullett.cpp]
//Author:GP11A341 21 ���ԗY��
//
//=====================================
#include "collisionManager.h"
#include "enemyBullet.h"
#include "playerModel.h"
#include "cameraShaker.h"

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
bool CheckCollisionEnemyBulletLower(DWORD elem, PLAYERMODEL *player, bool isCheckedUpper, COLLISION_MANAGER *manager);
bool CheckCollisionEnemyBulletUpper(DWORD elem, PLAYERMODEL *player, COLLISION_MANAGER *manager);

/**************************************
�Փ˔���
***************************************/
void CheckCollisionEnemyBullet(COLLISION_MANAGER *manager)
{
	for (DWORD cntCell = 0; cntCell < manager->cellNum; cntCell++)
	{
		//��Ԃ��쐬����Ă��Ȃ��ꍇ�̔���
		if (!manager->cellArray[OFT_PLAYER][cntCell])
			continue;

		//��ԂɃI�u�W�F�N�g���o�^����Ă��Ȃ��ꍇ�̔���
		if (manager->cellArray[OFT_PLAYER][cntCell]->latestObj == NULL)
			continue;

		//��Ԃɓo�^����Ă���v���C���[�S�Ăɑ΂��Ĕ���
		OBJECT_FOR_TREE *playerOFT = manager->cellArray[OFT_PLAYER][cntCell]->latestObj;
		for (; playerOFT != NULL; playerOFT = playerOFT->next)
		{
			PLAYERMODEL *player = (PLAYERMODEL*)playerOFT->object;
			CheckCollisionEnemyBulletLower(cntCell, player, false, manager);
		}
	}
}

/**************************************
�q��Ԃł̏Փ˔���
***************************************/
bool CheckCollisionEnemyBulletLower(DWORD elem, PLAYERMODEL *player, bool isCheckedUpper, COLLISION_MANAGER *manager)
{
	//�w�肳�ꂽ��Ԃ��ő��Ԑ��𒴂��Ă��锻��
	if (elem >= manager->cellNum)
		return false;

	//�e��Ԃł̔���
	if (!isCheckedUpper)
	{
		CheckCollisionEnemyBulletUpper(elem, player, manager);
	}


	//��Ԃ��쐬����Ă��Ȃ��ꍇ�̔���
	if (!manager->cellArray[OFT_ENEMYBULLET][elem])
		return false;

	//�w�肳�ꂽ��ԓ��̃G�l�~�[�o���b�g�ɂ������Ĕ���
	if (manager->cellArray[OFT_ENEMYBULLET][elem]->latestObj != NULL)
	{
		OBJECT_FOR_TREE *bulletOFT = manager->cellArray[OFT_ENEMYBULLET][elem]->latestObj;
		while (bulletOFT != NULL)
		{
			//�Փ˔���
			ENEMYBULLET *bullet = (ENEMYBULLET*)bulletOFT->object;
			if (ChechHitBoundingCube(&bullet->collider, &player->collider))
			{
				SetCameraShaker(5.0f);
			}

			//�o�^����Ă��鎟�̃o���b�g��
			bulletOFT = bulletOFT->next;
		}

		//�q��Ԃł�����
		for (int i = 0; i < 4; i++)
		{
			DWORD nextElem = elem * 4 + 1 + i;
			CheckCollisionEnemyBulletLower(nextElem, player, true, manager);
		}
	}
	return false;
}

/**************************************
�e��Ԃł̏Փ˔���
***************************************/
bool CheckCollisionEnemyBulletUpper(DWORD elem, PLAYERMODEL *player, COLLISION_MANAGER *manager)
{
	for (elem = (elem - 1) >> 2; elem < manager->cellNum; elem = (elem - 1) >> 2)
	{
		//��Ԃ��쐬����Ă��Ȃ��ꍇ�̔���
		if (!manager->cellArray[OFT_ENEMYBULLET][elem])
			continue;

		//�w�肳�ꂽ��ԓ��̃o���b�g�ɑ΂��Ĕ���
		if (manager->cellArray[OFT_ENEMYBULLET][elem]->latestObj != NULL)
		{
			OBJECT_FOR_TREE *bulletOFT = manager->cellArray[OFT_ENEMYBULLET][elem]->latestObj;
			while (bulletOFT != NULL)
			{
				//�Փ˔���
				ENEMYBULLET *bullet = (ENEMYBULLET*)bulletOFT->object;
				if (ChechHitBoundingCube(&bullet->collider, &player->collider))
				{
					SetCameraShaker(5.0f);
				}

				//���̃o���b�g��
				bulletOFT = bulletOFT->next;
			}
		}
	}
	return false;
}
