#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "scene.h"
#include "bullet.h"
#include "player.h"
#include "score.h"
#include "modelRenderer.h"
#include "bullet.h"


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

void Bullet::UnInit()
{
	delete m_Component;

	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();


}

void Bullet::Update()
{
	m_Position.z += 1.0f;
	
	if (m_Position.z > 25.0f) {
		
		SetDestroy();
	}
	BulletCollision();
	
}

void Bullet::BulletCollision() {
	Scene* scene;
	scene = Manager::GetScene();

	auto enemyList = scene->GetGameObjects<Enemy>();
	auto boxList = scene->GetGameObject<Box>();

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

		if (length < 1.0f) {
			Explosion* explosion = scene->AddGameObject<Explosion>(1);
			explosion->SetPosition(m_Position);
			scene->GetGameObject<Score>()->AddCount(1);

			enemy->SetDestroy();
			SetDestroy();

			return;
		}
	}

	for (Box* box : boxList) {
		XMFLOAT3 boxPosition = box->GetPosition();
		XMFLOAT3 boxScale = box->GetScale();

		// OBB
		XMFLOAT3 direction;		// ボックスの中心から弾までのベクトル
		direction.x = m_Position.x - boxPosition.x;
		direction.y = m_Position.y - boxPosition.y;
		direction.z = m_Position.z - boxPosition.z;

		// X分離軸
		XMFLOAT3 axisX = box->GetRight();
		float dotX = direction.x * axisX.x
				+ direction.y * axisX.y
				+ direction.z * axisX.z;

		// Z分離軸
		XMFLOAT3 axisZ = box->GetForward();
		float dotZ = direction.x * axisZ.x
				+ direction.y * axisZ.y
				+ direction.z * axisZ.z;

		if (-boxScale.x < dotX && dotX < boxScale.x && 
			-boxScale.z < dotZ && dotZ < boxScale.z) {
			Explosion* explosion = scene->AddGameObject<Explosion>(1);
			explosion->SetPosition(m_Position);

			SetDestroy();
		}
	}
}

void Bullet::Draw()
{
	// ���̓��C�A�E�g�ݒ�
	Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);

	// �V�F�[�_�ݒ�
	Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);

	// ���[���h�}�g���N�X�ݒ�
	XMMATRIX world, scale, rot, trans;
	scale = XMMatrixScaling(m_Scale.x,m_Scale.y,m_Scale.z);
	rot = XMMatrixRotationRollPitchYaw(m_Rotation.x, m_Rotation.y, m_Rotation.z);
	trans = XMMatrixTranslation(m_Position.x, m_Position.y, m_Position.z);
	world = scale * rot * trans;
	Renderer::SetWorldMatrix(world);

	m_Component->Draw();
}