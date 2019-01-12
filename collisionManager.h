//=====================================
//
//�R���[�W�����}�l�[�W���w�b�_[collisionManager.h]
//Author:GP11A341 21 ���ԗY��
//
//=====================================
#ifndef _COLLISIONMANAGER_H_
#define _COLLISIONMANAGER_H_

#include "main.h"
#include "collider.h"

/**************************************
�}�N����`
***************************************/

/**************************************
�\���̒�`
***************************************/
struct _CCell;

//�l���ؕ�����Ԃɓo�^����郊�X�g�I�u�W�F�N�g�\����
typedef struct _OBJECT_FOR_TREE {
	_CCell *registerSpace;		//�o�^���
	void *object;				//�ΏۃI�u�W�F�N�g�ւ̔ėp�|�C���^
	_OBJECT_FOR_TREE *prev;		//�O�̃��X�g�I�u�W�F�N�g
	_OBJECT_FOR_TREE *next;		//��̃��X�g�I�u�W�F�N�g
#ifdef _DEBUG
	DWORD elem;
#endif
}OBJECT_FOR_TREE;

//������ԍ\����
typedef struct _CCell {
	OBJECT_FOR_TREE *latestObj;	//��Ԃɓo�^����Ă���擪�̃I�u�W�F�N�g�ւ̃|�C���^
}CCell;

//��Ԃɓo�^�����I�u�W�F�N�g�����ʂ���ID(OFT : OBJECT_FOR_TREE)
enum OFT_ID
{
	OFT_PLAYERBULLET,
	OFT_CUBEOBJECT,
	OFT_HARDCUBE,
	OFT_BONUSCUBE,
	OFT_ID_MAX
};
/**************************************
�v���g�^�C�v�錾
***************************************/
void InitCollisionManager(int num);
void UninitCollisionManager(int num);
void UpdateCollisionManager(void);

//��ԂɃI�u�W�F�N�g��o�^���鏈��
//bool RegisterObjectToSpace(float left, float top, float right, float bottom, OBJECT_FOR_TREE *obj, OFT_ID id);
bool RegisterObjectToSpace(COLLIDER_CUBE *collider, OBJECT_FOR_TREE *obj, OFT_ID id);
//��Ԃ���I�u�W�F�N�g����菜������
bool RemoveObjectFromSpace(OBJECT_FOR_TREE *obj);
//OBJECT_FOT_TREE�쐬����
void CreateOFT(OBJECT_FOR_TREE *oft, void *object);
#endif