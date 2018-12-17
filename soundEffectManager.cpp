//=====================================
//
//�T�E���h�G�t�F�N�g�}�l�[�W������[soundEffectManager.cpp]
//Author:GP11A341 21 ���ԗY��
//
//=====================================
#include "soundEffectManager.h"
#include "sound.h"
#include <tchar.h>

#pragma comment ( lib, "dxguid.lib" )
#pragma comment ( lib, "dsound.lib" )
#pragma comment ( lib, "winmm.lib" )

/**************************************
�}�N����`
***************************************/

/**************************************
�\���̒�`
***************************************/

/**************************************
�O���[�o���ϐ�
***************************************/
const TCHAR* soundFileName[SOUND_MAX] =
{
	_T("data/SOUND/hoge.wav"),
	_T("data/SOUND/hoge.wav"),
};

static IDirectSound8 *directSound = NULL;
static LPDIRECTSOUNDBUFFER8 soundBuffer[SOUND_MAX];

/**************************************
�v���g�^�C�v�錾
***************************************/

/**************************************
����������
***************************************/
void InitSoundEffectManager(int num)
{
	if (num == 0)
	{
		for (int i = 0; i < SOUND_MAX; i++)
		{
			soundBuffer[i] = LoadSound(&soundFileName[i][0]);
		}
	}

	return;
}

/**************************************
�I������
***************************************/
void UninitSoundEffectManager(int num)
{
	if (num == 0)
	{
		for (int i = 0; i < SOUND_MAX; i++)
		{
			soundBuffer[i]->Release();
		}
	}
}

/**************************************
�X�V����
***************************************/
void UpdateSoundEffectManager(void)
{

}

/**************************************
�Đ�����
***************************************/
void PlaySE(DEFINE_SOUNDEFFECT sound)
{
	PlaySoundBuffer(soundBuffer[sound], E_DS8_FLAG_NONE, true);
}

/**************************************
��~����
***************************************/
void StopSE(DEFINE_SOUNDEFFECT sound)
{
	StopSoundBuffer(soundBuffer[sound]);
}

/**************************************
�ĊJ����
***************************************/
void ResumeSE(DEFINE_SOUNDEFFECT sound)
{
	PlaySoundBuffer(soundBuffer[sound], E_DS8_FLAG_NONE, false);
}

/**************************************
�Đ�������
***************************************/
bool IsPlayingSE(DEFINE_SOUNDEFFECT sound)
{
	return IsPlaying(soundBuffer[sound]);
}

/**************************************
���ʐݒ�
***************************************/
void SetSEVolume(DEFINE_SOUNDEFFECT sound, float volume)
{
	SetSoundVolume(soundBuffer[sound], volume);
}

