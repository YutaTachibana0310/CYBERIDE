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

#define PLAYER_INITMOVE_FRAME	(30)
#define PLAYERMODEL_MAX			(1)
#define PLAYER_DESTROT_MAX		(0.51f)
#define PLAYER_MOVERANGE		(50.0f)
#define PLAYER_ROCKON_MAX		(32)
#define PLAYER_HOMINGATK_INTERBAL	(60)

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
	PlayerStateMax
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

	D3DXVECTOR3 initPos;
	bool flgMove;
	int cntFrame;
	D3DXVECTOR3 destRot;

	//���b�N�I���֘A�p�����[�^
	ROCKONTARGET target[PLAYER_ROCKON_MAX];
	int atkInterbal;

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
void ReleaseRockonTarget(ROCKONTARGET *target);
#endif