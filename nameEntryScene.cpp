//=====================================
//
//�l�[���G���g���[�V�[������[nameEntryScene.cpp]
//Author:GP11A341 21 ���ԗY��
//
//=====================================
#include "nameEntryScene.h"
#include "sceneManager.h"
#include "nameEntryBG.h"
#include "battleCamera.h"
#include "nameEntryController.h"
#include "bgmManager.h"
#include "particleManager.h"

/**************************************
�}�N����`
***************************************/

/**************************************
�\���̒�`
***************************************/

/**************************************
�O���[�o���ϐ�
***************************************/

/**************************************
�v���g�^�C�v�錾
***************************************/

/**************************************
����������
***************************************/
HRESULT InitNameEntryScene(int num)
{
	FadeInBGM(BGM_NAMEENTRY, 30);
	InitNameEntryBG(num);
	InitBattleCamera();
	InitNameEntryController(num);
	return S_OK;
}

/**************************************
�I������
***************************************/
void UninitNameEntryScene(int num)
{
	UninitNameEntryBG(num);
	UninitNameEntryController(num);
}

/**************************************
�X�V����
***************************************/
void UpdateNameEntryScene(void)
{
	UpdateNameEntryBG();
	UpdateNameEntryController();
}

/**************************************
�`�揈��
***************************************/
void DrawNameEntryScene(void)
{
	SetBattleCamera();
	DrawNameEntryBG();
}
