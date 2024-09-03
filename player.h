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
	XMFLOAT4					m_Quaternion{};

	XMFLOAT3 m_Scale = { 0.1f,0.1f,0.1f };

	float						groundHeight = 0.0f;
	bool						groundFlag;
	float						m_Rot;

	class Audio* m_SE{};

public:
	void Init()override;
	void UnInit()override;
	void Update()override;
	void Draw()override;

	void PlayerCollision();

};