//=====================================
//
//�v���C���[�~�T�C������[playerMissile.cpp]
//Author:GP11A341 21 ���ԗY��
//
//=====================================
#include "playerMissile.h"
#include "enemyMissile.h"

/**************************************
�}�N����`
***************************************/
#define PLAYERMISSILE_MODEL				"data/MODEL/airplane000.x"
#define PLAYERMISSILE_COLLIDER_RADIUS	(20.0f);
#define PLAYERMISSILE_REACEFRAME		(30.0f)
/**************************************
�\���̒�`
***************************************/

/**************************************
�O���[�o���ϐ�
***************************************/
static LPD3DXMESH mesh;
static LPD3DXBUFFER materials;
static DWORD numMaterial;
static D3DXMATRIX mtxWorld;
static PLAYERMISSILE missile[PLAYERMISSILE_MAX];

/**************************************
�v���g�^�C�v�錾
***************************************/

/**************************************
����������
***************************************/
void InitPlayerMissile(int num)
{
	if (num == 0)
	{
		LPDIRECT3DDEVICE9 pDevice = GetDevice();

		mesh = NULL;
		materials = NULL;

		if (FAILED(D3DXLoadMeshFromX(PLAYERMISSILE_MODEL,
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

	PLAYERMISSILE *ptr = &missile[0];
	for (int i = 0; i < PLAYERMISSILE_MAX; i++, ptr++)
	{
		ptr->active = false;
		ptr->pos = D3DXVECTOR3(0.0f, 0.0f, -9999.9f);
		//ptr->collider.active = false;
		//ptr->collider.radius = false;
	}
}

/**************************************
�I������
***************************************/
void UninitPlayerMissile(int num)
{
	PLAYERMISSILE *ptr = &missile[0];
	for (int i = 0; i < PLAYERMISSILE_MAX; i++, ptr++)
	{
		ptr->active = false;
	}

	if (num == 0)
	{
		SAFE_RELEASE(mesh);
		SAFE_RELEASE(materials);
	}
}

/**************************************
�X�V����
***************************************/
void UpdatePlayerMissile(void)
{
	PLAYERMISSILE *ptr = &missile[0];
	D3DXVECTOR3 diff;			//�^�[�Q�b�g���W�Ǝ����̍��W�̍���
	D3DXVECTOR3 acceleration;	//�����x
	float period;

	for (int i = 0; i < PLAYERMISSILE_MAX; i++, ptr++)
	{
		if (!ptr->active)
		{
			continue;
		}
#if 1
		//�ϐ�������
		acceleration.x = acceleration.y = acceleration.z = 0.0f;
		period = ptr->cntFrame / PLAYERMISSILE_REACEFRAME;

		//���������
		diff = *ptr->target - ptr->pos;

		//�����x�v�Z
		acceleration = (diff - ptr->velocity * period) * 2.0f / (period * period);

		ptr->cntFrame--;
		if (ptr->cntFrame < 0)
		{
			ptr->active = false;
			*ptr->targetHP -= 1.0f;
			continue;
		}

		ptr->velocity += acceleration / 60.0f;
		ptr->pos += ptr->velocity / 60.0f;
		
#else
		D3DXVec3Normalize(&diff, &diff);
		ptr->pos += diff * 30.0f;
#endif
	}

	//ColliisonPlayerMissileAndEnemyMissile();
}

/**************************************
�`�揈��
***************************************/
void DrawPlayerMissile(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxTranslate, mtxRot;
	D3DXMATERIAL *pMaterial;
	D3DMATERIAL9 matDef;

	pDevice->GetMaterial(&matDef);

	PLAYERMISSILE *ptr = &missile[0];

	for (int i = 0; i < PLAYERMISSILE_MAX; ptr++, i++)
	{
		if (!ptr->active)
		{
			continue;
		}

		//Init World
		D3DXMatrixIdentity(&mtxWorld);

		//rotation

		//translate
		D3DXMatrixTranslation(&mtxTranslate, ptr->pos.x, ptr->pos.y, ptr->pos.z);
		D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTranslate);

		//set world
		pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);

		//set texture
		pDevice->SetTexture(0, NULL);

		//get material
		pMaterial = (D3DXMATERIAL*)materials->GetBufferPointer();

		//draw
		for (int j = 0; j < (int)numMaterial; j++)
		{
			pDevice->SetMaterial(&pMaterial[j].MatD3D);
			mesh->DrawSubset(j);
		}
	}

	//reset material
	pDevice->SetMaterial(&matDef);
}

/**************************************
�Q�b�^�[
***************************************/
PLAYERMISSILE *GetPlayerMissileAdr(int id)
{
	return &missile[id];
}

/**************************************
�Z�b�^�[
***************************************/
void SetPlayerMissile(D3DXVECTOR3 *pTargetPos, float *pTargetHP, D3DXVECTOR3 pos)
{
	PLAYERMISSILE *ptr = &missile[0];

	for (int i = 0; i < PLAYERMISSILE_MAX; i++, ptr++)
	{
		if (ptr->active)
		{
			continue;
		}

		//�^�[�Q�b�g�ݒ�
		ptr->active = true;
		ptr->target = pTargetPos;
		ptr->targetHP = pTargetHP;

		//�����x�ݒ�
		float vX = (pTargetPos->x - pos.x) > 0 ? 5.0f : -5.0f;
		float vY = RandomRange(-50.0f, 50.0f);
		float vZ = RandomRange(-50.0f, -30.0f);
		ptr->velocity = D3DXVECTOR3(vX, vY,vZ);
		ptr->velocity *= 10.0f;

		//�p�����[�^������
		ptr->cntFrame = ptr->reachFrame = rand() % 40 + 15;
		ptr->pos = pos;
		return;
	}
}

#if 0
/**************************************
�����蔻��
***************************************/
void ColliisonPlayerMissileAndEnemyMissile(void)
{
	ENEMYMISSILE *enemyMissile = GetEnemyMissileAdr(0);
	PLAYERMISSILE *ptr = &missile[0];
	float distSq, radiusSq;

	radiusSq = powf(ptr->collider.radius + enemyMissile->collider.radius, 2.0f);

	for(int i = 0; i < PLAYERMISSILE_MAX; i++, ptr++)
	{
		if (!ptr->active)
		{
			continue;
		}

		enemyMissile = GetEnemyMissileAdr(0);
		for (int j = 0; j < ENEMYMISSILE_MAX; j++, enemyMissile++)
		{
			if (!enemyMissile->active)
			{
				continue;
			}

			distSq = D3DXVec3LengthSq(&(enemyMissile->pos - ptr->pos));
			if (distSq < radiusSq)
			{
				enemyMissile->hp -= 1.0f;
				ptr->active = false;
			}
		}
	}
}
#endif