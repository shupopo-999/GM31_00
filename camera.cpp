#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "camera.h"
#include "player.h"
#include "scene.h"
#include "input.h"

void Camera::Init()
{
	m_Position = XMFLOAT3(0.0f, 2.0f, -10.0f);
	m_Target = XMFLOAT3(0.0f, 0.0f, 0.0f);

	m_Theta = 4.57f;//�J�����������p�x
	m_Delta = 0.43f;//�J�����c�����p�x
	m_Distance = 4;//�J�����ʒu����œ_�܂ł̋���
	m_MousePoint_a;//�}�E�X�ʒu
	m_MousePoint_b;//�}�E�X�ʒu

	m_Position.x = m_Distance * cos(m_Delta) * cos(m_Theta);//�J�����̈ʒuX���W
	m_Position.y = m_Distance * sin(m_Delta);//�J�����̈ʒuY���W
	m_Position.z = m_Distance * cos(m_Delta) * sin(m_Theta);//�J�����̈ʒuZ���W

}

void Camera::UnInit()
{

}


void Camera::Update()
{
	GetCursorPos(m_po);

	Scene* scene = Manager::GetScene();

	Player* player = scene->GetGameObject<Player>();
	m_Target = player->GetPosition();
	m_Target.y += 1.0f;

	if (Input::GetKeyPress('E')) {
		m_Rotation.y += CAMARA_ROTATE;
		if (m_Rotation.y > XM_PI) {
			m_Rotation.y -= XM_PI * 2.0f;
		}
		m_Position.x = m_Target.x + sinf(m_Rotation.y) * m_Len;
		m_Position.z = m_Target.z + cosf(m_Rotation.y) * m_Len;
	}
	if (Input::GetKeyPress('Q')) {
		m_Rotation.y -= CAMARA_ROTATE;
		if (m_Rotation.y < -XM_PI) {
			m_Rotation.y += XM_PI * 2.0f;
		}
		m_Position.x = m_Target.x + sinf(m_Rotation.y) * m_Len;
		m_Position.z = m_Target.z + cosf(m_Rotation.y) * m_Len;
	}

	if (Input::GetKeyTrigger(VK_CONTROL)) {
		m_Flag = !m_Flag;
	}

	if (m_Flag) {
		SetCursorPos(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	}

	/*m_Position.x = m_Target.x - sinf(m_Rotation.y) * 6.0f;
	m_Position.y = m_Target.y + 4.0f;
	m_Position.z = m_Target.z - cosf(m_Rotation.y) * 6.0f;*/

	GetCursorPos(&m_MousePoint_b);//�}�E�X�̃X�N���[�����W�擾

	m_Theta -= (m_MousePoint_b.x - m_MousePoint_a.x) * 0.003f;//�J�����������p�x�ύX

	if (m_Delta + (m_MousePoint_b.y - m_MousePoint_a.y) * 0.003f >= DirectX::XM_PI / 2.0f - 0.0001f)
	{
		m_Delta = DirectX::XM_PI / 2.0f - 0.0001f;//�J�����c�����p�x�ύX
	}
	else if (m_Delta + (m_MousePoint_b.y - m_MousePoint_a.y) * 0.003f <= -DirectX::XM_PI / 2.0f + 0.0001f)
	{
		m_Delta = -DirectX::XM_PI / 2.0f + 0.0001f;//�J�����c�����p�x�ύX
	}
	else
	{
		m_Delta += (m_MousePoint_b.y - m_MousePoint_a.y) * 0.003f;//�J�����c�����p�x�ύX
	}
	GetCursorPos(&m_MousePoint_a);//�}�E�X�̃X�N���[�����W�擾
	//�J�����ʒu����
	m_Position.x = m_Target.x + m_Distance * cos(m_Delta) * cos(m_Theta);
	m_Position.y = m_Target.y + m_Distance * sin(m_Delta);
	m_Position.z = m_Target.z + m_Distance * cos(m_Delta) * sin(m_Theta);
}

void Camera::Draw()
{
	XMFLOAT3 up{ 0.0f,1.0f,0.0f };
	XMMATRIX viewMatrix = XMMatrixLookAtLH(XMLoadFloat3(&m_Position),XMLoadFloat3(&m_Target), XMLoadFloat3(&up));
	
	Renderer::SetViewMatrix(viewMatrix);

	XMStoreFloat4x4(&m_ViewMatrix, viewMatrix);

	// �v���W�F�N�V�����}�g���N�X�ݒ�
	XMMATRIX projectionMatrix;
	projectionMatrix = XMMatrixPerspectiveFovLH(1.0f, (float)SCREEN_WIDTH / SCREEN_HEIGHT, 1.0f, 1000.0f);
	Renderer::SetProjectionMatrix(projectionMatrix);
}
