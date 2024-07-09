#pragma once

#include "gameobject.h"
#include "component.h"

class Bullet : public GameObject{
private:
	Component*					m_Component{ };

	ID3D11VertexShader*			m_VertexShader{};
	ID3D11PixelShader*			m_PixelShader{};
	ID3D11InputLayout*			m_VertexLayout{};

	float						m_Speed = 1.0f;

public:
	void Init()override;
	void UnInit()override;
	void Update()override;
	void Draw()override;

	void BulletCollision();

};