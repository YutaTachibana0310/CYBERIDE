//=====================================
//
//�o�g���R���g���[���w�b�_[battleController.h]
//Author:GP11A341 21 ���ԗY��
//
//=====================================
#ifndef _BATTLECONTROLLER_H_
#define _BATTLECONTROLLER_H_

#include "main.h"

/**************************************
�}�N����`
***************************************/
#define BATTLE_SPACE_DIVIDE_NUM			(4)					//�G�l�~�[�����͈͕�����
#define BATTLE_SPACE_MAX (BATTLE_SPACE_DIVIDE_NUM*BATTLE_SPACE_DIVIDE_NUM)	//�������ꂽ��Ԃ̑���
#define BATTLE_FUZZY_NEAR_BORDER		(0.0f)				//�����Ɋւ���t�@�W�B���_�̂������l1
#define BATTLE_FUZZY_MIDDLE_BORDER		(SCREEN_HEIGHT)		//�����Ɋւ���t�@�W�B���_�̂������l2
#define BATTLE_FUZZY_FAR_BORDER			(SCREEN_WIDTH*2.5f)	//�����Ɋւ���t�@�W�B���_�̂������l3
#define BATTLE_FUZZY_RECENTLY_BORDER	(120.0f)			//���ԂɊւ���t�@�W�B���_�̂������l1
#define BATTLE_FUZZY_LATELY_BORDER		(1200.0f)			//���ԂɊւ���t�@�W�B���_�̂������l2
#define BATTLE_CUBEEMMITT_NUM			(3)
#define BATTLE_CUBEEMMITT_SPEED			(10.0f)
#define BATTLE_EMMITT_INTERBAL			(60)

/**************************************
�\���̒�`
***************************************/
//�o�g���R���g���[���̊e�X�e�[�g
enum BATTLECONTROLLER_STATE {
	BattleNormalTime,
	BattleWaitBonusTimeBegin,
	BattleBonusTime,
	BattleBonusIntebal,
	BattleChangeView,
	BattleStateMax
};

//�o�g���R���g���[���[�̎��_���[�h
enum BATTLE_VIEWMODE {
	BattleViewFPS,
	BattleViewTop,
	BattleViewSide,
	BattleViewMax
};

//�o�g���R���g���[���[�\����
typedef struct {
	D3DXVECTOR2 enemyEmmittPos[BATTLE_SPACE_MAX];		//�G�l�~�[�������W
	DWORD lastEmittFrame[BATTLE_SPACE_MAX];				//�e��ԂɃG�l�~�[���������ꂽ�Ō�̃t���[��
	DWORD cntFrame[BattleViewMax];						//�t���[���J�E���g
	D3DXVECTOR3 checkPos[BATTLE_SPACE_MAX];				//������W
	D3DXVECTOR3 emmittPos[BATTLE_SPACE_MAX];			//�G�l�~�[�����ʒu
	DWORD bonusStartFrame;								//�{�[�i�X�^�C���J�n�^�C�~���O

	int currentState;									//���݂̏��
	int prevState;										//��O�̏��

	int viewMode;										//���_���[�h
	int nextViewMode;									//���ɑJ�ڂ��鎋�_���[�h
}BATTLECONTROLLER;


/**************************************
�v���g�^�C�v�錾
***************************************/
void InitBattleController(int num);
void UninitBattleController(int num);
void UpdateBattleController(void);
bool IsBonusTime(void);
void EmmittFromFuzzy(BATTLECONTROLLER *controller);
void ChangeStateBattleController(int next);
bool CheckEscapedBonusCube(void);
void ChangeViewModeBattleController(int next);
int GetBattleViewMode(void);
void SetBonusTimePresen(void);
#endif