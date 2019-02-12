//=====================================
//
//�l�[���G���g���[�V�[��GUI����[NameEntrySceneGUI.cpp]
//Author:GP11A341 21 ���ԗY��
//
//=====================================
#include "nameEntryRanking.h"
#include "rankingScore.h"
#include "nameEntryCursor.h"
#include "rankingTelop.h"
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

/**************************************
�v���g�^�C�v�錾
***************************************/

/**************************************
���ꏈ��
***************************************/
void OnEnterNameEntrySceneGUI(void)
{
	InitNameEntryRanking(0);
	InitRankingScore(0);
	InitNameEntryCursor(0);
	InitRankingTelop(0);
	InitEntryTelop(0);
}

/**************************************
�X�V����
***************************************/
void OnUpdateNameEntrySceneGUI(void)
{
	UpdateNameEntryRanking();
	UpdateRankingScore();
	UpdateNameEntryCursor();
	UpdateRankingTelop();
	UpdateEntryTelop();
}

/**************************************
�`�揈��
***************************************/
void OnDrawNameEntrySceneGUI(void)
{
	DrawNameEntryRanking();
	DrawRankingScore();
	DrawNameEntryCursor();
	DrawRankingTelop();
	DrawEntryTelop();
}