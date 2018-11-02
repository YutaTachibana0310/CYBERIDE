//=====================================
//
//�p�[�e�B�N���t���[�����[�N�w�b�_[particleFramework.h]
//Author:GP11A341 21 ���ԗY��
//
//=====================================
#ifndef _PARTICLEFRAMEWORK_H_
#define _PARTICLEFRAMEWORK_H_

#include "main.h"
#include "particleManager.h"

/**************************************
�v���g�^�C�v�錾
***************************************/
//�P�ʒ��_�o�b�t�@�쐬����
void MakeParticleVertexBuffer(VERTEX_PARTICLE *vtx, float particleSize, LPDIRECT3DVERTEXBUFFER9 *buff);

//UV���_�o�b�t�@�쐬����
void MakeParticleUVBuffer(int size, VERTEX_UV *uv, LPDIRECT3DVERTEXBUFFER9 *buff);

//���[���h�ϊ��o�b�t�@�쐬����
void MakeParticleWorldBuffer(int size, D3DXMATRIX *world, LPDIRECT3DVERTEXBUFFER9 *buff);

//�J���[�o�b�t�@�쐬����
void MakeParticleColorBuffer(int size, VERTEX_COLOR *color, LPDIRECT3DVERTEXBUFFER9 *buff);

#endif