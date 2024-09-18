#pragma once

#include "gameobject.h"
#include "component.h"
#include <string>

class Player : public GameObject{
private:
	Component*					m_Component{ };

	ID3D11VertexShader*			m_VertexShader{};
	ID3D11PixelShader*			m_PixelShader{};
	ID3D11InputLayout*			m_VertexLayout{};

	XMFLOAT3					m_Velocity{};
	XMFLOAT4					m_Quaternion{};

	XMFLOAT3 m_Scale = { 0.01f,0.01f,0.01f };

	float						groundHeight = 0.0f;
	bool						groundFlag;
	float						m_Rot;


	std::string					m_AnimationName1;
	std::string					m_AnimationName2;
	float						m_AnimationBlend;
	int 						m_AnimationFrame;

	class Audio* m_SE[2]{};

public:
	void Init()override;
	void UnInit()override;
	void Update()override;
	void Movement();
	void Draw()override;

	void PlayerCollision();

	void QuaternionRot(float x, float y, float z);

	void Blender(std::string AnimationName);

};