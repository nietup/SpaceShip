#pragma once
#include "Actor.h"

using namespace ci;

class Projectile : public Actor {
public:
	Projectile(vec2 StartPosition = { 0.f, 0.f });
	~Projectile();

	void Setup() override;
	void Update() override;
	void Draw() override;

	float GetBig() { return Big; };        //used for collision check
	float GetSmall() { return Small; };

private:
	float Speed;
	float Big, Small;
};

