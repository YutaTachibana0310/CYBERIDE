//=====================================
//
//�e���v���[�g����[targetSite.cpp]
//Author:GP11A341 21 ���ԗY��
//
//=====================================
#include "targetSite.h"
#include "playerModel.h"
#include "battleCamera.h"
#include "enemyMissile.h"
#include "debugproc.h"
#include "rockonSite.h"
#include "soundEffectManager.h"
#include "dataContainer.h"
#include "input.h"

#include "debugWindow.h"

/**************************************
�}�N����`
***************************************/
#define TARGETSITE_SIZE_X				(300.0f)
#define TARGETSITE_SIZE_Y				(300.0f)
#define TARGETSITE_MAX					PLAYERMODEL_MAX
#define TARGETSITE_MOVEVALUE			(3.0f)
#define TARGETSITE_INCIRCLE_ROTVALUE	(0.01f)
#define TARGETSITE_OUTCIRCLE_ROTVALUE	(-0.015f)
#define TARGETSITE_COLLIDER_RADIUS		(180.0f)
#define TARGETSITE_LOCKONRANGE_MAX		(3000.0f)
#define TARGETSITE_OPEN_VALUE			(0.1f)

/**************************************
�\���̒�`
***************************************/
enum TARGETSITE_TEXTUREINDEX
{
	TARGETSITE_INCIRCLE,
	TARGETSITE_OUTCIRCLE,
	TARGETSITE_TEXTUREMAX
};

/**************************************
�O���[�o���ϐ�
***************************************/
static LPDIRECT3DTEXTURE9 texture[TARGETSITE_TEXTUREMAX];
static TARGETSITE targetSite[TARGETSITE_MAX];
static VERTEX_2D vtxWk[NUM_VERTEX];
static float vtxRadius, vtxAngle;

static const char* texturePath[] = {
	"data/TEXTURE/UI/targetSite1_1.png",
	"data/TEXTURE/UI/targetSite1_2.png"
};

//���b�N�I�����x���ɉ������^�[�Q�b�g�T�C�g�̃X�P�[��
static const float ScaleLevel[DATACONTAINER_LOCKLEVEL_MAX] = {
	0.6f,0.7f, 0.8f, 0.9f, 1.0f, 1.1f, 1.2f
};


/**************************************
�v���g�^�C�v�錾
***************************************/
void MakeVertexTargetSite(void);
void SetVertexTargetSite(TARGETSITE *ptr, float rotation);

/**************************************
����������
***************************************/
void InitTargetSite(int num)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	static bool initialized = false;

	if (!initialized)
	{
		for (int i = 0; i < TARGETSITE_TEXTUREMAX; i++)
		{
			texture[i] = CreateTextureFromFile((LPSTR)texturePath[i], pDevice);
		}

		MakeVertexTargetSite();
		initialized = true;
	}

	TARGETSITE *ptr = &targetSite[0];
	for (int i = 0; i < TARGETSITE_MAX; i++, ptr++)
	{
		ptr->pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		ptr->insideRot = ptr->outsideRot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		ptr->baseScale = 0.0f;
	}
}

/**************************************
�I������
***************************************/
void UninitTargetSite(int num)
{
	TARGETSITE *ptr = &targetSite[0];
	for (int i = 0; i < TARGETSITE_MAX; i++, ptr++)
	{
		ptr->pos = D3DXVECTOR3(9999.9f, 9999.9f, -9999.9f);
	}

	if (num == 0)
	{
		for (int j = 0; j < TARGETSITE_TEXTUREMAX; j++)
		{
			SAFE_RELEASE(texture[j]);
		}
	}
}

/**************************************
�X�V����
***************************************/
void UpdateTargetSite(bool isOpen)
{
	TARGETSITE *ptr = &targetSite[0];
	D3DXVECTOR3 tmpPos;
	VERTEX_3D *pVtx = NULL;

	for (int i = 0; i < TARGETSITE_MAX; i++, ptr++)
	{
		if (!ptr->active)
		{
			continue;
		}

		//�X�P�[���v�Z
		float addValue = isOpen ? TARGETSITE_OPEN_VALUE : -TARGETSITE_OPEN_VALUE;
		ptr->baseScale = Clampf(0.0f, 1.0f, ptr->baseScale + addValue);

		//�X�N���[�����W����
		ptr->screenPos.x = Clampf(0.0f, SCREEN_WIDTH, ptr->screenPos.x);
		ptr->screenPos.y = Clampf(0.0f, SCREEN_HEIGHT, ptr->screenPos.y);

		//�����̃T�[�N������]
		ptr->insideRot.z += TARGETSITE_INCIRCLE_ROTVALUE;

		//�O���̃T�[�N�����X�V
		ptr->outsideRot.z += TARGETSITE_OUTCIRCLE_ROTVALUE;
	}
}

/**************************************
�`�揈��
***************************************/
void DrawTargetSite(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	float scale = ScaleLevel[GetLockonLevel()];

	pDevice->SetFVF(FVF_VERTEX_3D);

	TARGETSITE *ptr = &targetSite[0];
	for (int i = 0; i < TARGETSITE_MAX; i++, ptr++)
	{
		if (!ptr->active)
		{
			continue;
		}

		pDevice->SetFVF(FVF_VERTEX_2D);

		pDevice->SetTexture(0, texture[TARGETSITE_INCIRCLE]);
		SetVertexTargetSite(ptr, ptr->insideRot.z);
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, vtxWk, sizeof(VERTEX_2D));

		pDevice->SetTexture(0, texture[TARGETSITE_OUTCIRCLE]);
		SetVertexTargetSite(ptr, ptr->outsideRot.z);
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, vtxWk, sizeof(VERTEX_2D));
	}
}

/**************************************
���_�쐬����
***************************************/
void MakeVertexTargetSite(void)
{
	vtxWk[0].rhw =
		vtxWk[1].rhw =
		vtxWk[2].rhw =
		vtxWk[3].rhw = 1.0f;

	vtxWk[0].diffuse =
		vtxWk[1].diffuse =
		vtxWk[2].diffuse =
		vtxWk[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	vtxWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	vtxWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	vtxWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	vtxWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	vtxAngle = atan2f(TARGETSITE_SIZE_Y, TARGETSITE_SIZE_X);
	vtxRadius = D3DXVec2Length(&D3DXVECTOR2(TARGETSITE_SIZE_X, TARGETSITE_SIZE_Y));

	return;
}

/**************************************
���_�ݒ菈��
***************************************/
void SetVertexTargetSite(TARGETSITE *ptr, float rotation)
{
	float scale = ScaleLevel[GetLockonLevel()];

	vtxWk[0].vtx.x = ptr->screenPos.x - cosf(vtxAngle + rotation) * vtxRadius * ptr->baseScale * scale;
	vtxWk[0].vtx.y = ptr->screenPos.y - sinf(vtxAngle + rotation) * vtxRadius * ptr->baseScale * scale;
	vtxWk[1].vtx.x = ptr->screenPos.x + cosf(vtxAngle - rotation) * vtxRadius * ptr->baseScale * scale;
	vtxWk[1].vtx.y = ptr->screenPos.y - sinf(vtxAngle - rotation) * vtxRadius * ptr->baseScale * scale;
	vtxWk[2].vtx.x = ptr->screenPos.x - cosf(vtxAngle - rotation) * vtxRadius * ptr->baseScale * scale;
	vtxWk[2].vtx.y = ptr->screenPos.y + sinf(vtxAngle - rotation) * vtxRadius * ptr->baseScale * scale;
	vtxWk[3].vtx.x = ptr->screenPos.x + cosf(vtxAngle + rotation) * vtxRadius * ptr->baseScale * scale;
	vtxWk[3].vtx.y = ptr->screenPos.y + sinf(vtxAngle + rotation) * vtxRadius * ptr->baseScale * scale;
}

/**************************************
���W�Z�b�g����
***************************************/
void SetTargetSitePosition(D3DXVECTOR3 pos, int id, D3DXVECTOR3 offset)
{
	D3DXVECTOR3 screenPos;
	D3DXVec3TransformCoord(&screenPos, &pos, &GetBattleCameraView());
	D3DXVec3TransformCoord(&screenPos, &screenPos, &GetBattleCameraProjection());
	TranslateViewPort(&screenPos, &screenPos);

	targetSite[id].screenPos = screenPos + offset;
}

/**************************************
�A�h���X�擾����
***************************************/
TARGETSITE *GetTargetSiteAdr(int id)
{
	return &targetSite[id];
}

/**************************************
�����蔻��
***************************************/
bool CollisionTargetSite(int id, const D3DXVECTOR3* pos)
{
	if (pos->z > TARGETSITE_LOCKONRANGE_MAX)
		return false;

	TARGETSITE *ptr = &targetSite[id];
	if (pos->z < ptr->pos.z)
		return false;

	D3DXVECTOR3 targetScreenPos;
	PLAYERMODEL *player = GetPlayerAdr(id);
	float radius = TARGETSITE_COLLIDER_RADIUS * ScaleLevel[GetLockonLevel()] * ptr->baseScale;

	D3DXVec3TransformCoord(&targetScreenPos, pos, &GetBattleCameraView());
	D3DXVec3TransformCoord(&targetScreenPos, &targetScreenPos, &GetBattleCameraProjection());
	TranslateViewPort(&targetScreenPos, &targetScreenPos);

	if (D3DXVec3LengthSq(&(targetScreenPos - ptr->screenPos)) < powf(radius, 2))
	{
		return true;
	}

	return false;
}
