#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "player.h"
#include "modelRenderer.h"
#include "input.h"
#include "camara.h"
#include "enemy.h"
#include "cylinder.h"
#include "explosion.h"
#include "title.h"

Input* input;

void Player::Init()
{
	m_Component = new ModelRenderer(this);
	((ModelRenderer*)m_Component)->Load("asset\\model\\player.obj");


	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout,
		"shader\\unlitTextureVS.cso");
	Renderer::CreatePixelShader(&m_PixelShader,
		"shader\\unlitTexturePS.cso");

	m_Position.x = 5.0f;
	groundFlag = true;
}

void Player::UnInit()
{
	delete m_Component;

	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();


}

void Player::Update()
{
	XMFLOAT3 forward = GetForward();

	Scene* scene;
	scene = Manager::GetScene();
	float speed = 0.3f;
	float rot = 0.1f;

	m_Component->Update();

	if (Input::GetKeyPress(VK_LSHIFT))speed *= 1.5;

	if (Input::GetKeyPress('F')) {
		Bullet* bullet = scene->AddGameObject<Bullet>(2);
		bullet->SetPosition(m_Position);
	}
	if (Input::GetKeyTrigger('R')) {
		Enemy* ene = scene->AddGameObject<Enemy>(1);
		ene->SetPosition(m_Position);
	}
	if (Input::GetKeyTrigger('T')) {
		Cylinder* cy = scene->AddGameObject<Cylinder>(1);
		cy->SetPosition(m_Position);
	}
	if (Input::GetKeyTrigger(VK_RETURN)) {
		Manager::SetScene<Title>();
	}

	if (Input::GetKeyPress('W')) {
		m_Position.x += forward.x * speed;
		m_Position.y += forward.y * speed;
		m_Position.z += forward.z * speed;
	}
	if (Input::GetKeyPress('S')) {
		m_Position.x -= forward.x * speed;
		m_Position.y -= forward.y * speed;
		m_Position.z -= forward.z * speed;
	}
	if (Input::GetKeyPress('D')) {
		m_Position.x += forward.z * speed;
		m_Position.y += forward.y * speed;
		m_Position.z += forward.x * speed;
	}
	if (Input::GetKeyPress('A')) {
		m_Position.x -= forward.z * speed;
		m_Position.y -= forward.y * speed;
		m_Position.z -= forward.x * speed;
	}
	if (Input::GetKeyPress('E')){
		m_Rotation.y += rot;
	}
	if (Input::GetKeyPress('Q')) {
		m_Rotation.y -= rot;
	}
	if (Input::GetKeyTrigger(VK_SPACE)) {
		m_Velocity.y = 1.5f;
	}

	if (!groundFlag) {
		m_Velocity.y -= 0.1f;
		m_Position.y += m_Velocity.y;
	}

	// 地面との当たり判定
	if (m_Position.y < groundHeight) {
		m_Position.y = groundHeight;
		m_Velocity.y = 0.0f;
	}
	PlayerCollision();
}

void Player::PlayerCollision() {
	XMFLOAT3 oldPos = m_Position;

	Scene* scene;
	scene = Manager::GetScene();

	auto cyList = scene->GetGameObjects<Cylinder>();
	for (Cylinder* cy : cyList) {
		XMFLOAT3 cyPosition = cy->GetPosition();
		XMFLOAT3 cyScale = cy->GetScale();

		XMFLOAT3 direction;
		direction.x = cyPosition.x - m_Position.x;
		direction.y = cyPosition.y - m_Position.y;
		direction.z = cyPosition.z - m_Position.z;

		float length;
		length = sqrtf(direction.x * direction.x
			+ direction.z * direction.z);

		if (length < cyScale.x) {
			if (-direction.y > cyScale.y - 0.1) {
				groundHeight = cyPosition.y + cyScale.y;
			}
			else {
				m_Position.x = oldPos.x;
				m_Position.z = oldPos.z;
			}
		}
	}
}

void Player::Draw()
{
	// 入力レイアウト設定
	Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);

	// シェーダ設定
	Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);

	// ワールドマトリクス設定
	XMMATRIX world, scale, rot, trans;
	scale = XMMatrixScaling(m_Scale.x,m_Scale.y,m_Scale.z);
	rot = XMMatrixRotationRollPitchYaw(m_Rotation.x, m_Rotation.y + XM_PI, m_Rotation.z);
	trans = XMMatrixTranslation(m_Position.x, m_Position.y, m_Position.z);
	world = scale * rot * trans;
	Renderer::SetWorldMatrix(world);

	m_Component->Draw();
}