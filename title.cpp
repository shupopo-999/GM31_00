#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "title.h"
#include "input.h"
#include "game.h"

void Title::Init()
{
	AddGameObject<Polygon2D>(2);
}

void Title::Uninit() 
{
	Scene::Uninit();
}

void Title::Update()
{
	Scene::Update();

	if (Input::GetKeyTrigger(VK_RETURN)) {
		Manager::SetScene<Game>();
	}
}

void Title::Draw()
{
	Scene::Draw();
}
