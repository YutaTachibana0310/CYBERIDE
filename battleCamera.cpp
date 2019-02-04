//=============================================================================
//
// �J�������� [battleCamera.cpp]
// Author : GP11A341 21 ���ԗY��
//
//=============================================================================
#include "battleCamera.h"
#include "input.h"
#include "Easing.h"
#include "debugproc.h"
#include "playerModel.h"
#include "cameraShaker.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	BATTLECAMERA_VIEWANGLE				(D3DXToRadian(45.0f))	// ����p
#define	BATTLECAMERA_VIEWASPECT				((float)SCREEN_WIDTH / (float)SCREEN_HEIGHT)	// �r���[���ʂ̃A�X�y�N�g��
#define	BATTLECAMERA_NEAR					(50.0f)					// �r���[���ʂ�NearZ�l
#define	BATTLECAMERA_FAR					(20000.0f)				// �r���[���ʂ�FarZ�l
#define BATTLECAMERA_LENGTH_FPS				(175.0f)
#define BATTLECAMERA_LENGTH_TOP				(250.0f)
#define BATTLECAMERA_LENGTH_SIDE			(200.0f)
#define BATTLECAMERA_LENGTH_QUATER			(200.0f)
#define BATTLECAMERA_TOP_ANGLE_Y			(0.68f)
#define BATTLECAMERA_QUATER_ANGLE_Y			(0.34f)
#define BATTLECAMERA_QUATER_ANGLE_XZ		(1.19f)
#define BATTLECAMERA_SIDE_ANGLE_Y			(0.17f)

#define BATTLECAMERA_USE_QUATERNION			(0)
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
static BATTLECAMERA camera;

#if BATTLECAMERA_USE_QUATERNION
static const D3DXQUATERNION BattleCameraPosQ[] =
{
	//FPS
	D3DXQUATERNION(0.0f, 0.0f, -BATTLECAMERA_LENGTH * 0.7f, 1.0f),
	//�c
	D3DXQUATERNION(0.0f, sinf(BATTLECAMERA_TOP_ANGLE_Y) * BATTLECAMERA_LENGTH , -cosf(BATTLECAMERA_TOP_ANGLE_Y) * BATTLECAMERA_LENGTH, 1.0f),
	//��
	D3DXQUATERNION(BATTLECAMERA_LENGTH, 0.0f, 0.0f, 1.0f),
	//�N�H�[�^�[
	D3DXQUATERNION(
		cosf(BATTLECAMERA_QUATER_ANGLE_Y) * cosf(BATTLECAMERA_QUATER_ANGLE_XZ) * BATTLECAMERA_LENGTH * 0.8f,
		sinf(BATTLECAMERA_QUATER_ANGLE_Y) * BATTLECAMERA_LENGTH,
		cosf(BATTLECAMERA_QUATER_ANGLE_Y) * -sinf(BATTLECAMERA_QUATER_ANGLE_XZ) * BATTLECAMERA_LENGTH * 0.8f,
		1.0f
	)
};
#else
static const D3DXVECTOR3 BattleCameraPos[] =
{
	//FPS
	D3DXVECTOR3(0.0f, 0.0f, -BATTLECAMERA_LENGTH_FPS * 0.7f),
	//�c
	D3DXVECTOR3(0.0f, sinf(BATTLECAMERA_TOP_ANGLE_Y) * BATTLECAMERA_LENGTH_TOP , -cosf(BATTLECAMERA_TOP_ANGLE_Y) * BATTLECAMERA_LENGTH_TOP),
	//��
	D3DXVECTOR3(BATTLECAMERA_LENGTH_SIDE, 0.0f, 0.0f),
	//�N�H�[�^�[
	D3DXVECTOR3(
		cosf(BATTLECAMERA_QUATER_ANGLE_Y) * cosf(BATTLECAMERA_QUATER_ANGLE_XZ) * BATTLECAMERA_LENGTH_QUATER * 0.8f,
		sinf(BATTLECAMERA_QUATER_ANGLE_Y) * BATTLECAMERA_LENGTH_QUATER,
		cosf(BATTLECAMERA_QUATER_ANGLE_Y) * -sinf(BATTLECAMERA_QUATER_ANGLE_XZ) * BATTLECAMERA_LENGTH_QUATER * 0.8f
	)
};
#endif
//static float cameraLength = BATTLECAMERA_LENGTH_TOP;

static const D3DXVECTOR3 BattleCameraAt[] =
{
	D3DXVECTOR3(0.0f, 0.0f, 0.0f),
	D3DXVECTOR3(0.0f, 0.0f, 0.0f),
	D3DXVECTOR3(0.0f, 0.0f, 0.0f)
};

static const D3DXVECTOR3 BattleCameraUp[] =
{
	D3DXVECTOR3(0.0f, 1.0f, 0.0f),
	D3DXVECTOR3(0.0f, 1.0f, 0.0f),
	D3DXVECTOR3(0.0f, 1.0f, 0.0f),
	D3DXVECTOR3(0.0f, 1.0f, 0.0f)
};

static D3DXVECTOR3 offsetPos;

//=============================================================================
// �J�����̏�����
//=============================================================================
HRESULT InitBattleCamera(void)
{
#if BATTLECAMERA_USE_QUATERNION
	camera.pos.x = BattleCameraPosQ[0].x;
	camera.pos.y = BattleCameraPosQ[0].x;
	camera.pos.z = BattleCameraPosQ[0].z;
#else
	camera.pos.x = BattleCameraPos[0].x;
	camera.pos.y = BattleCameraPos[0].x;
	camera.pos.z = BattleCameraPos[0].z;
#endif
	camera.at = BattleCameraAt[0];
	camera.up = BattleCameraUp[0];

	InitCameraShaker(0);

	return S_OK;
}

//=============================================================================
// �J�����̏I������
//=============================================================================
void UninitBattleCamera(void)
{

}

//=============================================================================
// �J�����̍X�V����
//=============================================================================
void UpdateBattleCamera(void)
{
	UpdateCameraShaker();

	if (camera.isMoving)
	{
		camera.cntFrame++;
		float t = EaseOutCubic((float)camera.cntFrame / BATTLECAMERA_MOVEFRAME, 0.0f, 1.0f);
#if BATTLECAMERA_USE_QUATERNION
		D3DXQUATERNION q;
		D3DXQuaternionSlerp(&q, &BattleCameraPosQ[camera.currentState], &BattleCameraPosQ[camera.nextState], t);
		camera.pos.x = q.x;
		camera.pos.y = q.y;
		camera.pos.z = q.z;
#else
		camera.pos.x = EaseOutCubic(t, BattleCameraPos[camera.currentState].x, BattleCameraPos[camera.nextState].x);
		camera.pos.y = EaseOutCubic(t, BattleCameraPos[camera.currentState].y, BattleCameraPos[camera.nextState].y);
		camera.pos.z = EaseOutCubic(t, BattleCameraPos[camera.currentState].z, BattleCameraPos[camera.nextState].z);
#endif
		camera.up.x = EaseLinear(t, BattleCameraUp[camera.currentState].x, BattleCameraUp[camera.nextState].x);
		camera.up.y = EaseLinear(t, BattleCameraUp[camera.currentState].y, BattleCameraUp[camera.nextState].y);
		camera.up.z = EaseLinear(t, BattleCameraUp[camera.currentState].z, BattleCameraUp[camera.nextState].z);

		if (camera.cntFrame == BATTLECAMERA_MOVEFRAME)
		{
			camera.isMoving = false;
			camera.currentState = camera.nextState;
		}
	}

	if (GetKeyboardTrigger(DIK_M))
	{
		SetBattleCameraMove((camera.currentState + 1) % 4);
	}
}

//=============================================================================
// �J�����̐ݒ菈��
//=============================================================================
void SetBattleCamera(void)
{
	bool flg = GetKeyboardTrigger(DIK_Q);


	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXVECTOR3 cameraOffset = GetCameraOffsetValue();

	// �r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&camera.view);

	// �r���[�}�g���b�N�X�̍쐬
	D3DXMatrixLookAtLH(&camera.view, 
						&(camera.pos + cameraOffset),		// �J�����̎��_
						&(camera.at + cameraOffset),			// �J�����̒����_
						&camera.up);	
	// �J�����̏����

	// �r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &camera.view);


	// �v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&camera.projection);

	// �v���W�F�N�V�����}�g���b�N�X�̍쐬
	D3DXMatrixPerspectiveFovLH(&camera.projection,
								BATTLECAMERA_VIEWANGLE,			// ����p
								BATTLECAMERA_VIEWASPECT,		// �A�X�y�N�g��
								BATTLECAMERA_NEAR,		// �r���[���ʂ�NearZ�l
								BATTLECAMERA_FAR);		// �r���[���ʂ�FarZ�l

	// �v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &camera.projection);
}

//=============================================================================
// �r���[�}�g���b�N�X�̎擾
//=============================================================================
D3DXMATRIX GetBattleCameraView(void)
{
	return camera.view;
}

//=============================================================================
// �v���W�F�N�V�����}�g���b�N�X�̎擾
//=============================================================================
D3DXMATRIX GetBattleCameraProjection(void)
{
	return camera.projection;
}

//=============================================================================
// �J������������]�s��̎擾
//=============================================================================
void GetInvRotBattleCamera(D3DXMATRIX *mtx, D3DXVECTOR3 *pAt)
{
	if (pAt != NULL)
	{
		D3DXMATRIX inv;
		D3DXMatrixIdentity(mtx);
		D3DXMatrixLookAtLH(mtx, &camera.pos, pAt, &camera.up);
		D3DXMatrixInverse(mtx, NULL, mtx);
		mtx->_41 = 0.0f;
		mtx->_42 = 0.0f;
		mtx->_43 = 0.0f;
	}
	else {
		mtx->_11 = camera.view._11;
		mtx->_12 = camera.view._21;
		mtx->_13 = camera.view._31;

		mtx->_21 = camera.view._12;
		mtx->_22 = camera.view._22;
		mtx->_23 = camera.view._32;

		mtx->_31 = camera.view._13;
		mtx->_32 = camera.view._23;
		mtx->_33 = camera.view._33;

		mtx->_41 = 0.0f;
		mtx->_42 = 0.0f;
		mtx->_43 = 0.0f;
	}
}

//=============================================================================
// �J�������W�̎擾
//=============================================================================
D3DXVECTOR3 GetBattleCameraPos(void)
{
	return camera.pos;
}

//=============================================================================
// �J�����̈ړ��̃Z�b�g
//=============================================================================
void SetBattleCameraMove(int state)
{
	if (camera.isMoving)
	{
		return;
	}

	camera.isMoving = true;
	camera.nextState = state;
	camera.cntFrame = 0;

	PLAYERMODEL *player = GetPlayerAdr(0);
	for (int i = 0; i < PLAYERMODEL_MAX; i++, player++)
	{
		player->nextState = camera.nextState;
	}
	ChangeStatePlayerModel(PlayerTransition);
}

//=============================================================================
// �o�g���J�����擾�֐�
//=============================================================================
BATTLECAMERA *GetBattleCameraAdr(void)
{
	return &camera;
}


//=============================================================================
// �J�����̏�ԃZ�b�g
//=============================================================================
void SetBattleCameraState(int state)
{
	camera.isMoving = false;
	camera.currentState = state;
	camera.pos = BattleCameraPos[state];
	camera.at = BattleCameraAt[state];
	camera.up = BattleCameraUp[state];
}
