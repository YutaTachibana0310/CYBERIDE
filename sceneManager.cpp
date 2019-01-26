//=====================================
//
//�V�[���}�l�[�W������[sceneManager.cpp]
//Author:GP11A341 21 ���ԗY��
//
//=====================================
#include "sceneManager.h"
#include "logoScene.h"
#include "titleScene.h"
#include "battleScene.h"
#include "resultScene.h"
#include "particleManager.h"
#include "tutorialScene.h"

/**************************************
�}�N����`
***************************************/

/**************************************
�\���̒�`
***************************************/
typedef void(*SceneFunc)(void);			//�V�[���̊e�����̊֐��|�C���^��`
typedef HRESULT(*SceneInit)(int num);	//�V�[���̏����������̊֐��|�C���^��`
typedef void(*SceneUninit)(int num);	//�V�[���̏I�������̊֐��|�C���^��`

/**************************************
�O���[�o���ϐ�
***************************************/
static int* currentSceneId;

//�e�V�[������������
static SceneInit Init[] =
{
	InitLogoScene,
	InitTitleScene,
	InitBattleScene,
	InitResultScene,
	InitTutorialScene
};

//�e�V�[���I������
static SceneUninit Uninit[] =
{
	UninitLogoScene,
	UninitTitleScene,
	UninitBattleScene,
	UninitResultScene,
	UninitTutorialScene
};

//�e�V�[���X�V����
static SceneFunc Update[] =
{
	UpdateLogoScene,
	UpdateTitleScene,
	UpdateBattleScene,
	UpdateResultScene,
	UpdateTutorialScene
};

//�e�V�[���`�揈��
static SceneFunc Draw[] =
{
	DrawLogoScene,
	DrawTitleScene,
	DrawBattleScene,
	DrawResultScene,
	DrawTutorialScene
};

/**************************************
�v���g�^�C�v�錾
***************************************/

/**************************************
����������
***************************************/
void InitSceneManager(int* ptr)
{

	/*for (int i = 0; i < DefineSceneMax; i++)
	{
		Init[i](num);
	}*/

	currentSceneId = ptr;
}

/**************************************
�ʃV�[������������
***************************************/
void InitScene(int num)
{
	Init[*currentSceneId](num);
}

/**************************************
�I������
***************************************/
void UninitSceneManager(int num)
{
	for (int i = 0; i < DefineSceneMax; i++)
	{
		Uninit[i](num);
	}
}

/**************************************
�ʃV�[���I������
***************************************/
void UninitScene(int num)
{
	Uninit[*currentSceneId](num);
}

/**************************************
�X�V����
***************************************/
void UpdateSceneManager(void)
{
	Update[*currentSceneId]();
}

/**************************************
�`�揈��
***************************************/
void DrawSceneManager(void)
{
	Draw[*currentSceneId]();
}

/**************************************
�V�[���Z�b�g����
***************************************/
void SetScene(DefineScene sceneId)
{
	UninitScene(1);
	UninitParticleManager(1);
	*currentSceneId = sceneId;
	InitScene(1);
}
