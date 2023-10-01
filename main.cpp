#include "DXCommon.h"
#include "GameScene.h"
#include "ImGuiManager.h"
#include "TextureManager.h"
#include "DXCManager.h"
#include "WinApp.h"

// ウィンドウズアプリのエントリーポイント
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	// 各クラスの用意
	WinApp* win = nullptr;
	DirectXCommon* dxCommon = nullptr;

	// 汎用機能
	Input* input = nullptr;


	GameScene* gameScene = nullptr;

	// WinAppのシングルトンの取得
	win = WinApp::GetInstance();
	// ウィンドウの作成
	win->CreateGameWindow(L"LE2A_22_ワタナベ");

	// dxCommonのシングルトンの取得
	dxCommon = DirectXCommon::GetInstance();
	// directX関連の初期化処理
	dxCommon->Initialize(win);

	DXCManager::GetInstance()->CreateDXC();

#pragma region 初期化
	// ImGuiManagerのシングルトンの取得
	ImGuiManager* imguiManager = ImGuiManager::GetInstance();
	// ImGuiの初期化処理
	imguiManager->Initialize(win, dxCommon);

	// 入力の初期化
	input = Input::GetInstance();
	input->Initialize();


	// TextureManagerの初期化処理 (シングルトン)
	TextureManager::GetInstance()->Initialize(dxCommon->GetDevice());
	// 1x1の白画像を読み込む
	TextureManager::Load("white1x1.png");

	// スプライトの静的初期化
	Sprite::StaticInitialize(dxCommon->GetDevice(), WinApp::kWindowWidth, WinApp::kWindowHeight);
	Triangle::StaticInitialize(dxCommon->GetDevice(), WinApp::kWindowWidth, WinApp::kWindowHeight);
	Model::StaticInitialize();

#pragma endregion
	// ゲームシーンの初期化処理
	gameScene = new GameScene();
	gameScene->Initialize();

	// ゲームループ
	while (true) {
		// もしウィンドウが破棄されたらループを抜ける
		if (win->ProcessMessage()) {
			break;
		}
		else {
			// 入力関連の毎フレーム処理
			input->Update();
			// ImGuiの前処理
			imguiManager->Begin();


			// ゲームシーンの更新処理
			gameScene->Update();

			// ImGuiの後処理
			imguiManager->End();

			// 描画前処理
			dxCommon->preDraw();

			// 描画処理
			gameScene->Draw();

			// ImGui描画処理
			imguiManager->Draw();

			// 描画後処理
			dxCommon->postDraw();
		}
	}

	// ゲームシーンのdelete処理
	SafeDelete(gameScene);

	// ImGuiのRelease処理
	imguiManager->Finalize();

	// ウィンドウの破棄の処理
	win->TerminateGameWindow();

	return 0;
}

