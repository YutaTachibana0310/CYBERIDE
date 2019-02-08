//=====================================
//
//�i���o�[GUI�w�b�_[numGUI.h]
//Author:GP11A341 21 ���ԗY��
//
//=====================================
#ifndef _NUMGUI_H_
#define _NUMGUI_H_

#include "main.h"

/**************************************
�}�N����`
***************************************/
#define NUMTEX_DIV_X			(5)
#define NUMTEX_DIV_Y			(2)
#define NUMTEX_SCORE_NAME		"data/TEXTURE/UI/scoreNum.png"
#define NUMTEX_LOCKON_NAME		"data/TEXTURE/UI/lockonNum.png"
#define NUMTEX_TIME_NAME		"data/TEXTURE/UI/timeNum.png"
#define NUMTEX_RANKING_NAME		"data/TEXTURE/UI/rankingNum.png"

enum DefineNumTexture
{
	NumScore,
	NumLockon,
	NumBonusTime,
	NumRanking,
	NumDefineMax
};

/**************************************
�\���̒�`
***************************************/
class NumGUI
{
private:
	static NumGUI *instance;					//�V���O���g���C���X�^���X
	LPDIRECT3DTEXTURE9 texture[NumDefineMax];	//�e�N�X�`��
	VERTEX_2D vtxWk[NUM_VERTEX];				//���_���
	float scale;

	NumGUI() = default;							
	~NumGUI() = default;

public:
	/*�C���X�^���X�쐬����*/
	static void Create(void)
	{
		if (instance == nullptr)
		{
			instance = new NumGUI;

			//�e�N�X�`���ǂݍ���
			LPDIRECT3DDEVICE9 pDevice = GetDevice();
			instance->texture[0] = CreateTextureFromFile((LPSTR)NUMTEX_SCORE_NAME, pDevice);
			instance->texture[1] = CreateTextureFromFile((LPSTR)NUMTEX_LOCKON_NAME, pDevice);
			instance->texture[2] = CreateTextureFromFile((LPSTR)NUMTEX_TIME_NAME, pDevice);
			instance->texture[3] = CreateTextureFromFile((LPSTR)NUMTEX_RANKING_NAME, pDevice);

			//�`��D�揇�ʐݒ�
			instance->vtxWk[0].rhw =
				instance->vtxWk[1].rhw =
				instance->vtxWk[2].rhw =
				instance->vtxWk[3].rhw = 1.0f;

			//�f�B�t���[�Y������
			instance->vtxWk[0].diffuse =
				instance->vtxWk[1].diffuse =
				instance->vtxWk[2].diffuse =
				instance->vtxWk[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		}
	}

	/*�C���X�^���X�擾����*/
	static NumGUI* GetInstance(void)
	{
		return instance;
	}

	/*�C���X�^���X�������*/
	static void Release(void)
	{
		for (int i = 0; i < NumDefineMax; i++)
		{
			SAFE_RELEASE(instance->texture[i]);
		}

		delete instance;
		instance = nullptr;
	}

	/*���_���W�ݒ菈��*/
	void SetVertex(D3DXVECTOR3 pos, float sizeX, float sizeY)
	{
		instance->vtxWk[0].vtx = D3DXVECTOR3(-sizeX, -sizeY, 0.0f) + pos;
		instance->vtxWk[1].vtx = D3DXVECTOR3(sizeX, -sizeY, 0.0f) + pos;
		instance->vtxWk[2].vtx = D3DXVECTOR3(-sizeX, sizeY, 0.0f) + pos;
		instance->vtxWk[3].vtx = D3DXVECTOR3(sizeX, sizeY, 0.0f) + pos;
	}

	/*UV���W�ݒ菈��*/
	void SetTexture(int num)
	{
		float sizeX = 1.0f / NUMTEX_DIV_X;
		float sizeY = 1.0f / NUMTEX_DIV_Y;
		int x = num % NUMTEX_DIV_X;
		int y = num / NUMTEX_DIV_X;

		instance->vtxWk[0].tex = D3DXVECTOR2(x * sizeX, y * sizeY);
		instance->vtxWk[1].tex = D3DXVECTOR2((x + 1) * sizeX, y * sizeY);
		instance->vtxWk[2].tex = D3DXVECTOR2(x * sizeX, (y + 1) * sizeY);
		instance->vtxWk[3].tex = D3DXVECTOR2((x + 1) * sizeX, (y + 1) * sizeY);
	}

	/*�A���t�@�ݒ菈��*/
	void SetAlpha(float alpha)
	{
		instance->vtxWk[0].diffuse =
			instance->vtxWk[1].diffuse =
			instance->vtxWk[2].diffuse =
			instance->vtxWk[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, alpha);
	}

	/*�`�揈��*/
	void Draw(DefineNumTexture def)
	{
		LPDIRECT3DDEVICE9 pDevice = GetDevice();

		pDevice->SetFVF(FVF_VERTEX_2D);
		pDevice->SetTexture(0, instance->texture[def]);
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, vtxWk, sizeof(VERTEX_2D));
	}
};

#endif