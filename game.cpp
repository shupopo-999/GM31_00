#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "game.h"
#include "result.h"
#include "title.h"
#include "particleemitter.h"


void Game::Init()
{
	AddGameObject<Camara>(0);
	AddGameObject<Field>(1);
	AddGameObject<Player>(1);
	AddGameObject<Polygon2D>(2);

	AddGameObject<Enemy>(1)->SetPosition(XMFLOAT3(0.0f,0.0f,0.0f));

	AddGameObject<ParticleEmitter>(1)->SetPosition(XMFLOAT3(0.0f, 3.0f, 5.0f));
}

void Game::Update()
{
	Scene::Update();

	if (Input::GetKeyTrigger(VK_RETURN)) {
		Manager::SetScene<Result>();
	}

	auto enemyList = GetGameObjects<Enemy>();
	if (enemyList.size() == 0) {
		Manager::SetScene<Result>();
	}

}
