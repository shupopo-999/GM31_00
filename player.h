#pragma once

#include "gameobject.h"
#include "component.h"

class Player : public GameObject{
private:
	Component*					m_Component{ };

	ID3D11VertexShader*			m_VertexShader{};
	ID3D11PixelShader*			m_PixelShader{};
	ID3D11InputLayout*			m_VertexLayout{};

	XMFLOAT3					m_Velocity{};
	float						groundHeight = 0.0f;
	float						m_Rot;
	bool						groundFlag;

	class Audio* m_SE{};

public:
	void Init()override;
	void UnInit()override;
	void Update()override;
	void Draw()override;

	void PlayerCollision();
	void ParticleDelete();

};