#pragma once

#include "gameobject.h"


class Enter_Image : public GameObject{
private:
	ID3D11Buffer* m_VertexBuffer = nullptr;
	ID3D11ShaderResourceView* m_Texture = nullptr;

	ID3D11VertexShader* m_VertexShader;
	ID3D11PixelShader* m_PixelShader;
	ID3D11InputLayout* m_VertexLayout;

	class Audio*	m_BGM{};

	float			m_PositionY = 540.0f;
	float			m_alpha = 0.0f;
	bool			m_flag = false;
public:
	void Init()override;
	void UnInit()override;
	void Update()override;
	void Draw()override;
	void SetTitle(float posX, float posY, float sizeX, float sizeY);
};