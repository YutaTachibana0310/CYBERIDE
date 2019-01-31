//=====================================
//
//�l�[���G���g���[�R���g���[������[nameEntryController.cpp]
//Author:GP11A341 21 ���ԗY��
//
//=====================================
#include "nameEntryController.h"
#include "dataContainer.h"
#include "rankingName.h"
#include "input.h"
#include "nameEntryCursor.h"

/**************************************
�}�N����`
***************************************/

/**************************************
�\���̒�`
***************************************/
typedef void(*funcNameEntryContoller)(NAMEENTRY*);

/**************************************
�O���[�o���ϐ�
***************************************/
static NAMEENTRY entity;

//���ꏈ���e�[�u��
static funcNameEntryContoller Enter[NAMEENTRY_STATEMAX] = {
	OnEnterNameEntryInput,
	OnEnterNameEntryEnd
};

//�X�V����table
static funcNameEntryContoller Update[NAMEENTRY_STATEMAX] = {
	OnUpdateNameEntryInput,
	OnUpdateNameEntryEnd,
};

/**************************************
�v���g�^�C�v�錾
***************************************/

/**************************************
����������
***************************************/
void InitNameEntryController(int num)
{
	//�����L���O�̍X�V���m�F
	bool flgUpdate = CheckUpdateRanking(&entity.scoreIndex);

	//�X�V���������ꍇ
	if (flgUpdate)
	{
		entity.highScore = GetHighScore(entity.scoreIndex);

		//�e�p�����[�^���Z�b�g
		entity.nameIndex = 0;
		SetStateNameEntryCursor(true);

		//�v���C���[����������
		for (int i = 0; i < DATACONTAINER_PLAYERNAME_MAX; i++)
		{
			entity.highScore->playerName[i] = 31;
		}

		//���͏�Ԃ֑J��
		ChangeStateNameEntryController(NAMEENTRY_INPUT);
	}

	//�X�V���Ȃ������ꍇ
	else
	{
		ChangeStateNameEntryController(NAMEENTRY_END);
	}
}

/**************************************
�I������
***************************************/
void UninitNameEntryController(int num)
{

}

/**************************************
�X�V����
***************************************/
void UpdateNameEntryController(void)
{
	Update[entity.currentState](&entity);
}

/**************************************
�`�揈��
***************************************/
void DrawNameEntryController(void)
{

}

/**************************************
��ԑJ�ڏ���
***************************************/
void ChangeStateNameEntryController(int next)
{
	entity.currentState = next;
	Enter[entity.currentState](&entity);
}