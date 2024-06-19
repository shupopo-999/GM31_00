#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "player.h"
#include "modelRenderer.h"
#include "input.h"
#include "camara.h"
#include "explosion.h"

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
}

void Player::Uninit()
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

	if (Input::GetKeyTrigger(VK_SPACE)) {
		Bullet* bullet = scene->AddGameObject<Bullet>();
		bullet->SetPosition(m_Position);
	}
	if (Input::GetKeyTrigger('F')) {
		Explosion* exp = scene->AddGameObject<Explosion>();
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