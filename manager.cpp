#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "scene.h"
#include "game.h"
#include "title.h"
#include "input.h"

Scene* Manager::m_Scene{};
Scene* Manager::m_NextScene{};


void Manager::Init()
{
	Renderer::Init();
	Input::Init();

	m_Scene = new Title;
	m_Scene->Init();
}


void Manager::UnInit()
{
	m_Scene->UnInit();
	delete m_Scene;

	Input::UnInit();
	Renderer::UnInit();
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
	if (m_NextScene != nullptr)
	{
		if (m_Scene) {
			m_Scene->UnInit();
			delete m_Scene;
		}
		m_Scene = m_NextScene;
		m_Scene->Init();

		m_NextScene = nullptr;
	}
	Renderer::End();
}
