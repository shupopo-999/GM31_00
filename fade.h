#pragma once

#include "gameobject.h"


class Fade : public Scene, GameObject {
public:
	typedef enum {	// �t�F�[�h�̃X�e�[�g
		FADE_NONE = 0,	// �������Ȃ�
		FADE_IN,		// �t�F�[�h�C��
		FADE_OUT,		// �t�F�[�h�A�E�g
		FADE_MAX		// �t�F�[�h�X�e�[�g�̌�
	}MODE_FADE;

	void Init()override;
	void UnInit()override;
	void Update()override;
	void Draw()override;

	void SetFade(MODE_FADE state);
	MODE_FADE* GetFade() {
		return &m_FadeSteat;
	}

private:
	ID3D11Buffer* m_VertexBuffer = nullptr;
	ID3D11ShaderResourceView* m_Texture = nullptr;

	ID3D11VertexShader* m_VertexShader;
	ID3D11PixelShader* m_PixelShader;
	ID3D11InputLayout* m_VertexLayout;

	MODE_FADE	m_FadeSteat;
	float		m_FadeAlpha = 0.0f;

	class Audio* m_BGM{};


};

