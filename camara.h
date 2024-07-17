#pragma once

#include "gameobject.h"


class Camara : public GameObject{
private:
	XMFLOAT4X4  m_ViewMatrix;
	POINT		m_po;
	XMFLOAT3	m_Target = XMFLOAT3(0.0f, 0.0f, 0.0f);
	float		m_Rot;


public:
	void Init()override;
	void UnInit()override;
	void Update()override;
	void Draw()override;

	XMMATRIX GetViewMatrix() {
		return XMLoadFloat4x4(&m_ViewMatrix);
	}
};