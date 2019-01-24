//=====================================
//
//���b�N�I������[rockonSite.cpp]
//Author:GP11A341 21 ���ԗY��
//
//=====================================
#include "rockonSite.h"
#include "playerModel.h"
#include "battleCamera.h"
#include "debugproc.h"
#include "Easing.h"

/**************************************
�}�N����`
***************************************/
#define ROCKONSITE_SIZE				(20)
#define ROCKONSITE_TEXTURE			"data/TEXTURE/rockonSite.png"
#define ROCKONSITE_MAX				(PLAYER_ROCKON_MAX * PLAYERMODEL_MAX)
#define ROCKONSITE_INITSCALE		(20.0f)
#define ROCKONSITE_ENDSCALE			(1.0f)
#define ROCKONSITE_ANIMATIONFRAME	(15)
#define ROCKONSITE_ROT_VALUE		(0.02f)
#define ROCKONSITE_ROT_INTERBAL		(30)

#define ROCKONSITE_TEXT_NAME		"data/TEXTURE/rockonText.png"
#define ROCKONSITE_TEXT_OFFSET		(25.0f)

/**************************************
�\���̒�`
***************************************/

/**************************************
�O���[�o���ϐ�
***************************************/
static LPDIRECT3DTEXTURE9 texture;
static LPDIRECT3DTEXTURE9 textTex;
static ROCKONSITE rockon[ROCKONSITE_MAX];
static VERTEX_2D vtxWk[NUM_VERTEX];
static float vtxAngle, vtxRadius;

/**************************************
�v���g�^�C�v�錾
***************************************/
void MakeVertexRockonSite(void);
void SetVertexRockonSite(ROCKONSITE *ptr);
void SetVertexRockonSiteText(ROCKONSITE *ptr);

/**************************************
����������
***************************************/
void InitRockonSite(int num)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	static bool initialized = false;

	if (!initialized)
	{
		texture = CreateTextureFromFile((LPSTR)ROCKONSITE_TEXTURE, pDevice);
		textTex = CreateTextureFromFile((LPSTR)ROCKONSITE_TEXT_NAME, pDevice);
		MakeVertexRockonSite();

		initialized = true;
	}

	ROCKONSITE *ptr = &rockon[0];
	for (int i = 0; i < ROCKONSITE_MAX; i++, ptr++)
	{
		ptr->active = false;
		ptr->pos = D3DXVECTOR3(-9999.9f, -9999.9f, -9999.9f);
		ptr->scale = 1.0f;
		ptr->cntFrame = 0;
		ptr->rot = 0.0f;
	}
}

/**************************************
�I������
***************************************/
void UninitRockonSite(int num)
{
	ROCKONSITE *ptr = &rockon[0];
	for (int i = 0; i < ROCKONSITE_MAX; i++, ptr++)
	{
		ptr->active = false;
	}

	if (num == 0)
	{
		SAFE_RELEASE(texture);
	}
}

/**************************************
�X�V����
***************************************/
void UpdateRockonSite(void)
{
	ROCKONSITE *ptr = &rockon[0];
	int cnt = 0;

	for (int i = 0; i < ROCKONSITE_MAX; i++, ptr++)
	{
		if (!ptr->active)
		{
			continue;
		}

		ptr->cntFrame++;
		//�A�j���[�V����
		if (ptr->cntFrame < ROCKONSITE_ANIMATIONFRAME)
		{
			float t = (float)ptr->cntFrame / ROCKONSITE_ANIMATIONFRAME;
			ptr->scale = EaseOutCubic(t, ROCKONSITE_INITSCALE, ROCKONSITE_ENDSCALE);
			ptr->alpha = EaseInCubic(t, 0.0f, 1.0f);
		}

		//��]
		float t = (float)(ptr->cntFrame % (ROCKONSITE_ROT_INTERBAL + 1)) / ROCKONSITE_ROT_INTERBAL;
		ptr->rot = EaseInOutCubic(t, 0.0f, D3DX_PI);


		//�r���[�ϊ��A�v���W�F�N�V�����ϊ����s��
		D3DXVec3TransformCoord(&ptr->pos, &ptr->pos, &GetBattleCameraView());
		D3DXVec3TransformCoord(&ptr->pos, &ptr->pos, &GetBattleCameraProjection());

		//�r���[�|�[�g�ϊ��ŃX�N���[�����W�ɕϊ�����
		ptr->pos.x = ptr->pos.x * (SCREEN_WIDTH / 2.0f) + SCREEN_WIDTH / 2.0f;
		ptr->pos.y = ptr->pos.y * (-SCREEN_HEIGHT / 2.0f) + SCREEN_HEIGHT / 2.0f;
	}

	PrintDebugProc("rockon:%d\n", cnt);
}

/**************************************
�`�揈��
***************************************/
void DrawRockonSite(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxTranslate;

	pDevice->SetFVF(FVF_VERTEX_2D);
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, true);

	ROCKONSITE *ptr = &rockon[0];
	for (int i = 0; i < ROCKONSITE_MAX; i++, ptr++)
	{
		if (!ptr->active)
		{
			continue;
		}

		//���_��ݒ肵�ĕ`��
		pDevice->SetTexture(0, texture);
		SetVertexRockonSite(ptr);
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, vtxWk, sizeof(VERTEX_2D));

		pDevice->SetTexture(0, textTex);
		SetVertexRockonSiteText(ptr);
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, vtxWk, sizeof(VERTEX_2D));

		//�`���͔�A�N�e�B�u��
		ptr->active = false;
	}

	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, false);
}

/**************************************
���_�쐬����
***************************************/
void MakeVertexRockonSite(void)
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

	vtxAngle = atan2f(ROCKONSITE_SIZE, ROCKONSITE_SIZE);
	vtxRadius = D3DXVec2Length(&D3DXVECTOR2(ROCKONSITE_SIZE, ROCKONSITE_SIZE));
}

/**************************************
���_�ݒ菈��
***************************************/
void SetVertexRockonSite(ROCKONSITE *ptr)
{
	vtxWk[0].vtx.x = ptr->pos.x - cosf(vtxAngle + ptr->rot) * vtxRadius * ptr->scale;
	vtxWk[0].vtx.y = ptr->pos.y - sinf(vtxAngle + ptr->rot) * vtxRadius * ptr->scale;
	vtxWk[1].vtx.x = ptr->pos.x + cosf(vtxAngle - ptr->rot) * vtxRadius * ptr->scale;
	vtxWk[1].vtx.y = ptr->pos.y - sinf(vtxAngle - ptr->rot) * vtxRadius * ptr->scale;
	vtxWk[2].vtx.x = ptr->pos.x - cosf(vtxAngle - ptr->rot) * vtxRadius * ptr->scale;
	vtxWk[2].vtx.y = ptr->pos.y + sinf(vtxAngle - ptr->rot) * vtxRadius * ptr->scale;
	vtxWk[3].vtx.x = ptr->pos.x + cosf(vtxAngle + ptr->rot) * vtxRadius * ptr->scale;
	vtxWk[3].vtx.y = ptr->pos.y + sinf(vtxAngle + ptr->rot) * vtxRadius * ptr->scale;

	vtxWk[0].diffuse =
		vtxWk[1].diffuse =
		vtxWk[2].diffuse =
		vtxWk[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, ptr->alpha);
}

/**************************************
���_�ݒ菈��(������)
***************************************/
void SetVertexRockonSiteText(ROCKONSITE *ptr)
{
	vtxWk[0].vtx.x = ptr->pos.x - cosf(vtxAngle) * vtxRadius * ptr->scale;
	vtxWk[0].vtx.y = ptr->pos.y - sinf(vtxAngle) * vtxRadius * ptr->scale;
	vtxWk[1].vtx.x = ptr->pos.x + cosf(vtxAngle) * vtxRadius * ptr->scale;
	vtxWk[1].vtx.y = ptr->pos.y - sinf(vtxAngle) * vtxRadius * ptr->scale;
	vtxWk[2].vtx.x = ptr->pos.x - cosf(vtxAngle) * vtxRadius * ptr->scale;
	vtxWk[2].vtx.y = ptr->pos.y + sinf(vtxAngle) * vtxRadius * ptr->scale;
	vtxWk[3].vtx.x = ptr->pos.x + cosf(vtxAngle) * vtxRadius * ptr->scale;
	vtxWk[3].vtx.y = ptr->pos.y + sinf(vtxAngle) * vtxRadius * ptr->scale;

	for (int i = 0; i < NUM_VERTEX; i++)
	{
		vtxWk[i].vtx.y += ROCKONSITE_TEXT_OFFSET;
	}

	vtxWk[0].diffuse =
		vtxWk[1].diffuse =
		vtxWk[2].diffuse =
		vtxWk[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, ptr->alpha);
}

/**************************************
�Z�b�g����
***************************************/
ROCKONSITE *SetRockonSite(int id, D3DXVECTOR3 *target, bool *targetActive)
{
	//ROCKONSITE *ptr = &rockon[id * ROCKONSITE_MAX];
	//int end = (id + 1) * ROCKONSITE_MAX;

	//for (int i = 0; i < end; i++, ptr++)
	//{
	//	if (ptr->target == NULL)
	//	{
	//		ptr->active = true;
	//		ptr->target = target;
	//		ptr->targetActive = targetActive;
	//		return ptr;
	//	}

	//	if (ptr->target == target)
	//	{
	//		return ptr;
	//	}
	//}

	return NULL;
}

/**************************************
�����[�X����
***************************************/
void ReleaseRockonSite(ROCKONSITE *ptr)
{
	//ptr->active = false;
	//ptr->target = NULL;
}

/**************************************
���W�Z�b�g����
***************************************/
void SetRockonSitePos(int id, D3DXVECTOR3 pos)
{
	rockon[id].pos = pos;
	rockon[id].active = true;
}

/**************************************
�A�N�e�B�u������
***************************************/
void ActivateRockonSite(int id)
{
	rockon[id].cntFrame = 0;
	rockon[id].scale = ROCKONSITE_INITSCALE;
}