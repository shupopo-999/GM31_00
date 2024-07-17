#pragma once

#include "gameobject.h"

#define SCORE_MAX (999)
#define SCORE_DIGIT (3)

class Score : public GameObject{
private:
	ID3D11Buffer*				m_VertexBuffer = nullptr;
	ID3D11ShaderResourceView*	m_Texture = nullptr;

	ID3D11VertexShader*			m_VertexShader;
	ID3D11PixelShader*			m_PixelShader;
	ID3D11InputLayout*			m_VertexLayout;

	int m_score;

public:
	void Init()override;
	void UnInit()override;
	void Update()override;
	void Draw()override;

	void AddCount(int count) {
		m_score += count;
		if (m_score > SCORE_MAX)
		{
			m_score = SCORE_MAX;
		}
	}

};