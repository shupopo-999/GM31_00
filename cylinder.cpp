#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "player.h"
#include "cylinder.h"
#include "modelRenderer.h"

void Cylinder::Init()
{
	m_Component = new ModelRenderer(this);
	((ModelRenderer*)m_Component)->Load("asset\\model\\cylinder.obj");


	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout,
		"shader\\unlitTextureVS.cso");
	Renderer::CreatePixelShader(&m_PixelShader,
		"shader\\unlitTexturePS.cso");

	m_Position.x = 5.0f;
}

void Cylinder::UnInit()
{
	delete m_Component;

	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();


}

void Cylinder::Update()
{

}

void Cylinder::Draw()
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

	// テクスチャ設定
	Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, &m_EnvTexture);

	// カラーバッファマスク有効
	Renderer::SetBlendMaskEnable(true);

	// ステンシル書き込み有効
	Renderer::SetStencilEnable(true);

	// カリング無効
	Renderer::SetCullEnable(false);

	m_Component->Draw();

	// カラーバッファマスク無効
	Renderer::SetBlendMaskEnable(false);

	// ステンシル書き込み無効
	Renderer::SetDepthEnable(true);

	// カリング有効
	Renderer::SetCullEnable(true);
}