//=====================================
//
//�T�E���h�G�t�F�N�g�}�l�[�W���w�b�_[soundEffectManager.h]
//Author:GP11A341 21 ���ԗY��
//
//=====================================
#ifndef _SOUNDEFFECTMANAGER_H_
#define _SOUNDEFFECTMANAGER_H_

#include "main.h"

#include <dsound.h>
#include <mmsystem.h>

/**************************************
�}�N����`
***************************************/
#define SOUND_VOLUME_MAX	(100.0f)		//�ő剹��
#define SOUND_VOLUME_MIN	(0.0f)			//�ŏ�����

/**************************************
�\���̒�`
***************************************/
enum DEFINE_SOUNDEFFECT
{
	//�T�E���h�ʂ��i���o�[
	SOUND_LOCKON,
	//SOUND_S_EXPLOSION,
	SOUND_MAX
};

typedef struct
{
	LPDIRECTSOUNDBUFFER8 clip;
	bool playOrder;
}SOUNDEFFECT;

/**************************************
�v���g�^�C�v�錾
***************************************/
void InitSoundEffectManager(int num);
void UninitSoundEffectManager(int num);
void UpdateSoundEffectManager(void);

void PlaySE(DEFINE_SOUNDEFFECT sound);
void StopSE(DEFINE_SOUNDEFFECT sound);
void ResumeSE(DEFINE_SOUNDEFFECT sound);
bool IsPlayingSE(DEFINE_SOUNDEFFECT sound);

#endif