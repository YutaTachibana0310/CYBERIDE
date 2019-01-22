//=====================================
//
//�`���[�g���A���R���g���[���[����[TutorialController.cpp]
//Author:GP11A341 21 ���ԗY��
//
//=====================================
#include "tutorialController.h"
#include "enemyManager.h"

/**************************************
�}�N����`
***************************************/
#define TUTORIAL_CUBE_POSRANGE_X		(200.0f)
#define TUTORIAL_CUBE_POSRANGE_Y		(100.0f)
#define TUTORIAL_CUBE_POS_Z				(6000.0f)
#define TUTORIAL_CUBE_INTERBAL			(30)
#define TUTORIAL_CUBE_SPEED				(10.0f)

static const char* TexturePath[TutorialIndexMax] = {
	"data/TEXTURE/UI/tutorial00.png",
	"data/TEXTURE/UI/tutorial01.png",
	"data/TEXTURE/UI/tutorial02.png",
	"data/TEXTURE/UI/tutorial03.png",
	"data/TEXTURE/UI/tutorial04.png",
	NULL,
	NULL,
};
/**************************************
�\���̒�`
***************************************/
typedef void(*funcTutorialController)(void);
typedef void(*drawTutorialController)(LPDIRECT3DTEXTURE9 tex);

/**************************************
�O���[�o���ϐ�
***************************************/
static int currentState;
static LPDIRECT3DTEXTURE9 textures[TutorialIndexMax];
static WORD cntFrame;

//���ꏈ���e�[�u��
static funcTutorialController Enter[TutorialIndexMax] = {
	OnEnterTutorialMove,
	OnEnterTutorialLockon,
	OnEnterTutorialHomingAttack,
	OnEnterTutorialHardCube,
	OnEnterTutorialBonusCube,
	OnEnterTutorialBonusTime,
	OnEnterTutorialEnd
};

//�X�V�����e�[�u��
static funcTutorialController Update[TutorialIndexMax] = {
	OnUpdateTutorialMove,
	OnUpdateTutorialLockon,
	OnUpdateTutorialHomingAttack,
	OnUpdateTutorialHardCube,
	OnUpdateTutorialBonusCube,
	OnUpdateTutorialBonusTime,
	OnUpdateTutorialEnd
};

//�`�揈���e�[�u��
static drawTutorialController Draw[TutorialIndexMax] = {
	OnDrawTutorialMove,
	OnDrawTutorialLockon,
	OnDrawTutorialHomingAttack,
	OnDrawTutorialHardCube,
	OnDrawTutorialBonusCube,
	OnDrawTutorialBonusTime,
	OnDrawTutorialEnd
};
/**************************************
�v���g�^�C�v�錾
***************************************/

/**************************************
����������
***************************************/
void InitTutorialController(int num)
{
	static bool isInitialized = false;

	if (!isInitialized)
	{
		LPDIRECT3DDEVICE9 pDevice = GetDevice();
		for (int i = 0; i < TutorialIndexMax; i++)
		{
			textures[i] = CreateTextureFromFile((LPSTR)TexturePath[i], pDevice);
		}
	}

	ChangeStateTutorialController(TutorialMove);
}

/**************************************
�I������
***************************************/
void UninitTutorialController(int num)
{
	if (num == 0)
	{
		for (int i = 0; i < TutorialIndexMax; i++)
		{
			SAFE_RELEASE(textures[i]);
		}
	}
}

/**************************************
�X�V����
***************************************/
void UpdateTutorialController(void)
{
	if (cntFrame++ % TUTORIAL_CUBE_INTERBAL == 0)
	{
		D3DXVECTOR3 pos = D3DXVECTOR3(RandomRangef(-TUTORIAL_CUBE_POSRANGE_X, TUTORIAL_CUBE_POSRANGE_X), RandomRangef(-TUTORIAL_CUBE_POSRANGE_Y, TUTORIAL_CUBE_POSRANGE_Y), TUTORIAL_CUBE_POS_Z);
		EmmittCubeObject(1, &pos, TUTORIAL_CUBE_SPEED);
	}

	Update[currentState]();
}

/**************************************
�`�揈��
***************************************/
void DrawTutorialController(void)
{
	Draw[currentState](textures[currentState]);
}

/**************************************
��ԑJ�ڏ���
***************************************/
void ChangeStateTutorialController(TUTORIAL_INDEX next)
{
	currentState = next;
	Enter[currentState]();
}