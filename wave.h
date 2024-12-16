#pragma once

#include "gameobject.h"

class Wave : public GameObject {
private:
	ID3D11Buffer* m_VertexBuffer = nullptr;
	ID3D11Buffer* m_IndexBuffer = nullptr;
	ID3D11ShaderResourceView* m_Texture = nullptr;

	ID3D11VertexShader* m_VertexShader;
	ID3D11PixelShader* m_PixelShader;
	ID3D11InputLayout* m_VertexLayout;

	VERTEX_3D m_Vertex[21][21]{};
	float		m_time{};
	float		amplitude = 0.5f;		// êUïù
	float		waveLength = 3.0f;	// îgí∑
	float		waveCycle = 0.5f;	// îgí∑

public:
	void Init()override;
	void UnInit()override;
	void Update()override;
	void Draw()override;

	float GetHeight(XMFLOAT3 Position);



};