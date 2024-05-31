#pragma once

#include <list>

#include "gameobject.h"
#include "player.h"
#include "polygon2D.h"
#include "field.h"
#include "camara.h"

class Scene {
private:
	#define COUNT (4)

protected:

	// GameObject* m_GameObject[4]{};
	
	// listÇ…ïœçXÅI
	std::list<GameObject*> m_GameObject;

public:
	virtual void Init() {
		AddGameObject<Camara>();
		AddGameObject<Field>();
		AddGameObject<Player>();
		AddGameObject<Polygon2D>();
	}

	template <typename T>
	T* AddGameObject() {
		T* l_GameObject = new T();
		l_GameObject->Init();
		m_GameObject.push_back(l_GameObject);

		return l_GameObject;
	}

	template <typename T>
	T* GetGameObject() {
		for (GameObject* object : m_GameObject) {
			T* ret = dynamic_cast<T*>(object);

			if (ret != nullptr) return ret;
		}
		return nullptr;
	}

	virtual void Uninit() {
		for (GameObject* object : m_GameObject) {
			object->Uninit();
			delete object;
		}
		m_GameObject.clear();
	}

	virtual void Update() {
		for (GameObject* object : m_GameObject) {
			object->Update();
		}
	}

	virtual void Draw() {
		for (GameObject* object : m_GameObject) {
			object->Draw();
		}
	}

};