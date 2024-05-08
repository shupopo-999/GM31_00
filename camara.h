#pragma once

class Camara {
private:
	XMFLOAT4X4  m_ViewMatrix;

	XMFLOAT3	m_Position = XMFLOAT3(0.0f, 0.0f, 0.0f);
	XMFLOAT3	m_Rotation = XMFLOAT3(0.0f, 0.0f, 0.0f);
	XMFLOAT3	m_Target = XMFLOAT3(0.0f, 0.0f, 0.0f);

public:
	void Init();
	void Unini();
	void Update();
	void Draw();
};