#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "scene.h"
#include "bullet.h"
#include "player.h"
#include "modelRenderer.h"


void Bullet::Init()
{
	m_Component = new ModelRenderer(this);
   	((ModelRenderer*)m_Component)->Load("asset\\model\\bullet.obj");


	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout,
		"shader\\unlitTextureVS.cso");
	Renderer::CreatePixelShader(&m_PixelShader,
		"shader\\unlitTexturePS.cso");
	m_Position.y = 1.0f;

}

void Bullet::Uninit()
{
	delete m_Component;

	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();


}

void Bullet::Update()
{
	Player player;
	m_Rotation = player.GetRotation();

	XMFLOAT3 forward = GetForward();


	m_Position.x += forward.x * m_Speed;
	m_Position.y += forward.y * m_Speed;
	m_Position.z += forward.z * m_Speed;


	if (m_Position.x || m_Position.y || m_Position.z > 10.0f) {
		
		
		SetDestroy();
	}
	BulletCollision();
	
}

void Bullet::BulletCollision() {
	Scene* scene;
	scene = Manager::GetScene();

	auto enemyList = scene->GetGameObjects<Enemy>();

	for (Enemy* enemy : enemyList) {
		XMFLOAT3 enemyPosition = enemy->GetPosition();

		XMFLOAT3 direction;
		direction.x = enemyPosition.x - m_Position.x;
		direction.y = enemyPosition.y - m_Position.y;
		direction.z = enemyPosition.z - m_Position.z;

		float length;
		length = sqrtf(direction.x * direction.x
			+ direction.y * direction.y
			+ direction.z * direction.z);

		if (length < 3.0f) {
			Explosion* explosion = scene->AddGameObject<Explosion>(1);
			explosion->SetPosition(m_Position);

			enemy->SetDestroy();
			SetDestroy();

			return;
		}
	}
}

void Bullet::Draw()
{
	// 入力レイアウト設定
	Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);

	// シェーダ設定
	Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);

	// ワールドマトリクス設定
	XMMATRIX world, scale, rot, trans;
	scale = XMMatrixScaling(m_Scale.x,m_Scale.y,m_Scale.z);
	rot = XMMatrixRotationRollPitchYaw(m_Rotation.x, m_Rotation.y, m_Rotation.z);
	trans = XMMatrixTranslation(m_Position.x, m_Position.y, m_Position.z);
	world = scale * rot * trans;
	Renderer::SetWorldMatrix(world);

	m_Component->Draw();
}