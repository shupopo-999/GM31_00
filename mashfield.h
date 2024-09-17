#pragma once

#include "gameobject.h"

class MashField : public GameObject{
private:
	ID3D11Buffer*				m_VertexBuffer = nullptr;
	ID3D11Buffer*				m_IndexBuffer = nullptr;
	ID3D11ShaderResourceView*	m_Texture = nullptr;

	ID3D11VertexShader*			m_VertexShader;
	ID3D11PixelShader*			m_PixelShader;
	ID3D11InputLayout*			m_VertexLayout;

	VERTEX_3D m_Vertex[21][21]{};

public:
	void Init()override;
	void UnInit()override;
	void Update()override;
	void Draw()override;



};