#pragma once

class Field {
private:
	ID3D11Buffer*				m_VertexBuffer = nullptr;
	ID3D11ShaderResourceView*	m_Texture = nullptr;

	ID3D11VertexShader*			m_VertexShader;
	ID3D11PixelShader*			m_PixelShader;
	ID3D11InputLayout*			m_VertexLayout;

	XMFLOAT3			m_Scale		= XMFLOAT3(0.0f, 0.0f, 0.0f);
	XMFLOAT3			m_Position	= XMFLOAT3(0.0f, 0.0f, 0.0f);
	XMFLOAT3			m_Rotation	= XMFLOAT3(0.0f, 0.0f, 0.0f);

public:
	void Init();
	void Uninit();
	void Update();
	void Draw();



};