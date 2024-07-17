#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "camara.h"
#include "player.h"
#include "scene.h"
#include "input.h"

void Camara::Init()
{
	m_Position = XMFLOAT3(0.0f, 5.0f, -10.0f);
	m_Target = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_Rot = 0.1f;
}

void Camara::UnInit()
{

}


void Camara::Update()
{
	GetCursorPos(&m_po);

	Scene* scene = Manager::GetScene();

	Player* player = scene->GetGameObject<Player>();
	m_Target = player->GetPosition();
	m_Target.y += 1.0f;

	if (Input::GetKeyPress('E')) {
		m_Rotation.y += m_Rot;
	}
	if (Input::GetKeyPress('Q')) {
		m_Rotation.y -= m_Rot;
	}

	m_Position.x = m_Target.x - sinf(m_Rotation.y) * 6.0f;
	m_Position.y = m_Target.y + 4.0f;
	m_Position.z = m_Target.z - cosf(m_Rotation.y) * 6.0f;

}

void Camara::Draw()
{
	XMFLOAT3 up{ 0.0f,1.0f,0.0f };
	XMMATRIX viewMatrix = XMMatrixLookAtLH(XMLoadFloat3(&m_Position),XMLoadFloat3(&m_Target), XMLoadFloat3(&up));
	
	Renderer::SetViewMatrix(viewMatrix);

	XMStoreFloat4x4(&m_ViewMatrix, viewMatrix);

	// プロジェクションマトリクス設定
	XMMATRIX projectionMatrix;
	projectionMatrix = XMMatrixPerspectiveFovLH(1.0f, (float)SCREEN_WIDTH / SCREEN_HEIGHT, 1.0f, 1000.0f);
	Renderer::SetProjectionMatrix(projectionMatrix);
}
