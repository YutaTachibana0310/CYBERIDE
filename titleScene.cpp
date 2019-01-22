//=============================================================================
//
// �^�C�g���V�[������ [titleScene.cpp]
// Author : GP11A341 21 ���ԗY��
//
//=============================================================================
#include "main.h"
#include "titleScene.h"
#include "input.h"
#include "Easing.h"
#include "meshCylinder.h"
#include "playerModel.h"
#include "playerBullet.h"
#include "playerBulletTrail.h"
#include "battleCamera.h"
#include "sceneFade.h"
#include "bgmManager.h"
#include "soundEffectManager.h"

/*****************************************************************************
�}�N����`
*****************************************************************************/
#define TITLESCENE_FADEIN_END		(60)

#define TITLESCENE_LOGOTEX_NAME		"data/TEXTURE/UI/titlelogo00.png"
#define TITLESCENE_LOGOTEX_SIZE_X	(600)
#define TITLESCENE_LOGOTEX_SIZE_Y	(208)
#define TITLESCENE_LOGOTEX_POS		(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, 300.0f, 0.0f))

/*****************************************************************************
�v���g�^�C�v�錾
*****************************************************************************/
HRESULT MakeVertexTitleScene(void);			//���_�쐬�֐�

void SetTextureTitleLogo(void);				// �e�N�X�`�����W�̌v�Z����
void SetVertexTitleLogo(void);				// ���_�̌v�Z����
void SetTitleTextureAlpha(float alpha);		//�A���t�@�ݒ菈��

/*****************************************************************************
�\���̒�`
*****************************************************************************/
enum TITLESCENE_STATE
{
	TITLESCENE_FADEIN,
	TITLESCENE_INPUTWAIT,
	TITLESCENE_STATEMAX
};
/*****************************************************************************
�O���[�o���ϐ�
*****************************************************************************/
static LPDIRECT3DTEXTURE9 logoTex, bgTex, animTex;
static VERTEX_2D vertexWk[NUM_VERTEX];					//���_���i�[���[�N
static float logoRadius;
static float logoAngle;
static D3DXVECTOR3 logoPos;
static int cntFrame;
static TITLESCENE_STATE state;

/******************************************s************************************
����������
******************************************************************************/
HRESULT InitTitleScene(int num)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	static bool initialized = false;

	//���S�̏����ݒ�
	logoPos = TITLESCENE_LOGOTEX_POS;
	logoAngle = atan2f(TITLESCENE_LOGOTEX_SIZE_Y, TITLESCENE_LOGOTEX_SIZE_X);
	logoRadius = D3DXVec2Length(&D3DXVECTOR2(TITLESCENE_LOGOTEX_SIZE_X, TITLESCENE_LOGOTEX_SIZE_Y));

	// ���_���̍쐬
	MakeVertexTitleScene();

	if (!initialized)
	{
		// �e�N�X�`���̓ǂݍ���
		logoTex = CreateTextureFromFile((LPSTR)TITLESCENE_LOGOTEX_NAME, pDevice);
		initialized = true;
	}

	if (num != 0)
	{
		//SetBackColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		PlayBGM(BGM_TITLESCENE);
		SetTitleTextureAlpha(0.0f);

		InitMeshCylinder(num);
		InitPlayerModel(num);
		InitPlayerBullet(num);
		UninitPlayerBulletTrail(num);

		state = TITLESCENE_FADEIN;
		cntFrame = 0;

		ChangeStatePlayerModel(PlayerTitle);
		SetBattleCameraState(FirstPersonCamera);
	}

	return S_OK;
}

/******************************************************************************
�I������
******************************************************************************/
void UninitTitleScene(int num)
{
	if (num == 0)
	{
		SAFE_RELEASE(logoTex);
		SAFE_RELEASE(bgTex);
		SAFE_RELEASE(animTex);
	}
	else
	{
		UninitMeshCylinder(num);
		UninitPlayerModel(num);
		UninitPlayerBullet(num);
		UninitPlayerBulletTrail(num);
	}
}

/******************************************************************************
�X�V����
******************************************************************************/
void UpdateTitleScene(void)
{
	
	if (state == TITLESCENE_FADEIN)
	{
		cntFrame++;
		float t = (float)cntFrame / TITLESCENE_FADEIN_END;

		SetTitleTextureAlpha(EaseLinear(t, 0.0f, 1.0f));
		if (cntFrame == TITLESCENE_FADEIN_END)
		{
			state = TITLESCENE_INPUTWAIT;
		}
	}

	if (GetAttackButtonTrigger() && state == TITLESCENE_INPUTWAIT)
	{
		//SetScene(BattleScene);
		state = TITLESCENE_STATEMAX;
		ChangeStatePlayerModel(PlayerTitleLaunch);
		SetSceneFade(TutorialScene);
		PlaySE(SOUND_DECISION);
		FadeOutBGM(BGM_TITLESCENE, TITLESCENE_FADEIN_END);
	}

	UpdateMeshCylinder();
	UpdatePlayerModel();
	UpdatePlayerBullet();
	UpdatePlayerBulletTrail();
}

/******************************************************************************
�`�揈��
******************************************************************************/
void DrawTitleScene(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	SetBattleCamera();

	DrawMeshCylinder();
	DrawPlayerModel();
	DrawPlayerBullet();
	DrawPlayerBulletTrail();

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//���S�`��
	pDevice->SetTexture(0, logoTex);
	SetVertexTitleLogo();
	SetTextureTitleLogo();
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, vertexWk, sizeof(VERTEX_2D));
}


/******************************************************************************
���_�̍쐬
******************************************************************************/
HRESULT MakeVertexTitleScene(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// rhw�̐ݒ�
	vertexWk[0].rhw =
		vertexWk[1].rhw =
		vertexWk[2].rhw =
		vertexWk[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	return S_OK;
}

/******************************************************************************
�e�N�X�`�����W�̐ݒ�
******************************************************************************/
void SetTextureTitleLogo(void)
{
	// �e�N�X�`�����W�̐ݒ�
	vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	vertexWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	vertexWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);
}

/******************************************************************************
���_���W�̐ݒ�
******************************************************************************/
void SetVertexTitleLogo(void)
{
	// ���_���W�̐ݒ�
	vertexWk[0].vtx.x = logoPos.x - cosf(logoAngle) * logoRadius;
	vertexWk[0].vtx.y = logoPos.y - sinf(logoAngle) * logoRadius;
	vertexWk[1].vtx.x = logoPos.x + cosf(logoAngle) * logoRadius;
	vertexWk[1].vtx.y = logoPos.y - sinf(logoAngle) * logoRadius;
	vertexWk[2].vtx.x = logoPos.x - cosf(logoAngle) * logoRadius;
	vertexWk[2].vtx.y = logoPos.y + sinf(logoAngle) * logoRadius;
	vertexWk[3].vtx.x = logoPos.x + cosf(logoAngle) * logoRadius;
	vertexWk[3].vtx.y = logoPos.y + sinf(logoAngle) * logoRadius;
}

/******************************************************************************
�e�N�X�`���A���t�@�ݒ�
******************************************************************************/
void SetTitleTextureAlpha(float alpha)
{
	vertexWk[0].diffuse =
		vertexWk[1].diffuse =
		vertexWk[2].diffuse =
		vertexWk[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, alpha);
}