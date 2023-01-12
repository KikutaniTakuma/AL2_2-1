#include "Circle/Circle.h"
#include "Game/Mouse/Mouse.h"
#include "Game/MyMath/MyMath.h"
#include "Game/KeyInput/KeyInput.h"
#include "Game/Texture/Texture.h"

Circle::Circle(Camera* cameraPt) :
	Object(cameraPt),
	ease({ 10.0f,10.0f }, { 0.0f, 0.0f }, 0.02f, Easing::EaseOutQuad),
	shakeSize({10.0f,10.0f}),
	flg(false)
{
	pos.Set({ static_cast<float>(Mouse::x), -static_cast<float>(Mouse::y) + 480.0f }, { 30.0f,30.0f });
}

void Circle::Update() {
	pos.worldPos = { static_cast<float>(Mouse::x), -static_cast<float>(Mouse::y) + 480.0f };

	if(KeyInput::Pushed(DIK_SPACE)) {
		flg = true;
	}

	if (flg) {
		shakeSize = ease.Update();

		if (!ease) {
			flg = false;
			ease.Set({ 10.0f,10.0f }, { 0.0f, 0.0f }, 0.02f, Easing::EaseOutQuad);
		}
	}
}

void Circle::Draw(Texture& tex) {
	if (flg) {
		Vector2D tmp = pos.worldPos;
		pos.worldPos.x += MyMath::Random(static_cast<int>(-shakeSize.x), static_cast<int>(shakeSize.x));
		pos.worldPos.y += MyMath::Random(static_cast<int>(-shakeSize.y), static_cast<int>(shakeSize.y));
		pos.worldMatrix.Translate(pos.worldPos);
		camera->DrawQuad(pos, tex, 0, false);
		pos.worldPos = tmp;
	}
	else {
		pos.worldMatrix.Translate(pos.worldPos);
		camera->DrawQuad(pos, tex, 0, false);
	}
}

void Circle::Reset() {

}