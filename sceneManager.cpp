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

/**************************************
�}�N����`
***************************************/

/**************************************
�\���̒�`
***************************************/
typedef void(*SceneFunc)(void);		//�V�[���̊e�����̊֐��|�C���^��`
typedef HRESULT(*SceneInit)(int num);	//�V�[���̏����������̊֐��|�C���^��`

/**************************************
�O���[�o���ϐ�
***************************************/
static int currentSceneId = 0;

//�e�V�[������������
static SceneInit Init[] =
{
	InitLogoScene,
	InitTitleScene,
	InitBattleScene
};

//�e�V�[���I������
static SceneFunc Uninit[] =
{
	UninitLogoScene,
	UninitTitleScene,
	UninitBattleScene
};

//�e�V�[���X�V����
static SceneFunc Update[] =
{
	UpdateLogoScene,
	UpdateTitleScene,
	UpdateBattleScene
};

//�e�V�[���`�揈��
static SceneFunc Draw[] =
{
	DrawLogoScene,
	DrawTitleScene,
	DrawBattleScene
};

/**************************************
�v���g�^�C�v�錾
***************************************/

/**************************************
����������
***************************************/
void InitSceneManager(int num)
{
	for (int i = 0; i < DefineSceneMax; i++)
	{
		Init[i](num);
	}
}

/**************************************
�ʃV�[������������
***************************************/
void InitScene(int num)
{
	Init[currentSceneId](num);
}

/**************************************
�I������
***************************************/
void UninitSceneManager(void)
{
	for (int i = 0; i < DefineSceneMax; i++)
	{
		Uninit[i]();
	}
}

/**************************************
�X�V����
***************************************/
void UpdateSceneManager(void)
{
	Update[currentSceneId]();
}

/**************************************
�`�揈��
***************************************/
void DrawSceneManager(void)
{
	Draw[currentSceneId]();
}

/**************************************
�V�[���Z�b�g����
***************************************/
void SetScene(DefineScene sceneId)
{
	currentSceneId = sceneId;
}
