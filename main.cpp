#include <Novice.h>
#include "Game/Camera/Camera.h"
#include "Game/Mouse/Mouse.h"
#include "Game/KeyInput/KeyInput.h"
#include "Circle/Circle.h"
#include "Game/Texture/Texture.h"

const char kWindowTitle[] = "LC1A_08_キクタニタクマ_タイトル";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 640, 480);

	Novice::SetMouseCursorVisibility(false);

	Camera* camera = new Camera;

	Circle circle(camera);

	Texture tex("./circle.png", 128, 128, 128);

	Vector2D shake = {10.0f,10.0f};

	Vector2D shakePos;

	Easing ease({ 10.0f,10.0f }, { 0.0f, 0.0f }, 0.02f, Easing::EaseOutQuad);

	bool flg = false;

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		KeyInput::Input();
		Mouse::Input();

		///
		/// ↓更新処理ここから
		///
		circle.Update();

		if (KeyInput::Pushed(DIK_RETURN)) {
			flg = true;
		}

		if (flg) {
			shake = ease.Update();

			if (!ease) {
				flg = false;
				ease.Set({ 10.0f,10.0f }, { 0.0f, 0.0f }, 0.02f, Easing::EaseOutQuad);
			}
		}
		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///
		camera->Update();
		circle.Draw(tex);

		if (flg) {
			shakePos.x = static_cast<float>(MyMath::Random(static_cast<int>(-shake.x), static_cast<int>(shake.x)));
			shakePos.y = static_cast<float>(MyMath::Random(static_cast<int>(-shake.y), static_cast<int>(shake.y)));

			for (int i = 0; i < 40; i++) {
				Novice::DrawLine(i * 40 + static_cast<int>(shakePos.x), -10 + static_cast<int>(shakePos.y), i * 40 + static_cast<int>(shakePos.x), 490 + static_cast<int>(shakePos.y), WHITE);

				Novice::DrawLine(-10 + static_cast<int>(shakePos.x), i * 40 + static_cast<int>(shakePos.y), 650 + static_cast<int>(shakePos.x), i * 40 + static_cast<int>(shakePos.y), WHITE);
			}
		}
		else {
			for (int i = 0; i < 40; i++) {
				Novice::DrawLine(i * 40, -10, i * 40, 490, WHITE);

				Novice::DrawLine(-10, i * 40, 650, i * 40, WHITE);
			}
		}
		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (KeyInput::Released(DIK_ESCAPE)) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
