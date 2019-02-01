//=====================================
//
//�e���v���[�g����[nameEntryInput.cpp]
//Author:GP11A341 21 ���ԗY��
//
//=====================================
#include "nameEntryController.h"
#include "input.h"
#include "sceneManager.h"
#include "sceneFade.h"
#include "bgmManager.h"
#include "entryTelop.h"

/**************************************
�}�N����`
***************************************/

/**************************************
�\���̒�`
***************************************/

/**************************************
�O���[�o���ϐ�
***************************************/
static bool flgWait;

/**************************************
�v���g�^�C�v�錾
***************************************/

/**************************************
���ꏈ��
***************************************/
void OnEnterNameEntryEnd(NAMEENTRY *entity)
{
	SaveHighScoreData();
	flgWait = false;

	SetTextureEntryTelop(1);
}

/**************************************
�X�V����
***************************************/
void OnUpdateNameEntryEnd(NAMEENTRY *entity)
{
	if (flgWait)
		return;

	if (GetAttackButtonTrigger())
	{
		flgWait = true;
		FadeOutBGM(BGM_NAMEENTRY, 30);
		SetSceneFade(TitleScene);
		return;
	}

	if (GetHorizontalInputRepeat() == 1)
	{
		flgWait = true;
		FadeOutBGM(BGM_NAMEENTRY, 30);
		SetSceneFade(TitleScene);
		return;
	}
}