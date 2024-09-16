#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "game.h"
#include "result.h"
#include "title.h"
#include "score.h"
#include "particleemitter.h"


void Game::Init()
{
	int m_FieldX = 25;
	int m_FieldZ = 25;

	AddGameObject<Camara>(0);
	for (int x = -25; x < m_FieldX;x++) {
		for (int z = -25; z < m_FieldZ; z++) {
			AddGameObject<Field>(1)->SetPosition(XMFLOAT3(x, 0, z));
		}
	}
	AddGameObject<Player>(1);
	AddGameObject<Score>(2);

	AddGameObject<Enemy>(1)->SetPosition(XMFLOAT3(0.0f,0.0f,0.0f));

	AddGameObject<ParticleEmitter>(1)->SetPosition(XMFLOAT3(0.0f, 0.1f, 5.0f));
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
