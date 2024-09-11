#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "player.h"
#include "animationModel.h"
#include "input.h"
#include "camara.h"
#include "enemy.h"
#include "cylinder.h"
#include "explosion.h"
#include "result.h"
#include "camara.h"
#include "audio.h"

Input* input;


void Player::Init()
{
	m_Component = new AnimationModel(this);
	((AnimationModel*)m_Component)->Load("asset\\model\\Akai.fbx");
	((AnimationModel*)m_Component)->LoadAnimation("asset\\model\\Akai_Idle.fbx", "Idle");
	((AnimationModel*)m_Component)->LoadAnimation("asset\\model\\Akai_Run.fbx", "Run");

	m_AnimationName1 = "Idle";
	m_AnimationName2 = "Idle";


	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout,
		"shader\\unlitTextureVS.cso");
	Renderer::CreatePixelShader(&m_PixelShader,
		"shader\\unlitTexturePS.cso");

	m_Position.x = 5.0f;
	m_Position.y = 1.0f;
	groundFlag = true;

	// サウンドロード
	m_SE = new Audio(this);
	m_SE->Load("asset\\audio\\wan.wav");

	// Quaternion 初期化
	m_Quaternion.x = 0.0f;
	m_Quaternion.y = 0.0f;
	m_Quaternion.z = 0.0f;
	m_Quaternion.w = 1.0f;
}

void Player::UnInit()
{
	delete m_Component;

	m_SE->Uninit();
	delete m_SE;

	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();


}

void Player::Update()
{

	Scene* scene;
	scene = Manager::GetScene();

	Camara* camera = scene->GetGameObject<Camara>();
	XMFLOAT3 forward = camera->GetForward();

	float speed = 0.3f;
	float rot = 0.1f;

	m_Component->Update();

	if (Input::GetKeyPress(VK_LSHIFT))speed *= 1.5;

	if (Input::GetKeyPress('F')) {
		Bullet* bullet = scene->AddGameObject<Bullet>(1);
		bullet->SetPosition(m_Position);
		m_SE->Play();
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
		Manager::SetScene<Result>();
	}

	if (Input::GetKeyPress('W')) {
		m_Position.x += forward.x * speed;
		m_Position.y += forward.y * speed;
		m_Position.z += forward.z * speed;
		//QuaternionRot(0.1f,0.0f,0.0f);
		Blender("Run");
	}
	else {
		Blender("Idle");
	}
	m_AnimationBlend += 0.1f;
	if (m_AnimationBlend > 1.0f) {
		m_AnimationBlend = 1.0f;
	}
	if (Input::GetKeyPress('S')) {
		m_Position.x -= forward.x * speed;
		m_Position.y -= forward.y * speed;
		m_Position.z -= forward.z * speed;
		//QuaternionRot(-0.1f,0.0f,0.0f);
		Blender("Run");
	}
	if (Input::GetKeyPress('D')) {
		m_Position.x += forward.z * speed;
		m_Position.y += forward.y * speed;
		m_Position.z += forward.x * speed;
		//QuaternionRot(0.0f, 0.0f, -0.1f);
		Blender("Run");

	}
	if (Input::GetKeyPress('A')) {
		m_Position.x -= forward.z * speed;
		m_Position.y -= forward.y * speed;
		m_Position.z -= forward.x * speed;
		//QuaternionRot(0.0f, 0.0f, 0.1f);
		Blender("Run");

	}

	if (Input::GetKeyTrigger(VK_SPACE)) {
		m_Velocity.y = 1.5f;
	}

	if (!groundFlag) {
		m_Velocity.y -= 0.1f;
		m_Position.y += m_Velocity.y;
	}

	// groundHeight = 0.0f;
	PlayerCollision();

	// �n�ʂƂ̓����蔻��
	if (m_Position.y < groundHeight) {
		m_Position.y = groundHeight;
		m_Velocity.y = 0.0f;
	}
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

void Player::QuaternionRot(float x,float y, float z) {
	XMVECTOR quat = XMQuaternionRotationRollPitchYaw(x, y, z);
	quat = XMQuaternionMultiply(XMLoadFloat4(&m_Quaternion), quat);
	XMStoreFloat4(&m_Quaternion, quat);
}

void Player::Blender(std::string AnimationName) {
	if (m_AnimationName2 != AnimationName) {
		m_AnimationName1 = m_AnimationName2;
		m_AnimationName2 = AnimationName;
		m_AnimationBlend = 0.0f;
	}
}

void Player::Draw()
{
	((AnimationModel*)m_Component)->Update(m_AnimationName1.c_str(), m_AnimationFrame,
		m_AnimationName2.c_str(), m_AnimationFrame, 0.5f);
	m_AnimationFrame++;

	// 入力レイアウト設定
	Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);

	// シェーダー設定
	Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);

	// ワールドマトリクス設定
	XMMATRIX world, scale, rot, trans;
	scale = XMMatrixScaling(m_Scale.x,m_Scale.y,m_Scale.z);
	// rot = XMMatrixRotationRollPitchYaw(m_Rotation.x, m_Rotation.y + XM_PI, m_Rotation.z);
	rot = XMMatrixRotationQuaternion(XMLoadFloat4(&m_Quaternion));
	trans = XMMatrixTranslation(m_Position.x, m_Position.y, m_Position.z);
	world = scale * rot * trans;
	Renderer::SetWorldMatrix(world);

	m_Component->Draw();
}