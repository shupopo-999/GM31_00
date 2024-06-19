#pragma once

#include "gameobject.h"


class Camara : public GameObject{
private:
	XMFLOAT4X4  m_ViewMatrix;
	POINT		m_po;
	XMFLOAT3	m_Target = XMFLOAT3(0.0f, 0.0f, 0.0f);

	FLOAT fTheta = 4.57f;		//カメラ横方向角度
	FLOAT fDelta = 0.43f;		//カメラ縦方向角度
	bool  bMouseR_drag;			//マウス右ドラッグフラグ
	FLOAT fDistance = 4;		//カメラ位置から焦点までの距離
	POINT mousepoint_a;			//マウス位置
	POINT mousepoint_b;			//マウス位置
	FLOAT fCameraX = fDistance * cos(fDelta) * cos(fTheta);		//カメラの位置X座標
	FLOAT fCameraY = fDistance * sin(fDelta);					//カメラの位置Y座標
	FLOAT fCameraZ = fDistance * cos(fDelta) * sin(fTheta);		//カメラの位置Z座標

public:
	void Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

	XMMATRIX GetViewMatrix() {
		return XMLoadFloat4x4(&m_ViewMatrix);
	}
};