#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "title.h"
#include "result.h"
#include "game.h"
#include "input.h"

void Result::Init()
{
	AddGameObject<Polygon2D>(2);
}

void Result::Uninit() 
{
	Scene::Uninit();
}

void Result::Update()
{
	Scene::Update();

	if (Input::GetKeyTrigger(VK_RETURN)) {
		Manager::SetScene<Title>();
	}
}

void Result::Draw()
{
	Scene::Draw();
}
