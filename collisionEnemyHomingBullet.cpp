//=====================================
//
//�G�l�~�[�z�[�~���O�o���b�g�Փ˔��菈��[collisionEnemyHomingBullett.cpp]
//Author:GP11A341 21 ���ԗY��
//
//=====================================
#include "collisionManager.h"
#include "enemyHomingBullet.h"
#include "playerModel.h"
#include "cameraShaker.h"
#include "bulletParticle.h"
#include "dataContainer.h"

/**************************************
�}�N����`
***************************************/
#define ENEMYHOMINGBULLET_EMMIITT_PARTICLENUM	(30)
#define ENEMYHOMINGBULLET_DAMAGE				(-1.25f)

/**************************************
�\���̒�`
***************************************/

/**************************************
�O���[�o���ϐ�
***************************************/

/**************************************
�v���g�^�C�v�錾
***************************************/
bool CheckCollisionEnemyHomingBulletLower(DWORD elem, PLAYERMODEL *player, bool isCheckedUpper, COLLISION_MANAGER *manager);
bool CheckCollisionEnemyHomingBulletUpper(DWORD elem, PLAYERMODEL *player, COLLISION_MANAGER *manager);

/**************************************
�Փ˔���
***************************************/
void CheckCollisionEnemyHomingBullet(COLLISION_MANAGER *manager)
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
			if (!player->isInvincible)
			{
				CheckCollisionEnemyHomingBulletLower(cntCell, player, false, manager);
			}
			CheckCollisionEnemyHomingBulletLower(cntCell, player, false, manager);
		}
	}
}

/**************************************
�q��Ԃł̏Փ˔���
***************************************/
bool CheckCollisionEnemyHomingBulletLower(DWORD elem, PLAYERMODEL *player, bool isCheckedUpper, COLLISION_MANAGER *manager)
{
	//�w�肳�ꂽ��Ԃ��ő��Ԑ��𒴂��Ă��锻��
	if (elem >= manager->cellNum)
		return false;

	//�e��Ԃł̔���
	if (!isCheckedUpper)
	{
		CheckCollisionEnemyHomingBulletUpper(elem, player, manager);
	}


	//��Ԃ��쐬����Ă��Ȃ��ꍇ�̔���
	if (!manager->cellArray[OFT_ENEMYHOMINGBULLET][elem])
		return false;

	//�w�肳�ꂽ��ԓ��̃G�l�~�[�z�[�~���O�o���b�g�ɂ������Ĕ���
	if (manager->cellArray[OFT_ENEMYHOMINGBULLET][elem]->latestObj != NULL)
	{
		OBJECT_FOR_TREE *bulletOFT = manager->cellArray[OFT_ENEMYHOMINGBULLET][elem]->latestObj;
		while (bulletOFT != NULL)
		{
			//�Փ˔���
			ENEMYHOMINGBULLET *bullet = (ENEMYHOMINGBULLET*)bulletOFT->object;
			if (ChechHitBoundingCube(&bullet->collider, &player->collider))
			{
				EmmittBulletParticle(&bullet->pos, BULLETEXPL_HOMING, ENEMYHOMINGBULLET_EMMIITT_PARTICLENUM);
				AddPlayerHP(ENEMYHOMINGBULLET_DAMAGE);
				bullet->active = false;

				//�v���C���[�𖳓G�ɃZ�b�g
				player->invincibleStart = player->cntFrame;
				player->isInvincible = true;
			}

			//�o�^����Ă��鎟�̃o���b�g��
			bulletOFT = bulletOFT->next;
		}

		//�q��Ԃł�����
		for (int i = 0; i < 4; i++)
		{
			DWORD nextElem = elem * 4 + 1 + i;
			CheckCollisionEnemyHomingBulletLower(nextElem, player, true, manager);
		}
	}
	return false;
}

/**************************************
�e��Ԃł̏Փ˔���
***************************************/
bool CheckCollisionEnemyHomingBulletUpper(DWORD elem, PLAYERMODEL *player, COLLISION_MANAGER *manager)
{
	for (elem = (elem - 1) >> 2; elem < manager->cellNum; elem = (elem - 1) >> 2)
	{
		//��Ԃ��쐬����Ă��Ȃ��ꍇ�̔���
		if (!manager->cellArray[OFT_ENEMYHOMINGBULLET][elem])
			continue;

		//�w�肳�ꂽ��ԓ��̃o���b�g�ɑ΂��Ĕ���
		if (manager->cellArray[OFT_ENEMYHOMINGBULLET][elem]->latestObj != NULL)
		{
			OBJECT_FOR_TREE *bulletOFT = manager->cellArray[OFT_ENEMYHOMINGBULLET][elem]->latestObj;
			while (bulletOFT != NULL)
			{
				//�Փ˔���
				ENEMYHOMINGBULLET *bullet = (ENEMYHOMINGBULLET*)bulletOFT->object;
				if (ChechHitBoundingCube(&bullet->collider, &player->collider))
				{
					EmmittBulletParticle(&bullet->pos, BULLETEXPL_HOMING, ENEMYHOMINGBULLET_EMMIITT_PARTICLENUM);
					AddPlayerHP(ENEMYHOMINGBULLET_DAMAGE);
					bullet->active = false;

					//�v���C���[�𖳓G�ɃZ�b�g
					player->invincibleStart = player->cntFrame;
					player->isInvincible = true;
				}

				//���̃o���b�g��
				bulletOFT = bulletOFT->next;
			}
		}
	}
	return false;
}
