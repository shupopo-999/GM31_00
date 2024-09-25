#pragma once

#include "gameobject.h"

#define		CAMARA_ROTATE	(XM_PI * 0.01f)


class Camera : public GameObject{
private:
	XMFLOAT4X4  m_ViewMatrix;
	POINT*		m_po;
	XMFLOAT3	m_Target = XMFLOAT3(0.0f, 0.0f, 0.0f);
	float		m_Len = 6.0f;
	bool		m_Flag = true;

	FLOAT m_Theta;//カメラ横方向角度
	FLOAT m_Delta;//カメラ縦方向角度
	FLOAT m_Distance;//カメラ位置から焦点までの距離
	POINT m_MousePoint_a;//マウス位置
	POINT m_MousePoint_b;//マウス位置

	HWND	m_Window;

public:
	void Init()override;
	void UnInit()override;
	void Update()override;
	void Draw()override;


	XMMATRIX GetViewMatrix() {
		return XMLoadFloat4x4(&m_ViewMatrix);
	}
};