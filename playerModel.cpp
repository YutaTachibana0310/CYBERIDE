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
#include "playerModelTransition.h"
#include "playerModelTitle.h"
#include "playerModelTitleLaunch.h"
#include "playerBullet.h"
#include "playerMissile.h"
#include "soundEffectManager.h"
#include "dataContainer.h"
#include "soundEffectManager.h"
#include "collisionManager.h"
#include "scoreMagniGauge.h"
#include "shadow.h"

#ifdef _DEBUG
#include "debugproc.h"
#endif

/**************************************
�}�N����`
***************************************/
#define PLAYERMODEL_MODELNAME			"data/MODEL/player001.x"
#define PLAYER_ROTATEMAGNI				(0.2f)
#define PLATER_ROTATEVALUE_MAX			(0.085f)
#define PLAYER_TEXTURE_MAX				(19)
#define PLAYERMODEL_MODELNAME_DEBUG		"data/MODEL/airplane000.x"
#define PLAYERMODEL_COLLIDER_LENGTH		(D3DXVECTOR3(6.0f, 4.0f, 14.0f))
#define PLAYERMODE_INVINCIBLE_DURATION	(180)

/**************************************
�\���̒�`
***************************************/
typedef void(*funcPlayerModel)(PLAYERMODEL *player);

/**************************************
�O���[�o���ϐ�
***************************************/
static PLAYERMODEL model[PLAYERMODEL_MAX];
static OBJECT_FOR_TREE objectForTree[PLAYERMODEL_MAX];
static LPD3DXMESH mesh = NULL;
static LPD3DXBUFFER materials = NULL;
static DWORD numMaterial = 0;

static int playerState;

//�X�V�����֐��e�[�u��
static funcPlayerModel Update[PlayerStateMax] = {
	UpdatePlayerModelFPS,
	UpdatePlayerModelTopView,
	UpdatePlayerModelSideView,
	UpdatePlayerModelQuaterView,
	UpdatePlayerModelTransition,
	UpdatePlayerModelTitle,
	UpdatePlayerModelTitleLaunch,
	UpdatePlayerModelTutorialMove,
	UpdatePlayerModelTutorialLockon
};

//���ꏈ���֐��e�[�u��
static funcPlayerModel Enter[PlayerStateMax] = {
	EnterPlayerModelFPS,
	EnterPlayerModelTopView,
	EnterPlayerModelSideView,
	EnterPlayerModelQuaterView,
	EnterPlayerModelTransition,
	EnterPlayerModelTitle,
	EnterPlayerModelTitleLaunch,
	EnterPlayerModelTutorialMove,
	EnterPlayerModelTutorialLockon
};

//�ޏꏈ���֐��e�[�u��
static funcPlayerModel Exit[PlayerStateMax] = {
	ExitPlayerModelFPS,
	ExitPlayerModelTopView,
	ExitPlayerModelSideView,
	ExitPlayerModelQuaterView,
	ExitPlayerModelTransition,
	ExitPlayerModelTitle,
	ExitPlayerModelTitleLaunch,
	ExitPlayerModelTutorialMove,
	ExitPlayerModelTutorialLockon,
};

//�e�N�X�`����
static const char* textureName[PLAYER_TEXTURE_MAX] = {
	NULL,
	"data/TEXTURE/PLAYER/d10.jpg",
	"data/TEXTURE/PLAYER/door_mtl2_diffcol.jpg",
	NULL,
	NULL,
	"data/TEXTURE/PLAYER/d17.jpg",
	"data/TEXTURE/PLAYER/door_mtl1_diffcol.jpg",
	NULL,
	NULL,
	"data/TEXTURE/PLAYER/d17b.jpg",
	NULL,
	NULL,
	"data/TEXTURE/PLAYER/vj2c.jpg",
	NULL,
	NULL,
	"data/TEXTURE/PLAYER/cockpit_mtl1_diffcol.jpg",
	NULL,
	"data/TEXTURE/PLAYER/yx1_02_01_01.jpg",
	"data/TEXTURE/PLAYER/bmq1.jpg",
};

static LPDIRECT3DTEXTURE9 texture[PLAYER_TEXTURE_MAX];		//�e�N�X�`��

/**************************************
�v���g�^�C�v�錾
***************************************/

/**************************************
����������
***************************************/
void InitPlayerModel(int num)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	static bool initialized = false;

#ifdef _DEBUG
	if (!initialized)
	{
		D3DXLoadMeshFromX(PLAYERMODEL_MODELNAME_DEBUG, D3DXMESH_SYSTEMMEM, pDevice, NULL, &materials, NULL, &numMaterial, &mesh);
		initialized = true;
	}
#else
	if (!initialized)
	{
		D3DXLoadMeshFromX(PLAYERMODEL_MODELNAME, D3DXMESH_SYSTEMMEM, pDevice, NULL, &materials, NULL, &numMaterial, &mesh);
		for (int i = 0; i < PLAYER_TEXTURE_MAX; i++)
		{
			texture[i] = CreateTextureFromFile((LPSTR)textureName[i], pDevice);
		}
		initialized = true;
	}
#endif

	PLAYERMODEL *ptr = &model[0];
	OBJECT_FOR_TREE *oft = &objectForTree[0];
	for (int i = 0; i < PLAYERMODEL_MAX; i++, ptr++, oft++)
	{
		ptr->pos = D3DXVECTOR3(0, 0, 0);
		
		ptr->rot = ptr->destRot = D3DXVECTOR3(0, D3DXToRadian(180.0f), 0);
		ptr->scale = D3DXVECTOR3(1.5f, 1.5f, 1.5f);

		ptr->id = i;

		ptr->boostMode = false;

		ptr->collider.pos = &ptr->pos;
		ptr->collider.offset = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		ptr->collider.length = PLAYERMODEL_COLLIDER_LENGTH;

		CreateOFT(oft, (void*)ptr);
	}

	model[0].active = true;
	ChangeStatePlayerModel(PlayerFPS);
}

/**************************************
�I������
***************************************/
void UninitPlayerModel(int num)
{
	PLAYERMODEL *ptr = &model[0];
	OBJECT_FOR_TREE *oft = &objectForTree[0];
	for (int i = 0; i < PLAYERMODEL_MAX; i++, ptr++, oft++)
	{
		ptr->active = false;
		RemoveObjectFromSpace(oft);
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
	OBJECT_FOR_TREE *oft = &objectForTree[0];
	for (int i = 0; i < PLAYERMODEL_MAX; i++, ptr++, oft++)
	{
		if (!ptr->active)
		{
			continue;
		}

		//�e��Ԃɉ����čX�V����
		Update[playerState](ptr);

		//���f������]
		D3DXVECTOR3 diff = ptr->destRot - ptr->rot;
		ptr->rot.x += Clampf(-PLATER_ROTATEVALUE_MAX, PLATER_ROTATEVALUE_MAX, diff.x * PLAYER_ROTATEMAGNI);
		ptr->rot.y += Clampf(-PLATER_ROTATEVALUE_MAX, PLATER_ROTATEVALUE_MAX, diff.y * PLAYER_ROTATEMAGNI);
		ptr->rot.z += Clampf(-PLATER_ROTATEVALUE_MAX, PLATER_ROTATEVALUE_MAX, diff.z * PLAYER_ROTATEMAGNI);

		//���G���Ԃ̏I���𔻒�
		if (ptr->cntFrame - ptr->invincibleStart > PLAYERMODE_INVINCIBLE_DURATION)
		{
			ptr->isInvincible = false;
		}

		//�Փˋ�Ԃւ̓o�^���X�V
		RemoveObjectFromSpace(oft);
		if (ptr->active)
		{
			RegisterObjectToSpace(&ptr->collider, oft, OFT_PLAYER);
		}

		//�e��ݒ�
		SetShadow(ptr->pos);
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

		D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxScale);
		D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRot);
		D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTranslate);

		pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);
		ptr->mtxWorld = mtxWorld;

		pMaterial = (D3DXMATERIAL*)materials->GetBufferPointer();

		for (int j = 0; j < (int)numMaterial; j++)
		{
			pDevice->SetMaterial(&pMaterial[j].MatD3D);
			pDevice->SetTexture(0, texture[j]);
			mesh->DrawSubset(j);
		}
#ifdef _DEBUG
		DrawBoundingCube(&ptr->collider);
#endif
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
	if (next <= PlayerQuaterView && playerState != PlayerTransition)
		playerState = PlayerTransition;
	else
		playerState = next;

	PLAYERMODEL *ptr = &model[0];
	//�ޏꏈ��
	for (int i = 0; i < PLAYERMODEL_MAX; i++, ptr++)
	{
		if (!ptr->active)
			continue;

		if (next <= PlayerQuaterView)
			ptr->nextState = next;

		Exit[playerState](ptr);
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
	if (ptr->atkInterbal < PLAYER_HOMINGATK_INTERBAL && !ptr->boostMode)
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
	int lockMax = GetLockonMax();
	for (int i = 0; i < lockMax; i++)
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
		PlaySE(DefineSE::LOCKON);
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

/**************************************
�z�[�~���O�U������
***************************************/
void AttackPlayerMissile(PLAYERMODEL *player)
{
	//�C���^�[�o�����ł���΃��^�[��
	if (player->atkInterbal < PLAYER_HOMINGATK_INTERBAL)
	{
		return;
	}

	//�������b�N�I�����Ă��Ȃ���΃��^�[��
	if (player->lockonNum == 0)
	{
		return;
	}

	//�X�R�A�{����ݒ�
	SetScoreMagni(player->lockonNum);
	SetScoreMagniGauge();

	//���b�N�I���ΏۂɌ����ă~�T�C������
	for (int i = 0; i < PLAYER_ROCKON_MAX; i++)
	{
		if (player->target[i].pos == NULL)
		{
			continue;
		}

		SetPlayerMissile(player->target[i].pos, player->target[i].hp, player->target[i].active, player->pos);
		ReleaseRockonTarget(player, i);
		player->target[i].use = false;
	}

	PlaySE(DefineSE::MISSILELAUNCH);
	player->lockonNum = 0;

	if (!player->boostMode)
	{
		player->atkInterbal = 0;
	}
}