//=====================================
//
//�v���C���[���f���w�b�_[playerModel.h]
//Author:GP11A341 21 ���ԗY��
//
//=====================================
#ifndef _PLAYERMODEL_H_
#define _PLAYERMODEL_H_

#include "main.h"
#include "EasingVector.h"
#include "battleCamera.h"
#include "rockonSite.h"

#define PLAYER_INITMOVE_FRAME		(30)
#define PLAYERMODEL_MAX				(1)
#define PLAYER_DESTROT_MAX			(0.51f)
#define PLAYER_MOVERANGE			(50.0f)
#define PLAYER_ROCKON_MAX			(80)
#define PLAYER_HOMINGATK_INTERBAL	(60)
#define PLAYER_SHOT_INTERBAL		(5)
/**************************************
�}�N����`
***************************************/

/**************************************
�\���̒�`
***************************************/
//�v���C���[�X�e�[�g
enum PlayerState
{
	PlayerFPS,
	PlayerTopView,
	PlayerSideView,
	PlayerQuaterView,
	PlayerTransition,
	PlayerTitle,
	PlayerTitleLaunch,
	PlayerTutorialMove,
	PlayerTutorialLockon,
	PlayerStateMax,
};

//���b�N�I���Ώۍ\����
typedef struct
{
	bool use;			//�g�p�t���O
	D3DXVECTOR3 *pos;	//�^�[�Q�b�g���W
	bool *active;		//�^�[�Q�b�g���
	float *hp;			//�^�[�Q�b�gHP
}ROCKONTARGET;

//�v���C���[�\����
typedef struct
{

	bool active;
	int id;

	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
	D3DXVECTOR3 scale;
	D3DXMATRIX mtxWorld;

	D3DXVECTOR3 initPos;
	int cntFrame;
	D3DXVECTOR3 destRot;
	int nextState;

	//���b�N�I���֘A�p�����[�^
	ROCKONTARGET target[PLAYER_ROCKON_MAX];
	int atkInterbal;
	int lockonNum;
	bool boostMode;

	D3DXVECTOR3 shotpos1, shotpos2;

}PLAYERMODEL;

/**************************************
�v���g�^�C�v�錾
***************************************/
void InitPlayerModel(int num);
void UninitPlayerModel(int num);
void UpdatePlayerModel(void);
void DrawPlayerModel(void);
PLAYERMODEL *GetPlayerAdr(int num);
void ChangeStatePlayerModel(int next);
ROCKONTARGET *AddRockonTarget(int id, D3DXVECTOR3 *targetPos, bool *targetActive, float *targetHP);
void ReleaseRockonTarget(PLAYERMODEL *player, int targetID);
void AttackPlayerMissile(PLAYERMODEL *player);

//���ꏈ��
void EnterPlayerModelTutorialMove(PLAYERMODEL *ptr);
void EnterPlayerModelTutorialLockon(PLAYERMODEL *ptr);

//�X�V����
void UpdatePlayerModelTutorialMove(PLAYERMODEL *ptr);
void UpdatePlayerModelTutorialLockon(PLAYERMODEL *ptr);

//�ޏꏈ��
void ExitPlayerModelTutorialMove(PLAYERMODEL *ptr);
void ExitPlayerModelTutorialLockon(PLAYERMODEL *ptr);

//�`���[�g���A�����b�N�I���񐔎擾����
int GetTutorialLockOnNum(void);

//�`���[�g���A���z�[�~���O�U���񐔎擾����
int GetTutorialHomingAttackNum(void);

#endif