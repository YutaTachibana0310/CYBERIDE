//=====================================
//
//�e���v���[�g����[playerBullet.cpp]
//Author:GP11A341 21 ���ԗY��
//
//=====================================
#include "playerBullet.h"
#include "battleCamera.h"
#include "particleFramework.h"
#include "playerBulletTrail.h"

/**************************************
�}�N����`
***************************************/
#define PLAYERULLET_SPEED			(25.0f)
#define PLAYERBULLET_TEXNAME		"data/TEXTURE/PLAYER/playerbullet.png"
#define PLAYERBULLET_TEXSIZE_X		(10.0f)
#define PLAYERBULLET_TEXSIZE_Y		(10.0f)
#define PLAYERBULLET_ROTVALUE		(0.05f)
#define PLAYERbULLET_MOVE_END		(120)
#define PLAYERBULLET_SHADER_NAME	"data/EFFECT/playerBullet.fx"
#define PLAYERBULLET_TRAIL_OFFSET	(-5.0f)
#define PLAYERBULLET_TRAIL_ALPHA	(0.2f)
#define PLAYERBULLET_TRAIL_NUM		(5)

/**************************************
�\���̒�`
***************************************/
enum PLAYERBULLET_STATE
{
	PlayerBulletFPS,
	PlayerBulletTop,
	PlayerBulletSide,
	PlayerBulletQuater,
	PlayerBulletStateMax
};

/**************************************
�O���[�o���ϐ�
***************************************/
static LPDIRECT3DTEXTURE9 tex;
static D3DXMATRIX mtxWorld;
static LPDIRECT3DVERTEXBUFFER9 vtxBuff;

static PLAYERBULLET bullet[PLAYERBULLET_MAX];
static int currentState = 0;
static D3DXMATRIX pos;

static const D3DXVECTOR3 rotAngle[PlayerBulletStateMax] = {
	D3DXVECTOR3(0.0f, 0.0f, 0.0f),		//FPS�r���[���̉�]�p�x
	D3DXVECTOR3(0.0f, 0.0f, 0.0f),		//�T�C�h�r���[���̉�]�p�x
	D3DXVECTOR3(0.0f, 0.0f, 0.0f),		//�N�H�[�^�[�r���[���̉�]�p�x
};

//�P�ʒ��_�̐ݒ�
//static VERTEX_PARTICLE vtx[NUM_VERTEX * PlayerBulletStateMax] = {
//	//FPS�r���[�̒P�ʒ��_�ݒ�
//	{ -PLAYERBULLET_TEXSIZE_X, 0.0f,  PLAYERBULLET_TEXSIZE_Y, 0.0f, 0.0f },
//	{  PLAYERBULLET_TEXSIZE_X, 0.0f,  PLAYERBULLET_TEXSIZE_Y, 1.0f, 0.0f },
//	{ -PLAYERBULLET_TEXSIZE_X, 0.0f, -PLAYERBULLET_TEXSIZE_Y, 0.0f, 1.0f },
//	{  PLAYERBULLET_TEXSIZE_X, 0.0f, -PLAYERBULLET_TEXSIZE_Y, 1.0f, 1.0f },
//	//�g�b�v�r���[�̒P�ʒ��_�ݒ�
//	{ -PLAYERBULLET_TEXSIZE_X, 0.0f,  PLAYERBULLET_TEXSIZE_Y, 0.0f, 0.0f },
//	{  PLAYERBULLET_TEXSIZE_X, 0.0f,  PLAYERBULLET_TEXSIZE_Y, 1.0f, 0.0f },
//	{ -PLAYERBULLET_TEXSIZE_X, 0.0f, -PLAYERBULLET_TEXSIZE_Y, 0.0f, 1.0f },
//	{  PLAYERBULLET_TEXSIZE_X, 0.0f, -PLAYERBULLET_TEXSIZE_Y, 1.0f, 1.0f },
//	//�T�C�h�r���[
//	{ 0.0f,  PLAYERBULLET_TEXSIZE_X, -PLAYERBULLET_TEXSIZE_Y, 0.0f, 0.0f },
//	{ 0.0f,  PLAYERBULLET_TEXSIZE_X,  PLAYERBULLET_TEXSIZE_Y, 1.0f, 0.0f },
//	{ 0.0f, -PLAYERBULLET_TEXSIZE_X, -PLAYERBULLET_TEXSIZE_Y, 0.0f, 1.0f },
//	{ 0.0f, -PLAYERBULLET_TEXSIZE_X,  PLAYERBULLET_TEXSIZE_Y, 1.0f, 1.0f },
//	//�N�H�[�^�[�r���[
//	{ -PLAYERBULLET_TEXSIZE_X, 0.0f,  PLAYERBULLET_TEXSIZE_Y, 0.0f, 0.0f },
//	{ PLAYERBULLET_TEXSIZE_X, 0.0f,  PLAYERBULLET_TEXSIZE_Y, 1.0f, 0.0f },
//	{ -PLAYERBULLET_TEXSIZE_X, 0.0f, -PLAYERBULLET_TEXSIZE_Y, 0.0f, 1.0f },
//	{ PLAYERBULLET_TEXSIZE_X, 0.0f, -PLAYERBULLET_TEXSIZE_Y, 1.0f, 1.0f },
//};


/**************************************
�v���g�^�C�v�錾
***************************************/
void CreatePlayerBulletVertexBuffer(void);
#if 0
void CreatePlayerBulletVertexBufferFPS(void);
void CreatePlayerBulletVertexBufferTop(void);
void CreatePlayerBulletVertexBufferSide(void);
void CreatePlayerBulletVertexBufferQuater(void);
#endif
/**************************************
����������
***************************************/
void InitPlayerBullet(int num)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	if (num == 0)
	{
		//CreatePlayerBulletVertexBufferFPS();
		//CreatePlayerBulletVertexBufferSide();
		//CreatePlayerBulletVertexBufferTop();
		//CreatePlayerBulletVertexBufferQuater();
		CreatePlayerBulletVertexBuffer();

		tex = CreateTextureFromFile((LPSTR)PLAYERBULLET_TEXNAME, pDevice);
	}

	PLAYERBULLET *ptr = &bullet[0];
	for (int i = 0; i < PLAYERBULLET_MAX; i++, ptr++)
	{
		ptr->active = false;
		ptr->pos = D3DXVECTOR3(9999.9f, 9999.9f, 9999.9f);
		ptr->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		ptr->scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

		ptr->collider.pos = &ptr->pos;
		ptr->collider.radius = PLAYERBULLET_COLLIDER_RAIDUS;
		ptr->collider.offset = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		ptr->collider2.pos = &ptr->pos;
		ptr->collider2.offset = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		ptr->collider2.length = D3DXVECTOR3(PLAYERBULLET_COLLIDER_RAIDUS, PLAYERBULLET_COLLIDER_RAIDUS, PLAYERBULLET_COLLIDER_RAIDUS);
	}
}

/**************************************
�I������
***************************************/
void UninitPlayerBullet(int num)
{
	if (num == 0)
	{
		SAFE_RELEASE(vtxBuff);
		SAFE_RELEASE(tex);
	}

	PLAYERBULLET *ptr = &bullet[0];
	for (int i = 0; i < PLAYERBULLET_MAX; i++, ptr++)
	{
		ptr->active = false;

	}
}

/**************************************
�X�V����
***************************************/
void UpdatePlayerBullet(void)
{
	PLAYERBULLET *ptr = &bullet[0];
	BATTLECAMERA *camera = GetBattleCameraAdr();

	for (int i = 0; i < PLAYERBULLET_MAX; i++, ptr++)
	{
		if (!ptr->active)
		{
			continue;
		}

		ptr->pos += ptr->moveDir * ptr->speed;

		for (int j = 0; j < PLAYERBULLET_TRAIL_NUM; j++)
		{
			SetPlayerBulletTrail(ptr->pos + ptr->moveDir * PLAYERBULLET_TRAIL_OFFSET * j, 1.0f - PLAYERBULLET_TRAIL_ALPHA * j );
		}

		if (ptr->pos.z > 1000.0f)
		{
			ptr->active = false;
		}
	}
}

/**************************************
�`�揈��
***************************************/
void DrawPlayerBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	PLAYERBULLET *ptr = &bullet[0];
	D3DXMATRIX mtxRot, mtxScale, mtxTranslate;

	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, true);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, false);
	pDevice->SetRenderState(D3DRS_LIGHTING, false);

	pDevice->SetStreamSource(0, vtxBuff, 0, sizeof(VERTEX_3D));

	pDevice->SetFVF(FVF_VERTEX_3D);

	pDevice->SetTexture(0, tex);

	for (int i = 0; i < PLAYERBULLET_MAX; i++, ptr++)
	{
		if (!ptr->active)
		{
			continue;
		}

		D3DXMatrixIdentity(&mtxWorld);

		//D3DXMatrixRotationYawPitchRoll(&mtxRot, rotAngle[currentState].y, rotAngle[currentState].x, rotAngle[currentState].z);
		GetInvRotBattleCamera(&mtxWorld);
		//D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRot);

		D3DXMatrixTranslation(&mtxTranslate, ptr->pos.x, ptr->pos.y, ptr->pos.z);
		D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTranslate);

		pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);

		//�ʏ�`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);

		//���Z�`��
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	}

	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, true);
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, false);
	pDevice->SetRenderState(D3DRS_LIGHTING, true);

#ifdef _DEBUG
	ptr = &bullet[0];
	for (int i = 0; i < PLAYERBULLET_MAX; i++, ptr++)
	{
		if (!ptr->active)
		{
			continue;
		}
		DrawBoundingSphere(&ptr->collider);
	}
#endif
}

/**************************************
�v���C���[�o���b�g�Z�b�g�֐�
***************************************/
void SetPlayerBullet(D3DXVECTOR3 pos, float speed)
{
	PLAYERBULLET *ptr = &bullet[0];
	const float randomAngle = 0.1f;

	for (int i = 0; i < PLAYERBULLET_MAX; i++, ptr++)
	{
		if (ptr->active)
		{
			continue;
		}

		ptr->pos = pos;
		ptr->rotation = RandomRangef(0.0f, 6.12f);

		ptr->moveDir = D3DXVECTOR3(0.0f, 0.0f, 1.0f);

		ptr->speed = speed;

		ptr->active = true;
		return;
	}
}

/**************************************
�v���C���[�o���b�g�Q�b�g�֐�
***************************************/
PLAYERBULLET *GetPlayerBulletAdr(int id)
{
	return &bullet[id];
}

/**************************************
�v���C���[�o���b�g��ԃZ�b�g�֐�
***************************************/
void SetPlayerBulletState(int state)
{
	if (state < PlayerBulletStateMax)
		currentState = state;
}

/**************************************
���_�쐬����
***************************************/
void CreatePlayerBulletVertexBuffer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * NUM_VERTEX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&vtxBuff,
		NULL)))
	{
		return;
	}

	VERTEX_3D *pVtx;
	vtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].vtx = D3DXVECTOR3(-PLAYERBULLET_TEXSIZE_X, PLAYERBULLET_TEXSIZE_Y, 0.0f);
	pVtx[1].vtx = D3DXVECTOR3(PLAYERBULLET_TEXSIZE_X, PLAYERBULLET_TEXSIZE_Y, 0.0f);
	pVtx[2].vtx = D3DXVECTOR3(-PLAYERBULLET_TEXSIZE_X, -PLAYERBULLET_TEXSIZE_Y, 0.0f);
	pVtx[3].vtx = D3DXVECTOR3(PLAYERBULLET_TEXSIZE_X, -PLAYERBULLET_TEXSIZE_Y, 0.0f);

	pVtx[0].nor =
		pVtx[1].nor =
		pVtx[2].nor =
		pVtx[3].nor = D3DXVECTOR3(0.0f, -1.0f, 1.0f);

	pVtx[0].diffuse =
		pVtx[1].diffuse =
		pVtx[2].diffuse =
		pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	vtxBuff->Unlock();

	return;
}

#if 0
/**************************************
FPS�r���[���_�쐬����
***************************************/
void CreatePlayerBulletVertexBufferFPS(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * NUM_VERTEX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&vtxBuff[PlayerBulletFPS],
		NULL)))
	{
		return;
	}

	VERTEX_3D *pVtx;
	vtxBuff[PlayerBulletFPS]->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].vtx = D3DXVECTOR3(-PLAYERBULLET_TEXSIZE_X, 0.0f, PLAYERBULLET_TEXSIZE_Y);
	pVtx[1].vtx = D3DXVECTOR3(PLAYERBULLET_TEXSIZE_X, 0.0f, PLAYERBULLET_TEXSIZE_Y);
	pVtx[2].vtx = D3DXVECTOR3(-PLAYERBULLET_TEXSIZE_X, 0.0f, -PLAYERBULLET_TEXSIZE_Y);
	pVtx[3].vtx = D3DXVECTOR3(PLAYERBULLET_TEXSIZE_X, 0.0f, -PLAYERBULLET_TEXSIZE_Y);

	pVtx[0].nor =
		pVtx[1].nor =
		pVtx[2].nor =
		pVtx[3].nor = D3DXVECTOR3(0.0f, -1.0f, 1.0f);

	pVtx[0].diffuse =
		pVtx[1].diffuse =
		pVtx[2].diffuse =
		pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	vtxBuff[PlayerBulletFPS]->Unlock();

	return;
}

/**************************************
�g�b�v�r���[���_�쐬����
***************************************/
void CreatePlayerBulletVertexBufferTop(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * NUM_VERTEX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&vtxBuff[PlayerBulletTop],
		NULL)))
	{
		return;
	}

	VERTEX_3D *pVtx;
	vtxBuff[PlayerBulletTop]->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].vtx = D3DXVECTOR3(-PLAYERBULLET_TEXSIZE_X, 0.0f, PLAYERBULLET_TEXSIZE_Y);
	pVtx[1].vtx = D3DXVECTOR3(PLAYERBULLET_TEXSIZE_X, 0.0f, PLAYERBULLET_TEXSIZE_Y);
	pVtx[2].vtx = D3DXVECTOR3(-PLAYERBULLET_TEXSIZE_X, 0.0f, -PLAYERBULLET_TEXSIZE_Y);
	pVtx[3].vtx = D3DXVECTOR3(PLAYERBULLET_TEXSIZE_X, 0.0f, -PLAYERBULLET_TEXSIZE_Y);

	pVtx[0].nor =
		pVtx[1].nor =
		pVtx[2].nor =
		pVtx[3].nor = D3DXVECTOR3(0.0f, -1.0f, 1.0f);

	pVtx[0].diffuse =
		pVtx[1].diffuse =
		pVtx[2].diffuse =
		pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	vtxBuff[PlayerBulletTop]->Unlock();

	return;
}

/**************************************
�T�C�h�r���[���_�쐬����
***************************************/
void CreatePlayerBulletVertexBufferSide(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * NUM_VERTEX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&vtxBuff[PlayerBulletSide],
		NULL)))
	{
		return;
	}

	VERTEX_3D *pVtx;
	vtxBuff[PlayerBulletSide]->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].vtx = D3DXVECTOR3(0.0f, PLAYERBULLET_TEXSIZE_X, -PLAYERBULLET_TEXSIZE_Y);
	pVtx[1].vtx = D3DXVECTOR3(0.0f, PLAYERBULLET_TEXSIZE_X, PLAYERBULLET_TEXSIZE_Y);
	pVtx[2].vtx = D3DXVECTOR3(0.0f, -PLAYERBULLET_TEXSIZE_X, -PLAYERBULLET_TEXSIZE_Y);
	pVtx[3].vtx = D3DXVECTOR3(0.0f, -PLAYERBULLET_TEXSIZE_X, PLAYERBULLET_TEXSIZE_Y);

	pVtx[0].nor =
		pVtx[1].nor =
		pVtx[2].nor =
		pVtx[3].nor = D3DXVECTOR3(0.0f, -1.0f, 1.0f);

	pVtx[0].diffuse =
		pVtx[1].diffuse =
		pVtx[2].diffuse =
		pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	vtxBuff[PlayerBulletSide]->Unlock();

	return;
}

/**************************************
�N�H�[�^�[�r���[���_�쐬����
***************************************/
void CreatePlayerBulletVertexBufferQuater(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * NUM_VERTEX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&vtxBuff[PlayerBulletQuater],
		NULL)))
	{
		return;
	}

	VERTEX_3D *pVtx;
	vtxBuff[PlayerBulletQuater]->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].vtx = D3DXVECTOR3(-PLAYERBULLET_TEXSIZE_X, 0.0f, PLAYERBULLET_TEXSIZE_Y);
	pVtx[1].vtx = D3DXVECTOR3(PLAYERBULLET_TEXSIZE_X, 0.0f, PLAYERBULLET_TEXSIZE_Y);
	pVtx[2].vtx = D3DXVECTOR3(-PLAYERBULLET_TEXSIZE_X, 0.0f, -PLAYERBULLET_TEXSIZE_Y);
	pVtx[3].vtx = D3DXVECTOR3(PLAYERBULLET_TEXSIZE_X, 0.0f, -PLAYERBULLET_TEXSIZE_Y);

	pVtx[0].nor =
		pVtx[1].nor =
		pVtx[2].nor =
		pVtx[3].nor = D3DXVECTOR3(0.0f, -1.0f, 1.0f);

	pVtx[0].diffuse =
		pVtx[1].diffuse =
		pVtx[2].diffuse =
		pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	vtxBuff[PlayerBulletQuater]->Unlock();

	return;
}
#endif