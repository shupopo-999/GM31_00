#pragma once

#include "gameobject.h"


class Fade : public GameObject {
public:
	typedef enum {	// フェードのステート
		FADE_NONE = 0,	// 何もしない
		FADE_IN,		// フェードイン
		FADE_OUT,		// フェードアウト
		FADE_MAX		// フェードステートの個数
	}MODE_FADE;

	void Init()override;
	void UnInit()override;
	void Update()override;
	void Draw()override;

private:
	ID3D11Buffer* m_VertexBuffer = nullptr;
	ID3D11ShaderResourceView* m_Texture = nullptr;

	ID3D11VertexShader* m_VertexShader;
	ID3D11PixelShader* m_PixelShader;
	ID3D11InputLayout* m_VertexLayout;

	MODE_FADE	m_FadeSteat;
	float		m_FadeAlpha = 0.0f;

};

