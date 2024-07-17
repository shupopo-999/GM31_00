#pragma once

class GameObject {
protected:
	bool	 m_Destroy = false;

	XMFLOAT3 m_Position = XMFLOAT3(0.0f, 0.0f, 0.0f);
	XMFLOAT3 m_Rotation = XMFLOAT3(0.0f, 0.0f, 0.0f);
	XMFLOAT3 m_Scale = XMFLOAT3(1.0f, 1.0f, 1.0f);

public:
	virtual ~GameObject() {};
	virtual void Init() = 0;
	virtual void UnInit() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;

	XMFLOAT3 GetPosition() { return m_Position; }
	XMFLOAT3 GetRotation() { return m_Rotation; }
	XMFLOAT3 GetScale() { return m_Scale; }

	void SetPosition(XMFLOAT3 pos) { m_Position = pos; }
	void SetRotation(XMFLOAT3 rot) { m_Position = rot; }
	void SetScale(XMFLOAT3 sca) { m_Position = sca; }

	void SetDestroy() { m_Destroy = true; }

	bool Destroy() {
		if (m_Destroy) {
			UnInit();
			delete this;
			return this;
		}
		else return false;
	}
	XMFLOAT3 GetForward() {
		// オイラー角から回転行列を生成
		XMMATRIX rotationMatrix;
		rotationMatrix = XMMatrixRotationRollPitchYaw(m_Rotation.x, m_Rotation.y, m_Rotation.z);

		XMFLOAT3 forward;
		XMStoreFloat3(&forward, rotationMatrix.r[2]);
		return forward;
	}
	XMFLOAT3 GetRight() {
		// オイラー角から回転行列を生成
		XMMATRIX rotationMatrix;
		rotationMatrix = XMMatrixRotationRollPitchYaw(m_Rotation.x, m_Rotation.y, m_Rotation.z);

		XMFLOAT3 forward;
		XMStoreFloat3(&forward, rotationMatrix.r[3]);
		return forward;
	}
};