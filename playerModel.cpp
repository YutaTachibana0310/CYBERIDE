//=====================================
//
//�v���C���[���f������[playerModel.cpp]
//Author:GP11A341 21 ���ԗY��
//
//=====================================
#include "playerModel.h"
#include "input.h"
#include "playerModelFPS.h"
#include "playerModelTopView.h"
#include "playerModelSideView.h"
#include "playerModelQuaterView.h"
#include "playerBullet.h"

#ifdef _DEBUG
#include "debugproc.h"
#endif

/**************************************
�}�N����`
***************************************/
#define PLAYERMODEL_MODELNAME		"data/MODEL/airplane000.x"
#define PLAYER_ROTATEMAGNI			(0.2f)
#define PLATER_ROTATEVALUE_MAX		(0.085f)

/**************************************
�\���̒�`
***************************************/
typedef void(*funcPlayerModel)(PLAYERMODEL *player);

/**************************************
�O���[�o���ϐ�
***************************************/
static PLAYERMODEL model[PLAYERMODEL_MAX];
static LPD3DXMESH mesh = NULL;
static LPD3DXBUFFER materials = NULL;
static DWORD numMaterial = 0;

static int playerState;

static funcPlayerModel Update[PlayerStateMax] = {
	UpdatePlayerModelFPS,
	UpdatePlayerModelTopView,
	UpdatePlayerModelSideView,
	UpdatePlayerModelQuaterView
};

static funcPlayerModel Enter[PlayerStateMax] = {
	EnterPlayerModelFPS,
	EnterPlayerModelTopView,
	EnterPlayerModelSideView,
	EnterPlayerModelQuaterView
};

/**************************************
�v���g�^�C�v�錾
***************************************/

/**************************************
����������
***************************************/
void InitPlayerModel(int num)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	
	if (num == 0)
	{
		D3DXLoadMeshFromX(PLAYERMODEL_MODELNAME, D3DXMESH_SYSTEMMEM, pDevice, NULL, &materials, NULL, &numMaterial, &mesh);
	}

	PLAYERMODEL *ptr = &model[0];
	for (int i = 0; i < PLAYERMODEL_MAX; i++, ptr++)
	{
		ptr->pos = D3DXVECTOR3(0, 0, 0);
		
		ptr->rot = ptr->destRot = D3DXVECTOR3(0, D3DXToRadian(180.0f), 0);
		ptr->scale = D3DXVECTOR3(10.0f, 10.0f, 10.0f);

		ptr->id = i;
	}

	ChangeStatePlayerModel(PlayerFPS);
	model[0].active = true;
}

/**************************************
�I������
***************************************/
void UninitPlayerModel(int num)
{
	PLAYERMODEL *ptr = &model[0];
	for (int i = 0; i < PLAYERMODEL_MAX; i++, ptr++)
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
void UpdatePlayerModel(void)
{
	PLAYERMODEL *ptr = &model[0];

	for (int i = 0; i < PLAYERMODEL_MAX; i++, ptr++)
	{
		if (!ptr->active)
		{
			continue;
		}

		Update[playerState](ptr);

		D3DXVECTOR3 diff = ptr->destRot - ptr->rot;
		ptr->rot.x += Clampf(-PLATER_ROTATEVALUE_MAX, PLATER_ROTATEVALUE_MAX, diff.x * PLAYER_ROTATEMAGNI);
		ptr->rot.y += Clampf(-PLATER_ROTATEVALUE_MAX, PLATER_ROTATEVALUE_MAX, diff.y * PLAYER_ROTATEMAGNI);
		ptr->rot.z += Clampf(-PLATER_ROTATEVALUE_MAX, PLATER_ROTATEVALUE_MAX, diff.z * PLAYER_ROTATEMAGNI);

		PrintDebugProc("playerpos[%d]:%f %f %f\n", i, ptr->pos.x, ptr->pos.y, ptr->pos.z);
	}


}

/**************************************
�`�揈��
***************************************/
void DrawPlayerModel(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTranslate, mtxScale, mtxWorld;
	D3DXMATERIAL *pMaterial;
	D3DMATERIAL9 matDef;

	pDevice->GetMaterial(&matDef);
	pDevice->SetTexture(0, NULL);	

	PLAYERMODEL *ptr = &model[0];
	for (int i = 0; i < PLAYERMODEL_MAX; i++, ptr++)
	{
		if (!ptr->active)
		{
			continue;
		}

		//���[���h�}�g���N�X�̕ϊ�
		D3DXMatrixIdentity(&mtxWorld);
		D3DXMatrixScaling(&mtxScale, ptr->scale.x, ptr->scale.y, ptr->scale.z);
		D3DXMatrixRotationYawPitchRoll(&mtxRot, ptr->rot.y, ptr->rot.x, ptr->rot.z);
		D3DXMatrixTranslation(&mtxTranslate, ptr->pos.x, ptr->pos.y, ptr->pos.z);

		//D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxScale);
		D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRot);
		D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTranslate);

		pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);

		pMaterial = (D3DXMATERIAL*)materials->GetBufferPointer();

		for (int j = 0; j < (int)numMaterial; j++)
		{
			pDevice->SetMaterial(&pMaterial[j].MatD3D);
			mesh->DrawSubset(j);
		}
	}

	pDevice->SetMaterial(&matDef);
}

/*********************************************
�֐���	�FPLAYERMODEL *GetPlayerModelAdr(int num)
����	�Fint num �c �A�h���X���擾�������v���C���[�̃C���f�b�N�X
�߂�l	�F�v���C���[�\���̂̃A�h���X
*********************************************/
PLAYERMODEL *GetPlayerAdr(int num)
{
	return &model[num];
}

/*********************************************
�֐���	�FPLAYERMODEL *GetPlayerModelAdr(int num)
����	�Fint next ���̏��
�߂�l	�F�v���C���[�\���̂̃A�h���X
*********************************************/
void ChangeStatePlayerModel(int next)
{

	playerState = next;
	PLAYERMODEL *ptr = &model[0];
	for (int i = 0; i < PLAYERMODEL_MAX; i++, ptr++)
	{
		if (!ptr->active)
			continue;

		Enter[playerState](ptr);
	}
}

/*********************************************
�֐���	�Fvoid AddRockonTarget(int id, D3DXVECTOR3 *targetPos, bool *targetActive, float *targetHP)
����	�Fint id�F���b�N�I�������v���C���[��ID
����	�FD3DXVECTOR3 *targetPos�F���b�N�I���Ώۂ̍��W
����	�Fbool *targetActive�F���b�N�I���Ώۂ̃A�N�e�B�u���
����	�Ffloat *targetHP�F���b�N�I���Ώۂ�HP
�߂�l	�Fvoid
*********************************************/
ROCKONTARGET *AddRockonTarget(int id, D3DXVECTOR3 *targetPos, bool *targetActive, float *targetHP)
{
	PLAYERMODEL *ptr = &model[id];

	//�C���^�[�o������
	if (ptr->atkInterbal < PLAYER_HOMINGATK_INTERBAL)
	{
		return NULL;
	}

	//�_�u������
	for (int i = 0; i < PLAYER_ROCKON_MAX; i++)
	{
		if (ptr->target[i].pos == targetPos)
		{
			return NULL;
		}
	}

	//���g�p�̃^�[�Q�b�g�ɐݒ�
	for (int i = 0; i < PLAYER_ROCKON_MAX; i++)
	{
		//���b�N�I���̋󂫂�����܂Ń��[�v
		if (ptr->target[i].use)
		{
			continue;
		}

		//���b�N�I���Ώۂɐݒ肵return
		ptr->target[i].pos = targetPos;
		ptr->target[i].active = targetActive;
		ptr->target[i].hp = targetHP;
		ptr->target[i].use = true;
		ActivateRockonSite(ptr->id * PLAYER_ROCKON_MAX + i);
		ptr->lockonNum++;
		return &ptr->target[i];
	}

	//���b�N�I���̋󂫂��Ȃ��̂�return NULL
	return NULL;
}

/*********************************************
�֐���	�FReleaseRockonTarget(ROCKONTARGET *target)
����	�FROCKONTARGET *target�F���b�N�I���������������^�[�Q�b�g�ւ̃|�C���^
�߂�l	�Fvoid
*********************************************/
void ReleaseRockonTarget(PLAYERMODEL *player, int targetID)
{
	//target->active = NULL;
	//target->hp = NULL;
	//target->pos = NULL;

	player->target[targetID].active = NULL;
	player->target[targetID].hp = NULL;
	player->target[targetID].pos = NULL;
	player->target[targetID].use = false;
	player->lockonNum--;
}