#pragma once

class GameObject {
protected:
	XMFLOAT3 m_Position = XMFLOAT3(0.0f, 0.0f, 0.0f);
	XMFLOAT3 m_Rotation = XMFLOAT3(0.0f, 0.0f, 0.0f);
	XMFLOAT3 m_Scale = XMFLOAT3(1.0f, 1.0f, 1.0f);

public:
	virtual void Init() = 0;
	virtual void Uninit() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;

	XMFLOAT3 GetPosition() { return m_Position; }
	XMFLOAT3 GetRotation() { return m_Rotation; }
	XMFLOAT3 GetScale() { return m_Scale; }
};