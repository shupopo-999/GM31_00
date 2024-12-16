#pragma once

#include <list>
#include <vector>
#include "gameobject.h"
#include "player.h"
#include "polygon2D.h"
#include "field.h"
#include "camera.h"
#include "bullet.h"
#include "explosion.h"
#include "enemy.h"

class Scene {
private:
#define OBJECT_COUNT (4)

protected:

	std::list<GameObject*> m_GameObject[OBJECT_COUNT];

public:

	virtual ~Scene() {};

	virtual void Init() {
		
	}

	template <typename T>			// テンプレート関数
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

	template <typename T>
	std::vector<T*> GetGameObjects() {
		std::vector<T*> objectList;
		for (int i = 0; i < 3; i++) {
			for (GameObject* object : m_GameObject[i]) {
				T* ret = dynamic_cast<T*>(object);

				if (ret != nullptr)
					objectList.push_back(ret);
			}
		}
		return objectList;
	}

	virtual void UnInit() {
		for (int i = 0; i < 3; i++) {
			for (GameObject* object : m_GameObject[i]) {
				object->UnInit();
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
			m_GameObject[i].remove_if([](GameObject* object) {	return object->Destroy(); });
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