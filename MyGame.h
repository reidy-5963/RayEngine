#pragma once
#include "DXCommon.h"
#include "GameScene.h"
#include "ImGuiManager.h"
#include "TextureManager.h"
#include "DXCManager.h"
#include "WinApp.h"

class MyGame {
public:
	//
	void Initialize();
	void Finalize();
	void Update();
	void Draw();

	bool IsEndRequest() { return endRequest_; }
private:
	/*Microsoft::WRL::ComPtr<*/
	WinApp* winApp_;
	DirectXCommon* dxCommon_;
	Input* input_;
	GameScene* gameScene_;
	ImGuiManager* imGuiManager_;

	bool endRequest_ = false;

};