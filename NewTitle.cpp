#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "NewTitle.h"
#include "skydome.h"
#include "particleemitter.h"
#include "mashfield.h"
#include "cylinder.h"
#include "title.h"
#include "enter_image.h"
#include "game.h"


void NewTitle::Init()
{
	int m_FieldX = 50;
	int m_FieldZ = 50;

	AddGameObject<Camera>(0);
	AddGameObject<MashField>(1);
	AddGameObject<SkyDome>(1);
	AddGameObject<Player>(1);
	AddGameObject<Title>(2);
	AddGameObject<Enter_Image>(2);

	AddGameObject<ParticleEmitter>(1)->SetPosition(XMFLOAT3(0.0f, 0.1f, 5.0f));
	// AddGameObject<Cylinder>(1)->SetPosition(XMFLOAT3(0.0f, 0.1f, 5.0f));
}

void NewTitle::UnInit() {

	Scene::UnInit();
}

void NewTitle::Update()
{
	Scene::Update();

	if (Input::GetKeyTrigger(VK_RETURN)) {
		Manager::SetScene<Game>();
	}
	if (Input::GetKeyTrigger(DIK_M)) {
	
	}

}

void NewTitle::Draw()
{
	Scene::Draw();
}
