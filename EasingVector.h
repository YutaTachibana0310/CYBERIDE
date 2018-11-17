//=============================================================================
//
// �C�[�W���O�w�b�_ [Easing.h]
// Author : GP11A341 21 ���ԗY��
//
//=============================================================================
#ifndef _EASING_H_
#define _EASING_H_

#include "d3dx9.h"

//*****************************************************************************
// �񋓑̒�`
//*****************************************************************************
enum EASINGVECTOR_TYPE
{
	InCubic,
	OutCubic,
	InOutCubic,
	Linear,
	InExponential,
	OutExponential,
	InOutExponential,
	EasingMax
};

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
D3DXVECTOR3 GetEasingValue(float time, D3DXVECTOR3 start, D3DXVECTOR3 goal, EASINGVECTOR_TYPE type);
D3DXVECTOR3 EaseInCubic(float time, D3DXVECTOR3 start, D3DXVECTOR3 goal);			//InCubic�v�Z����
D3DXVECTOR3 EaseOutCubic(float time, D3DXVECTOR3 start, D3DXVECTOR3 goal);		//OutCubic�v�Z����
D3DXVECTOR3 EaseInOutCubic(float time, D3DXVECTOR3 start, D3DXVECTOR3 goal);		//InOutCubic�v�Z����
D3DXVECTOR3 EaseLinear(float time, D3DXVECTOR3 start, D3DXVECTOR3 goal);			//Linear�v�Z����
D3DXVECTOR3 EaseInExponential(float time, D3DXVECTOR3 start, D3DXVECTOR3 goal);	//InExponential�v�Z����
D3DXVECTOR3 EaseOutExponential(float time, D3DXVECTOR3 start, D3DXVECTOR3 goal);	//OutExponential�v�Z����
D3DXVECTOR3 EaseInOutExponential(float time, D3DXVECTOR3 start, D3DXVECTOR3 goal);//InOutExponential�v�Z����
#endif