//=====================================
//
//�o�g���{�[�i�X�^�C���J�n�ҋ@����[battleWaitBonusTimeBegin.cpp]
//Author:GP11A341 21 ���ԗY��
//
//=====================================
#include "battleController.h"
#include "bonusCube.h"

/**************************************
�}�N����`
***************************************/

/**************************************
�\���̒�`
***************************************/

/**************************************
�O���[�o���ϐ�
***************************************/
static int cntFrame;

/**************************************
�v���g�^�C�v�錾
***************************************/

/**************************************
���ꏈ��
***************************************/
void OnEnterBattleWaitBonusTimeBegin(BATTLECONTROLLER *controller)
{
	cntFrame = 0;
}

/**************************************
�X�V����
***************************************/
void OnUpdateBattleWaitBonusTimeBegin(BATTLECONTROLLER *controller)
{
	cntFrame++;
	if (cntFrame % BATTLE_EMMITT_INTERBAL != 0)
		EmmittFromFuzzy(controller);

	//�J�ڏ���

}
