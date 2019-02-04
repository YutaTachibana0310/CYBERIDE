//=====================================
//
//�x�[�XGUI����[baseGUI.cpp]
//Author:GP11A341 21 ���ԗY��
//
//=====================================
#include "baseGUI.h"

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
�R���X�g���N�^
***************************************/
BaseGUI::BaseGUI(LPSTR texName, float sizeX, float sizeY)
{
	if (texture != NULL)
		return;

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	texture = CreateTextureFromFile(texName, pDevice);
	size = D3DXVECTOR2(sizeX, sizeY);

	vtxWk[0].rhw =
		vtxWk[1].rhw =
		vtxWk[2].rhw =
		vtxWk[3].rhw = 1.0f;
	
	this->SetTexture(1, 1, 0);

	this->SetAlpha(1.0f);

	this->SetVertex(D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_CENTER_Y, 0.0f));

	scale = 1.0f;
}

/**************************************
�f�X�g���N�^
***************************************/
BaseGUI::~BaseGUI()
{
	SAFE_RELEASE(texture);
}

/**************************************
�ǂݍ��ݏ���
***************************************/
void BaseGUI::Load(LPSTR texName, float sizeX, float sizeY)
{
	if (texture != NULL)
		return;

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	texture = CreateTextureFromFile(texName, pDevice);
	size = D3DXVECTOR2(sizeX, sizeY);

	vtxWk[0].rhw =
		vtxWk[1].rhw =
		vtxWk[2].rhw =
		vtxWk[3].rhw = 1.0f;

	this->SetTexture(1, 1, 0);

	this->SetAlpha(1.0f);

	this->SetVertex(D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_CENTER_Y, 0.0f));

	scale = 1.0f;
}

/**************************************
���_�ݒ菈��
**************************************/
void BaseGUI::SetVertex(D3DXVECTOR3 pos, D3DXVECTOR2 scale)
{
	vtxWk[0].vtx = pos + D3DXVECTOR3(-size.x * scale.x, -size.y * scale.y, 0.0f);
	vtxWk[1].vtx = pos + D3DXVECTOR3(size.x * scale.x, -size.y * scale.y, 0.0f);
	vtxWk[2].vtx = pos + D3DXVECTOR3(-size.x * scale.x, size.y * scale.y, 0.0f);
	vtxWk[3].vtx = pos + D3DXVECTOR3(size.x * scale.x, size.y * scale.y, 0.0f);
}

/**************************************
�e�N�X�`�����W�ݒ菈��
**************************************/
void BaseGUI::SetTexture(int divX, int divY, int pattern)
{
	float sizeX = 1.0f / divX;
	float sizeY = 1.0f / divY;
	int x = pattern % divX;
	int y = pattern / divX;

	vtxWk[0].tex = D3DXVECTOR2(x * sizeX, y * sizeY);
	vtxWk[1].tex = D3DXVECTOR2((x + 1) * sizeX, y * sizeY);
	vtxWk[2].tex = D3DXVECTOR2(x * sizeX, (y + 1)* sizeY);
	vtxWk[3].tex = D3DXVECTOR2((x + 1) * sizeX, (y + 1) * sizeY);
}

/**************************************
�A���t�@�ݒ菈��
**************************************/
void BaseGUI::SetAlpha(float alpha)
{
	vtxWk[0].diffuse =
		vtxWk[1].diffuse =
		vtxWk[2].diffuse =
		vtxWk[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, alpha);
}

/**************************************
�`�揈��
**************************************/
void BaseGUI::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	pDevice->SetFVF(FVF_VERTEX_2D);

	pDevice->SetTexture(0, texture);

	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, vtxWk, sizeof(VERTEX_2D));
}
