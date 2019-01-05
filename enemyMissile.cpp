//=====================================
//
//�G�l�~�[�~�T�C������[enemyMissile.cpp]
//Author:GP11A341 21 ���ԗY��
//
//=====================================
#include "enemyMissile.h"
#include "enemyMissileLaunch.h"
#include "enemyMissileHoming.h"
#include "enemyMissileStraight.h"
#include "enemyMissileSmog.h"
#include "playerBullet.h"
#include "playerModel.h"
#include "targetSite.h"
#include "particleManager.h"

#if 1
#include "battleCamera.h"
#include "input.h"
#include "particle.h"
#endif

#include "debugWindow.h"

/**************************************
�}�N����`
**************************************/
#define ENEMYMISSILE_MODEL				"data/MODEL/missile.x"		//���f����
#define ENEMYMISSILE_ROTATEVALUE		(0.017f)					//1�t���[��������̉�]��
#define ENEMYMISSILE_COLLIDER_RADIUS	(20.0f)				//�����蔻��̔��a
#define ENEMYMISSILE_DAMAGE				(0.25f)				//�~�T�C���̃_���[�W
/**************************************
�\���̒�`
**************************************/
typedef void(*funcEnemyMissile)(ENEMYMISSILE*);

/*************************************
�v���g�^�C�v�錾
**************************************/
void CheckDestroyEnemyMissile(void);						//���S����

#ifdef USE_DEBUGWINDOW
void DrawDebugInfoEnemyMissile(void);
#endif

/*************************************
�O���[�o���ϐ�
**************************************/
static LPD3DXMESH mesh;										//���b�V���ւ̃|�C���^
static LPD3DXBUFFER materials;								//�}�e���A�����
static DWORD numMaterial;									//�������̑���
static D3DXMATRIX worldMtx;									//���[���h�}�g���N�X
static ENEMYMISSILE missile[ENEMYMISSILE_MAX];				//�G�l�~�[�~�T�C���\����

static int cntFrame = 0;

//�X�V�����̊֐��e�[�u��
static funcEnemyMissile Update[ENEMYMISSILE_STATEMAX] = { 
	EnemyMissileLaunchUpdate,
	EnemyMissileHomingUpdate,
	EnemyMissileStraightUpdate
};

//���ꏈ���̊֐��e�[�u��
static funcEnemyMissile Enter[ENEMYMISSILE_STATEMAX] = {
	EnemyMissileLaunchEnter,
	EnemyMissileHomingEnter,
	EnemyMissileStraightEnter,
};

//�ޏꏈ���̊֐��e�[�u��
static funcEnemyMissile Exit[ENEMYMISSILE_STATEMAX] = {
	EnemyMissileLaunchExit,
	EnemyMissileHomingExit,
	EnemyMissileStraightExit
};

static LARGE_INTEGER startSet, endSet;
static LARGE_INTEGER startUpdate, endUpdate;
static LARGE_INTEGER startParticle, endParticle;
static LARGE_INTEGER startCollision, endCollision;

/*************************************
����������
**************************************/
void InitEnemyMissile(int num)
{
	if (num == 0)
	{
		LPDIRECT3DDEVICE9 pDevice = GetDevice();

		mesh = NULL;
		materials = NULL;

		if (FAILED(D3DXLoadMeshFromX(ENEMYMISSILE_MODEL,
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&materials,
			NULL,
			&numMaterial,
			&mesh)))
		{
			return;
		}
	}

	ENEMYMISSILE *ptr = &missile[0];
	for (int i = 0; i < ENEMYMISSILE_MAX; i++, ptr++)
	{
		ptr->active = false;
		ptr->pos = D3DXVECTOR3(0.0f, 0.0f, -9999.0f);
		ptr->rot = D3DXQUATERNION(0.0f, 0.0f, 0.0f, 0.0f);
		ptr->velocity = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		ptr->speed = 0.0f;
		ptr->collider.active = false;
		ptr->collider.radius = ENEMYMISSILE_COLLIDER_RADIUS;
	}
}

/****************************************
�I������
*****************************************/
void UninitEnemyMissile(int num)
{
	ENEMYMISSILE *ptr = &missile[0];
	for (int i = 0; i < ENEMYMISSILE_MAX; i++)
	{
		missile[0].active = false;
	}

	if(num == 0)
	{
		SAFE_RELEASE(mesh);
		SAFE_RELEASE(materials);
	}
}

/****************************************
�X�V����
*****************************************/
void UpdateEnemyMissile(void)
{

	ENEMYMISSILE *ptr = &missile[0];

	GetTimerCount(&startSet);
	cntFrame++;
	if (cntFrame % 2 == 0)
	{
		for (int k = 0; k < 16; k++)
		{
			float angle = RandomRangef(45.0f, 135.0f);
			D3DXVECTOR3 target = D3DXVECTOR3(cosf(0.017f * angle), sinf(0.017f * angle), 0.0f);
			//SetEnemyMissile(D3DXVECTOR3(RandomRange(-500.0f, 500.0f), -200.0f, 2000), target, GetBattleCameraPos() + D3DXVECTOR3(RandomRange(-20.0f, 20.0f), RandomRange(-20.0f, 20.0f), 0.0f));
		}
	}
	GetTimerCount(&endSet);

	GetTimerCount(&startUpdate);
	for (int i = 0; i < ENEMYMISSILE_MAX; i++, ptr++)
	{
		if (!ptr->active)
		{
			continue;
		}

		Update[ptr->state](ptr);
		ptr->cntFrame++;
	}
	GetTimerCount(&endUpdate);

	GetTimerCount(&startParticle);
	CheckDestroyEnemyMissile();
	GetTimerCount(&endParticle);

	GetTimerCount(&startCollision);
	//CollisionEnemyMissileAndBullet();
	GetTimerCount(&endCollision);


	GetTimerCount(&endUpdate);
}

/*****************************************
�`�揈��
******************************************/
void DrawEnemyMissile(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTranslate;
	D3DXMATERIAL *pMaterial;
	D3DMATERIAL9 matDef;

	pDevice->GetMaterial(&matDef);

	ENEMYMISSILE *ptr = &missile[0];
	for (int i = 0; i < ENEMYMISSILE_MAX; i++, ptr++)
	{
		if (!ptr->active)

		{
			continue;
		}

		//���[���h�}�g���N�X�̏�����
		D3DXMatrixIdentity(&worldMtx);

		//��]�𔽉f
		D3DXMatrixRotationQuaternion(&mtxRot, &ptr->rot);
		D3DXMatrixMultiply(&worldMtx, &worldMtx, &mtxRot);

		//�ړ��𔽉f
		D3DXMatrixTranslation(&mtxTranslate, ptr->pos.x, ptr->pos.y, ptr->pos.z);
		D3DXMatrixMultiply(&worldMtx, &worldMtx, &mtxTranslate);

		//���[���h�}�g���N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &worldMtx);

		//�e�N�X�`���̐ݒ�iNULL�j
		pDevice->SetTexture(0, NULL);

		//�}�e���A�����ɑ΂���|�C���^���擾
		pMaterial = (D3DXMATERIAL*)materials->GetBufferPointer();

		//�`��
		for (int i = 0; i < (int)numMaterial; i++)
		{
			pDevice->SetMaterial(&pMaterial[i].MatD3D);
			mesh->DrawSubset(i);
		}
	}

	//�}�e���A�����f�t�H���g�ɖ߂�
	pDevice->SetMaterial(&matDef);

	DrawDebugInfoEnemyMissile();
}

/******************************************
�G�l�~�[�~�T�C���A�h���X�擾�֐�
*******************************************/
ENEMYMISSILE *GetEnemyMissileAdr(int n)
{
	return (n < ENEMYMISSILE_MAX) ? &missile[n] : NULL;
}

/*****************************************
�G�l�~�[�~�T�C����ԑJ�ڊ֐�
******************************************/
void ChangeStateEnemyMissile(ENEMYMISSILE *ptr, int targetState)
{
	//�ޏꏈ�����Ăяo��
	Exit[ptr->state](ptr);

	//��ԑJ��
	ptr->state = targetState;

	//���ꏈ�����Ăяo��
	Enter[ptr->state](ptr);
}

/*****************************************
�G�l�~�[�~�T�C���Z�b�g�֐�
******************************************/
void SetEnemyMissile(D3DXVECTOR3 pos, D3DXVECTOR3 moveDir, D3DXVECTOR3 targetPos)
{
	ENEMYMISSILE *ptr = &missile[0];

	for (int i = 0; i < ENEMYMISSILE_MAX; i++, ptr++)
	{
		if (ptr->active)
		{
			continue;
		}

		ptr->pos = pos;
		ptr->velocity = moveDir;
		ptr->cntFrame = 0;
		//ptr->state = ENEMYMISSILE_LAUNCH;
		ChangeStateEnemyMissile(ptr, ENEMYMISSILE_LAUNCH);
		ptr->hp = 1.0f;
		ptr->active = true;

		return;
	}
}

/*****************************************
�G�l�~�[�~�T�C�������蔻��
******************************************/
void CollisionEnemyMissileAndBullet(void)
{
	ENEMYMISSILE *ptr = &missile[0];
	PLAYERBULLET *bullet = GetPlayerBulletAdr(0);
	float distSq, radiusSq;

	//�v���C���[�o���b�g�Ƃ̓����蔻��
	for (int i = 0; i < ENEMYMISSILE_MAX; i++, ptr++)
	{
		if (!ptr->active)
		{
			continue;
		}

		bullet = GetPlayerBulletAdr(0);
		for (int j = 0; j < PLAYERBULLET_MAX; j++, bullet++)
		{
			if (!bullet->active)
			{
				continue;
			}

			distSq = D3DXVec3LengthSq(&(bullet->pos - ptr->pos));
			if (distSq < 400.0f)
			{
				ptr->hp = 0.0f;
				bullet->active = false;
			}
		}
	}
}

/*****************************************
�G�l�~�[�~�T�C�����b�N�I������
******************************************/
void LockonEnemyMissile(void)
{
	ENEMYMISSILE *ptr = &missile[0];
	TARGETSITE *targetSite = GetTargetSiteAdr(0);

	for (int i = 0; i < PLAYERMODEL_MAX; i++, targetSite++)
	{
		if (!targetSite->active)
		{
			continue;
		}

		ptr = &missile[0];
		for (int j = 0; j < ENEMYMISSILE_MAX; j++, ptr++)
		{
			if (!ptr->active)
			{
				continue;
			}

			if (CollisionTargetSite(i, &ptr->pos))
			{
				AddRockonTarget(i, &ptr->pos, &ptr->active, &ptr->hp);
			}
		}

	}
}

/*****************************************
���S����
******************************************/
void CheckDestroyEnemyMissile(void)
{
	ENEMYMISSILE *ptr = &missile[0];
	for (int i = 0; i < ENEMYMISSILE_MAX; i++, ptr++)
	{
		if (!ptr->active)
		{
			continue;
		}

		if (ptr->hp <= 0.0f)
		{
			//for (int j = 0; j < 2; j++)
			//{
			//	SetExplosionFlare(&ptr->pos);
			//}
			//for (int j = 0; j < 1; j++)
			//{
			//	SetExplosionFire(&ptr->pos);
			//}
			//for (int j = 0; j < 1; j++)
			//{
			//	SetExplosionSmog(&ptr->pos);
			//}
			SetEnemyExplosion(ptr->pos);
			ptr->active = false;

		}
	}
}

#ifdef USE_DEBUGWINDOW
/*****************************************
�f�o�b�O���\��
******************************************/
void DrawDebugInfoEnemyMissile(void)
{
	ImGui::StyleColorsDark();
	ImGui::SetNextWindowSize(ImVec2(200.0f, 100.0f));
	ImGui::SetNextWindowPos(ImVec2(5.0f, 310.0f));
	ImGui::Begin("EnemyMissle");

	ImGui::Text("Set       : %fmsec", CalcProgressTime(startSet, endSet));
	ImGui::Text("Update    : %fmsec", CalcProgressTime(startUpdate, endUpdate));
	ImGui::Text("Destroy   : %fmsec", CalcProgressTime(startParticle, endParticle));
	ImGui::Text("Collision : %fmsec", CalcProgressTime(startCollision, endCollision));

	ImGui::End();
}
#endif