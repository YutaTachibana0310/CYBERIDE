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
	_T("data/SOUND/lockon.wav"),
	//_T("data/SOUND/hoge.wav"),
};

static SOUNDEFFECT se[SOUND_MAX];

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
		SOUNDEFFECT *ptr = &se[0];
		for (int i = 0; i < SOUND_MAX; i++)
		{
			ptr->clip = LoadSound(&soundFileName[i][0]);
		}
	}

	SOUNDEFFECT *ptr = &se[0];
	for (int i = 0; i < SOUND_MAX; i++)
	{
		ptr->playOrder = false;
		SetSoundVolume(ptr->clip, 50.0f);
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
		SOUNDEFFECT *ptr = &se[0];
		for (int i = 0; i < SOUND_MAX; i++)
		{
			ptr->clip->Release();
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
	//PlaySoundBuffer(se[sound].clip, E_DS8_FLAG_NONE, true);
}

/**************************************
��~����
***************************************/
void StopSE(DEFINE_SOUNDEFFECT sound)
{
	StopSoundBuffer(se[sound].clip);
}

/**************************************
�ĊJ����
***************************************/
void ResumeSE(DEFINE_SOUNDEFFECT sound)
{
	PlaySoundBuffer(se[sound].clip, E_DS8_FLAG_NONE, false);
}

/**************************************
�Đ�������
***************************************/
bool IsPlayingSE(DEFINE_SOUNDEFFECT sound)
{
	return IsPlaying(se[sound].clip);
}

/**************************************
���ʐݒ�
***************************************/
void SetSEVolume(DEFINE_SOUNDEFFECT sound, float volume)
{
	SetSoundVolume(se[sound].clip, volume);
}

