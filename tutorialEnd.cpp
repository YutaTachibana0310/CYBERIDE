//=====================================
//
//�`���[�g���A���I������[tutorialEnd.cpp]
//Author:GP11A341 21 ���ԗY��
//
//=====================================
#include "sceneFade.h"
#include "bgmManager.h"

/**************************************
�}�N����`
***************************************/
#define TUTORIAL_END_FADE_DURATION		(60)

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
void OnEnterTutorialEnd(void)
{
	FadeOutBGM(BGM_TUTORIALSCENE, TUTORIAL_END_FADE_DURATION);
	SetSceneFade(BattleScene);
}

/**************************************
�X�V����
***************************************/
void OnUpdateTutorialEnd(void)
{

}

/**************************************
�`�揈��
***************************************/
void OnDrawTutorialEnd(LPDIRECT3DTEXTURE9 tex)
{

}