#pragma once

#include "gameobject.h"


class Camara : public GameObject{
private:
	XMFLOAT4X4  m_ViewMatrix;

	XMFLOAT3	m_Target = XMFLOAT3(0.0f, 0.0f, 0.0f);

public:
	void Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
};