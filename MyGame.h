﻿#pragma once
#include "Framework.h"

#include "GameScene.h"

class MyGame : public Framework {
public:
	//
	void Initialize() override;
	void Finalize() override;
	void Update() override;
	void Draw() override;

private:
	/*Microsoft::WRL::ComPtr<*/
	GameScene* gameScene_;
};