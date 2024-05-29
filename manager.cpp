#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "player.h"
#include "polygon2D.h"
#include "field.h"
#include "camara.h"
#include "input.h"

GameObject* g_GameObject[COUNT]{};


void Manager::Init()
{
	Renderer::Init();

	g_GameObject[0] = new Camara;
	g_GameObject[0]->Init();

	g_GameObject[1] = new Field;
	g_GameObject[1]->Init();
	
	g_GameObject[2] = new Player;
	g_GameObject[2]->Init();

	g_GameObject[3] = new Polygon2D();
	g_GameObject[3]->Init();

	
	Input::Init();
}


void Manager::Uninit()
{

	for (int i = 0; i < COUNT;i++) {
		g_GameObject[i]->Uninit();
		delete g_GameObject[i];
	}

	Input::Uninit();
	Renderer::Uninit();
}

void Manager::Update()
{
	for (int i = 0; i < COUNT; i++) {
		g_GameObject[i]->Update();
	}

	Input::Update();
}

void Manager::Draw()
{
	Renderer::Begin();

	for (int i = 0; i < COUNT; i++) {
		g_GameObject[i]->Draw();
	}

	Renderer::End();
}
