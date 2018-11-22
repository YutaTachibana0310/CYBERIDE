//=============================================================================
//
// �R���C�_�[�w�b�_ [collider.h]
// Author : GP11A341 21 ���ԗY��
//
//=============================================================================
#ifndef _COLLIDER_H_
#define _COLLIDER_H_

#include "main.h"
//*****************************************************************************
// �\���̒�`
//*****************************************************************************

/*
�l�p�`�|���S����\���\����
*/
typedef struct
{
	D3DXVECTOR3 topL;		//���㒸�_
	D3DXVECTOR3 bottomL;	//�������_
	D3DXVECTOR3 bottomR;	//�E�����_
	D3DXVECTOR3 topR;		//�E�㒸�_
	D3DXVECTOR3 nor;		//�@���x�N�g��
}PLANE;

/*
�O�p�`�|���S����\���\����
*/
typedef struct
{
	D3DXVECTOR3 a;			//���_1
	D3DXVECTOR3 b;			//���_2
	D3DXVECTOR3 c;			//���_3
	D3DXVECTOR3 nor;		//�@���x�N�g��
}TRIANGLE;

typedef struct
{
	D3DXVECTOR3 pos;		//���S�ʒu
	float radius;			//���a
	bool active;			//�A�N�e�B�u����
}SPHERE;
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
bool CheckHitTriangleAndLine(D3DXVECTOR3 start, D3DXVECTOR3 end, TRIANGLE tri, D3DXVECTOR3 *out);
bool CheckHitPlaneAndLine(D3DXVECTOR3 start, D3DXVECTOR3 end, PLANE plane, D3DXVECTOR3 *out);
bool ChechHitBoundingSphere(SPHERE s1, SPHERE s2);
void UpdateCollision(void);
#endif