#pragma once

#include "gameobject.h"


class Fade : public Scene,GameObject {
private:
	ID3D11Buffer* m_VertexBuffer = nullptr;
	ID3D11ShaderResourceView* m_Texture = nullptr;

	ID3D11VertexShader* m_VertexShader;
	ID3D11PixelShader* m_PixelShader;
	ID3D11InputLayout* m_VertexLayout;

	float		m_FadeAlpha = 0.0f;

public:
	void Init()override;
	void UnInit()override;
	void Update()override;
	void Draw()override;


};

