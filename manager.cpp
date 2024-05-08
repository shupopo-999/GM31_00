#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "polygon2D.h"


Polygon2D* g_Polygon{};


void Manager::Init()
{
	Renderer::Init();

	g_Polygon = new Polygon2D();
	g_Polygon->Init();
}


void Manager::Uninit()
{
	Renderer::Uninit();

	g_Polygon->Uninit();
	delete g_Polygon;
}

void Manager::Update()
{
	g_Polygon->Update();
}

void Manager::Draw()
{
	Renderer::Begin();

	g_Polygon->Draw();

	Renderer::End();
}
