//=====================================
//
//�G�l�~�[�~�T�C������[enemyMissile.cpp]
//Author:GP11A341 21 ���ԗY��
//
//=====================================
#include "enemyMissile.h"

/**************************************
�}�N����`
**************************************/
#define ENEMYMISSILE_MAX			(128)						//�~�T�C���ő吔
#define ENEMYMISSILE_MODEL			"data/MODEL/missile.x"		//���f����
#define ENEMYMISSILE_ROTATEVALUE	(0.017f)					//1�t���[��������̉�]��

/**************************************
�\���̒�`
**************************************/
enum ENEMYMISSILE_STATE
{
	ENEMYMISSILE_LAUNCH,			//���˒�����
	ENEMYMISSILE_HOMING,			//�z�[�~���O���
	ENEMYMISSILE_STRAIGHT,			//���i���
	ENEMYMISSILE_STATEMAX
};

/*************************************
�v���g�^�C�v�錾
**************************************/

/*************************************
�O���[�o���ϐ�
**************************************/
static LPD3DXMESH mesh;										//���b�V���ւ̃|�C���^
static LPD3DXBUFFER materials;								//�}�e���A�����
static DWORD numMaterial;									//�������̑���
static D3DXMATRIX worldMtx;									//���[���h�}�g���N�X
static ENEMYMISSILE missile[ENEMYMISSILE_MAX];				//�G�l�~�[�~�T�C���\����

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
		ptr->pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		ptr->rot = D3DXQUATERNION(0.0f, 0.0f, 0.0f, 0.0f);
		ptr->moveDir = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		ptr->speed = 0.0f;
		ptr->collider.active = false;
		ptr->flgHoming = false;
	}
}

/****************************************
�I������
*****************************************/
void UninitEnemyMissile(void)
{
	SAFE_RELEASE(mesh);
	SAFE_RELEASE(materials);
}

/****************************************
�X�V����
*****************************************/
void UpdateEnemyMissile(void)
{

	ENEMYMISSILE *ptr = &missile[0];

	for (int i = 0; i < ENEMYMISSILE_MAX; i++, ptr++)
	{
		if (!ptr->active)
		{
			continue;
		}


	}
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
}

/******************************************
�G�l�~�[�~�T�C���A�h���X�擾�֐�
*******************************************/
ENEMYMISSILE *GetEnemyMissileAdr(int n)
{
	return (n < ENEMYMISSILE_MAX) ? &missile[n] : NULL;
}

/*****************************************
���˒���̍X�V����
******************************************/
void UpdateEnemyMissileLaunch(ENEMYMISSILE *ptr)
{

}

/******************************************
�z�[�~���O���̍X�V����
*******************************************/
void UpdateEnemyMissileHoming(ENEMYMISSILE *ptr)
{

}

/********************************************
���i���̍X�V����
*********************************************/
void UpdateEnemyMissileStraight(ENEMYMISSILE *ptr)
{

}