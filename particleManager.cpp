//=====================================
//
//�p�[�e�B�N���}�l�[�W������[particleManager.cpp]
//Author:GP11A341 21 ���ԗY��
//
//=====================================
#include "particleManager.h"
#include "explosionFire.h"
#include "explosionFlare.h"
#include "explosionSmog.h"

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
����������
***************************************/
void InitParticleManager(int num)
{
	InitExplosionSmog(num);
	InitExplosionFire(num);
	InitExplosionFlare(num);
}

/**************************************
�I������
***************************************/
void UninitParticleManager(void)
{
	UninitExplosionSmog();
	UninitExplosionFire();
	UninitExplosionFlare();
}

/**************************************
�X�V����
***************************************/
void UpdateParticleManager(void)
{
	UpdateExplosionSmog();
	UpdateExplosionFire();
	UpdateExplosionFlare();
}

/**************************************
�`�揈��
***************************************/
void DrawParticleManager(void)
{
	GetDevice()->SetRenderState(D3DRS_LIGHTING, false);

	DrawExplosionSmog();
	DrawExplosionFire();
	DrawExplosionFlare();

	GetDevice()->SetRenderState(D3DRS_LIGHTING, true);
}
