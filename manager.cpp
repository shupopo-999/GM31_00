#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "scene.h"
#include "input.h"

Scene* Manager::m_Scene{};

void Manager::Init()
{
	Renderer::Init();
	Input::Init();

	m_Scene = new Scene;
	m_Scene->Init();
}


void Manager::Uninit()
{
	m_Scene->Uninit();
	delete m_Scene;

	Input::Uninit();
	Renderer::Uninit();
}

void Manager::Update()
{
	m_Scene->Update();

	Input::Update();
}

void Manager::Draw()
{
	Renderer::Begin();

	m_Scene->Draw();

	Renderer::End();
}
