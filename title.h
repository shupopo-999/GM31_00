#pragma once

#include "gameobject.h"


class Title : public Scene {

public:
	void Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;



};