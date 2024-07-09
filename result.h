#pragma once

#include "gameobject.h"


class Result : public Scene {
private:
	ID3D11Buffer* m_VertexBuffer = nullptr;
	ID3D11ShaderResourceView* m_Texture = nullptr;

	ID3D11VertexShader* m_VertexShader;
	ID3D11PixelShader* m_PixelShader;
	ID3D11InputLayout* m_VertexLayout;
public:
	void Init()override;
	void UnInit()override;
	void Update()override;
	void Draw()override;



};