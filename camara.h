#pragma once

#include "gameobject.h"


class Camara : public GameObject{
private:
	XMFLOAT4X4  m_ViewMatrix;
	POINT		m_po;
	XMFLOAT3	m_Target = XMFLOAT3(0.0f, 0.0f, 0.0f);

	FLOAT fTheta = 4.57f;		//�J�����������p�x
	FLOAT fDelta = 0.43f;		//�J�����c�����p�x
	bool  bMouseR_drag;			//�}�E�X�E�h���b�O�t���O
	FLOAT fDistance = 4;		//�J�����ʒu����œ_�܂ł̋���
	POINT mousepoint_a;			//�}�E�X�ʒu
	POINT mousepoint_b;			//�}�E�X�ʒu
	FLOAT fCameraX = fDistance * cos(fDelta) * cos(fTheta);		//�J�����̈ʒuX���W
	FLOAT fCameraY = fDistance * sin(fDelta);					//�J�����̈ʒuY���W
	FLOAT fCameraZ = fDistance * cos(fDelta) * sin(fTheta);		//�J�����̈ʒuZ���W

public:
	void Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

	XMMATRIX GetViewMatrix() {
		return XMLoadFloat4x4(&m_ViewMatrix);
	}
};