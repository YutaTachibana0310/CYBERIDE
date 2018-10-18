#include "quadTree.h"

/*
�Ώۂ�1�r�b�g�Ԋu�ɕ�������֐�
*/
DWORD BitSeparate32(DWORD n)
{
	n = (n | (n << 8)) & 0x00ff00ff;
	n = (n | (n << 4)) & 0x0f0f0f0f;
	n = (n | (n << 2)) & 0x33333333;
	n = (n | (n << 1)) & 0x55555555;

	return n;
}

/*
���[�g���ԍ��i���������t�B�[���h�̒ʂ��ԍ��j���Z�o����֐�
����1�FX���W
����2�FY���W
*/
DWORD GetMortonNum(WORD x, WORD y)
{
	return (BitSeparate32(x) | BitSeparate32(y) << 1);
}

/*
��ԃ��x���v�Z�֐�
�����F�Ώۂ̃��[�g���ԍ��̔r���I�_���a
*/
SpaceLevel CalcSpaceLevel(DWORD n)
{
	int cnt = -1;
	for (int i = 0; i < 6; i++)
	{
		if ((n & 0x0001) == 1)
		{
			cnt = i;
		}

		n = n >> 1;
	}

	if (cnt == -1)
		return GrandSon;

	if (cnt < 2)
		return Child;

	if (cnt < 4)
		return Parent;

	else
		return Root;
}

int CalcSpaceIndex(SpaceLevel level, DWORD morton)
{
	morton = morton >> level;

	return (morton & 0x0003);
}

/*
���[�v�n�_�v�Z�����iX���j
*/
float CalcLoopStartX(SpaceLevel level, DWORD morton)
{
	float res = 0.0f;

	switch (level)
	{
	case GrandSon:
		res += (CalcSpaceIndex(Parent, morton) & 0x0001) * 0.5f;
		res += (CalcSpaceIndex(Child, morton) & 0x0001) * 0.25f;
		res += (CalcSpaceIndex(GrandSon, morton) & 0x0001) * 0.125f;
		break;

	case Child:
		res += (CalcSpaceIndex(Parent, morton) & 0x0001) * 0.5f;
		res += (CalcSpaceIndex(Child, morton) & 0x0001) * 0.25f;
		break;


	case Parent:
		res += (CalcSpaceIndex(Parent, morton) & 0x0001) * 0.5f;
		break;


	default:
		res = 0.0f;
		break;
	}

	return res;
}

/*
���[�v�I�_�v�Z�����iX���j
*/
float CalcLoopEndX(SpaceLevel level, DWORD morton)
{
	float res = 0.0f;

	switch (level)
	{
	case GrandSon:
		res += (CalcSpaceIndex(Parent, morton) & 0x0001) * 0.5f;
		res += (CalcSpaceIndex(Child, morton) & 0x0001) * 0.25f;
		res += (CalcSpaceIndex(GrandSon, morton) & 0x0001) * 0.125f;
		res += 0.125f;
		break;

	case Child:
		res += (CalcSpaceIndex(Parent, morton) & 0x0001) * 0.5f;
		res += (CalcSpaceIndex(Child, morton) & 0x0001) * 0.25f;
		res += 0.25f;
		break;


	case Parent:
		res += (CalcSpaceIndex(Parent, morton) & 0x0001) * 0.5f;
		res += 0.5f;
		break;


	default:
		res = 1.0f;
		break;
	}

	return res;
}

/*
���[�v�n�_�v�Z�����iX���j
*/
float CalcLoopStartZ(SpaceLevel level, DWORD morton)
{
	float res = 0.0f;

	switch (level)
	{
	case GrandSon:
		res += ((CalcSpaceIndex(Parent, morton) >> 1) & 0x0001) * 0.5f;
		res += ((CalcSpaceIndex(Child, morton) >> 1) & 0x0001) * 0.25f;
		res += ((CalcSpaceIndex(GrandSon, morton) >> 1) & 0x0001) * 0.125f;
		break;

	case Child:
		res += ((CalcSpaceIndex(Parent, morton) >> 1) & 0x0001) * 0.5f;
		res += ((CalcSpaceIndex(Child, morton) >> 1) & 0x0001) * 0.25f;
		break;

	case Parent:
		res += ((CalcSpaceIndex(Parent, morton) >> 1) & 0x0001) * 0.5f;
		break;

	default:
		res = 0.0f;
		break;
	}

	return res;
}

/*
���[�v�I�_�v�Z�����iX���j
*/
float CalcLoopEndZ(SpaceLevel level, DWORD morton)
{
	float res = 0.0f;

	switch (level)
	{
	case GrandSon:
		res += ((CalcSpaceIndex(Parent, morton) >> 1) & 0x0001) * 0.5f;
		res += ((CalcSpaceIndex(Child, morton) >> 1) & 0x0001) * 0.25f;
		res += ((CalcSpaceIndex(GrandSon, morton) >> 1) & 0x0001) * 0.125f;
		res += 0.125f;
		break;

	case Child:
		res += ((CalcSpaceIndex(Parent, morton) >> 1) & 0x0001) * 0.5f;
		res += ((CalcSpaceIndex(Child, morton) >> 1) & 0x0001) * 0.25f;
		res += 0.25f;
		break;

	case Parent:
		res += ((CalcSpaceIndex(Parent, morton) >> 1) & 0x0001) * 0.5f;
		res += 0.5f;
		break;

	default:
		res = 1.0f;
		break;
	}

	return res;
}