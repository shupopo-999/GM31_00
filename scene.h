#pragma once

#include <list>

#include "gameobject.h"
#include "player.h"
#include "polygon2D.h"
#include "field.h"
#include "camara.h"
#include "bullet.h"
#include "explosion.h"
#include "enemy.h"

class Scene {
private:
#define OBJECT_COUNT (4)

protected:

	std::list<GameObject*> m_GameObject[OBJECT_COUNT];

public:
	virtual void Init() {
		AddGameObject<Camara>(0);
		AddGameObject<Field>(1);
		AddGameObject<Player>(1);
		AddGameObject<Polygon2D>(3);
	}

	template <typename T>
	T* AddGameObject(int Layer) {
		T* l_GameObject = new T();
		l_GameObject->Init();
		m_GameObject[Layer].push_back(l_GameObject);

		return l_GameObject;
	}

	template <typename T>
	T* GetGameObject() {
		for (int i = 0; i < 3; i++) {
			for (GameObject* object : m_GameObject[i]) {
				T* ret = dynamic_cast<T*>(object);

				if (ret != nullptr) return ret;
			}
		}
		return nullptr;
	}

	virtual void Uninit() {
		for (int i = 0; i < 3; i++) {
			for (GameObject* object : m_GameObject[i]) {
				object->Uninit();
				delete object;
			}
			m_GameObject[i].clear();
		}
	}

	virtual void Update() {
		for (int i = 0; i < 3; i++) {
			for (GameObject* object : m_GameObject[i]) {
				object->Update();
			}
			m_GameObject[i].remove_if([](GameObject* object) {return object->Destroy(); });
		}
	}

	virtual void Draw() {
		for (int i = 0; i < 3; i++) {
			for (GameObject* object : m_GameObject[i]) {
				object->Draw();
			}
		}
	}

};