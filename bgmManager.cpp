//=====================================
//
//BGM�}�l�[�W������[bgmManager.cpp]
//Author:GP11A341 21 ���ԗY��
//
//=====================================
#include "bgmManager.h"
#include "sound.h"
#include <tchar.h>

/**************************************
�}�N����`
***************************************/

/**************************************
�\���̒�`
***************************************/

/**************************************
�O���[�o���ϐ�
***************************************/
static const TCHAR* BgmFileName[BGM_MAX] = {
	_T("data/SOUND/LAST_GUARDIAN.wav"),
};

static BGM bgmData[BGM_MAX];

/**************************************
�v���g�^�C�v�錾
***************************************/

/**************************************
����������
***************************************/
void InitBgmManager(int num)
{
	static bool initialized = false;

	if (!initialized)
	{
		BGM *ptr = &bgmData[0];
		for (int i = 0; i < BGM_MAX; i++, ptr++)
		{
			ptr->clip = LoadSound(&BgmFileName[i][0]);
			SetSoundVolume(ptr->clip, SOUND_VOLUME_INIT);
		}
		initialized = true;
	}
}

/**************************************
�I������
***************************************/
void UninitBgmManager(int num)
{
	if (num == 0)
	{
		BGM *ptr = &bgmData[0];
		for (int i = 0; i < BGM_MAX; i++, ptr++)
		{
			SAFE_RELEASE(ptr->clip);
		}
	}
}

/**************************************
�X�V����
***************************************/
void UpdateBgmManager(void)
{

}

/**************************************
�Đ�����
***************************************/
void PlayBGM(DEFINE_BGM bgm)
{
	PlaySoundBuffer(bgmData[bgm].clip, E_DS8_FLAG_LOOP, true);
}

/**************************************
��~
***************************************/
void StopBGM(DEFINE_BGM bgm)
{
	StopSoundBuffer(bgmData[bgm].clip);
}

/**************************************
�ĊJ
***************************************/
void ResumeBGM(DEFINE_BGM bgm)
{
	PlaySoundBuffer(bgmData[bgm].clip, E_DS8_FLAG_LOOP, false);
}

/**************************************
�Đ�������
***************************************/
bool IsPlayingBGM(DEFINE_BGM bgm)
{
	return IsPlaying(bgmData[bgm].clip);
}