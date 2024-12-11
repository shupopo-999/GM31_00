#pragma once


#include "scene.h"

class Game : public Scene {

private:

	class Audio* m_SE{};

public:
	void Init()override;
	void UnInit()override;
	void Update()override;



};