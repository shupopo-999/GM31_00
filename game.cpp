#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "game.h"
#include "result.h"
#include "title.h"
#include "score.h"
#include "skydome.h"
#include "particleemitter.h"
#include "mashfield.h"


void Game::Init()
{
	int m_FieldX = 50;
	int m_FieldZ = 50;

	AddGameObject<Camara>(0);
	AddGameObject<MashField>(1);
	AddGameObject<SkyDome>(1);
	AddGameObject<Player>(1);
	AddGameObject<Score>(2);

	AddGameObject<Enemy>(1)->SetPosition(XMFLOAT3(0.0f,0.0f,0.0f));
	AddGameObject<Enemy>(1)->SetPosition(XMFLOAT3(10.0f,23.0f,4.0f));
	AddGameObject<Enemy>(1)->SetPosition(XMFLOAT3(12.0f,36.0f,23.0f));
	AddGameObject<Enemy>(1)->SetPosition(XMFLOAT3(23.0f,42.0f,-15.0f));
	AddGameObject<Enemy>(1)->SetPosition(XMFLOAT3(-20.0f,10.0f,0.0f));
	AddGameObject<Enemy>(1)->SetPosition(XMFLOAT3(-10.0f,22.0f,-10.0f));

	AddGameObject<ParticleEmitter>(1)->SetPosition(XMFLOAT3(0.0f, 0.1f, 5.0f));
}

void Game::Update()
{
	Scene::Update();

	if (Input::GetKeyTrigger(VK_RETURN)) {
		Manager::SetScene<Fade>();
		Manager::SetScene<Result>();
	}

	auto enemyList = GetGameObjects<Enemy>();
	if (enemyList.size() == 0) {
		Manager::SetScene<Fade>();
		Manager::SetScene<Result>();
	}

}
