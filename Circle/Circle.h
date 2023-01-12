#pragma once

#include "Game/Object/Object.h"
#include "Game/Easing/Easing.h"

class Circle : public Object {
public:
	Circle() = delete;
	Circle(Camera* cameraPt);

private:
	bool flg;
	Easing ease;
	Vector2D shakeSize;

public:
	void Update() override;
	void Draw(class Texture& tex) override;
	void Reset() override;
};